//
// Copyright Contributors to the MaterialX Project
// SPDX-License-Identifier: Apache-2.0
//

#include <MaterialX/MXGenMdlNodes/ClosureSourceCodeNodeMdl.h>

#include <MaterialX/MXGenShaderGenContext.h>
#include <MaterialX/MXGenShaderShaderGenerator.h>
#include <MaterialX/MXGenShaderShaderNode.h>
#include <MaterialX/MXGenShaderShaderStage.h>
#include <MaterialX/MXGenShaderUtil.h>

MATERIALX_NAMESPACE_BEGIN

ShaderNodeImplPtr ClosureSourceCodeNodeMdl::create()
{
    return std::make_shared<ClosureSourceCodeNodeMdl>();
}

void ClosureSourceCodeNodeMdl::emitFunctionCall(const ShaderNode& node, GenContext& context, ShaderStage& stage) const
{
    DEFINE_SHADER_STAGE(stage, Stage::PIXEL)
    {
        const ShaderGenerator& shadergen = context.getShaderGenerator();

        // Emit calls for any closure dependencies upstream from this node.
        shadergen.emitDependentFunctionCalls(node, context, stage, ShaderNode::Classification::CLOSURE);

        SourceCodeNodeMdl::emitFunctionCall(node, context, stage);
    }
}

MATERIALX_NAMESPACE_END
