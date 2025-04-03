#include "CustomPass.hpp"
#include <llvm/Passes/PassBuilder.h>
#include <llvm/Passes/PassPlugin.h>
using namespace llvm;
PreservedAnalyses CustomPass::run(Function &F, FunctionAnalysisManager &fam) {
  errs() << "Hello function " << F.getName() << "\n";
  // TODO do something with f, anlyses can be calculated or retrieved with fam
  return PreservedAnalyses::all(); // which analyses are preserved, i.e., not
                                   // destroyed by this pass. all() = none are
                                   // destroyed, none() = all are destroyed.
}
bool FPMHook(StringRef Name, FunctionPassManager &FPM,
             ArrayRef<PassBuilder::PipelineElement>) {
  FPM.addPass(CustomPass());
  return true;
}

void PBHook(PassBuilder &PB) {
  // this one is needed for opt
  PB.registerPipelineParsingCallback(FPMHook);
  // this one is needed for clang
  PB.registerPipelineEarlySimplificationEPCallback(
      [&](ModulePassManager &MPM, auto) {
        MPM.addPass(createModuleToFunctionPassAdaptor(CustomPass()));
        return true;
      });
}

llvm::PassPluginLibraryInfo getCustomPluginInfo() {
  // the second parameter is the name of the pass, the last one the hook that
  // allows us to register the pass in the pass manager
  return {LLVM_PLUGIN_API_VERSION, "custom-pass", LLVM_VERSION_STRING, PBHook};
}
// this is invoced to register the plugin
extern "C" LLVM_ATTRIBUTE_WEAK llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
  return getCustomPluginInfo();
}
