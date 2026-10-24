#ifndef CUBISM_RENDERER_FRAME_DECOUPLE_HPP
#define CUBISM_RENDERER_FRAME_DECOUPLE_HPP

#include <vulkan/vulkan.h>
#include "CubismFramework.hpp"

//------------ LIVE2D NAMESPACE ------------
namespace Live2D { namespace Cubism { namespace Framework { namespace Rendering {

// ---- 外部帧录制（帧解耦绘制） ----
// 帧解耦模式下渲染器不再拥有/提交命令缓冲：所有命令直接录制进宿主提供的帧命令缓冲；
// mask 区间与渲染器自有区间通过挂起/恢复钩子管理（钩子由宿主注入，避免 Framework 依赖宿主管理器）。
// 本文件由维护分支（aki-5-r.5）携带，官方 SDK 原始文件不包含这些声明。

typedef void (*SuspendMainRegionFunc)(VkCommandBuffer commandBuffer);
typedef void (*ResumeMainRegionFunc)(VkCommandBuffer commandBuffer);

/**
 * @brief   设置外部帧录制（每次 Draw 前由宿主刷新）
 *
 * @param[in]   commandBuffer  -> 宿主帧命令缓冲（处于渲染区间内，只能录绘制类命令）
 * @param[in]   uploadBuffer   -> 宿主传输命令缓冲（渲染区间外，vkCmdCopyBuffer 等必须录在这里）
 * @param[in]   suspendFunc    -> 挂起主区间钩子（vkCmdEndRendering）
 * @param[in]   resumeFunc     -> 恢复主区间钩子（vkCmdBeginRendering, loadOp=LOAD）
 */
void SetExternalFrameRecording(VkCommandBuffer commandBuffer,
                               VkCommandBuffer uploadBuffer,
                               SuspendMainRegionFunc suspendFunc,
                               ResumeMainRegionFunc resumeFunc);

/**
 * @brief   当前是否处于外部帧录制模式
 */
csmBool IsExternalRecording();

}}}}  // namespace Live2D::Cubism::Framework::Rendering

#endif  // CUBISM_RENDERER_FRAME_DECOUPLE_HPP
