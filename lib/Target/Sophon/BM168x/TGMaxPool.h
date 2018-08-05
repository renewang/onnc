//===---------------------------------------------------------------------===//
//
//                             The ONNC Project
//
// Copyright(c) 2018, The ONNC Team
//
// This file is part of the ONNC Project and is distributed under
// 3-clause BSD license (https://opensource.org/licenses/BSD-3-Clause)
//
// See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
#ifndef ONNX_BM_TGMAXPOOL_H
#define ONNX_BM_TGMAXPOOL_H

#include "ComputeOperator.h"
#include <onnx/common/ir.h>

namespace onnc {

// m_emOperands: input, output
class TGMaxPool : public ComputeOperator2
{
public:
  TGMaxPool(const ::onnx::Node &pNode);

  void emit() const override;

private:
  int m_N;
  int m_C;
  int m_H;
  int m_W;
  int m_KH;
  int m_KW;
  int m_PadH;
  int m_PadW;
  int m_StrideH;
  int m_StrideW;
};

} // namespace onnc

#endif