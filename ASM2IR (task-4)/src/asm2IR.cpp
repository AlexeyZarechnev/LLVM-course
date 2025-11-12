#include <istream>
#include <string>
#include <map>
#include <fstream>
#include <iostream>

#include "instructions.hpp"
#include "../../C-app (task-1)/include/sim.h"

#include "llvm/ADT/ArrayRef.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/IR/Attributes.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"

static std::map<std::string, std::function<void(std::istream&, llvm::IRBuilder<>&)>> instruction_map = {
    {"add", Instruction<instructions::ADD>::build},
    {"sub", Instruction<instructions::SUB>::build},
    {"mul", Instruction<instructions::MUL>::build},
    {"alloca", Instruction<instructions::ALLOCA>::build},
    {"gep2", Instruction<instructions::GEP2>::build},
    {"load", Instruction<instructions::LOAD>::build},
    {"store", Instruction<instructions::STORE>::build},
    {"eq", Instruction<instructions::EQ>::build},
    {"neq", Instruction<instructions::NEQ>::build},
    {"br", Instruction<instructions::BR>::build},
    {"br_cond", Instruction<instructions::BR_COND>::build},
    {"EXIT", Instruction<instructions::EXIT>::build},
    {"FILL_INIT_STATE", Instruction<instructions::FILL_INIT_STATE>::build},
    {"PUT_PIXEL", Instruction<instructions::PUT_PIXEL>::build},
    {"FLUSH", Instruction<instructions::FLUSH>::build}
};

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "File with asm code should be specified!";
        return 1;
    }
    std::ifstream input(argv[1]);
    if (!input.is_open()) {
        std::cerr << "Cannot open file: " << argv[1];
        return 1;
    }

    std::map<std::string, llvm::BasicBlock*> label_blocks;

    llvm::LLVMContext ctx;
    llvm::Module *module = new llvm::Module(argv[1], ctx);
    llvm::IRBuilder<> builder(ctx);

    init_builder(builder, module);

    llvm::Function* main_function =
        llvm::Function::Create(llvm::FunctionType::get(llvm::Type::getVoidTy(ctx), false),
                               llvm::GlobalValue::ExternalLinkage, "main", module);
    llvm::BasicBlock* entry_block = llvm::BasicBlock::Create(ctx, "entry", main_function);
    builder.SetInsertPoint(entry_block);

    std::string label;
    while (input >> label) {
        if (label.ends_with(":")) {
            label_blocks[label.substr(0, label.size() - 1)] = llvm::BasicBlock::Create(ctx, label, main_function);
        }
    }

    set_label_blocks(label_blocks);

    input.clear();
    input.seekg(0, std::ios::beg);

    std::string command;
    while (input >> command) {
        if (command.empty() || command == "//") {
            continue;
        }
        if (command.ends_with(":")) {
            llvm::BasicBlock* block = label_blocks[command.substr(0, command.size() - 1)];
            if (builder.GetInsertBlock()->empty() || !builder.GetInsertBlock()->back().isTerminator()) {
                builder.CreateBr(block);
            }
            builder.SetInsertPoint(block);
            continue;
        }
        if (!instruction_map.contains(command)) {
            std::cerr << "Unknown command: " << command << '\n';
            return 1;
        } 
        instruction_map[command](input, builder);
    }

    // Dump LLVM IR
    module->print(llvm::outs(), nullptr);
    llvm::outs() << '\n';
    bool verified = llvm::verifyModule(*module, &llvm::outs());
    llvm::outs() << "[VERIFICATION] " << (verified ? "FAIL\n\n" : "OK\n\n");

    if (!verified) {
        // LLVM IR Interpreter
        llvm::outs() << "[EE] Run\n";
        llvm::InitializeNativeTarget();
        llvm::InitializeNativeTargetAsmPrinter();

        llvm::ExecutionEngine *ee = llvm::EngineBuilder(std::unique_ptr<llvm::Module>(module)).create();
        map_functions(ee);
        ee->finalizeObject();

        init();

        llvm::ArrayRef<llvm::GenericValue> noargs;
        llvm::GenericValue v = ee->runFunction(main_function, noargs);
        llvm::outs() << "[EE] Result: " << v.IntVal << '\n';

        quit();
    }
    return EXIT_SUCCESS;
}