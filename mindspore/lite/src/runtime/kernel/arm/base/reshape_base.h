/**
 * Copyright 2020 Huawei Technologies Co., Ltd
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MINDSPORE_LITE_SRC_RUNTIME_KERNEL_ARM_BASE_RESHAPE_BASE_H_
#define MINDSPORE_LITE_SRC_RUNTIME_KERNEL_ARM_BASE_RESHAPE_BASE_H_

#include <vector>
#include "src/lite_kernel.h"
#include "src/runtime/kernel/arm/opclib/reshape_parameter.h"

using mindspore::lite::Context;

namespace mindspore::kernel {
class ReshapeBaseCPUKernel : public LiteKernel {
 public:
  ReshapeBaseCPUKernel(OpParameter *parameter, const std::vector<lite::tensor::Tensor *> &inputs,
                      const std::vector<lite::tensor::Tensor *> &outputs, const Context *ctx)
    : LiteKernel(parameter, inputs, outputs), ctx_(ctx), thread_count_(ctx->threadNum) {
    reshape_param_ = reinterpret_cast<ReshapeParameter *>(opParameter);
  }
  ~ReshapeBaseCPUKernel() = default;

  int Init() override;
  int ReSize() override { return 0; }
  int Run() override { return 0; }

 protected:
  int thread_count_;
  const Context *ctx_;
  ReshapeParameter *reshape_param_;
};
}  // namespace mindspore::kernel

#endif  // MINDSPORE_LITE_SRC_RUNTIME_KERNEL_ARM_BASE_RESHAPE_BASE_H_

