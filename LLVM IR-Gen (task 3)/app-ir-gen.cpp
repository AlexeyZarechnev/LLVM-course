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

#include "../C-app (task-1)/include/sim.h"

using namespace llvm;

// declare void @llvm.lifetime.start.p0(i64 immarg, ptr nocapture) #1
FunctionCallee declare_llvm_life_start(LLVMContext &ctx, Module *module,
                                       IRBuilder<> &builder) {
  Type *void_type = Type::getVoidTy(ctx);
  Type *i64_type = Type::getInt64Ty(ctx);
  Type *ptr_type = PointerType::get(ctx, 0);
  ArrayRef<Type *> args = {i64_type, ptr_type};
  FunctionType *func_type = FunctionType::get(void_type, args, false);
  Function *func = Function::Create(func_type, GlobalValue::ExternalLinkage,
                                    "llvm.lifetime.start.p0", module);
  return func;
}

// declare void @llvm.memset.p0.i64(ptr nocapture writeonly, i8, i64, i1 immarg)
// #2
FunctionCallee declare_llvm_memset(LLVMContext &ctx, Module *module,
                                   IRBuilder<> &builder) {
  Type *void_type = Type::getVoidTy(ctx);
  Type *ptr_type = PointerType::get(ctx, 0);
  Type *i8_type = Type::getInt8Ty(ctx);
  Type *i64_type = Type::getInt64Ty(ctx);
  Type *i1_type = Type::getInt1Ty(ctx);
  ArrayRef<Type *> args = {ptr_type, i8_type, i64_type, i1_type};
  FunctionType *func_type = FunctionType::get(void_type, args, false);
  Function *func = Function::Create(func_type, GlobalValue::ExternalLinkage,
                                    "llvm.memset.p0.i64", module);
  return func;
}

// declare void @fill_init_state(ptr noundef) local_unnamed_addr #3
FunctionCallee declare_fill_init_state(LLVMContext &ctx, Module *module,
                                       IRBuilder<> &builder) {
  Type *void_type = Type::getVoidTy(ctx);
  Type *ptr_type = PointerType::get(ctx, 0);
  ArrayRef<Type *> args = {ptr_type};
  FunctionType *func_type = FunctionType::get(void_type, args, false);
  Function *func = Function::Create(func_type, GlobalValue::ExternalLinkage,
                                    "fill_init_state", module);
  return func;
}

// declare void @put_pixel(i32 noundef, i32 noundef, i32 noundef)
// local_unnamed_addr #3
FunctionCallee declare_put_pixel(LLVMContext &ctx, Module *module,
                                 IRBuilder<> &builder) {
  Type *void_type = Type::getVoidTy(ctx);
  Type *i32_type = Type::getInt32Ty(ctx);
  ArrayRef<Type *> args = {i32_type, i32_type, i32_type};
  FunctionType *func_type = FunctionType::get(void_type, args, false);
  Function *func = Function::Create(func_type, GlobalValue::ExternalLinkage,
                                    "put_pixel", module);
  return func;
}

// declare void @llvm.lifetime.end.p0(i64 immarg, ptr nocapture) #1
FunctionCallee declare_llvm_life_end(LLVMContext &ctx, Module *module,
                                     IRBuilder<> &builder) {
  Type *void_type = Type::getVoidTy(ctx);
  Type *i64_type = Type::getInt64Ty(ctx);
  Type *ptr_type = PointerType::get(ctx, 0);
  ArrayRef<Type *> args = {i64_type, ptr_type};
  FunctionType *func_type = FunctionType::get(void_type, args, false);
  Function *func = Function::Create(func_type, GlobalValue::ExternalLinkage,
                                    "llvm.lifetime.end.p0", module);
  return func;
}

// declare i32 @flush() local_unnamed_addr #3
FunctionCallee declare_flush(LLVMContext &ctx, Module *module,
                             IRBuilder<> &builder) {
  Type *i32_type = Type::getInt32Ty(ctx);
  FunctionType *func_type = FunctionType::get(i32_type, false);
  Function *func = Function::Create(func_type, GlobalValue::ExternalLinkage,
                                    "flush", module);
  return func;
}

int main(void) {

  LLVMContext ctx;
  Module *module = new Module("app.c", ctx);
  IRBuilder<> builder(ctx);

  FunctionCallee llvm_life_start_func =
      declare_llvm_life_start(ctx, module, builder);
  FunctionCallee llvm_memset_func = declare_llvm_memset(ctx, module, builder);
  FunctionCallee fill_init_state_func =
      declare_fill_init_state(ctx, module, builder);
  FunctionCallee put_pixel_func = declare_put_pixel(ctx, module, builder);
  FunctionCallee llvm_life_end_func =
      declare_llvm_life_end(ctx, module, builder);
  FunctionCallee flush_func = declare_flush(ctx, module, builder);

  // define void @app() local_unnamed_addr #0 {
  Function *app_func =
      Function::Create(FunctionType::get(Type::getVoidTy(ctx), false),
                       GlobalValue::ExternalLinkage, "app", module);

  BasicBlock *BB0 = BasicBlock::Create(ctx, "", app_func);
  BasicBlock *BB3 = BasicBlock::Create(ctx, "", app_func);
  BasicBlock *BB8 = BasicBlock::Create(ctx, "", app_func);
  BasicBlock *BB11 = BasicBlock::Create(ctx, "", app_func);
  BasicBlock *BB13 = BasicBlock::Create(ctx, "", app_func);
  BasicBlock *BB15 = BasicBlock::Create(ctx, "", app_func);
  BasicBlock *BB43 = BasicBlock::Create(ctx, "", app_func);
  BasicBlock *BB45 = BasicBlock::Create(ctx, "", app_func);
  BasicBlock *BB54 = BasicBlock::Create(ctx, "", app_func);
  BasicBlock *BB55 = BasicBlock::Create(ctx, "", app_func);
  BasicBlock *BB60 = BasicBlock::Create(ctx, "", app_func);
  BasicBlock *BB69 = BasicBlock::Create(ctx, "", app_func);
  BasicBlock *BB72 = BasicBlock::Create(ctx, "", app_func);
  BasicBlock *BB74 = BasicBlock::Create(ctx, "", app_func);
  BasicBlock *BB100 = BasicBlock::Create(ctx, "", app_func);
  BasicBlock *BB102 = BasicBlock::Create(ctx, "", app_func);
  BasicBlock *BB111 = BasicBlock::Create(ctx, "", app_func);
  BasicBlock *BB112 = BasicBlock::Create(ctx, "", app_func);
  BasicBlock *BB117 = BasicBlock::Create(ctx, "", app_func);

  Type *array_type =
      ArrayType::get(ArrayType::get(Type::getInt32Ty(ctx), 302), 502);

  // 0:
  builder.SetInsertPoint(BB0);
  // %1 = alloca [502 x [302 x i32]], align 4
  Value *val1 = builder.CreateAlloca(array_type, 0, "");
  // %2 = alloca [502 x [302 x i32]], align 4
  Value *val2 = builder.CreateAlloca(array_type, 0, "");
  // call void @llvm.lifetime.start.p0(i64 606416, ptr nonnull %1) #4
  builder.CreateCall(llvm_life_start_func, {builder.getInt64(606416), val1});
  // call void @llvm.memset.p0.i64(ptr noundef nonnull align 4
  // dereferenceable(606416) %1, i8 0, i64 606416, i1 false)
  builder.CreateCall(
      llvm_memset_func,
      {val1, builder.getInt8(0), builder.getInt64(606416), builder.getFalse()});
  // call void @llvm.lifetime.start.p0(i64 606416, ptr nonnull %2) #4
  builder.CreateCall(llvm_life_start_func, {builder.getInt64(606416), val2});
  // call void @llvm.memset.p0.i64(ptr noundef nonnull align 4
  // dereferenceable(606416) %2, i8 0, i64 606416, i1 false)
  builder.CreateCall(
      llvm_memset_func,
      {val2, builder.getInt8(0), builder.getInt64(606416), builder.getFalse()});
  // call void @fill_init_state(ptr noundef nonnull %1) #4
  builder.CreateCall(fill_init_state_func, {val1});
  // br label %3
  builder.CreateBr(BB3);

  // 3:                                                ; preds = %13, %0
  builder.SetInsertPoint(BB3);
  // %4 = phi i64 [ 1, %0 ], [ %14, %13 ]
  PHINode *phi4 = builder.CreatePHI(Type::getInt64Ty(ctx), 2);
  // %5 = add nuw nsw i64 %4, 1
  Value *val5 = builder.CreateAdd(phi4, builder.getInt64(1));
  // %6 = add nsw i64 %4, -1
  Value *val6 = builder.CreateAdd(phi4, builder.getInt64(-1));
  // %7 = trunc nuw nsw i64 %6 to i32
  Value *val7 = builder.CreateTrunc(val6, Type::getInt32Ty(ctx));
  // br label %15
  builder.CreateBr(BB15);

  // 8:                                                ; preds = %11
  builder.SetInsertPoint(BB8);
  // %9 = call i32 @flush() #4
  Value *val9 = builder.CreateCall(flush_func);
  // %10 = icmp eq i32 %9, 0
  Value *val10 = builder.CreateICmpEQ(val9, builder.getInt32(0));
  // br i1 %10, label %60, label %117
  builder.CreateCondBr(val10, BB60, BB117);

  // 11:                                               ; preds = %55
  builder.SetInsertPoint(BB11);
  // %12 = icmp eq i64 %5, 501
  Value *val12 = builder.CreateICmpEQ(val5, builder.getInt64(501));
  // br i1 %12, label %8, label %13
  builder.CreateCondBr(val12, BB8, BB13);

  // 13:                                               ; preds = %11, %69
  builder.SetInsertPoint(BB13);
  // %14 = phi i64 [ %5, %11 ], [ 1, %69 ]
  PHINode *phi14 = builder.CreatePHI(Type::getInt64Ty(ctx), 2);
  // br label %3
  builder.CreateBr(BB3);

  // 15:                                               ; preds = %3, %55
  builder.SetInsertPoint(BB15);
  // %16 = phi i64 [ 1, %3 ], [ %17, %55 ]
  PHINode *phi16 = builder.CreatePHI(Type::getInt64Ty(ctx), 2);
  // %17 = add nuw nsw i64 %16, 1
  Value *val17 = builder.CreateAdd(phi16, builder.getInt64(1));
  // %18 = getelementptr inbounds [502 x [302 x i32]], ptr %1, i64 0, i64 %4,
  // i64 %17
  Value *val18 =
      builder.CreateGEP(array_type, val1, {builder.getInt64(0), phi4, val17});
  // %19 = load i32, ptr %18, align 4, !tbaa !6
  Value *val19 = builder.CreateLoad(Type::getInt32Ty(ctx), val18);
  // %20 = add nsw i64 %16, -1
  Value *val20 = builder.CreateAdd(phi16, builder.getInt64(-1));
  // %21 = getelementptr inbounds [502 x [302 x i32]], ptr %1, i64 0, i64 %4,
  // i64 %20
  Value *val21 =
      builder.CreateGEP(array_type, val1, {builder.getInt64(0), phi4, val20});
  // %22 = load i32, ptr %21, align 4, !tbaa !6
  Value *val22 = builder.CreateLoad(Type::getInt32Ty(ctx), val21);
  // %23 = add nsw i32 %22, %19
  Value *val23 = builder.CreateAdd(val22, val19);
  // %24 = getelementptr inbounds [502 x [302 x i32]], ptr %1, i64 0, i64 %5,
  // i64 %16
  Value *val24 =
      builder.CreateGEP(array_type, val1, {builder.getInt64(0), val5, phi16});
  // %25 = load i32, ptr %24, align 4, !tbaa !6
  Value *val25 = builder.CreateLoad(Type::getInt32Ty(ctx), val24);
  // %26 = add nsw i32 %23, %25
  Value *val26 = builder.CreateAdd(val23, val25);
  // %27 = getelementptr inbounds [502 x [302 x i32]], ptr %1, i64 0, i64 %6,
  // i64 %16
  Value *val27 =
      builder.CreateGEP(array_type, val1, {builder.getInt64(0), val6, phi16});
  // %28 = load i32, ptr %27, align 4, !tbaa !6
  Value *val28 = builder.CreateLoad(Type::getInt32Ty(ctx), val27);
  // %29 = add nsw i32 %26, %28
  Value *val29 = builder.CreateAdd(val26, val28);
  // %30 = getelementptr inbounds [502 x [302 x i32]], ptr %1, i64 0, i64 %6,
  // i64 %20
  Value *val30 =
      builder.CreateGEP(array_type, val1, {builder.getInt64(0), val6, val20});
  // %31 = load i32, ptr %30, align 4, !tbaa !6
  Value *val31 = builder.CreateLoad(Type::getInt32Ty(ctx), val30);
  // %32 = add nsw i32 %29, %31
  Value *val32 = builder.CreateAdd(val29, val31);
  // %33 = getelementptr inbounds [502 x [302 x i32]], ptr %1, i64 0, i64 %6,
  // i64 %17
  Value *val33 =
      builder.CreateGEP(array_type, val1, {builder.getInt64(0), val6, val17});
  // %34 = load i32, ptr %33, align 4, !tbaa !6
  Value *val34 = builder.CreateLoad(Type::getInt32Ty(ctx), val33);
  // %35 = add nsw i32 %32, %34
  Value *val35 = builder.CreateAdd(val32, val34);
  // %36 = getelementptr inbounds [502 x [302 x i32]], ptr %1, i64 0, i64 %5,
  // i64 %20
  Value *val36 =
      builder.CreateGEP(array_type, val1, {builder.getInt64(0), val5, val20});
  // %37 = load i32, ptr %36, align 4, !tbaa !6
  Value *val37 = builder.CreateLoad(Type::getInt32Ty(ctx), val36);
  // %38 = add nsw i32 %35, %37
  Value *val38 = builder.CreateAdd(val35, val37);
  // %39 = getelementptr inbounds [502 x [302 x i32]], ptr %1, i64 0, i64 %5,
  // i64 %17
  Value *val39 =
      builder.CreateGEP(array_type, val1, {builder.getInt64(0), val5, val17});
  // %40 = load i32, ptr %39, align 4, !tbaa !6
  Value *val40 = builder.CreateLoad(Type::getInt32Ty(ctx), val39);
  // %41 = add nsw i32 %38, %40
  Value *val41 = builder.CreateAdd(val38, val40);
  // %42 = icmp eq i32 %41, 3
  Value *val42 = builder.CreateICmpEQ(val41, builder.getInt32(3));
  // br i1 %42, label %43, label %45
  builder.CreateCondBr(val42, BB43, BB45);

  // 43:                                               ; preds = %15
  builder.SetInsertPoint(BB43);
  // %44 = getelementptr inbounds [502 x [302 x i32]], ptr %2, i64 0, i64 %4,
  // i64 %16
  Value *val44 =
      builder.CreateGEP(array_type, val2, {builder.getInt64(0), phi4, phi16});
  // store i32 1, ptr %44, align 4, !tbaa !6
  builder.CreateStore(builder.getInt32(1), val44);
  // br label %54
  builder.CreateBr(BB54);

  // 45:                                               ; preds = %15
  builder.SetInsertPoint(BB45);
  // %46 = getelementptr inbounds [502 x [302 x i32]], ptr %1, i64 0, i64 %4,
  // i64 %16
  Value *val46 =
      builder.CreateGEP(array_type, val1, {builder.getInt64(0), phi4, phi16});
  // %47 = load i32, ptr %46, align 4, !tbaa !6
  Value *val47 = builder.CreateLoad(Type::getInt32Ty(ctx), val46);
  // %48 = icmp ne i32 %47, 0
  Value *val48 = builder.CreateICmpNE(val47, builder.getInt32(0));
  // %49 = icmp eq i32 %41, 2
  Value *val49 = builder.CreateICmpEQ(val41, builder.getInt32(2));
  // %50 = and i1 %49, %48
  Value *val50 = builder.CreateAnd(val49, val48);
  // %51 = freeze i1 %50
  Value *val51 = builder.CreateFreeze(val50);
  // %52 = zext i1 %51 to i32
  Value *val52 = builder.CreateZExt(val51, Type::getInt32Ty(ctx));
  // %53 = getelementptr inbounds [502 x [302 x i32]], ptr %2, i64 0, i64 %4,
  // i64 %16
  Value *val53 =
      builder.CreateGEP(array_type, val2, {builder.getInt64(0), phi4, phi16});
  // store i32 %52, ptr %53, align 4, !tbaa !6
  builder.CreateStore(val52, val53);
  // br i1 %51, label %54, label %55
  builder.CreateCondBr(val51, BB54, BB55);

  // 54:                                               ; preds = %43, %45
  builder.SetInsertPoint(BB54);
  // br label %55
  builder.CreateBr(BB55);

  // 55:                                               ; preds = %45, %54
  builder.SetInsertPoint(BB55);
  // %56 = phi i32 [ 16777215, %54 ], [ 0, %45 ]
  PHINode *phi56 = builder.CreatePHI(Type::getInt32Ty(ctx), 2);
  // %57 = trunc i64 %16 to i32
  Value *val57 = builder.CreateTrunc(phi16, Type::getInt32Ty(ctx));
  // %58 = sub i32 300, %57
  Value *val58 = builder.CreateSub(builder.getInt32(300), val57);
  // call void @put_pixel(i32 noundef %7, i32 noundef %58, i32 noundef %56) #4
  builder.CreateCall(put_pixel_func, {val7, val58, phi56});
  // %59 = icmp eq i64 %17, 301
  Value *val59 = builder.CreateICmpEQ(val17, builder.getInt64(301));
  // br i1 %59, label %11, label %15
  builder.CreateCondBr(val59, BB11, BB15);

  // 60:                                               ; preds = %8, %72
  builder.SetInsertPoint(BB60);
  // %61 = phi i64 [ %62, %72 ], [ 1, %8 ]
  PHINode *phi61 = builder.CreatePHI(Type::getInt64Ty(ctx), 2);
  // %62 = add nuw nsw i64 %61, 1
  Value *val62 = builder.CreateAdd(phi61, builder.getInt64(1));
  // %63 = add nsw i64 %61, -1
  Value *val63 = builder.CreateAdd(phi61, builder.getInt64(-1));
  // %64 = getelementptr inbounds [502 x [302 x i32]], ptr %2, i64 0, i64 %62,
  // i64 1
  Value *val64 = builder.CreateGEP(
      array_type, val2, {builder.getInt64(0), val62, builder.getInt64(1)});
  // %65 = load i32, ptr %64, align 4, !tbaa !6
  Value *val65 = builder.CreateLoad(Type::getInt32Ty(ctx), val64);
  // %66 = getelementptr inbounds [502 x [302 x i32]], ptr %2, i64 0, i64 %63,
  // i64 1
  Value *val66 = builder.CreateGEP(
      array_type, val2, {builder.getInt64(0), val63, builder.getInt64(1)});
  // %67 = load i32, ptr %66, align 4, !tbaa !6
  Value *val67 = builder.CreateLoad(Type::getInt32Ty(ctx), val66);
  // %68 = trunc nuw nsw i64 %63 to i32
  Value *val68 = builder.CreateTrunc(val63, Type::getInt32Ty(ctx));
  // br label %74
  builder.CreateBr(BB74);

  // 69:                                               ; preds = %72
  builder.SetInsertPoint(BB69);
  // %70 = call i32 @flush() #4
  Value *val70 = builder.CreateCall(flush_func);
  // %71 = icmp eq i32 %70, 0
  Value *val71 = builder.CreateICmpEQ(val70, builder.getInt32(0));
  // br i1 %71, label %13, label %117
  builder.CreateCondBr(val71, BB13, BB117);

  // 72:                                               ; preds = %112
  builder.SetInsertPoint(BB72);
  // %73 = icmp eq i64 %62, 501
  Value *val73 = builder.CreateICmpEQ(val62, builder.getInt64(501));
  // br i1 %73, label %69, label %60
  builder.CreateCondBr(val73, BB69, BB60);

  // 74:                                               ; preds = %60, %112
  builder.SetInsertPoint(BB74);
  // %75 = phi i32 [ %67, %60 ], [ %91, %112 ]
  PHINode *phi75 = builder.CreatePHI(Type::getInt32Ty(ctx), 2);
  // %76 = phi i32 [ %65, %60 ], [ %97, %112 ]
  PHINode *phi76 = builder.CreatePHI(Type::getInt32Ty(ctx), 2);
  // %77 = phi i64 [ 1, %60 ], [ %78, %112 ]
  PHINode *phi77 = builder.CreatePHI(Type::getInt64Ty(ctx), 2);
  // %78 = add nuw nsw i64 %77, 1
  Value *val78 = builder.CreateAdd(phi77, builder.getInt64(1));
  // %79 = getelementptr inbounds [502 x [302 x i32]], ptr %2, i64 0, i64 %61,
  // i64 %78
  Value *val79 =
      builder.CreateGEP(array_type, val2, {builder.getInt64(0), phi61, val78});
  // %80 = load i32, ptr %79, align 4, !tbaa !6
  Value *val80 = builder.CreateLoad(Type::getInt32Ty(ctx), val79);
  // %81 = add nsw i64 %77, -1
  Value *val81 = builder.CreateAdd(phi77, builder.getInt64(-1));
  // %82 = getelementptr inbounds [502 x [302 x i32]], ptr %2, i64 0, i64 %61,
  // i64 %81
  Value *val82 =
      builder.CreateGEP(array_type, val2, {builder.getInt64(0), phi61, val81});
  // %83 = load i32, ptr %82, align 4, !tbaa !6
  Value *val83 = builder.CreateLoad(Type::getInt32Ty(ctx), val82);
  // %84 = add nsw i32 %83, %80
  Value *val84 = builder.CreateAdd(val83, val80);
  // %85 = add nsw i32 %84, %76
  Value *val85 = builder.CreateAdd(val84, phi76);
  // %86 = add nsw i32 %85, %75
  Value *val86 = builder.CreateAdd(val85, phi75);
  // %87 = getelementptr inbounds [502 x [302 x i32]], ptr %2, i64 0, i64 %63,
  // i64 %81
  Value *val87 =
      builder.CreateGEP(array_type, val2, {builder.getInt64(0), val63, val81});
  // %88 = load i32, ptr %87, align 4, !tbaa !6
  Value *val88 = builder.CreateLoad(Type::getInt32Ty(ctx), val87);
  // %89 = add nsw i32 %86, %88
  Value *val89 = builder.CreateAdd(val86, val88);
  // %90 = getelementptr inbounds [502 x [302 x i32]], ptr %2, i64 0, i64 %63,
  // i64 %78
  Value *val90 =
      builder.CreateGEP(array_type, val2, {builder.getInt64(0), val63, val78});
  // %91 = load i32, ptr %90, align 4, !tbaa !6
  Value *val91 = builder.CreateLoad(Type::getInt32Ty(ctx), val90);
  // %92 = add nsw i32 %89, %91
  Value *val92 = builder.CreateAdd(val89, val91);
  // %93 = getelementptr inbounds [502 x [302 x i32]], ptr %2, i64 0, i64 %62,
  // i64 %81
  Value *val93 =
      builder.CreateGEP(array_type, val2, {builder.getInt64(0), val62, val81});
  // %94 = load i32, ptr %93, align 4, !tbaa !6
  Value *val94 = builder.CreateLoad(Type::getInt32Ty(ctx), val93);
  // %95 = add nsw i32 %92, %94
  Value *val95 = builder.CreateAdd(val92, val94);
  // %96 = getelementptr inbounds [502 x [302 x i32]], ptr %2, i64 0, i64 %62,
  // i64 %78
  Value *val96 =
      builder.CreateGEP(array_type, val2, {builder.getInt64(0), val62, val78});
  // %97 = load i32, ptr %96, align 4, !tbaa !6
  Value *val97 = builder.CreateLoad(Type::getInt32Ty(ctx), val96);
  // %98 = add nsw i32 %95, %97
  Value *val98 = builder.CreateAdd(val95, val97);
  // %99 = icmp eq i32 %98, 3
  Value *val99 = builder.CreateICmpEQ(val98, builder.getInt32(3));
  // br i1 %99, label %100, label %102
  builder.CreateCondBr(val99, BB100, BB102);

  // 100:                                              ; preds = %74
  builder.SetInsertPoint(BB100);
  // %101 = getelementptr inbounds [502 x [302 x i32]], ptr %1, i64 0, i64 %61,
  // i64 %77
  Value *val101 =
      builder.CreateGEP(array_type, val1, {builder.getInt64(0), phi61, phi77});
  // store i32 1, ptr %101, align 4, !tbaa !6
  builder.CreateStore(builder.getInt32(1), val101);
  // br label %111
  builder.CreateBr(BB111);

  // 102:                                              ; preds = %74
  builder.SetInsertPoint(BB102);
  // %103 = getelementptr inbounds [502 x [302 x i32]], ptr %2, i64 0, i64 %61,
  // i64 %77
  Value *val103 =
      builder.CreateGEP(array_type, val2, {builder.getInt64(0), phi61, phi77});
  // %104 = load i32, ptr %103, align 4, !tbaa !6
  Value *val104 = builder.CreateLoad(Type::getInt32Ty(ctx), val103);
  // %105 = icmp ne i32 %104, 0
  Value *val105 = builder.CreateICmpNE(val104, builder.getInt32(0));
  // %106 = icmp eq i32 %98, 2
  Value *val106 = builder.CreateICmpEQ(val98, builder.getInt32(2));
  // %107 = and i1 %106, %105
  Value *val107 = builder.CreateAnd(val106, val105);
  // %108 = freeze i1 %107
  Value *val108 = builder.CreateFreeze(val107);
  // %109 = zext i1 %108 to i32
  Value *val109 = builder.CreateZExt(val108, Type::getInt32Ty(ctx));
  // %110 = getelementptr inbounds [502 x [302 x i32]], ptr %1, i64 0, i64 %61,
  // i64 %77
  Value *val110 =
      builder.CreateGEP(array_type, val1, {builder.getInt64(0), phi61, phi77});
  // store i32 %109, ptr %110, align 4, !tbaa !6
  builder.CreateStore(val109, val110);
  // br i1 %108, label %111, label %112
  builder.CreateCondBr(val108, BB111, BB112);

  // 111:                                              ; preds = %100, %102
  builder.SetInsertPoint(BB111);
  // br label %112
  builder.CreateBr(BB112);

  // 112:                                              ; preds = %102, %111
  builder.SetInsertPoint(BB112);
  // %113 = phi i32 [ 16777215, %111 ], [ 0, %102 ]
  PHINode *phi113 = builder.CreatePHI(Type::getInt32Ty(ctx), 2);
  // %114 = trunc i64 %77 to i32
  Value *val114 = builder.CreateTrunc(phi77, Type::getInt32Ty(ctx));
  // %115 = sub i32 300, %114
  Value *val115 = builder.CreateSub(builder.getInt32(300), val114);
  // call void @put_pixel(i32 noundef %68, i32 noundef %115, i32 noundef %113)
  // #4
  builder.CreateCall(put_pixel_func, {val68, val115, phi113});
  // %116 = icmp eq i64 %78, 301
  Value *val116 = builder.CreateICmpEQ(val78, builder.getInt64(301));
  // br i1 %116, label %72, label %74
  builder.CreateCondBr(val116, BB72, BB74);

  // 117:                                              ; preds = %69, %8
  builder.SetInsertPoint(BB117);
  // call void @llvm.lifetime.end.p0(i64 606416, ptr nonnull %2) #4
  builder.CreateCall(llvm_life_end_func, {builder.getInt64(606416), val2});
  // call void @llvm.lifetime.end.p0(i64 606416, ptr nonnull %1) #4
  builder.CreateCall(llvm_life_end_func, {builder.getInt64(606416), val1});
  // ret void
  builder.CreateRetVoid();

  // Phi nodes linking
  // %4 = phi i64 [ 1, %0 ], [ %14, %13 ]
  phi4->addIncoming(builder.getInt64(1), BB0);
  phi4->addIncoming(phi14, BB13);
  // %14 = phi i64 [ %5, %11 ], [ 1, %69 ]
  phi14->addIncoming(val5, BB11);
  phi14->addIncoming(builder.getInt64(1), BB69);
  // %16 = phi i64 [ 1, %3 ], [ %17, %55 ]
  phi16->addIncoming(builder.getInt64(1), BB3);
  phi16->addIncoming(val17, BB55);
  // %56 = phi i32 [ 16777215, %54 ], [ 0, %45 ]
  phi56->addIncoming(builder.getInt32(16777215), BB54);
  phi56->addIncoming(builder.getInt32(0), BB45);
  // %61 = phi i64 [ %62, %72 ], [ 1, %8 ]
  phi61->addIncoming(val62, BB72);
  phi61->addIncoming(builder.getInt64(1), BB8);
  // %75 = phi i32 [ %67, %60 ], [ %91, %112 ]
  phi75->addIncoming(val67, BB60);
  phi75->addIncoming(val91, BB112);
  // %76 = phi i32 [ %65, %60 ], [ %97, %112 ]
  phi76->addIncoming(val65, BB60);
  phi76->addIncoming(val97, BB112);
  // %77 = phi i64 [ 1, %60 ], [ %78, %112 ]
  phi77->addIncoming(builder.getInt64(1), BB60);
  phi77->addIncoming(val78, BB112);
  // %113 = phi i32 [ 16777215, %111 ], [ 0, %102 ]
  phi113->addIncoming(builder.getInt32(16777215), BB111);
  phi113->addIncoming(builder.getInt32(0), BB102);

  // Dump LLVM IR
  module->print(outs(), nullptr);
  outs() << '\n';
  bool verified = verifyModule(*module, &outs());
  outs() << "[VERIFICATION] " << (verified ? "FAIL\n\n" : "OK\n\n");

  // LLVM IR Interpreter
  outs() << "[EE] Run\n";
  InitializeNativeTarget();
  InitializeNativeTargetAsmPrinter();

  ExecutionEngine *ee = EngineBuilder(std::unique_ptr<Module>(module)).create();
  ee->InstallLazyFunctionCreator([](const std::string &fnName) -> void * {
    if (fnName == "fill_init_state") {
      return reinterpret_cast<void *>(fill_init_state);
    }
    if (fnName == "put_pixel") {
      return reinterpret_cast<void *>(put_pixel);
    }
    if (fnName == "flush") {
      return reinterpret_cast<void *>(flush);
    }
    return nullptr;
  });
  ee->finalizeObject();

  init();

  ArrayRef<GenericValue> noargs;
  GenericValue v = ee->runFunction(app_func, noargs);
  outs() << "[EE] Result: " << v.IntVal << '\n';

  quit();
  return EXIT_SUCCESS;
}
