// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the OpenColorIO Project.
// Swift C++ Interop Bridge for SwiftASWF

#include <OpenColorIO/OCIOBridge.h>

namespace OCIO_NAMESPACE
{

// ============================================================================
// Config Factory Functions
// ============================================================================

ConfigRcPtr OCIOConfig_Create()
{
    return Config::Create();
}

ConstConfigRcPtr OCIOConfig_CreateRaw()
{
    return Config::CreateRaw();
}

ConstConfigRcPtr OCIOConfig_CreateFromEnv()
{
    return Config::CreateFromEnv();
}

ConstConfigRcPtr OCIOConfig_CreateFromFile(const char * filename)
{
    return Config::CreateFromFile(filename);
}

ConstConfigRcPtr OCIOConfig_CreateFromBuiltinConfig(const char * configName)
{
    return Config::CreateFromBuiltinConfig(configName);
}

// ============================================================================
// Config Bridge Functions
// ============================================================================

bool OCIOConfig_isValid(const ConstConfigRcPtr & config)
{
    return config != nullptr;
}

unsigned int OCIOConfig_getMajorVersion(const ConstConfigRcPtr & config)
{
    return config ? config->getMajorVersion() : 0;
}

unsigned int OCIOConfig_getMinorVersion(const ConstConfigRcPtr & config)
{
    return config ? config->getMinorVersion() : 0;
}

const char * OCIOConfig_getName(const ConstConfigRcPtr & config)
{
    return config ? config->getName() : "";
}

const char * OCIOConfig_getDescription(const ConstConfigRcPtr & config)
{
    return config ? config->getDescription() : "";
}

const char * OCIOConfig_getCacheID(const ConstConfigRcPtr & config)
{
    return config ? config->getCacheID() : "";
}

void OCIOConfig_validate(const ConstConfigRcPtr & config)
{
    if (config) config->validate();
}

int OCIOConfig_getNumColorSpaces(const ConstConfigRcPtr & config)
{
    return config ? config->getNumColorSpaces() : 0;
}

const char * OCIOConfig_getColorSpaceNameByIndex(const ConstConfigRcPtr & config, int index)
{
    return config ? config->getColorSpaceNameByIndex(index) : nullptr;
}

int OCIOConfig_getIndexForColorSpace(const ConstConfigRcPtr & config, const char * name)
{
    return config ? config->getIndexForColorSpace(name) : -1;
}

ConstColorSpaceRcPtr OCIOConfig_getColorSpace(const ConstConfigRcPtr & config, const char * name)
{
    return config ? config->getColorSpace(name) : ConstColorSpaceRcPtr();
}

int OCIOConfig_getNumRoles(const ConstConfigRcPtr & config)
{
    return config ? config->getNumRoles() : 0;
}

bool OCIOConfig_hasRole(const ConstConfigRcPtr & config, const char * role)
{
    return config ? config->hasRole(role) : false;
}

const char * OCIOConfig_getRoleName(const ConstConfigRcPtr & config, int index)
{
    return config ? config->getRoleName(index) : nullptr;
}

const char * OCIOConfig_getColorSpaceNameByRole(const ConstConfigRcPtr & config, const char * role)
{
    return config ? config->getRoleColorSpace(role) : nullptr;
}

const char * OCIOConfig_getDefaultDisplay(const ConstConfigRcPtr & config)
{
    return config ? config->getDefaultDisplay() : "";
}

int OCIOConfig_getNumDisplays(const ConstConfigRcPtr & config)
{
    return config ? config->getNumDisplays() : 0;
}

const char * OCIOConfig_getDisplay(const ConstConfigRcPtr & config, int index)
{
    return config ? config->getDisplay(index) : nullptr;
}

const char * OCIOConfig_getDefaultView(const ConstConfigRcPtr & config, const char * display)
{
    return config ? config->getDefaultView(display) : "";
}

int OCIOConfig_getNumViews(const ConstConfigRcPtr & config, const char * display)
{
    return config ? config->getNumViews(display) : 0;
}

const char * OCIOConfig_getView(const ConstConfigRcPtr & config, const char * display, int index)
{
    return config ? config->getView(display, index) : nullptr;
}

const char * OCIOConfig_getDisplayViewColorSpaceName(
    const ConstConfigRcPtr & config, const char * display, const char * view)
{
    return config ? config->getDisplayViewColorSpaceName(display, view) : "";
}

int OCIOConfig_getNumLooks(const ConstConfigRcPtr & config)
{
    return config ? config->getNumLooks() : 0;
}

const char * OCIOConfig_getLookNameByIndex(const ConstConfigRcPtr & config, int index)
{
    return config ? config->getLookNameByIndex(index) : nullptr;
}

ConstLookRcPtr OCIOConfig_getLook(const ConstConfigRcPtr & config, const char * name)
{
    return config ? config->getLook(name) : ConstLookRcPtr();
}

int OCIOConfig_getNumViewTransforms(const ConstConfigRcPtr & config)
{
    return config ? config->getNumViewTransforms() : 0;
}

ConstViewTransformRcPtr OCIOConfig_getViewTransformByIndex(const ConstConfigRcPtr & config, int index)
{
    if (!config) return ConstViewTransformRcPtr();
    const char * name = config->getViewTransformNameByIndex(index);
    return name ? config->getViewTransform(name) : ConstViewTransformRcPtr();
}

ConstViewTransformRcPtr OCIOConfig_getViewTransform(const ConstConfigRcPtr & config, const char * name)
{
    return config ? config->getViewTransform(name) : ConstViewTransformRcPtr();
}

ConstProcessorRcPtr OCIOConfig_getProcessor(
    const ConstConfigRcPtr & config, const char * srcColorSpace, const char * dstColorSpace)
{
    return config ? config->getProcessor(srcColorSpace, dstColorSpace) : ConstProcessorRcPtr();
}

ConstProcessorRcPtr OCIOConfig_getProcessorWithContext(
    const ConstConfigRcPtr & config, const ConstContextRcPtr & context,
    const char * srcColorSpace, const char * dstColorSpace)
{
    return config ? config->getProcessor(context, srcColorSpace, dstColorSpace) : ConstProcessorRcPtr();
}

ConstProcessorRcPtr OCIOConfig_getProcessorFromTransform(
    const ConstConfigRcPtr & config, const ConstTransformRcPtr & transform)
{
    return config ? config->getProcessor(transform) : ConstProcessorRcPtr();
}

ConstProcessorRcPtr OCIOConfig_getProcessorFromTransformWithDirection(
    const ConstConfigRcPtr & config, const ConstTransformRcPtr & transform, TransformDirection direction)
{
    return config ? config->getProcessor(transform, direction) : ConstProcessorRcPtr();
}

int OCIOConfig_getNumSearchPaths(const ConstConfigRcPtr & config)
{
    return config ? config->getNumSearchPaths() : 0;
}

const char * OCIOConfig_getSearchPath(const ConstConfigRcPtr & config, int index)
{
    return config ? config->getSearchPath(index) : nullptr;
}

const char * OCIOConfig_getWorkingDir(const ConstConfigRcPtr & config)
{
    return config ? config->getWorkingDir() : "";
}

ConstContextRcPtr OCIOConfig_getCurrentContext(const ConstConfigRcPtr & config)
{
    return config ? config->getCurrentContext() : ConstContextRcPtr();
}

// ============================================================================
// ColorSpace Bridge Functions
// ============================================================================

bool OCIOColorSpace_isValid(const ConstColorSpaceRcPtr & cs)
{
    return cs != nullptr;
}

const char * OCIOColorSpace_getName(const ConstColorSpaceRcPtr & cs)
{
    return cs ? cs->getName() : "";
}

const char * OCIOColorSpace_getFamily(const ConstColorSpaceRcPtr & cs)
{
    return cs ? cs->getFamily() : "";
}

const char * OCIOColorSpace_getDescription(const ConstColorSpaceRcPtr & cs)
{
    return cs ? cs->getDescription() : "";
}

const char * OCIOColorSpace_getEncoding(const ConstColorSpaceRcPtr & cs)
{
    return cs ? cs->getEncoding() : "";
}

BitDepth OCIOColorSpace_getBitDepth(const ConstColorSpaceRcPtr & cs)
{
    return cs ? cs->getBitDepth() : BIT_DEPTH_UNKNOWN;
}

bool OCIOColorSpace_isData(const ConstColorSpaceRcPtr & cs)
{
    return cs ? cs->isData() : false;
}

ReferenceSpaceType OCIOColorSpace_getReferenceSpaceType(const ConstColorSpaceRcPtr & cs)
{
    return cs ? cs->getReferenceSpaceType() : REFERENCE_SPACE_SCENE;
}

ConstTransformRcPtr OCIOColorSpace_getTransform(const ConstColorSpaceRcPtr & cs, ColorSpaceDirection direction)
{
    return cs ? cs->getTransform(direction) : ConstTransformRcPtr();
}

// ============================================================================
// Look Bridge Functions
// ============================================================================

bool OCIOLook_isValid(const ConstLookRcPtr & look)
{
    return look != nullptr;
}

const char * OCIOLook_getName(const ConstLookRcPtr & look)
{
    return look ? look->getName() : "";
}

const char * OCIOLook_getProcessSpace(const ConstLookRcPtr & look)
{
    return look ? look->getProcessSpace() : "";
}

const char * OCIOLook_getDescription(const ConstLookRcPtr & look)
{
    return look ? look->getDescription() : "";
}

ConstTransformRcPtr OCIOLook_getTransform(const ConstLookRcPtr & look)
{
    return look ? look->getTransform() : ConstTransformRcPtr();
}

ConstTransformRcPtr OCIOLook_getInverseTransform(const ConstLookRcPtr & look)
{
    return look ? look->getInverseTransform() : ConstTransformRcPtr();
}

// ============================================================================
// ViewTransform Bridge Functions
// ============================================================================

bool OCIOViewTransform_isValid(const ConstViewTransformRcPtr & vt)
{
    return vt != nullptr;
}

const char * OCIOViewTransform_getName(const ConstViewTransformRcPtr & vt)
{
    return vt ? vt->getName() : "";
}

const char * OCIOViewTransform_getFamily(const ConstViewTransformRcPtr & vt)
{
    return vt ? vt->getFamily() : "";
}

const char * OCIOViewTransform_getDescription(const ConstViewTransformRcPtr & vt)
{
    return vt ? vt->getDescription() : "";
}

ReferenceSpaceType OCIOViewTransform_getReferenceSpaceType(const ConstViewTransformRcPtr & vt)
{
    return vt ? vt->getReferenceSpaceType() : REFERENCE_SPACE_SCENE;
}

ConstTransformRcPtr OCIOViewTransform_getTransform(const ConstViewTransformRcPtr & vt, ViewTransformDirection direction)
{
    return vt ? vt->getTransform(direction) : ConstTransformRcPtr();
}

// ============================================================================
// Processor Bridge Functions
// ============================================================================

bool OCIOProcessor_isValid(const ConstProcessorRcPtr & proc)
{
    return proc != nullptr;
}

bool OCIOProcessor_isNoOp(const ConstProcessorRcPtr & proc)
{
    return proc ? proc->isNoOp() : true;
}

bool OCIOProcessor_hasChannelCrosstalk(const ConstProcessorRcPtr & proc)
{
    return proc ? proc->hasChannelCrosstalk() : false;
}

const char * OCIOProcessor_getCacheID(const ConstProcessorRcPtr & proc)
{
    return proc ? proc->getCacheID() : "";
}

int OCIOProcessor_getNumTransforms(const ConstProcessorRcPtr & proc)
{
    return proc ? proc->getNumTransforms() : 0;
}

ConstCPUProcessorRcPtr OCIOProcessor_getDefaultCPUProcessor(const ConstProcessorRcPtr & proc)
{
    return proc ? proc->getDefaultCPUProcessor() : ConstCPUProcessorRcPtr();
}

ConstCPUProcessorRcPtr OCIOProcessor_getOptimizedCPUProcessor(
    const ConstProcessorRcPtr & proc, OptimizationFlags oFlags)
{
    return proc ? proc->getOptimizedCPUProcessor(oFlags) : ConstCPUProcessorRcPtr();
}

ConstCPUProcessorRcPtr OCIOProcessor_getOptimizedCPUProcessorWithBitDepth(
    const ConstProcessorRcPtr & proc, BitDepth inBitDepth, BitDepth outBitDepth, OptimizationFlags oFlags)
{
    return proc ? proc->getOptimizedCPUProcessor(inBitDepth, outBitDepth, oFlags) : ConstCPUProcessorRcPtr();
}

ConstGPUProcessorRcPtr OCIOProcessor_getDefaultGPUProcessor(const ConstProcessorRcPtr & proc)
{
    return proc ? proc->getDefaultGPUProcessor() : ConstGPUProcessorRcPtr();
}

ConstGPUProcessorRcPtr OCIOProcessor_getOptimizedGPUProcessor(
    const ConstProcessorRcPtr & proc, OptimizationFlags oFlags)
{
    return proc ? proc->getOptimizedGPUProcessor(oFlags) : ConstGPUProcessorRcPtr();
}

// ============================================================================
// CPUProcessor Bridge Functions
// ============================================================================

bool OCIOCPUProcessor_isValid(const ConstCPUProcessorRcPtr & cpu)
{
    return cpu != nullptr;
}

bool OCIOCPUProcessor_isNoOp(const ConstCPUProcessorRcPtr & cpu)
{
    return cpu ? cpu->isNoOp() : true;
}

bool OCIOCPUProcessor_isIdentity(const ConstCPUProcessorRcPtr & cpu)
{
    return cpu ? cpu->isIdentity() : true;
}

bool OCIOCPUProcessor_hasChannelCrosstalk(const ConstCPUProcessorRcPtr & cpu)
{
    return cpu ? cpu->hasChannelCrosstalk() : false;
}

const char * OCIOCPUProcessor_getCacheID(const ConstCPUProcessorRcPtr & cpu)
{
    return cpu ? cpu->getCacheID() : "";
}

BitDepth OCIOCPUProcessor_getInputBitDepth(const ConstCPUProcessorRcPtr & cpu)
{
    return cpu ? cpu->getInputBitDepth() : BIT_DEPTH_UNKNOWN;
}

BitDepth OCIOCPUProcessor_getOutputBitDepth(const ConstCPUProcessorRcPtr & cpu)
{
    return cpu ? cpu->getOutputBitDepth() : BIT_DEPTH_UNKNOWN;
}

void OCIOCPUProcessor_applyRGB(const ConstCPUProcessorRcPtr & cpu, float * pixel)
{
    if (cpu && pixel) cpu->applyRGB(pixel);
}

void OCIOCPUProcessor_applyRGBA(const ConstCPUProcessorRcPtr & cpu, float * pixel)
{
    if (cpu && pixel) cpu->applyRGBA(pixel);
}

// ============================================================================
// GPUProcessor Bridge Functions
// ============================================================================

bool OCIOGPUProcessor_isValid(const ConstGPUProcessorRcPtr & gpu)
{
    return gpu != nullptr;
}

bool OCIOGPUProcessor_isNoOp(const ConstGPUProcessorRcPtr & gpu)
{
    return gpu ? gpu->isNoOp() : true;
}

bool OCIOGPUProcessor_hasChannelCrosstalk(const ConstGPUProcessorRcPtr & gpu)
{
    return gpu ? gpu->hasChannelCrosstalk() : false;
}

const char * OCIOGPUProcessor_getCacheID(const ConstGPUProcessorRcPtr & gpu)
{
    return gpu ? gpu->getCacheID() : "";
}

// ============================================================================
// Context Bridge Functions
// ============================================================================

bool OCIOContext_isValid(const ConstContextRcPtr & ctx)
{
    return ctx != nullptr;
}

const char * OCIOContext_getCacheID(const ConstContextRcPtr & ctx)
{
    return ctx ? ctx->getCacheID() : "";
}

int OCIOContext_getNumStringVars(const ConstContextRcPtr & ctx)
{
    return ctx ? ctx->getNumStringVars() : 0;
}

const char * OCIOContext_getStringVarNameByIndex(const ConstContextRcPtr & ctx, int index)
{
    return ctx ? ctx->getStringVarNameByIndex(index) : nullptr;
}

const char * OCIOContext_getStringVar(const ConstContextRcPtr & ctx, const char * name)
{
    return ctx ? ctx->getStringVar(name) : "";
}

const char * OCIOContext_getWorkingDir(const ConstContextRcPtr & ctx)
{
    return ctx ? ctx->getWorkingDir() : "";
}

const char * OCIOContext_resolveStringVar(const ConstContextRcPtr & ctx, const char * val)
{
    return ctx ? ctx->resolveStringVar(val) : "";
}

// ============================================================================
// Transform Creation Functions
// ============================================================================

ColorSpaceTransformRcPtr OCIOColorSpaceTransform_Create()
{
    return ColorSpaceTransform::Create();
}

DisplayViewTransformRcPtr OCIODisplayViewTransform_Create()
{
    return DisplayViewTransform::Create();
}

MatrixTransformRcPtr OCIOMatrixTransform_Create()
{
    return MatrixTransform::Create();
}

ExponentTransformRcPtr OCIOExponentTransform_Create()
{
    return ExponentTransform::Create();
}

LogTransformRcPtr OCIOLogTransform_Create()
{
    return LogTransform::Create();
}

LookTransformRcPtr OCIOLookTransform_Create()
{
    return LookTransform::Create();
}

GroupTransformRcPtr OCIOGroupTransform_Create()
{
    return GroupTransform::Create();
}

CDLTransformRcPtr OCIOCDLTransform_Create()
{
    return CDLTransform::Create();
}

FileTransformRcPtr OCIOFileTransform_Create()
{
    return FileTransform::Create();
}

RangeTransformRcPtr OCIORangeTransform_Create()
{
    return RangeTransform::Create();
}

// ============================================================================
// ColorSpaceTransform Bridge Functions
// ============================================================================

const char * OCIOColorSpaceTransform_getSrc(const ConstColorSpaceTransformRcPtr & t)
{
    return t ? t->getSrc() : "";
}

const char * OCIOColorSpaceTransform_getDst(const ConstColorSpaceTransformRcPtr & t)
{
    return t ? t->getDst() : "";
}

void OCIOColorSpaceTransform_setSrc(ColorSpaceTransformRcPtr & t, const char * src)
{
    if (t && src) t->setSrc(src);
}

void OCIOColorSpaceTransform_setDst(ColorSpaceTransformRcPtr & t, const char * dst)
{
    if (t && dst) t->setDst(dst);
}

bool OCIOColorSpaceTransform_getDataBypass(const ConstColorSpaceTransformRcPtr & t)
{
    return t ? t->getDataBypass() : false;
}

void OCIOColorSpaceTransform_setDataBypass(ColorSpaceTransformRcPtr & t, bool bypass)
{
    if (t) t->setDataBypass(bypass);
}

// ============================================================================
// DisplayViewTransform Bridge Functions
// ============================================================================

const char * OCIODisplayViewTransform_getSrc(const ConstDisplayViewTransformRcPtr & t)
{
    return t ? t->getSrc() : "";
}

const char * OCIODisplayViewTransform_getDisplay(const ConstDisplayViewTransformRcPtr & t)
{
    return t ? t->getDisplay() : "";
}

const char * OCIODisplayViewTransform_getView(const ConstDisplayViewTransformRcPtr & t)
{
    return t ? t->getView() : "";
}

void OCIODisplayViewTransform_setSrc(DisplayViewTransformRcPtr & t, const char * src)
{
    if (t && src) t->setSrc(src);
}

void OCIODisplayViewTransform_setDisplay(DisplayViewTransformRcPtr & t, const char * display)
{
    if (t && display) t->setDisplay(display);
}

void OCIODisplayViewTransform_setView(DisplayViewTransformRcPtr & t, const char * view)
{
    if (t && view) t->setView(view);
}

bool OCIODisplayViewTransform_getLooksBypass(const ConstDisplayViewTransformRcPtr & t)
{
    return t ? t->getLooksBypass() : false;
}

void OCIODisplayViewTransform_setLooksBypass(DisplayViewTransformRcPtr & t, bool bypass)
{
    if (t) t->setLooksBypass(bypass);
}

bool OCIODisplayViewTransform_getDataBypass(const ConstDisplayViewTransformRcPtr & t)
{
    return t ? t->getDataBypass() : false;
}

void OCIODisplayViewTransform_setDataBypass(DisplayViewTransformRcPtr & t, bool bypass)
{
    if (t) t->setDataBypass(bypass);
}

// ============================================================================
// MatrixTransform Bridge Functions
// ============================================================================

void OCIOMatrixTransform_getMatrix(const ConstMatrixTransformRcPtr & t, double * m44)
{
    if (t && m44) t->getMatrix(m44);
}

void OCIOMatrixTransform_setMatrix(MatrixTransformRcPtr & t, const double * m44)
{
    if (t && m44) t->setMatrix(m44);
}

void OCIOMatrixTransform_getOffset(const ConstMatrixTransformRcPtr & t, double * offset4)
{
    if (t && offset4) t->getOffset(offset4);
}

void OCIOMatrixTransform_setOffset(MatrixTransformRcPtr & t, const double * offset4)
{
    if (t && offset4) t->setOffset(offset4);
}

} // namespace OCIO_NAMESPACE
