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

#ifndef MINDSPORE_LITE_SRC_BACKEND_OPENCL_MATMUL_H_
#define MINDSPORE_LITE_SRC_BACKEND_OPENCL_MATMUL_H_

#include <vector>

#include "src/lite_kernel.h"
#include "src/runtime/kernel/arm/opclib/conv_parameter.h"
#include "src/runtime/opencl/opencl_runtime.h"

#ifdef ENABLE_FP16
using FLOAT_T = float16_t;
#else
using FLOAT_T = float;
#endif

namespace mindspore::kernel {

class MatMulOpenCLKernel : public LiteKernel {
 public:
  explicit MatMulOpenCLKernel(OpParameter *parameter, const std::vector<lite::tensor::Tensor *> &inputs,
                              const std::vector<lite::tensor::Tensor *> &outputs, bool hasBias)
      : LiteKernel(parameter, inputs, outputs) {
    hasBias_ = hasBias;
  }
  ~MatMulOpenCLKernel() override{};

  int Init() override;
  int InferShape() {}
  int ReSize() override;
  int Run() override;
  void PadWeight();

 private:
  cl::Kernel kernel_;
  FLOAT_T *padWeight_;
  FLOAT_T *bias_;
  bool hasBias_ = false;
  cl_int2 sizeCI;
  cl_int2 sizeCO;
};
}  // namespace mindspore::kernel

#endif  // MINDSPORE_LITE_SRC_BACKEND_OPENCL_MATMUL_H_

