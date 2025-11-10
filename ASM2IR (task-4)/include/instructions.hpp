#pragma once

#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include <llvm/Support/raw_ostream.h>
#include <llvm/IR/IRBuilder.h>
#include <map>

namespace instructions {

struct ADD {};
struct SUB {};
struct MUL {};
struct ALLOCA {};
struct GEP2 {};
struct LOAD {};
struct STORE {};
struct EQ {};
struct NEQ {};
struct BR {};
struct BR_COND {};
struct EXIT {};
struct FILL_INIT_STATE {};
struct PUT_PIXEL {};
struct FLUSH {};

} // namespace instructions

template <typename INSTR_TAG>
class Instruction;

template<>
class Instruction<instructions::ADD> {
public:
    static void build(std::istream& input, llvm::IRBuilder<>& builder) noexcept;
};

template<>
class Instruction<instructions::SUB> {
public:
    static void build(std::istream& input, llvm::IRBuilder<>& builder) noexcept;
};

template<>
class Instruction<instructions::MUL> {
public:
    static void build(std::istream& input, llvm::IRBuilder<>& builder) noexcept;
};

template<>
class Instruction<instructions::ALLOCA> {
public:
    static void build(std::istream& input, llvm::IRBuilder<>& builder) noexcept;
};

template<>
class Instruction<instructions::GEP2> {
public:
    static void build(std::istream& input, llvm::IRBuilder<>& builder) noexcept;
};

template<>
class Instruction<instructions::LOAD> {
public:
    static void build(std::istream& input, llvm::IRBuilder<>& builder) noexcept;
};

template<>
class Instruction<instructions::STORE> {
public:
    static void build(std::istream& input, llvm::IRBuilder<>& builder) noexcept;
};

template<>
class Instruction<instructions::EQ> {
public:
    static void build(std::istream& input, llvm::IRBuilder<>& builder) noexcept;
};

template<>
class Instruction<instructions::NEQ> {
public:
    static void build(std::istream& input, llvm::IRBuilder<>& builder) noexcept;
};

template<>
class Instruction<instructions::BR> {
public:
    static void build(std::istream& input, llvm::IRBuilder<>& builder) noexcept;
};

template<>
class Instruction<instructions::BR_COND> {
public:
    static void build(std::istream& input, llvm::IRBuilder<>& builder) noexcept;
};

template<>
class Instruction<instructions::EXIT> {
public:
    static void build(std::istream& input, llvm::IRBuilder<>& builder) noexcept;
};

template<>
class Instruction<instructions::FILL_INIT_STATE> {
public:
    static void build(std::istream& input, llvm::IRBuilder<>& builder) noexcept;
};

template<>
class Instruction<instructions::PUT_PIXEL> {
public:
    static void build(std::istream& input, llvm::IRBuilder<>& builder) noexcept;
};

template<>
class Instruction<instructions::FLUSH> {
public:
    static void build(std::istream& input, llvm::IRBuilder<>& builder) noexcept;
};

void init_builder(llvm::IRBuilder<>& builder, llvm::Module* module) noexcept;

void set_label_blocks(const std::map<std::string, llvm::BasicBlock*>& blocks) noexcept;

void map_functions(llvm::ExecutionEngine* engine) noexcept;
