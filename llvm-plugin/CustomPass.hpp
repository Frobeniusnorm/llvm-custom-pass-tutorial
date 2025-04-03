#include <llvm/IR/PassManager.h>
struct CustomPass : public llvm::PassInfoMixin<CustomPass> {
  // this is the function that will be invoced for each defined function of the
  // moudle
  llvm::PreservedAnalyses run(llvm::Function &F,
                              llvm::FunctionAnalysisManager &fam);
};
