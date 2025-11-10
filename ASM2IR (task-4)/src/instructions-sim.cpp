#include "../../C-app (task-1)/include/sim.h"
#include "instructions.hpp"

#include "llvm/ADT/SmallVector.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"
#include <array>
#include <cstddef>
#include <cstdint>
#include <istream>
#include <map>
#include <string>

struct Cleaner {
  ~Cleaner() {
    for (auto ptr : allocated_memory) {
      delete[] ptr;
    }
  }
  std::vector<char *> allocated_memory;
};

static Cleaner cleaner;

static std::string arg;

static std::array<uint64_t, 8> REGISTERS = {};

static llvm::Function *add_sim_func = nullptr;
static llvm::Function *sub_sim_func = nullptr;
static llvm::Function *mul_sim_func = nullptr;
static llvm::Function *alloca_sim_func = nullptr;
static llvm::Function *gep2_sim_func = nullptr;
static llvm::Function *load_sim_func = nullptr;
static llvm::Function *store_sim_func = nullptr;
static llvm::Function *eq_sim_func = nullptr;
static llvm::Function *neq_sim_func = nullptr;
static llvm::Function *to_bool_func = nullptr;
static llvm::Function *fill_init_state_sim_func = nullptr;
static llvm::Function *put_pixel_sim_func = nullptr;
static llvm::Function *flush_sim_func = nullptr;

static std::map<std::string, llvm::BasicBlock *> label_blocks;

static uint64_t get_value(std::string src) noexcept {
  uint64_t result = 0;
  if (src[0] == 'x') {
    auto num = std::stoi(std::string(src.substr(1)));
    result = REGISTERS[num];
  } else {
    result = std::stoull(std::string(src));
  }
  return result;
}

static uint64_t get_num(std::string src) noexcept {
  return std::stoi(src.substr(1));
}

static llvm::Value *createGlobalString(llvm::IRBuilder<> &builder,
                                       const std::string &str) {
  static std::map<std::string, llvm::Value *> globalStrings;

  auto it = globalStrings.find(str);
  if (it != globalStrings.end()) {
    return it->second;
  }

  llvm::Value *stringVal = builder.CreateGlobalString(str);
  globalStrings[str] = stringVal;
  return stringVal;
}

template <size_t N>
static llvm::SmallVector<llvm::Value *, N>
parse_args(std::istream &input, llvm::IRBuilder<> &builder) noexcept {
  llvm::SmallVector<llvm::Value *, N> args(N);
  for (size_t i = 0; i < N; ++i) {
    input >> arg;
    args[i] = createGlobalString(builder, arg);
  }
  return args;
}

void add_sim(const char* dst, const char* src1,
             const char* src2) noexcept {
  uint64_t val1 = get_value(src1);
  uint64_t val2 = get_value(src2);

  REGISTERS[get_num(dst)] = val1 + val2;
}

void Instruction<instructions::ADD>::build(
    std::istream &input, llvm::IRBuilder<> &builder) noexcept {
  builder.CreateCall(add_sim_func, parse_args<3>(input, builder));
}

void sub_sim(const char* dst, const char* src1,
             const char* src2) noexcept {
  uint64_t val1 = get_value(src1);
  uint64_t val2 = get_value(src2);

  REGISTERS[get_num(dst)] = val1 - val2;
}

void Instruction<instructions::SUB>::build(
    std::istream &input, llvm::IRBuilder<> &builder) noexcept {
  builder.CreateCall(sub_sim_func, parse_args<3>(input, builder));
}

void mul_sim(const char* dst, const char* src1,
             const char* src2) noexcept {
  uint64_t val1 = get_value(src1);
  uint64_t val2 = get_value(src2);

  REGISTERS[get_num(dst)] = val1 * val2;
}

void Instruction<instructions::MUL>::build(
    std::istream &input, llvm::IRBuilder<> &builder) noexcept {
  builder.CreateCall(mul_sim_func, parse_args<3>(input, builder));
}

void alloca_sim(const char* dst, const char* size) noexcept {
  uint64_t alloc_size = get_value(size);

  char *memory = new char[alloc_size];
  REGISTERS[get_num(dst)] = reinterpret_cast<uint64_t>(memory);
  cleaner.allocated_memory.push_back(memory);

  llvm::outs() << "Allocated from" << reinterpret_cast<uint64_t>(memory) << " to " << reinterpret_cast<uint64_t>(memory + alloc_size) << "\n";
}

//4909598928

void Instruction<instructions::ALLOCA>::build(
    std::istream &input, llvm::IRBuilder<> &builder) noexcept {
  builder.CreateCall(alloca_sim_func, parse_args<2>(input, builder));
}

void gep2_sim(const char* dst, const char* base, const char* ptr,
              const char* idx1, const char* idx2,
              const char* off1, const char* off2) noexcept {
  uint64_t base_size = get_value(base);
  uint64_t ptr_addr = get_value(ptr);
  uint64_t index1 = get_value(idx1);
  uint64_t index2 = get_value(idx2);
  uint64_t offset1 = get_value(off1);
  uint64_t offset2 = get_value(off2);

  // llvm::outs() << ", index1: " << index1 << ", index2: " << index2 << "\n";

  REGISTERS[get_num(dst)] =
      ptr_addr + ((index1 + offset1) * base_size + (index2 + offset2)) * 4;
}

void Instruction<instructions::GEP2>::build(
    std::istream &input, llvm::IRBuilder<> &builder) noexcept {
  builder.CreateCall(gep2_sim_func, parse_args<7>(input, builder));
}

void load_sim(const char* dst, const char* addr) noexcept {
  uint64_t addr_val = get_value(addr);
  uint32_t loaded_value = *reinterpret_cast<uint32_t *>(addr_val);

  REGISTERS[get_num(dst)] = static_cast<uint64_t>(loaded_value);
}

void Instruction<instructions::LOAD>::build(
    std::istream &input, llvm::IRBuilder<> &builder) noexcept {
  builder.CreateCall(load_sim_func, parse_args<2>(input, builder));
}

void store_sim(const char* addr, const char* value) noexcept {
  uint64_t addr_val = get_value(addr);
  uint32_t value_val = static_cast<uint32_t>(get_value(value));

  *reinterpret_cast<uint32_t *>(addr_val) = value_val;
}

void Instruction<instructions::STORE>::build(
    std::istream &input, llvm::IRBuilder<> &builder) noexcept {
  builder.CreateCall(store_sim_func, parse_args<2>(input, builder));
}

void eq_sim(const char* dst, const char* src1,
            const char* src2) noexcept {
  uint64_t val1 = get_value(src1);
  uint64_t val2 = get_value(src2);

  // llvm::outs() << "EQ: " << val1 << " == " << val2 << "\n";

  REGISTERS[get_num(dst)] = (val1 == val2) ? 1 : 0;
}

void Instruction<instructions::EQ>::build(std::istream &input,
                                          llvm::IRBuilder<> &builder) noexcept {
  builder.CreateCall(eq_sim_func, parse_args<3>(input, builder));
}

void neq_sim(const char* dst, const char* src1,
             const char* src2) noexcept {
  uint64_t val1 = get_value(src1);
  uint64_t val2 = get_value(src2);

  REGISTERS[get_num(dst)] = (val1 != val2) ? 1 : 0;
}

void Instruction<instructions::NEQ>::build(
    std::istream &input, llvm::IRBuilder<> &builder) noexcept {
  builder.CreateCall(neq_sim_func, parse_args<3>(input, builder));
}

void Instruction<instructions::BR>::build(std::istream &input,
                                          llvm::IRBuilder<> &builder) noexcept {
  input >> arg;
  builder.CreateBr(label_blocks[arg]);
}

bool to_bool(const char* src) noexcept {
  uint64_t val = get_value(src);
  return val != 0;
}

void Instruction<instructions::BR_COND>::build(
    std::istream &input, llvm::IRBuilder<> &builder) noexcept {
  llvm::Value *cond =
      builder.CreateCall(to_bool_func, parse_args<1>(input, builder));
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

void fill_init_state_sim(const char* ptr) noexcept {
  uint64_t ptr_addr = get_value(ptr);
  fill_init_state(reinterpret_cast<int (*)[302]>(ptr_addr));
}

void Instruction<instructions::FILL_INIT_STATE>::build(
    std::istream &input, llvm::IRBuilder<> &builder) noexcept {
  builder.CreateCall(fill_init_state_sim_func, parse_args<1>(input, builder));
}

void put_pixel_sim(const char* x, const char* y,
                   const char* rgb) noexcept {
  int x_val = static_cast<int>(get_value(x));
  int y_val = static_cast<int>(get_value(y));
  int rgb_val = static_cast<int>(get_value(rgb));

  put_pixel(x_val, y_val, rgb_val);
}

void Instruction<instructions::PUT_PIXEL>::build(
    std::istream &input, llvm::IRBuilder<> &builder) noexcept {
  builder.CreateCall(put_pixel_sim_func, parse_args<3>(input, builder));
}

void flush_sim(const char* dst) noexcept {
  int result = flush();
  REGISTERS[get_num(dst)] = static_cast<uint64_t>(result);
}

void Instruction<instructions::FLUSH>::build(
    std::istream &input, llvm::IRBuilder<> &builder) noexcept {
  builder.CreateCall(flush_sim_func, parse_args<1>(input, builder));
}

template <size_t N>
llvm::Function *init_func(llvm::Type *void_type, llvm::Type *string_type,
                          llvm::Module *module, const char *name) noexcept {
  llvm::SmallVector<llvm::Type *, N> args(N, string_type);
  llvm::FunctionType *func_type =
      llvm::FunctionType::get(void_type, args, false);
  llvm::Function *func = llvm::Function::Create(
      func_type, llvm::GlobalValue::ExternalLinkage, name, module);
  return func;
}

void init_builder(llvm::IRBuilder<> &builder, llvm::Module *module) noexcept {
  llvm::Type *void_type = llvm::Type::getVoidTy(builder.getContext());
  llvm::Type *string_type = llvm::PointerType::get(builder.getContext(), 0);
  llvm::Type *int1_type = llvm::Type::getInt1Ty(builder.getContext());
  add_sim_func = init_func<3>(void_type, string_type, module, "add");
  sub_sim_func = init_func<3>(void_type, string_type, module, "sub");
  mul_sim_func = init_func<3>(void_type, string_type, module, "mul");
  alloca_sim_func = init_func<2>(void_type, string_type, module, "alloca");
  gep2_sim_func = init_func<7>(void_type, string_type, module, "gep2");
  load_sim_func = init_func<2>(void_type, string_type, module, "load");
  store_sim_func = init_func<2>(void_type, string_type, module, "store");
  eq_sim_func = init_func<3>(void_type, string_type, module, "eq");
  neq_sim_func = init_func<3>(void_type, string_type, module, "neq");
  to_bool_func = init_func<1>(int1_type, string_type, module, "get");
  fill_init_state_sim_func =
      init_func<1>(void_type, string_type, module, "fill_init_state");
  put_pixel_sim_func =
      init_func<3>(void_type, string_type, module, "put_pixel");
  flush_sim_func = init_func<1>(void_type, string_type, module, "flush");
}

void set_label_blocks(
    const std::map<std::string, llvm::BasicBlock *> &blocks) noexcept {
  label_blocks = blocks;
}

void map_functions(llvm::ExecutionEngine *engine) noexcept {
  engine->addGlobalMapping(add_sim_func, reinterpret_cast<void *>(&add_sim));
  engine->addGlobalMapping(sub_sim_func, reinterpret_cast<void *>(&sub_sim));
  engine->addGlobalMapping(mul_sim_func, reinterpret_cast<void *>(&mul_sim));
  engine->addGlobalMapping(alloca_sim_func,
                           reinterpret_cast<void *>(&alloca_sim));
  engine->addGlobalMapping(gep2_sim_func, reinterpret_cast<void *>(&gep2_sim));
  engine->addGlobalMapping(load_sim_func, reinterpret_cast<void *>(&load_sim));
  engine->addGlobalMapping(store_sim_func,
                           reinterpret_cast<void *>(&store_sim));
  engine->addGlobalMapping(eq_sim_func, reinterpret_cast<void *>(&eq_sim));
  engine->addGlobalMapping(neq_sim_func, reinterpret_cast<void *>(&neq_sim));
  engine->addGlobalMapping(to_bool_func, reinterpret_cast<void *>(&to_bool));
  engine->addGlobalMapping(fill_init_state_sim_func,
                           reinterpret_cast<void *>(&fill_init_state_sim));
  engine->addGlobalMapping(put_pixel_sim_func,
                           reinterpret_cast<void *>(&put_pixel_sim));
  engine->addGlobalMapping(flush_sim_func,
                           reinterpret_cast<void *>(&flush_sim));
}
