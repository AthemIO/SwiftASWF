// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the OpenColorIO Project.
// Swift C++ Interop Bridge for SwiftASWF

#ifndef INCLUDED_OCIO_BRIDGE_H
#define INCLUDED_OCIO_BRIDGE_H

#include "OpenColorIO.h"
#include <cstdint>

/**
 * @brief Swift C++ Interop Bridge Functions for OpenColorIO
 *
 * These functions provide a Swift-friendly interface to OpenColorIO by
 * wrapping shared_ptr method calls into free functions. This is necessary
 * because Swift's C++ interop doesn't support accessing methods through
 * std::shared_ptr directly.
 *
 * Usage in Swift:
 * @code
 * let config = OpenColorIO_v2_4.GetCurrentConfig()
 * let numColorSpaces = OpenColorIO_v2_4.OCIOConfig_getNumColorSpaces(config)
 * @endcode
 */

namespace OCIO_NAMESPACE
{

// ============================================================================
// Config Factory Functions
// ============================================================================

/// Create a new empty Config
extern OCIOEXPORT ConfigRcPtr OCIOConfig_Create();

/// Create a raw/fallback Config
extern OCIOEXPORT ConstConfigRcPtr OCIOConfig_CreateRaw();

/// Create a Config from the OCIO environment variable
extern OCIOEXPORT ConstConfigRcPtr OCIOConfig_CreateFromEnv();

/// Create a Config from a file
extern OCIOEXPORT ConstConfigRcPtr OCIOConfig_CreateFromFile(const char * filename);

/// Create a Config from a built-in config name
extern OCIOEXPORT ConstConfigRcPtr OCIOConfig_CreateFromBuiltinConfig(const char * configName);

// ============================================================================
// Config Bridge Functions
// ============================================================================

/// Check if a Config pointer is valid (non-null)
extern OCIOEXPORT bool OCIOConfig_isValid(const ConstConfigRcPtr & config);

/// Get the config major version
extern OCIOEXPORT unsigned int OCIOConfig_getMajorVersion(const ConstConfigRcPtr & config);

/// Get the config minor version
extern OCIOEXPORT unsigned int OCIOConfig_getMinorVersion(const ConstConfigRcPtr & config);

/// Get the config name (returns empty string if null)
extern OCIOEXPORT const char * OCIOConfig_getName(const ConstConfigRcPtr & config);

/// Get the config description
extern OCIOEXPORT const char * OCIOConfig_getDescription(const ConstConfigRcPtr & config);

/// Get the cache ID for the config
extern OCIOEXPORT const char * OCIOConfig_getCacheID(const ConstConfigRcPtr & config);

/// Validate the config (throws Exception on error)
extern OCIOEXPORT void OCIOConfig_validate(const ConstConfigRcPtr & config);

// Color Spaces
extern OCIOEXPORT int OCIOConfig_getNumColorSpaces(const ConstConfigRcPtr & config);
extern OCIOEXPORT const char * OCIOConfig_getColorSpaceNameByIndex(const ConstConfigRcPtr & config, int index);
extern OCIOEXPORT int OCIOConfig_getIndexForColorSpace(const ConstConfigRcPtr & config, const char * name);
extern OCIOEXPORT ConstColorSpaceRcPtr OCIOConfig_getColorSpace(const ConstConfigRcPtr & config, const char * name);

// Roles
extern OCIOEXPORT int OCIOConfig_getNumRoles(const ConstConfigRcPtr & config);
extern OCIOEXPORT bool OCIOConfig_hasRole(const ConstConfigRcPtr & config, const char * role);
extern OCIOEXPORT const char * OCIOConfig_getRoleName(const ConstConfigRcPtr & config, int index);
extern OCIOEXPORT const char * OCIOConfig_getColorSpaceNameByRole(const ConstConfigRcPtr & config, const char * role);

// Displays and Views
extern OCIOEXPORT const char * OCIOConfig_getDefaultDisplay(const ConstConfigRcPtr & config);
extern OCIOEXPORT int OCIOConfig_getNumDisplays(const ConstConfigRcPtr & config);
extern OCIOEXPORT const char * OCIOConfig_getDisplay(const ConstConfigRcPtr & config, int index);
extern OCIOEXPORT const char * OCIOConfig_getDefaultView(const ConstConfigRcPtr & config, const char * display);
extern OCIOEXPORT int OCIOConfig_getNumViews(const ConstConfigRcPtr & config, const char * display);
extern OCIOEXPORT const char * OCIOConfig_getView(const ConstConfigRcPtr & config, const char * display, int index);
extern OCIOEXPORT const char * OCIOConfig_getDisplayViewColorSpaceName(
    const ConstConfigRcPtr & config, const char * display, const char * view);

// Looks
extern OCIOEXPORT int OCIOConfig_getNumLooks(const ConstConfigRcPtr & config);
extern OCIOEXPORT const char * OCIOConfig_getLookNameByIndex(const ConstConfigRcPtr & config, int index);
extern OCIOEXPORT ConstLookRcPtr OCIOConfig_getLook(const ConstConfigRcPtr & config, const char * name);

// View Transforms
extern OCIOEXPORT int OCIOConfig_getNumViewTransforms(const ConstConfigRcPtr & config);
extern OCIOEXPORT ConstViewTransformRcPtr OCIOConfig_getViewTransformByIndex(const ConstConfigRcPtr & config, int index);
extern OCIOEXPORT ConstViewTransformRcPtr OCIOConfig_getViewTransform(const ConstConfigRcPtr & config, const char * name);

// Processors
extern OCIOEXPORT ConstProcessorRcPtr OCIOConfig_getProcessor(
    const ConstConfigRcPtr & config, const char * srcColorSpace, const char * dstColorSpace);
extern OCIOEXPORT ConstProcessorRcPtr OCIOConfig_getProcessorWithContext(
    const ConstConfigRcPtr & config, const ConstContextRcPtr & context,
    const char * srcColorSpace, const char * dstColorSpace);
extern OCIOEXPORT ConstProcessorRcPtr OCIOConfig_getProcessorFromTransform(
    const ConstConfigRcPtr & config, const ConstTransformRcPtr & transform);
extern OCIOEXPORT ConstProcessorRcPtr OCIOConfig_getProcessorFromTransformWithDirection(
    const ConstConfigRcPtr & config, const ConstTransformRcPtr & transform, TransformDirection direction);

// Search Paths
extern OCIOEXPORT int OCIOConfig_getNumSearchPaths(const ConstConfigRcPtr & config);
extern OCIOEXPORT const char * OCIOConfig_getSearchPath(const ConstConfigRcPtr & config, int index);
extern OCIOEXPORT const char * OCIOConfig_getWorkingDir(const ConstConfigRcPtr & config);

// Context
extern OCIOEXPORT ConstContextRcPtr OCIOConfig_getCurrentContext(const ConstConfigRcPtr & config);

// ============================================================================
// ColorSpace Bridge Functions
// ============================================================================

extern OCIOEXPORT bool OCIOColorSpace_isValid(const ConstColorSpaceRcPtr & cs);
extern OCIOEXPORT const char * OCIOColorSpace_getName(const ConstColorSpaceRcPtr & cs);
extern OCIOEXPORT const char * OCIOColorSpace_getFamily(const ConstColorSpaceRcPtr & cs);
extern OCIOEXPORT const char * OCIOColorSpace_getDescription(const ConstColorSpaceRcPtr & cs);
extern OCIOEXPORT const char * OCIOColorSpace_getEncoding(const ConstColorSpaceRcPtr & cs);
extern OCIOEXPORT BitDepth OCIOColorSpace_getBitDepth(const ConstColorSpaceRcPtr & cs);
extern OCIOEXPORT bool OCIOColorSpace_isData(const ConstColorSpaceRcPtr & cs);
extern OCIOEXPORT ReferenceSpaceType OCIOColorSpace_getReferenceSpaceType(const ConstColorSpaceRcPtr & cs);
extern OCIOEXPORT ConstTransformRcPtr OCIOColorSpace_getTransform(
    const ConstColorSpaceRcPtr & cs, ColorSpaceDirection direction);

// ============================================================================
// Look Bridge Functions
// ============================================================================

extern OCIOEXPORT bool OCIOLook_isValid(const ConstLookRcPtr & look);
extern OCIOEXPORT const char * OCIOLook_getName(const ConstLookRcPtr & look);
extern OCIOEXPORT const char * OCIOLook_getProcessSpace(const ConstLookRcPtr & look);
extern OCIOEXPORT const char * OCIOLook_getDescription(const ConstLookRcPtr & look);
extern OCIOEXPORT ConstTransformRcPtr OCIOLook_getTransform(const ConstLookRcPtr & look);
extern OCIOEXPORT ConstTransformRcPtr OCIOLook_getInverseTransform(const ConstLookRcPtr & look);

// ============================================================================
// ViewTransform Bridge Functions
// ============================================================================

extern OCIOEXPORT bool OCIOViewTransform_isValid(const ConstViewTransformRcPtr & vt);
extern OCIOEXPORT const char * OCIOViewTransform_getName(const ConstViewTransformRcPtr & vt);
extern OCIOEXPORT const char * OCIOViewTransform_getFamily(const ConstViewTransformRcPtr & vt);
extern OCIOEXPORT const char * OCIOViewTransform_getDescription(const ConstViewTransformRcPtr & vt);
extern OCIOEXPORT ReferenceSpaceType OCIOViewTransform_getReferenceSpaceType(const ConstViewTransformRcPtr & vt);
extern OCIOEXPORT ConstTransformRcPtr OCIOViewTransform_getTransform(
    const ConstViewTransformRcPtr & vt, ViewTransformDirection direction);

// ============================================================================
// Processor Bridge Functions
// ============================================================================

extern OCIOEXPORT bool OCIOProcessor_isValid(const ConstProcessorRcPtr & proc);
extern OCIOEXPORT bool OCIOProcessor_isNoOp(const ConstProcessorRcPtr & proc);
extern OCIOEXPORT bool OCIOProcessor_hasChannelCrosstalk(const ConstProcessorRcPtr & proc);
extern OCIOEXPORT const char * OCIOProcessor_getCacheID(const ConstProcessorRcPtr & proc);
extern OCIOEXPORT int OCIOProcessor_getNumTransforms(const ConstProcessorRcPtr & proc);
extern OCIOEXPORT ConstCPUProcessorRcPtr OCIOProcessor_getDefaultCPUProcessor(const ConstProcessorRcPtr & proc);
extern OCIOEXPORT ConstCPUProcessorRcPtr OCIOProcessor_getOptimizedCPUProcessor(
    const ConstProcessorRcPtr & proc, OptimizationFlags oFlags);
extern OCIOEXPORT ConstCPUProcessorRcPtr OCIOProcessor_getOptimizedCPUProcessorWithBitDepth(
    const ConstProcessorRcPtr & proc, BitDepth inBitDepth, BitDepth outBitDepth, OptimizationFlags oFlags);
extern OCIOEXPORT ConstGPUProcessorRcPtr OCIOProcessor_getDefaultGPUProcessor(const ConstProcessorRcPtr & proc);
extern OCIOEXPORT ConstGPUProcessorRcPtr OCIOProcessor_getOptimizedGPUProcessor(
    const ConstProcessorRcPtr & proc, OptimizationFlags oFlags);

// ============================================================================
// CPUProcessor Bridge Functions
// ============================================================================

extern OCIOEXPORT bool OCIOCPUProcessor_isValid(const ConstCPUProcessorRcPtr & cpu);
extern OCIOEXPORT bool OCIOCPUProcessor_isNoOp(const ConstCPUProcessorRcPtr & cpu);
extern OCIOEXPORT bool OCIOCPUProcessor_isIdentity(const ConstCPUProcessorRcPtr & cpu);
extern OCIOEXPORT bool OCIOCPUProcessor_hasChannelCrosstalk(const ConstCPUProcessorRcPtr & cpu);
extern OCIOEXPORT const char * OCIOCPUProcessor_getCacheID(const ConstCPUProcessorRcPtr & cpu);
extern OCIOEXPORT BitDepth OCIOCPUProcessor_getInputBitDepth(const ConstCPUProcessorRcPtr & cpu);
extern OCIOEXPORT BitDepth OCIOCPUProcessor_getOutputBitDepth(const ConstCPUProcessorRcPtr & cpu);
extern OCIOEXPORT void OCIOCPUProcessor_applyRGB(const ConstCPUProcessorRcPtr & cpu, float * pixel);
extern OCIOEXPORT void OCIOCPUProcessor_applyRGBA(const ConstCPUProcessorRcPtr & cpu, float * pixel);

// ============================================================================
// GPUProcessor Bridge Functions
// ============================================================================

extern OCIOEXPORT bool OCIOGPUProcessor_isValid(const ConstGPUProcessorRcPtr & gpu);
extern OCIOEXPORT bool OCIOGPUProcessor_isNoOp(const ConstGPUProcessorRcPtr & gpu);
extern OCIOEXPORT bool OCIOGPUProcessor_hasChannelCrosstalk(const ConstGPUProcessorRcPtr & gpu);
extern OCIOEXPORT const char * OCIOGPUProcessor_getCacheID(const ConstGPUProcessorRcPtr & gpu);

// ============================================================================
// Context Bridge Functions
// ============================================================================

extern OCIOEXPORT bool OCIOContext_isValid(const ConstContextRcPtr & ctx);
extern OCIOEXPORT const char * OCIOContext_getCacheID(const ConstContextRcPtr & ctx);
extern OCIOEXPORT int OCIOContext_getNumStringVars(const ConstContextRcPtr & ctx);
extern OCIOEXPORT const char * OCIOContext_getStringVarNameByIndex(const ConstContextRcPtr & ctx, int index);
extern OCIOEXPORT const char * OCIOContext_getStringVar(const ConstContextRcPtr & ctx, const char * name);
extern OCIOEXPORT const char * OCIOContext_getWorkingDir(const ConstContextRcPtr & ctx);
extern OCIOEXPORT const char * OCIOContext_resolveStringVar(const ConstContextRcPtr & ctx, const char * val);

// ============================================================================
// Transform Creation Functions (returns mutable pointers)
// ============================================================================

extern OCIOEXPORT ColorSpaceTransformRcPtr OCIOColorSpaceTransform_Create();
extern OCIOEXPORT DisplayViewTransformRcPtr OCIODisplayViewTransform_Create();
extern OCIOEXPORT MatrixTransformRcPtr OCIOMatrixTransform_Create();
extern OCIOEXPORT ExponentTransformRcPtr OCIOExponentTransform_Create();
extern OCIOEXPORT LogTransformRcPtr OCIOLogTransform_Create();
extern OCIOEXPORT LookTransformRcPtr OCIOLookTransform_Create();
extern OCIOEXPORT GroupTransformRcPtr OCIOGroupTransform_Create();
extern OCIOEXPORT CDLTransformRcPtr OCIOCDLTransform_Create();
extern OCIOEXPORT FileTransformRcPtr OCIOFileTransform_Create();
extern OCIOEXPORT RangeTransformRcPtr OCIORangeTransform_Create();

// ============================================================================
// ColorSpaceTransform Bridge Functions
// ============================================================================

extern OCIOEXPORT const char * OCIOColorSpaceTransform_getSrc(const ConstColorSpaceTransformRcPtr & t);
extern OCIOEXPORT const char * OCIOColorSpaceTransform_getDst(const ConstColorSpaceTransformRcPtr & t);
extern OCIOEXPORT void OCIOColorSpaceTransform_setSrc(ColorSpaceTransformRcPtr & t, const char * src);
extern OCIOEXPORT void OCIOColorSpaceTransform_setDst(ColorSpaceTransformRcPtr & t, const char * dst);
extern OCIOEXPORT bool OCIOColorSpaceTransform_getDataBypass(const ConstColorSpaceTransformRcPtr & t);
extern OCIOEXPORT void OCIOColorSpaceTransform_setDataBypass(ColorSpaceTransformRcPtr & t, bool bypass);

// ============================================================================
// DisplayViewTransform Bridge Functions
// ============================================================================

extern OCIOEXPORT const char * OCIODisplayViewTransform_getSrc(const ConstDisplayViewTransformRcPtr & t);
extern OCIOEXPORT const char * OCIODisplayViewTransform_getDisplay(const ConstDisplayViewTransformRcPtr & t);
extern OCIOEXPORT const char * OCIODisplayViewTransform_getView(const ConstDisplayViewTransformRcPtr & t);
extern OCIOEXPORT void OCIODisplayViewTransform_setSrc(DisplayViewTransformRcPtr & t, const char * src);
extern OCIOEXPORT void OCIODisplayViewTransform_setDisplay(DisplayViewTransformRcPtr & t, const char * display);
extern OCIOEXPORT void OCIODisplayViewTransform_setView(DisplayViewTransformRcPtr & t, const char * view);
extern OCIOEXPORT bool OCIODisplayViewTransform_getLooksBypass(const ConstDisplayViewTransformRcPtr & t);
extern OCIOEXPORT void OCIODisplayViewTransform_setLooksBypass(DisplayViewTransformRcPtr & t, bool bypass);
extern OCIOEXPORT bool OCIODisplayViewTransform_getDataBypass(const ConstDisplayViewTransformRcPtr & t);
extern OCIOEXPORT void OCIODisplayViewTransform_setDataBypass(DisplayViewTransformRcPtr & t, bool bypass);

// ============================================================================
// MatrixTransform Bridge Functions
// ============================================================================

extern OCIOEXPORT void OCIOMatrixTransform_getMatrix(const ConstMatrixTransformRcPtr & t, double * m44);
extern OCIOEXPORT void OCIOMatrixTransform_setMatrix(MatrixTransformRcPtr & t, const double * m44);
extern OCIOEXPORT void OCIOMatrixTransform_getOffset(const ConstMatrixTransformRcPtr & t, double * offset4);
extern OCIOEXPORT void OCIOMatrixTransform_setOffset(MatrixTransformRcPtr & t, const double * offset4);

} // namespace OCIO_NAMESPACE

#endif // INCLUDED_OCIO_BRIDGE_H
