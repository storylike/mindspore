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

#ifndef PREDICT_TFLITE_SQUAREDDIFFERENCE_PARSER_H
#define PREDICT_TFLITE_SQUAREDDIFFERENCE_PARSER_H

#include <memory>
#include <vector>
#include "mindspore/lite/tools/converter/parser/tflite/tflite_node_parser.h"
#include "mindspore/lite/tools/converter/parser/tflite/tflite_node_parser_registry.h"

namespace mindspore {
namespace lite {
class TfliteSquaredDifferenceParser : public TfliteNodeParser {
 public:
  TfliteSquaredDifferenceParser() : TfliteNodeParser("SquaredDifference") {}

  STATUS Parse(const std::unique_ptr<tflite::OperatorT> &tfliteOp,
               const std::vector<std::unique_ptr<tflite::TensorT>> &tfliteTensors,
               const std::vector<std::unique_ptr<tflite::BufferT>> &tfliteModelBuffer,
               const std::vector<std::unique_ptr<tflite::OperatorCodeT>> &tfliteOpSet, schema::CNodeT *op,
               TensorCache *tensor_cache, bool quantizedModel) override;
};
}  // namespace lite
}  // namespace mindspore

#endif  // PREDICT_TFLITE_SQUAREDDIFFERENCE_PARSER_H

