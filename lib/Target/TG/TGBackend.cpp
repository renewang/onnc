//===- TGBackend.cpp --------------------------------------------------===//
//
//                             The ONNC Project
//
// See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
#include "TG.h"
#include "TGBackend.h"
#include "TargetInfo/TGTargetInfo.h"
#include <onnc/Target/TargetRegistry.h>

using namespace onnc;

//===----------------------------------------------------------------------===//
// TGBackend
//===----------------------------------------------------------------------===//

void TGBackend::addTensorSel(PassManager &pPM) {
  // IR level pass
  pPM.add(createRemoveUnusedNodePass());
  pPM.add(createUpdateOutputInfoPass());
  // TGbackend require memory allocation before TensorSel (lowering)
  pPM.add(createTGMemAllocInfoPass(this));
  pPM.add(createTargetLoweringPass(this));
  return;
}

void TGBackend::addCodeEmit(PassManager& pPM, Path &output, CodeGenFileType &fileType)
{
  if (TargetBackend::AssemblyFile == fileType)
    return;

  if (TargetBackend::ObjectFile == fileType) {
    m_outputPath = output;
    pPM.add(createTGCodeEmitPass(this));
  }

}

TargetBackend* CreateTGBM1680Backend(const TargetOptions& pOptions)
{
  return new TGBackend(pOptions);
}

TargetBackend* CreateTGBM1682Backend(const TargetOptions& pOptions)
{
  return new TGBackend(pOptions);
}

TGBackend::TGBackend(const TargetOptions &pOptions)
    : DLATargetBackend(pOptions), m_pTLI(new TGTargetLowering(this)), m_pCE(new TGCodeEmitter(this)) {}

TGBackend::~TGBackend() {
  delete m_pTLI;
  delete m_pCE;
}

void TGBackend::codeEmit(void) {
  m_pCE->encodeInstructions(m_outputPath);
}

extern "C" void InitializeTGONNCBackend()
{
  onnc::TargetRegistry::RegisterTargetBackend(getTheTGBM1680Target(),
      CreateTGBM1680Backend);
//  onnc::TargetRegistry::RegisterTargetBackend(getTheTGBM1682Target(),
//      CreateTGBM1682Backend);
}