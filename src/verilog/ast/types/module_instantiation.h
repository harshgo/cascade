// Copyright 2017-2018 VMware, Inc.
// SPDX-License-Identifier: BSD-2-Clause
//
// The BSD-2 license (the License) set forth below applies to all parts of the
// Cascade project.  You may not use this file except in compliance with the
// License.
//
// BSD-2 License
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice, this
// list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS AS IS AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef CASCADE_SRC_VERILOG_AST_MODULE_INSTANTIATION_H
#define CASCADE_SRC_VERILOG_AST_MODULE_INSTANTIATION_H

#include <cassert>
#include "src/verilog/ast/types/arg_assign.h"
#include "src/verilog/ast/types/attributes.h"
#include "src/verilog/ast/types/identifier.h"
#include "src/verilog/ast/types/if_generate_construct.h"
#include "src/verilog/ast/types/instantiation.h"
#include "src/verilog/ast/types/many.h"
#include "src/verilog/ast/types/maybe.h"
#include "src/verilog/ast/types/macro.h"
#include "src/verilog/ast/types/module_declaration.h"
#include "src/verilog/ast/types/range_expression.h"

namespace cascade {

class ModuleInstantiation : public Instantiation {
  public:
    // Constructors:
    ModuleInstantiation(Attributes* attrs__, Identifier* mid__, Identifier* iid__, Maybe<RangeExpression>* range__, Many<ArgAssign>* params__, Many<ArgAssign>* ports__);
    ~ModuleInstantiation() override;

    // Node Interface:
    NODE(ModuleInstantiation, TREE(attrs), TREE(mid), TREE(iid), TREE(range), TREE(params), TREE(ports))
    // Get/Set:
    TREE_GET_SET(attrs)
    TREE_GET_SET(mid)
    TREE_GET_SET(iid)
    TREE_GET_SET(range)
    TREE_GET_SET(params)
    TREE_GET_SET(ports)

    // Convention Interface:
    bool uses_named_params() const;
    bool uses_ordered_params() const;
    bool uses_named_ports() const;
    bool uses_ordered_ports() const;

  private:
    TREE_ATTR(Attributes*, attrs);
    TREE_ATTR(Identifier*, mid);
    TREE_ATTR(Identifier*, iid);
    TREE_ATTR(Maybe<RangeExpression>*, range);
    TREE_ATTR(Many<ArgAssign>*, params);
    TREE_ATTR(Many<ArgAssign>*, ports);

    friend class Elaborate;
    friend class Inline;
    DECORATION(ModuleDeclaration*, inst);
    DECORATION(IfGenerateConstruct*, inline);
};

inline ModuleInstantiation::ModuleInstantiation(Attributes* attrs__, Identifier* mid__, Identifier* iid__, Maybe<RangeExpression>* range__, Many<ArgAssign>* params__, Many<ArgAssign>* ports__) : Instantiation() {
  parent_ = nullptr;
  TREE_SETUP(attrs);
  TREE_SETUP(mid);
  TREE_SETUP(iid);
  TREE_SETUP(range);
  TREE_SETUP(params);
  TREE_SETUP(ports);
  inst_ = nullptr;
  inline_ = nullptr;
}

inline ModuleInstantiation::~ModuleInstantiation() {
  TREE_TEARDOWN(attrs);
  TREE_TEARDOWN(mid);
  TREE_TEARDOWN(iid);
  TREE_TEARDOWN(range);
  TREE_TEARDOWN(params);
  TREE_TEARDOWN(ports);
  if (inst_ != nullptr) {
    delete inst_;
  }
  if (inline_ != nullptr) {
    delete inline_;
  }
}

inline bool ModuleInstantiation::uses_named_params() const {
  return params_->empty() || !params_->front()->get_exp()->null();
}

inline bool ModuleInstantiation::uses_ordered_params() const {
  return !uses_named_params();
}

inline bool ModuleInstantiation::uses_named_ports() const {
  return ports_->empty() || !ports_->front()->get_exp()->null();  
}

inline bool ModuleInstantiation::uses_ordered_ports() const {
  return !uses_named_ports();
}

} // namespace cascade 

#endif
