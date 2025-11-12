#include "../../C-app (task-1)/include/sim.h"
#include "instructions.hpp"

#include "llvm/ADT/SmallVector.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Value.h"
#include <cstddef>
#include <istream>
#include <map>
#include <string>

constexpr static size_t REGISTERS_COUNT = 8;

static std::string dst;
static std::string arg;

static llvm::Function *fill_init_state_func = nullptr;
static llvm::Function *put_pixel_func = nullptr;
static llvm::Function *flush_func = nullptr;
static llvm::Function* memset_func = nullptr;


static llvm::Value *REGISTERS = nullptr;

static std::map<llvm::Value*, size_t> array_sizes;
static std::map<std::string, llvm::BasicBlock *> label_blocks;

llvm::Value *get_ptr(std::string &arg, llvm::IRBuilder<> &builder) noexcept {
  return builder.CreateGEP(llvm::ArrayType::get(builder.getInt64Ty(), REGISTERS_COUNT), REGISTERS,
                           {builder.getInt64(0), builder.getInt64(std::stoull(arg.substr(1)))});
}

llvm::Value *parse_value(std::istream &input,
                         llvm::IRBuilder<> &builder) noexcept {
  input >> arg;
  if (arg.starts_with("x")) {
    llvm::Value *ptr = get_ptr(arg, builder);
    return builder.CreateLoad(builder.getInt64Ty(), ptr);
  }
  return builder.getInt64(std::stoull(arg));
}

void Instruction<instructions::ADD>::build(
    std::istream &input, llvm::IRBuilder<> &builder) noexcept {
  input >> dst;

  llvm::Value *lhs = parse_value(input, builder);
  llvm::Value *rhs = parse_value(input, builder);

  llvm::Value *sum = builder.CreateAdd(lhs, rhs);
  builder.CreateStore(sum, get_ptr(dst, builder));
}

void Instruction<instructions::SUB>::build(
    std::istream &input, llvm::IRBuilder<> &builder) noexcept {
  input >> dst;

  llvm::Value *lhs = parse_value(input, builder);
  llvm::Value *rhs = parse_value(input, builder);

  llvm::Value *sum = builder.CreateSub(lhs, rhs);
  builder.CreateStore(sum, get_ptr(dst, builder));
}

void Instruction<instructions::MUL>::build(
    std::istream &input, llvm::IRBuilder<> &builder) noexcept {
  input >> dst;

  llvm::Value *lhs = parse_value(input, builder);
  llvm::Value *rhs = parse_value(input, builder);

  llvm::Value *sum = builder.CreateMul(lhs, rhs);
  builder.CreateStore(sum, get_ptr(dst, builder));
}

void Instruction<instructions::ALLOCA>::build(
    std::istream &input, llvm::IRBuilder<> &builder) noexcept {

  input >> dst;
  llvm::Value *size = builder.CreateTrunc(parse_value(input, builder), builder.getInt32Ty());

  llvm::Value *ptr = builder.CreateAlloca(builder.getInt32Ty(), size);

  llvm::Value *size_bytes = builder.CreateMul(size, builder.getInt64(4));

  builder.CreateCall(memset_func, {ptr, builder.getInt8(0), size_bytes, builder.getInt1(false)});

  llvm::Value* value = builder.CreatePtrToInt(ptr, builder.getInt64Ty());

  builder.CreateStore(value,
                      get_ptr(dst, builder));
}

void Instruction<instructions::GEP2>::build(
    std::istream &input, llvm::IRBuilder<> &builder) noexcept {
  input >> arg;
  uint64_t size = std::stoull(arg);
  input >> dst;

  llvm::Value *base = parse_value(input, builder);
  llvm::Value *ptr = builder.CreateIntToPtr(parse_value(input, builder), llvm::PointerType::get(builder.getContext(), 0));
  llvm::Value *idx1 = parse_value(input, builder);
  llvm::Value *idx2 = parse_value(input, builder);
  llvm::Value *off1 = parse_value(input, builder);
  llvm::Value *off2 = parse_value(input, builder);

  llvm::Value *total_off =
      builder.CreateAdd(builder.CreateAdd(idx2, off2),
                        builder.CreateMul(base, builder.CreateAdd(idx1, off1)));

  llvm::Value* value = builder.CreateGEP(llvm::ArrayType::get(builder.getInt32Ty(), size), ptr, {builder.getInt64(0), total_off});

  builder.CreateStore(builder.CreatePtrToInt(value, builder.getInt64Ty()),
                      get_ptr(dst, builder));
}

void Instruction<instructions::LOAD>::build(
    std::istream &input, llvm::IRBuilder<> &builder) noexcept {
  input >> dst;

  llvm::Value* ptr = builder.CreateIntToPtr(parse_value(input, builder), llvm::PointerType::get(builder.getContext(), 0));
  llvm::Value* value = builder.CreateZExt(builder.CreateLoad(builder.getInt32Ty(), ptr), builder.getInt64Ty());

  // // builder.CreateCall(printf_func, {format_str, value});
  builder.CreateStore(value, get_ptr(dst, builder));
}

void Instruction<instructions::STORE>::build(
    std::istream &input, llvm::IRBuilder<> &builder) noexcept {
  
  llvm::Value* ptr = builder.CreateIntToPtr(parse_value(input, builder), llvm::PointerType::get(builder.getContext(), 0));
  llvm::Value* value = builder.CreateTrunc(parse_value(input, builder), builder.getInt32Ty());

  // builder.CreateCall(printf_func, {format_str, value});
  // builder.CreateCall(printf_func, {format_str, ptr});

  builder.CreateStore(value, ptr);
}

void Instruction<instructions::EQ>::build(std::istream &input,
                                          llvm::IRBuilder<> &builder) noexcept {
  input >> dst;

  llvm::Value* lhs = parse_value(input, builder);
  llvm::Value* rhs = parse_value(input, builder);

  llvm::Value* result = builder.CreateCmp(llvm::CmpInst::ICMP_EQ, lhs, rhs);

  builder.CreateStore(builder.CreateZExt(result, builder.getInt64Ty()), get_ptr(dst, builder));
}

void Instruction<instructions::NEQ>::build(
    std::istream &input, llvm::IRBuilder<> &builder) noexcept {
  input >> dst;

  llvm::Value* lhs = parse_value(input, builder);
  llvm::Value* rhs = parse_value(input, builder);

  llvm::Value* result = builder.CreateCmp(llvm::CmpInst::ICMP_NE, lhs, rhs);

  builder.CreateStore(builder.CreateZExt(result, builder.getInt64Ty()), get_ptr(dst, builder));
}

void Instruction<instructions::BR>::build(std::istream &input,
                                          llvm::IRBuilder<> &builder) noexcept {
  input >> arg;
  builder.CreateBr(label_blocks[arg]);
}

void Instruction<instructions::BR_COND>::build(
    std::istream &input, llvm::IRBuilder<> &builder) noexcept {
  llvm::Value* cond = builder.CreateTrunc(parse_value(input, builder), builder.getInt1Ty());
  llvm::BasicBlock *false_block = llvm::BasicBlock::Create(
      builder.getContext(), "", builder.GetInsertBlock()->getParent());
  input >> arg;
  builder.CreateCondBr(cond, label_blocks[arg], false_block);
  builder.SetInsertPoint(false_block);
}

void Instruction<instructions::EXIT>::build(
    std::istream &input, llvm::IRBuilder<> &builder) noexcept {
  builder.CreateRetVoid();
}

void Instruction<instructions::FILL_INIT_STATE>::build(
    std::istream &input, llvm::IRBuilder<> &builder) noexcept {

  llvm::Value* ptr = parse_value(input, builder);

  builder.CreateCall(fill_init_state_func, {builder.CreateIntToPtr(ptr, llvm::PointerType::get(builder.getContext(), 0))});
}

void Instruction<instructions::PUT_PIXEL>::build(
    std::istream &input, llvm::IRBuilder<> &builder) noexcept {
  
  llvm::Value* x = builder.CreateTrunc(parse_value(input, builder), builder.getInt32Ty());
  llvm::Value* y = builder.CreateTrunc(parse_value(input, builder), builder.getInt32Ty());
  llvm::Value* rgb = builder.CreateTrunc(parse_value(input, builder), builder.getInt32Ty());

  builder.CreateCall(put_pixel_func, {x, y, rgb});
}

void Instruction<instructions::FLUSH>::build(
    std::istream &input, llvm::IRBuilder<> &builder) noexcept {
  input >> dst;

  llvm::Value* result = builder.CreateCall(flush_func);

  builder.CreateStore(builder.CreateZExt(result, builder.getInt64Ty()), get_ptr(dst, builder));
}

llvm::Value* create_regs(llvm::IRBuilder<>& builder, llvm::Module* module) noexcept {
  llvm::ArrayType *regFileType = llvm::ArrayType::get(builder.getInt64Ty(), REGISTERS_COUNT);
  llvm::GlobalVariable *regFile = new llvm::GlobalVariable(
      *module, regFileType, false, llvm::GlobalValue::PrivateLinkage, 0,
      "registers");
  regFile->setInitializer(llvm::ConstantAggregateZero::get(regFileType));
  return regFile;
}

llvm::Function* declare_fill_init_state(llvm::IRBuilder<> &builder, llvm::Module *module) {
  llvm::Type *void_type = builder.getVoidTy();
  llvm::Type *ptr_type = llvm::PointerType::get(builder.getContext(), 0);
  llvm::SmallVector<llvm::Type *, 1> args = {ptr_type};
  llvm::FunctionType *func_type = llvm::FunctionType::get(void_type, args, false);
  llvm::Function *func = llvm::Function::Create(func_type, llvm::GlobalValue::ExternalLinkage,
                                    "fill_init_state", module);
  return func;
}

llvm::Function* declare_put_pixel(llvm::IRBuilder<> &builder, llvm::Module *module) {
  llvm::Type *void_type = builder.getVoidTy();
  llvm::Type *i32_type = builder.getInt32Ty();
  llvm::SmallVector<llvm::Type *, 3> args = {i32_type, i32_type, i32_type};
  llvm::FunctionType *func_type = llvm::FunctionType::get(void_type, args, false);
  llvm::Function *func = llvm::Function::Create(func_type, llvm::GlobalValue::ExternalLinkage,
                                    "put_pixel", module);
  return func;
}

llvm::Function* declare_flush(llvm::IRBuilder<> &builder, llvm::Module *module) {
  llvm::Type *i32_type = builder.getInt32Ty();
  llvm::FunctionType *func_type = llvm::FunctionType::get(i32_type, false);
  llvm::Function *func = llvm::Function::Create(func_type, llvm::GlobalValue::ExternalLinkage,
                                    "flush", module);
  return func;
}

llvm::Function* declare_llvm_memset(llvm::IRBuilder<> &builder, llvm::Module *module) {
  llvm::Type *void_type = builder.getVoidTy();
  llvm::Type *ptr_type = llvm::PointerType::get(builder.getContext(), 0);
  llvm::Type *i8_type = builder.getInt8Ty();
  llvm::Type *i32_type = builder.getInt32Ty();
  llvm::Type *i1_type = builder.getInt1Ty();
  llvm::SmallVector<llvm::Type *, 4> args = {ptr_type, i8_type, i32_type, i1_type};
  llvm::FunctionType *func_type = llvm::FunctionType::get(void_type, args, false);
  llvm::Function *func = llvm::Function::Create(func_type, llvm::GlobalValue::ExternalLinkage,
                                    "llvm.memset.p0.i32", module);
  return func;
}

void init_builder(llvm::IRBuilder<> &builder, llvm::Module *module) noexcept {
  REGISTERS = create_regs(builder, module);
  fill_init_state_func = declare_fill_init_state(builder, module);
  put_pixel_func = declare_put_pixel(builder, module);
  flush_func = declare_flush(builder, module);
  memset_func = declare_llvm_memset(builder, module);
}

void set_label_blocks(
    const std::map<std::string, llvm::BasicBlock *> &blocks) noexcept {
  label_blocks = blocks;
}

void map_functions(llvm::ExecutionEngine *engine) noexcept {
  engine->addGlobalMapping(fill_init_state_func, reinterpret_cast<void*>(&fill_init_state));
  engine->addGlobalMapping(put_pixel_func, reinterpret_cast<void*>(&put_pixel));
  engine->addGlobalMapping(flush_func, reinterpret_cast<void*>(&flush));
}
