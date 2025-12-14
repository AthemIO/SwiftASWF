// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the OpenColorIO Project.


#if !defined(_WIN32)

// do nothing.

#else // defined(_WIN32)

#include <windows.h>
#include <sstream>

#include <Logging.h>

#include "Platform.h"
#include "utils/StringUtils.h"
#include "SystemMonitor.h"

namespace OCIO_NAMESPACE
{


static constexpr char ErrorMsg[] { "Problem obtaining monitor profile information from operating system." };

// List all active display paths using QueryDisplayConfig and GetDisplayConfigBufferSizes.
// Get the data from each path using DisplayConfigGetDeviceInfo.
// Note: Uses std::wstring since Windows display APIs always return wide strings
void getAllMonitorsWithQueryDisplayConfig(std::vector<std::wstring> & monitorsName)
{
    // https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-displayconfig_path_info
    std::vector<DISPLAYCONFIG_PATH_INFO> paths;
    // https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-displayconfig_mode_info
    std::vector<DISPLAYCONFIG_MODE_INFO> modes;

    UINT32 flags = QDC_ONLY_ACTIVE_PATHS | QDC_VIRTUAL_MODE_AWARE;
    LONG result = ERROR_SUCCESS;

    do
    {
        // Determine how many path and mode structures to allocate.
        UINT32 pathCount, modeCount;
        // The GetDisplayConfigBufferSizes function retrieves the size of the buffers that are 
        // required to call the QueryDisplayConfig function.
        result = GetDisplayConfigBufferSizes(flags, &pathCount, &modeCount);
        
        // Allocate the path and mode arrays.
        paths.resize(pathCount);
        modes.resize(modeCount);

        // The QueryDisplayConfig function retrieves information about all possible display paths 
        // for all display devices, or views, in the current setting.
        result = QueryDisplayConfig(flags, &pathCount, paths.data(), &modeCount, modes.data(), nullptr);

        // The function may have returned fewer paths/modes than estimated.
        paths.resize(pathCount);
        modes.resize(modeCount);

        // It's possible that between the call to GetDisplayConfigBufferSizes and QueryDisplayConfig
        // that the display state changed, so loop on the case of ERROR_INSUFFICIENT_BUFFER.
    } while (result == ERROR_INSUFFICIENT_BUFFER);

    if (result == ERROR_SUCCESS)
    {
        // For each active path
        for (auto& path : paths)
        {
            // The DISPLAYCONFIG_TARGET_DEVICE_NAME structure contains information about the target.
            // Find the target (monitor) friendly name
            DISPLAYCONFIG_TARGET_DEVICE_NAME targetName = {};
            targetName.header.adapterId = path.targetInfo.adapterId;
            targetName.header.id = path.targetInfo.id;
            targetName.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_TARGET_NAME;
            targetName.header.size = sizeof(targetName);
            result = DisplayConfigGetDeviceInfo(&targetName.header);

            if (result == ERROR_SUCCESS)
            {
                monitorsName.push_back(
                    (result == ERROR_SUCCESS && targetName.flags.friendlyNameFromEdid) ? 
                    targetName.monitorFriendlyDeviceName : L""
                );
            }
        }
    }

}

/**
 * Populate the internal structure with monitors name and ICC profiles name.
 * 
 * Expected monitor display name: 
 * 
 * DISPLAYn, <monitorFriendlyDeviceName | DeviceString>
 * 
 * where n is a positive integer starting at 1.
 * where monitorFriendlyDeviceName comes from DISPLAYCONFIG_TARGET_DEVICE_NAME structure.
 * where DeviceString comes from DISPLAY_DEVICE structure.
 * 
 */
void SystemMonitorsImpl::getAllMonitors()
{
    m_monitors.clear();

    // Use wstring for friendly names since Windows APIs return wide strings
    std::vector<std::wstring> friendlyMonitorNames;
    getAllMonitorsWithQueryDisplayConfig(friendlyMonitorNames);

    // Initialize the structure.
    DISPLAY_DEVICEW dispDevice;
    ZeroMemory(&dispDevice, sizeof(dispDevice));
    dispDevice.cb = sizeof(dispDevice);

    // Iterate over all the monitors.
    DWORD dispNum = 0;
    // After the first call to EnumDisplayDevices, dispDevice.DeviceString is the adapter name.
    // Use wide string version explicitly for consistent Unicode handling
    while (EnumDisplayDevicesW(nullptr, dispNum, &dispDevice, 0))
    {
        const std::wstring deviceName = dispDevice.DeviceName;

        // Only select active monitors.
        // NOTE: Currently the two DISPLAY enums are equivalent, but we check both in case one may
        // change in the future.
        if ((dispDevice.StateFlags & DISPLAY_DEVICE_ACTIVE)
            && (dispDevice.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP))
        {
            HDC hDC = CreateDCW(nullptr, deviceName.c_str(), nullptr, nullptr);
            if (hDC)
            {
                ZeroMemory(&dispDevice, sizeof(dispDevice));
                dispDevice.cb = sizeof(dispDevice);

                // After second call, dispDevice.DeviceString is the monitor name for that device.
                // Second parameters must be 0 to get the monitor name.
                // See https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-enumdisplaydevicesw
                EnumDisplayDevicesW(deviceName.c_str(), 0, &dispDevice, 0);

                WCHAR icmPath[MAX_PATH + 1];
                DWORD pathLength = MAX_PATH;

                // TODO: Is a monitor without ICM profile possible?

                // TODO: Several ICM profiles could be associated to a single device.

                bool idxExists = friendlyMonitorNames.size() >= dispNum+1;
                bool friendlyNameExists = idxExists && !friendlyMonitorNames.at(dispNum).empty();

                // Check if the distNum index exists in friendlyMonitorNames vector and check if
                // there is a corresponding friendly name.
                const std::wstring extra = friendlyNameExists ?
                        friendlyMonitorNames.at(dispNum) : std::wstring(dispDevice.DeviceString);

                std::wstring strippedDeviceName = deviceName;
                if(StringUtils::StartsWith(Platform::Utf16ToUtf8(deviceName), "\\\\.\\DISPLAY"))
                {
                    // Remove the slashes.
                    std::wstring prefix = L"\\\\.\\";
                    strippedDeviceName = deviceName.substr(prefix.length());
                }

                const std::wstring displayName = strippedDeviceName + L", " + extra;

                // Get the associated ICM profile path.
                if (GetICMProfileW(hDC, &pathLength, icmPath))
                {
                    m_monitors.push_back({Platform::Utf16ToUtf8(displayName), Platform::Utf16ToUtf8(icmPath)});
                }
                else
                {
                    std::wostringstream oss;
                    oss << L"Unable to access the ICM profile for the monitor '"
                        << displayName << L"'.";

                    LogDebug(Platform::Utf16ToUtf8(oss.str()));
                }

                DeleteDC(hDC);
            }
            else
            {
                std::wostringstream oss;
                oss << L"Unable to access the monitor '" << deviceName << L"'.";
                LogDebug(Platform::Utf16ToUtf8(oss.str()));
            }
        }

        ZeroMemory(&dispDevice, sizeof(dispDevice));
        dispDevice.cb = sizeof(dispDevice);

        ++dispNum;
    }
}

} // namespace OCIO_NAMESPACE

#endif // defined(_WIN32)
