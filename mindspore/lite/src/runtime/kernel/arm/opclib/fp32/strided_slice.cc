/**
 * Copyright 2019 Huawei Technologies Co., Ltd
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

#include "src/runtime/kernel/arm/opclib/fp32/strided_slice.h"
#include "src/runtime/kernel/arm/opclib/errorcode.h"

void PadStridedSliceParameterTo4D(StridedSliceParameter *param) {
  int32_t begins[DIMENSION_4D];
  int32_t ends[DIMENSION_4D];
  int32_t strides[DIMENSION_4D];
  int32_t input_shape[DIMENSION_4D];
  for (int32_t i = 0; i < param->num_axes_; ++i) {
    begins[i] = param->begins_[i];
    ends[i] = param->ends_[i];
    strides[i] = param->strides_[i];
    input_shape[i] = param->in_shape_[i];
  }
  int32_t real_index = param->num_axes_ - 1;
  for (int32_t i = DIMENSION_4D - 1; i >= 0; --i) {
    if (real_index >= 0) {
      param->begins_[i] = begins[real_index];
      param->ends_[i] = ends[real_index];
      param->strides_[i] = strides[real_index];
      param->in_shape_[i] = input_shape[real_index--];
    } else {
      param->begins_[i] = 0;
      param->ends_[i] = 1;
      param->strides_[i] = 1;
      param->in_shape_[i] = 1;
    }
  }
  param->num_axes_ = DIMENSION_4D;
}

int DoStridedSlice(const float *in_data, float *out_data, StridedSliceParameter *param) {
  if (in_data == nullptr || out_data == nullptr || param == nullptr) {
    return OPCLIB_NULL_PTR;
  }
  if (param->num_axes_ > DIMENSION_4D) {
    return OPCLIB_PARAM_INVALID;
  }

  int *begins = param->begins_;
  int *ends = param->ends_;
  int *strides = param->strides_;
  int *in_shape = param->in_shape_;

  if (param->num_axes_ < DIMENSION_4D) {
    PadStridedSliceParameterTo4D(param);
  }

  size_t dim_offset[DIMENSION_4D - 1];
  dim_offset[2] = in_shape[3];
  dim_offset[1] = dim_offset[2] * in_shape[2];
  dim_offset[0] = dim_offset[1] * in_shape[1];
  size_t output_index = 0;
  for (int32_t dim0 = begins[0]; dim0 < ends[0]; dim0 += strides[0]) {
    for (int32_t dim1 = begins[1]; dim1 < ends[1]; dim1 += strides[1]) {
      for (int32_t dim2 = begins[2]; dim2 < ends[2]; dim2 += strides[2]) {
        for (int32_t dim3 = begins[3]; dim3 < ends[3]; dim3 += strides[3]) {
          out_data[output_index++] =
            *(in_data + dim0 * dim_offset[0] + dim1 * dim_offset[1] + dim2 * dim_offset[2] + dim3);
        }
      }
    }
  }

  return OPCLIB_OK;
}
