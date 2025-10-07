#include "llvm/ADT/StringRef.h"
#include "llvm/IR/Analysis.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Pass.h"
#include "llvm/Passes/OptimizationLevel.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

struct TracePass : public PassInfoMixin<TracePass> {
  Type* voidType;
  Type* int8PtrTy;

  bool insertInstructionLog(Module &M, Function &F, IRBuilder<> &builder) {
    SmallVector<Type *, 2> instrParamTypes = {int8PtrTy, int8PtrTy};
    FunctionType *instrLogFuncType =
        FunctionType::get(voidType, instrParamTypes, false);
    FunctionCallee instrLogFunc =
        M.getOrInsertFunction("log_instruction", instrLogFuncType);

    bool Inserted = false;
    for (auto &B : F) {
      for (auto &I : B) {
        if (isa<PHINode>(I)) {
          continue;
        }
        builder.SetInsertPoint(&I);
        for (std::size_t i = 0; i < I.getNumOperands(); ++i) {
          if (auto* op = dyn_cast<Instruction>(I.getOperand(i))) {
            Value* user_name = builder.CreateGlobalString(I.getOpcodeName());
            Value* operand_name = builder.CreateGlobalString(op->getOpcodeName());
            Value* args[] = {user_name, operand_name};
            builder.CreateCall(instrLogFunc, args);
            Inserted = true;
          }
        }
      }
    }
    return Inserted;
  }

  PreservedAnalyses run(Module &M, ModuleAnalysisManager &AM) {
    outs() << "[Module] " << M.getName() << '\n';
    if (!M.getName().ends_with("app.c")) {
      outs() << "  Skipping...\n";
      return PreservedAnalyses::all();
    }

    // Prepare builder for IR modification
    LLVMContext &Ctx = M.getContext();
    IRBuilder<> builder(Ctx);
    voidType = Type::getVoidTy(Ctx);
    int8PtrTy = PointerType::getUnqual(Ctx);

    for (auto &F : M) {
      if (F.isDeclaration()) {
        continue;
      }

      outs() << "[Function] " << F.getName() << '\n';
      if (F.getName() == "log_instruction") {
        outs() << "  Skipping...\n";
        continue;
      }

      if (insertInstructionLog(M, F, builder)) {
        outs() << "[INFO] insertInstructionLog done\n";
      }

      outs() << '\n';
      bool verif = verifyFunction(F, &outs());
      outs() << "[VERIFICATION] " << (verif ? "FAIL\n\n" : "OK\n\n");
    }
    outs() << '\n';
    return PreservedAnalyses::none();
  };
};

PassPluginLibraryInfo getPassPluginInfo() {
  const auto callback = [](PassBuilder &PB) {
    PB.registerOptimizerLastEPCallback([](ModulePassManager &MPM, OptimizationLevel OL, ThinOrFullLTOPhase phase) {
      MPM.addPass(TracePass{});
      return;
    });
  };

  return {LLVM_PLUGIN_API_VERSION, "TracePlugin", "0.0.1", callback};
};

/* When a plugin is loaded by the driver, it will call this entry point to
obtain information about this plugin and about how to register its passes.
*/
extern "C" LLVM_ATTRIBUTE_WEAK PassPluginLibraryInfo llvmGetPassPluginInfo() {
  return getPassPluginInfo();
}
