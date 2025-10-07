; ModuleID = 'C-app (task-1)/src/app.c'
source_filename = "C-app (task-1)/src/app.c"
target datalayout = "e-m:o-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-n32:64-S128-Fn32"
target triple = "arm64-apple-macosx15.0.0"

@0 = private unnamed_addr constant [5 x i8] c"load\00", align 1
@1 = private unnamed_addr constant [4 x i8] c"and\00", align 1
@2 = private unnamed_addr constant [5 x i8] c"zext\00", align 1
@3 = private unnamed_addr constant [7 x i8] c"select\00", align 1
@4 = private unnamed_addr constant [7 x i8] c"freeze\00", align 1
@5 = private unnamed_addr constant [6 x i8] c"store\00", align 1
@6 = private unnamed_addr constant [14 x i8] c"getelementptr\00", align 1
@7 = private unnamed_addr constant [6 x i8] c"trunc\00", align 1
@8 = private unnamed_addr constant [4 x i8] c"sub\00", align 1
@9 = private unnamed_addr constant [4 x i8] c"phi\00", align 1
@10 = private unnamed_addr constant [4 x i8] c"add\00", align 1
@11 = private unnamed_addr constant [3 x i8] c"br\00", align 1
@12 = private unnamed_addr constant [5 x i8] c"icmp\00", align 1
@13 = private unnamed_addr constant [5 x i8] c"call\00", align 1
@14 = private unnamed_addr constant [7 x i8] c"alloca\00", align 1

; Function Attrs: nounwind ssp uwtable(sync)
define void @app() local_unnamed_addr #0 {
  %1 = alloca [502 x [302 x i32]], align 4
  %2 = alloca [502 x [302 x i32]], align 4
  call void @log_instruction(ptr @13, ptr @14)
  call void @llvm.lifetime.start.p0(i64 606416, ptr nonnull %1) #4
  call void @log_instruction(ptr @13, ptr @14)
  call void @llvm.memset.p0.i64(ptr noundef nonnull align 4 dereferenceable(606416) %1, i8 0, i64 606416, i1 false)
  call void @log_instruction(ptr @13, ptr @14)
  call void @llvm.lifetime.start.p0(i64 606416, ptr nonnull %2) #4
  call void @log_instruction(ptr @13, ptr @14)
  call void @llvm.memset.p0.i64(ptr noundef nonnull align 4 dereferenceable(606416) %2, i8 0, i64 606416, i1 false)
  call void @log_instruction(ptr @13, ptr @14)
  call void @fill_init_state(ptr noundef nonnull %1) #4
  br label %3

3:                                                ; preds = %0, %11
  %4 = phi i64 [ 1, %0 ], [ %5, %11 ]
  call void @log_instruction(ptr @10, ptr @9)
  %5 = add nuw nsw i64 %4, 1
  call void @log_instruction(ptr @10, ptr @9)
  %6 = add nsw i64 %4, -1
  call void @log_instruction(ptr @7, ptr @10)
  %7 = trunc nuw nsw i64 %6 to i32
  br label %13

8:                                                ; preds = %11
  %9 = call i32 @flush() #4
  call void @log_instruction(ptr @12, ptr @13)
  %10 = icmp eq i32 %9, 0
  call void @log_instruction(ptr @11, ptr @12)
  br i1 %10, label %57, label %112

11:                                               ; preds = %50
  call void @log_instruction(ptr @12, ptr @10)
  %12 = icmp eq i64 %5, 501
  call void @log_instruction(ptr @11, ptr @12)
  br i1 %12, label %8, label %3, !llvm.loop !6

13:                                               ; preds = %3, %50
  %14 = phi i64 [ 1, %3 ], [ %15, %50 ]
  call void @log_instruction(ptr @10, ptr @9)
  %15 = add nuw nsw i64 %14, 1
  call void @log_instruction(ptr @6, ptr @14)
  call void @log_instruction(ptr @6, ptr @9)
  call void @log_instruction(ptr @6, ptr @10)
  %16 = getelementptr inbounds nuw [502 x [302 x i32]], ptr %1, i64 0, i64 %4, i64 %15
  call void @log_instruction(ptr @0, ptr @6)
  %17 = load i32, ptr %16, align 4, !tbaa !8
  call void @log_instruction(ptr @10, ptr @9)
  %18 = add nsw i64 %14, -1
  call void @log_instruction(ptr @6, ptr @14)
  call void @log_instruction(ptr @6, ptr @9)
  call void @log_instruction(ptr @6, ptr @10)
  %19 = getelementptr inbounds [502 x [302 x i32]], ptr %1, i64 0, i64 %4, i64 %18
  call void @log_instruction(ptr @0, ptr @6)
  %20 = load i32, ptr %19, align 4, !tbaa !8
  call void @log_instruction(ptr @10, ptr @0)
  call void @log_instruction(ptr @10, ptr @0)
  %21 = add nsw i32 %20, %17
  call void @log_instruction(ptr @6, ptr @14)
  call void @log_instruction(ptr @6, ptr @10)
  call void @log_instruction(ptr @6, ptr @9)
  %22 = getelementptr inbounds nuw [502 x [302 x i32]], ptr %1, i64 0, i64 %5, i64 %14
  call void @log_instruction(ptr @0, ptr @6)
  %23 = load i32, ptr %22, align 4, !tbaa !8
  call void @log_instruction(ptr @10, ptr @10)
  call void @log_instruction(ptr @10, ptr @0)
  %24 = add nsw i32 %21, %23
  call void @log_instruction(ptr @6, ptr @14)
  call void @log_instruction(ptr @6, ptr @10)
  call void @log_instruction(ptr @6, ptr @9)
  %25 = getelementptr inbounds [502 x [302 x i32]], ptr %1, i64 0, i64 %6, i64 %14
  call void @log_instruction(ptr @0, ptr @6)
  %26 = load i32, ptr %25, align 4, !tbaa !8
  call void @log_instruction(ptr @10, ptr @10)
  call void @log_instruction(ptr @10, ptr @0)
  %27 = add nsw i32 %24, %26
  call void @log_instruction(ptr @6, ptr @14)
  call void @log_instruction(ptr @6, ptr @10)
  call void @log_instruction(ptr @6, ptr @10)
  %28 = getelementptr inbounds [502 x [302 x i32]], ptr %1, i64 0, i64 %6, i64 %18
  call void @log_instruction(ptr @0, ptr @6)
  %29 = load i32, ptr %28, align 4, !tbaa !8
  call void @log_instruction(ptr @10, ptr @10)
  call void @log_instruction(ptr @10, ptr @0)
  %30 = add nsw i32 %27, %29
  call void @log_instruction(ptr @6, ptr @14)
  call void @log_instruction(ptr @6, ptr @10)
  call void @log_instruction(ptr @6, ptr @10)
  %31 = getelementptr inbounds [502 x [302 x i32]], ptr %1, i64 0, i64 %6, i64 %15
  call void @log_instruction(ptr @0, ptr @6)
  %32 = load i32, ptr %31, align 4, !tbaa !8
  call void @log_instruction(ptr @10, ptr @10)
  call void @log_instruction(ptr @10, ptr @0)
  %33 = add nsw i32 %30, %32
  call void @log_instruction(ptr @6, ptr @14)
  call void @log_instruction(ptr @6, ptr @10)
  call void @log_instruction(ptr @6, ptr @10)
  %34 = getelementptr inbounds [502 x [302 x i32]], ptr %1, i64 0, i64 %5, i64 %18
  call void @log_instruction(ptr @0, ptr @6)
  %35 = load i32, ptr %34, align 4, !tbaa !8
  call void @log_instruction(ptr @10, ptr @10)
  call void @log_instruction(ptr @10, ptr @0)
  %36 = add nsw i32 %33, %35
  call void @log_instruction(ptr @6, ptr @14)
  call void @log_instruction(ptr @6, ptr @10)
  call void @log_instruction(ptr @6, ptr @10)
  %37 = getelementptr inbounds nuw [502 x [302 x i32]], ptr %1, i64 0, i64 %5, i64 %15
  call void @log_instruction(ptr @0, ptr @6)
  %38 = load i32, ptr %37, align 4, !tbaa !8
  call void @log_instruction(ptr @10, ptr @10)
  call void @log_instruction(ptr @10, ptr @0)
  %39 = add nsw i32 %36, %38
  call void @log_instruction(ptr @12, ptr @10)
  %40 = icmp eq i32 %39, 3
  call void @log_instruction(ptr @11, ptr @12)
  br i1 %40, label %50, label %41

41:                                               ; preds = %13
  call void @log_instruction(ptr @6, ptr @14)
  call void @log_instruction(ptr @6, ptr @9)
  call void @log_instruction(ptr @6, ptr @9)
  %42 = getelementptr inbounds nuw [502 x [302 x i32]], ptr %1, i64 0, i64 %4, i64 %14
  call void @log_instruction(ptr @0, ptr @6)
  %43 = load i32, ptr %42, align 4, !tbaa !8
  call void @log_instruction(ptr @12, ptr @0)
  %44 = icmp ne i32 %43, 0
  call void @log_instruction(ptr @12, ptr @10)
  %45 = icmp eq i32 %39, 2
  call void @log_instruction(ptr @1, ptr @12)
  call void @log_instruction(ptr @1, ptr @12)
  %46 = and i1 %45, %44
  call void @log_instruction(ptr @4, ptr @1)
  %47 = freeze i1 %46
  call void @log_instruction(ptr @2, ptr @4)
  %48 = zext i1 %47 to i32
  call void @log_instruction(ptr @3, ptr @4)
  %49 = select i1 %47, i32 16777215, i32 0
  br label %50

50:                                               ; preds = %13, %41
  %51 = phi i32 [ %48, %41 ], [ 1, %13 ]
  %52 = phi i32 [ %49, %41 ], [ 16777215, %13 ]
  call void @log_instruction(ptr @6, ptr @14)
  call void @log_instruction(ptr @6, ptr @9)
  call void @log_instruction(ptr @6, ptr @9)
  %53 = getelementptr inbounds nuw [502 x [302 x i32]], ptr %2, i64 0, i64 %4, i64 %14
  call void @log_instruction(ptr @5, ptr @9)
  call void @log_instruction(ptr @5, ptr @6)
  store i32 %51, ptr %53, align 4, !tbaa !8
  call void @log_instruction(ptr @7, ptr @9)
  %54 = trunc i64 %14 to i32
  call void @log_instruction(ptr @8, ptr @7)
  %55 = sub i32 300, %54
  call void @log_instruction(ptr @13, ptr @7)
  call void @log_instruction(ptr @13, ptr @8)
  call void @log_instruction(ptr @13, ptr @9)
  call void @put_pixel(i32 noundef %7, i32 noundef %55, i32 noundef %52) #4
  call void @log_instruction(ptr @12, ptr @10)
  %56 = icmp eq i64 %15, 301
  call void @log_instruction(ptr @11, ptr @12)
  br i1 %56, label %11, label %13, !llvm.loop !12

57:                                               ; preds = %8, %68
  %58 = phi i64 [ %59, %68 ], [ 1, %8 ]
  call void @log_instruction(ptr @10, ptr @9)
  %59 = add nuw nsw i64 %58, 1
  call void @log_instruction(ptr @10, ptr @9)
  %60 = add nsw i64 %58, -1
  call void @log_instruction(ptr @6, ptr @14)
  call void @log_instruction(ptr @6, ptr @10)
  %61 = getelementptr inbounds nuw [502 x [302 x i32]], ptr %2, i64 0, i64 %59, i64 1
  call void @log_instruction(ptr @0, ptr @6)
  %62 = load i32, ptr %61, align 4, !tbaa !8
  call void @log_instruction(ptr @6, ptr @14)
  call void @log_instruction(ptr @6, ptr @10)
  %63 = getelementptr inbounds [502 x [302 x i32]], ptr %2, i64 0, i64 %60, i64 1
  call void @log_instruction(ptr @0, ptr @6)
  %64 = load i32, ptr %63, align 4, !tbaa !8
  call void @log_instruction(ptr @7, ptr @10)
  %65 = trunc nuw nsw i64 %60 to i32
  br label %70

66:                                               ; preds = %68
  %67 = call i32 @flush() #4
  br label %112

68:                                               ; preds = %105
  call void @log_instruction(ptr @12, ptr @10)
  %69 = icmp eq i64 %59, 501
  call void @log_instruction(ptr @11, ptr @12)
  br i1 %69, label %66, label %57, !llvm.loop !13

70:                                               ; preds = %57, %105
  %71 = phi i32 [ %64, %57 ], [ %87, %105 ]
  %72 = phi i32 [ %62, %57 ], [ %93, %105 ]
  %73 = phi i64 [ 1, %57 ], [ %74, %105 ]
  call void @log_instruction(ptr @10, ptr @9)
  %74 = add nuw nsw i64 %73, 1
  call void @log_instruction(ptr @6, ptr @14)
  call void @log_instruction(ptr @6, ptr @9)
  call void @log_instruction(ptr @6, ptr @10)
  %75 = getelementptr inbounds nuw [502 x [302 x i32]], ptr %2, i64 0, i64 %58, i64 %74
  call void @log_instruction(ptr @0, ptr @6)
  %76 = load i32, ptr %75, align 4, !tbaa !8
  call void @log_instruction(ptr @10, ptr @9)
  %77 = add nsw i64 %73, -1
  call void @log_instruction(ptr @6, ptr @14)
  call void @log_instruction(ptr @6, ptr @9)
  call void @log_instruction(ptr @6, ptr @10)
  %78 = getelementptr inbounds [502 x [302 x i32]], ptr %2, i64 0, i64 %58, i64 %77
  call void @log_instruction(ptr @0, ptr @6)
  %79 = load i32, ptr %78, align 4, !tbaa !8
  call void @log_instruction(ptr @10, ptr @0)
  call void @log_instruction(ptr @10, ptr @0)
  %80 = add nsw i32 %79, %76
  call void @log_instruction(ptr @10, ptr @10)
  call void @log_instruction(ptr @10, ptr @9)
  %81 = add nsw i32 %80, %72
  call void @log_instruction(ptr @10, ptr @10)
  call void @log_instruction(ptr @10, ptr @9)
  %82 = add nsw i32 %81, %71
  call void @log_instruction(ptr @6, ptr @14)
  call void @log_instruction(ptr @6, ptr @10)
  call void @log_instruction(ptr @6, ptr @10)
  %83 = getelementptr inbounds [502 x [302 x i32]], ptr %2, i64 0, i64 %60, i64 %77
  call void @log_instruction(ptr @0, ptr @6)
  %84 = load i32, ptr %83, align 4, !tbaa !8
  call void @log_instruction(ptr @10, ptr @10)
  call void @log_instruction(ptr @10, ptr @0)
  %85 = add nsw i32 %82, %84
  call void @log_instruction(ptr @6, ptr @14)
  call void @log_instruction(ptr @6, ptr @10)
  call void @log_instruction(ptr @6, ptr @10)
  %86 = getelementptr inbounds [502 x [302 x i32]], ptr %2, i64 0, i64 %60, i64 %74
  call void @log_instruction(ptr @0, ptr @6)
  %87 = load i32, ptr %86, align 4, !tbaa !8
  call void @log_instruction(ptr @10, ptr @10)
  call void @log_instruction(ptr @10, ptr @0)
  %88 = add nsw i32 %85, %87
  call void @log_instruction(ptr @6, ptr @14)
  call void @log_instruction(ptr @6, ptr @10)
  call void @log_instruction(ptr @6, ptr @10)
  %89 = getelementptr inbounds [502 x [302 x i32]], ptr %2, i64 0, i64 %59, i64 %77
  call void @log_instruction(ptr @0, ptr @6)
  %90 = load i32, ptr %89, align 4, !tbaa !8
  call void @log_instruction(ptr @10, ptr @10)
  call void @log_instruction(ptr @10, ptr @0)
  %91 = add nsw i32 %88, %90
  call void @log_instruction(ptr @6, ptr @14)
  call void @log_instruction(ptr @6, ptr @10)
  call void @log_instruction(ptr @6, ptr @10)
  %92 = getelementptr inbounds nuw [502 x [302 x i32]], ptr %2, i64 0, i64 %59, i64 %74
  call void @log_instruction(ptr @0, ptr @6)
  %93 = load i32, ptr %92, align 4, !tbaa !8
  call void @log_instruction(ptr @10, ptr @10)
  call void @log_instruction(ptr @10, ptr @0)
  %94 = add nsw i32 %91, %93
  call void @log_instruction(ptr @12, ptr @10)
  %95 = icmp eq i32 %94, 3
  call void @log_instruction(ptr @11, ptr @12)
  br i1 %95, label %105, label %96

96:                                               ; preds = %70
  call void @log_instruction(ptr @6, ptr @14)
  call void @log_instruction(ptr @6, ptr @9)
  call void @log_instruction(ptr @6, ptr @9)
  %97 = getelementptr inbounds nuw [502 x [302 x i32]], ptr %2, i64 0, i64 %58, i64 %73
  call void @log_instruction(ptr @0, ptr @6)
  %98 = load i32, ptr %97, align 4, !tbaa !8
  call void @log_instruction(ptr @12, ptr @0)
  %99 = icmp ne i32 %98, 0
  call void @log_instruction(ptr @12, ptr @10)
  %100 = icmp eq i32 %94, 2
  call void @log_instruction(ptr @1, ptr @12)
  call void @log_instruction(ptr @1, ptr @12)
  %101 = and i1 %100, %99
  call void @log_instruction(ptr @4, ptr @1)
  %102 = freeze i1 %101
  call void @log_instruction(ptr @2, ptr @4)
  %103 = zext i1 %102 to i32
  call void @log_instruction(ptr @3, ptr @4)
  %104 = select i1 %102, i32 16777215, i32 0
  br label %105

105:                                              ; preds = %70, %96
  %106 = phi i32 [ %103, %96 ], [ 1, %70 ]
  %107 = phi i32 [ %104, %96 ], [ 16777215, %70 ]
  call void @log_instruction(ptr @6, ptr @14)
  call void @log_instruction(ptr @6, ptr @9)
  call void @log_instruction(ptr @6, ptr @9)
  %108 = getelementptr inbounds nuw [502 x [302 x i32]], ptr %1, i64 0, i64 %58, i64 %73
  call void @log_instruction(ptr @5, ptr @9)
  call void @log_instruction(ptr @5, ptr @6)
  store i32 %106, ptr %108, align 4, !tbaa !8
  call void @log_instruction(ptr @7, ptr @9)
  %109 = trunc i64 %73 to i32
  call void @log_instruction(ptr @8, ptr @7)
  %110 = sub i32 300, %109
  call void @log_instruction(ptr @13, ptr @7)
  call void @log_instruction(ptr @13, ptr @8)
  call void @log_instruction(ptr @13, ptr @9)
  call void @put_pixel(i32 noundef %65, i32 noundef %110, i32 noundef %107) #4
  call void @log_instruction(ptr @12, ptr @10)
  %111 = icmp eq i64 %74, 301
  call void @log_instruction(ptr @11, ptr @12)
  br i1 %111, label %68, label %70, !llvm.loop !14

112:                                              ; preds = %66, %8
  call void @log_instruction(ptr @13, ptr @14)
  call void @llvm.lifetime.end.p0(i64 606416, ptr nonnull %2) #4
  call void @log_instruction(ptr @13, ptr @14)
  call void @llvm.lifetime.end.p0(i64 606416, ptr nonnull %1) #4
  ret void
}

; Function Attrs: mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.start.p0(i64 immarg, ptr captures(none)) #1

; Function Attrs: mustprogress nocallback nofree nounwind willreturn memory(argmem: write)
declare void @llvm.memset.p0.i64(ptr writeonly captures(none), i8, i64, i1 immarg) #2

declare void @fill_init_state(ptr noundef) local_unnamed_addr #3

declare void @put_pixel(i32 noundef, i32 noundef, i32 noundef) local_unnamed_addr #3

; Function Attrs: mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.end.p0(i64 immarg, ptr captures(none)) #1

declare i32 @flush() local_unnamed_addr #3

declare void @log_instruction(ptr, ptr)

attributes #0 = { nounwind ssp uwtable(sync) "frame-pointer"="non-leaf" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+altnzcv,+ccdp,+ccidx,+ccpp,+complxnum,+crc,+dit,+dotprod,+flagm,+fp-armv8,+fp16fml,+fptoint,+fullfp16,+jsconv,+lse,+neon,+pauth,+perfmon,+predres,+ras,+rcpc,+rdm,+sb,+sha2,+sha3,+specrestrict,+ssbs,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8a" }
attributes #1 = { mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite) }
attributes #2 = { mustprogress nocallback nofree nounwind willreturn memory(argmem: write) }
attributes #3 = { "frame-pointer"="non-leaf" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+altnzcv,+ccdp,+ccidx,+ccpp,+complxnum,+crc,+dit,+dotprod,+flagm,+fp-armv8,+fp16fml,+fptoint,+fullfp16,+jsconv,+lse,+neon,+pauth,+perfmon,+predres,+ras,+rcpc,+rdm,+sb,+sha2,+sha3,+specrestrict,+ssbs,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8a" }
attributes #4 = { nounwind }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 2, !"SDK Version", [2 x i32] [i32 15, i32 5]}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 8, !"PIC Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 1}
!4 = !{i32 7, !"frame-pointer", i32 1}
!5 = !{!"Homebrew clang version 21.1.2"}
!6 = distinct !{!6, !7}
!7 = !{!"llvm.loop.mustprogress"}
!8 = !{!9, !9, i64 0}
!9 = !{!"int", !10, i64 0}
!10 = !{!"omnipotent char", !11, i64 0}
!11 = !{!"Simple C/C++ TBAA"}
!12 = distinct !{!12, !7}
!13 = distinct !{!13, !7}
!14 = distinct !{!14, !7}
