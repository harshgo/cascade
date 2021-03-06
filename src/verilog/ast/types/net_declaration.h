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

#ifndef CASCADE_SRC_VERILOG_AST_NET_DECLARATION_H
#define CASCADE_SRC_VERILOG_AST_NET_DECLARATION_H

#include <cassert>
#include "src/verilog/ast/types/declaration.h"
#include "src/verilog/ast/types/delay_control.h"
#include "src/verilog/ast/types/expression.h"
#include "src/verilog/ast/types/macro.h"
#include "src/verilog/ast/types/maybe.h"
#include "src/verilog/ast/types/range_expression.h"

namespace cascade {

class NetDeclaration : public Declaration {
  public:
    // Supporting Concepts:
    enum Type {
      WIRE = 0
    };

    // Constructors:
    NetDeclaration(Attributes* attrs__, Type type__, Maybe<DelayControl>* ctrl__, Identifier* id__, bool signed__, Maybe<RangeExpression>* dim__);
    ~NetDeclaration() override;

    // Node Interface:
    NODE(NetDeclaration, TREE(attrs), LEAF(type), TREE(ctrl), TREE(id), LEAF(signed), TREE(dim))
    // Get/Set:
    LEAF_GET_SET(type)
    TREE_GET_SET(ctrl)
    LEAF_GET_SET(signed)
    TREE_GET_SET(dim)

  private:
    LEAF_ATTR(Type, type);
    TREE_ATTR(Maybe<DelayControl>*, ctrl);
    LEAF_ATTR(bool, signed);
    TREE_ATTR(Maybe<RangeExpression>*, dim);
};

inline NetDeclaration::NetDeclaration(Attributes* attrs__, Type type__, Maybe<DelayControl>* ctrl__, Identifier* id__, bool signed__, Maybe<RangeExpression>* dim__) : Declaration() {
  parent_ = nullptr;
  TREE_SETUP(attrs);
  LEAF_SETUP(type);
  TREE_SETUP(ctrl);
  TREE_SETUP(id);
  LEAF_SETUP(signed);
  TREE_SETUP(dim);
}

inline NetDeclaration::~NetDeclaration() {
  TREE_TEARDOWN(attrs);
  LEAF_TEARDOWN(type);
  TREE_TEARDOWN(ctrl);
  TREE_TEARDOWN(id);
  LEAF_TEARDOWN(signed);
  TREE_TEARDOWN(dim);
}

} // namespace cascade 

#endif
