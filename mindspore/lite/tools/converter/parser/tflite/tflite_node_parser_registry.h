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

#ifndef MINDSPORE_CCSRC_TOOLS_LITE_CONVERTER_PARSER_TFLITE_NODE_PARSER_REGISTRY_H
#define MINDSPORE_CCSRC_TOOLS_LITE_CONVERTER_PARSER_TFLITE_NODE_PARSER_REGISTRY_H

#include <string>
#include <unordered_map>
#include "tools/common/node_util.h"
#include "mindspore/lite/tools/converter/parser/tflite/tflite_node_parser.h"

namespace mindspore {
namespace lite {
class TfliteNodeParserRegistry {
 public:
  TfliteNodeParserRegistry();

  virtual ~TfliteNodeParserRegistry();

  static TfliteNodeParserRegistry *GetInstance();

  TfliteNodeParser *GetNodeParser(const std::string &name);

  std::unordered_map<std::string, TfliteNodeParser *> parsers;
};

class TfliteNodeRegister {
 public:
  TfliteNodeRegister(const std::string &name, TfliteNodeParser *parser) {
    TfliteNodeParserRegistry::GetInstance()->parsers[name] = parser;
  }
};
}  // namespace lite
}  // namespace mindspore

#endif  // MINDSPORE_CCSRC_TOOLS_LITE_CONVERTER_PARSER_TFLITE_NODE_PARSER_REGISTRY_H

