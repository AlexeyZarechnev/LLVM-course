; ModuleID = 'src/app.c'
source_filename = "src/app.c"
target datalayout = "e-m:o-i64:64-i128:128-n32:64-S128-Fn32"
target triple = "arm64-apple-macosx15.0.0"

; Function Attrs: nounwind ssp uwtable(sync)
define void @app() local_unnamed_addr #0 {
  %1 = alloca [502 x [302 x i32]], align 4
  %2 = alloca [502 x [302 x i32]], align 4
  call void @llvm.lifetime.start.p0(i64 606416, ptr nonnull %1) #4
  call void @llvm.memset.p0.i64(ptr noundef nonnull align 4 dereferenceable(606416) %1, i8 0, i64 606416, i1 false)
  call void @llvm.lifetime.start.p0(i64 606416, ptr nonnull %2) #4
  call void @llvm.memset.p0.i64(ptr noundef nonnull align 4 dereferenceable(606416) %2, i8 0, i64 606416, i1 false)
  call void @fill_init_state(ptr noundef nonnull %1) #4
  br label %3

3:                                                ; preds = %13, %0
  %4 = phi i64 [ 1, %0 ], [ %14, %13 ]
  %5 = add nuw nsw i64 %4, 1
  %6 = add nsw i64 %4, -1
  %7 = trunc nuw nsw i64 %6 to i32
  br label %15

8:                                                ; preds = %11
  %9 = call i32 @flush() #4
  %10 = icmp eq i32 %9, 0
  br i1 %10, label %60, label %117

11:                                               ; preds = %55
  %12 = icmp eq i64 %5, 501
  br i1 %12, label %8, label %13

13:                                               ; preds = %11, %69
  %14 = phi i64 [ %5, %11 ], [ 1, %69 ]
  br label %3

15:                                               ; preds = %3, %55
  %16 = phi i64 [ 1, %3 ], [ %17, %55 ]
  %17 = add nuw nsw i64 %16, 1
  %18 = getelementptr inbounds [502 x [302 x i32]], ptr %1, i64 0, i64 %4, i64 %17
  %19 = load i32, ptr %18, align 4, !tbaa !6
  %20 = add nsw i64 %16, -1
  %21 = getelementptr inbounds [502 x [302 x i32]], ptr %1, i64 0, i64 %4, i64 %20
  %22 = load i32, ptr %21, align 4, !tbaa !6
  %23 = add nsw i32 %22, %19
  %24 = getelementptr inbounds [502 x [302 x i32]], ptr %1, i64 0, i64 %5, i64 %16
  %25 = load i32, ptr %24, align 4, !tbaa !6
  %26 = add nsw i32 %23, %25
  %27 = getelementptr inbounds [502 x [302 x i32]], ptr %1, i64 0, i64 %6, i64 %16
  %28 = load i32, ptr %27, align 4, !tbaa !6
  %29 = add nsw i32 %26, %28
  %30 = getelementptr inbounds [502 x [302 x i32]], ptr %1, i64 0, i64 %6, i64 %20
  %31 = load i32, ptr %30, align 4, !tbaa !6
  %32 = add nsw i32 %29, %31
  %33 = getelementptr inbounds [502 x [302 x i32]], ptr %1, i64 0, i64 %6, i64 %17
  %34 = load i32, ptr %33, align 4, !tbaa !6
  %35 = add nsw i32 %32, %34
  %36 = getelementptr inbounds [502 x [302 x i32]], ptr %1, i64 0, i64 %5, i64 %20
  %37 = load i32, ptr %36, align 4, !tbaa !6
  %38 = add nsw i32 %35, %37
  %39 = getelementptr inbounds [502 x [302 x i32]], ptr %1, i64 0, i64 %5, i64 %17
  %40 = load i32, ptr %39, align 4, !tbaa !6
  %41 = add nsw i32 %38, %40
  %42 = icmp eq i32 %41, 3
  br i1 %42, label %43, label %45

43:                                               ; preds = %15
  %44 = getelementptr inbounds [502 x [302 x i32]], ptr %2, i64 0, i64 %4, i64 %16
  store i32 1, ptr %44, align 4, !tbaa !6
  br label %54

45:                                               ; preds = %15
  %46 = getelementptr inbounds [502 x [302 x i32]], ptr %1, i64 0, i64 %4, i64 %16
  %47 = load i32, ptr %46, align 4, !tbaa !6
  %48 = icmp ne i32 %47, 0
  %49 = icmp eq i32 %41, 2
  %50 = and i1 %49, %48
  %51 = freeze i1 %50
  %52 = zext i1 %51 to i32
  %53 = getelementptr inbounds [502 x [302 x i32]], ptr %2, i64 0, i64 %4, i64 %16
  store i32 %52, ptr %53, align 4, !tbaa !6
  br i1 %51, label %54, label %55

54:                                               ; preds = %43, %45
  br label %55

55:                                               ; preds = %45, %54
  %56 = phi i32 [ 16777215, %54 ], [ 0, %45 ]
  %57 = trunc i64 %16 to i32
  %58 = sub i32 300, %57
  call void @put_pixel(i32 noundef %7, i32 noundef %58, i32 noundef %56) #4
  %59 = icmp eq i64 %17, 301
  br i1 %59, label %11, label %15

60:                                               ; preds = %8, %72
  %61 = phi i64 [ %62, %72 ], [ 1, %8 ]
  %62 = add nuw nsw i64 %61, 1
  %63 = add nsw i64 %61, -1
  %64 = getelementptr inbounds [502 x [302 x i32]], ptr %2, i64 0, i64 %62, i64 1
  %65 = load i32, ptr %64, align 4, !tbaa !6
  %66 = getelementptr inbounds [502 x [302 x i32]], ptr %2, i64 0, i64 %63, i64 1
  %67 = load i32, ptr %66, align 4, !tbaa !6
  %68 = trunc nuw nsw i64 %63 to i32
  br label %74

69:                                               ; preds = %72
  %70 = call i32 @flush() #4
  %71 = icmp eq i32 %70, 0
  br i1 %71, label %13, label %117

72:                                               ; preds = %112
  %73 = icmp eq i64 %62, 501
  br i1 %73, label %69, label %60

74:                                               ; preds = %60, %112
  %75 = phi i32 [ %67, %60 ], [ %91, %112 ]
  %76 = phi i32 [ %65, %60 ], [ %97, %112 ]
  %77 = phi i64 [ 1, %60 ], [ %78, %112 ]
  %78 = add nuw nsw i64 %77, 1
  %79 = getelementptr inbounds [502 x [302 x i32]], ptr %2, i64 0, i64 %61, i64 %78
  %80 = load i32, ptr %79, align 4, !tbaa !6
  %81 = add nsw i64 %77, -1
  %82 = getelementptr inbounds [502 x [302 x i32]], ptr %2, i64 0, i64 %61, i64 %81
  %83 = load i32, ptr %82, align 4, !tbaa !6
  %84 = add nsw i32 %83, %80
  %85 = add nsw i32 %84, %76
  %86 = add nsw i32 %85, %75
  %87 = getelementptr inbounds [502 x [302 x i32]], ptr %2, i64 0, i64 %63, i64 %81
  %88 = load i32, ptr %87, align 4, !tbaa !6
  %89 = add nsw i32 %86, %88
  %90 = getelementptr inbounds [502 x [302 x i32]], ptr %2, i64 0, i64 %63, i64 %78
  %91 = load i32, ptr %90, align 4, !tbaa !6
  %92 = add nsw i32 %89, %91
  %93 = getelementptr inbounds [502 x [302 x i32]], ptr %2, i64 0, i64 %62, i64 %81
  %94 = load i32, ptr %93, align 4, !tbaa !6
  %95 = add nsw i32 %92, %94
  %96 = getelementptr inbounds [502 x [302 x i32]], ptr %2, i64 0, i64 %62, i64 %78
  %97 = load i32, ptr %96, align 4, !tbaa !6
  %98 = add nsw i32 %95, %97
  %99 = icmp eq i32 %98, 3
  br i1 %99, label %100, label %102

100:                                              ; preds = %74
  %101 = getelementptr inbounds [502 x [302 x i32]], ptr %1, i64 0, i64 %61, i64 %77
  store i32 1, ptr %101, align 4, !tbaa !6
  br label %111

102:                                              ; preds = %74
  %103 = getelementptr inbounds [502 x [302 x i32]], ptr %2, i64 0, i64 %61, i64 %77
  %104 = load i32, ptr %103, align 4, !tbaa !6
  %105 = icmp ne i32 %104, 0
  %106 = icmp eq i32 %98, 2
  %107 = and i1 %106, %105
  %108 = freeze i1 %107
  %109 = zext i1 %108 to i32
  %110 = getelementptr inbounds [502 x [302 x i32]], ptr %1, i64 0, i64 %61, i64 %77
  store i32 %109, ptr %110, align 4, !tbaa !6
  br i1 %108, label %111, label %112

111:                                              ; preds = %100, %102
  br label %112

112:                                              ; preds = %102, %111
  %113 = phi i32 [ 16777215, %111 ], [ 0, %102 ]
  %114 = trunc i64 %77 to i32
  %115 = sub i32 300, %114
  call void @put_pixel(i32 noundef %68, i32 noundef %115, i32 noundef %113) #4
  %116 = icmp eq i64 %78, 301
  br i1 %116, label %72, label %74

117:                                              ; preds = %69, %8
  call void @llvm.lifetime.end.p0(i64 606416, ptr nonnull %2) #4
  call void @llvm.lifetime.end.p0(i64 606416, ptr nonnull %1) #4
  ret void
}

; Function Attrs: mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.start.p0(i64 immarg, ptr nocapture) #1

; Function Attrs: mustprogress nocallback nofree nounwind willreturn memory(argmem: write)
declare void @llvm.memset.p0.i64(ptr nocapture writeonly, i8, i64, i1 immarg) #2

declare void @fill_init_state(ptr noundef) local_unnamed_addr #3

declare void @put_pixel(i32 noundef, i32 noundef, i32 noundef) local_unnamed_addr #3

; Function Attrs: mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.end.p0(i64 immarg, ptr nocapture) #1

declare i32 @flush() local_unnamed_addr #3

attributes #0 = { nounwind ssp uwtable(sync) "frame-pointer"="non-leaf" "no-trapping-math"="true" "probe-stack"="__chkstk_darwin" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+altnzcv,+bti,+ccdp,+ccidx,+complxnum,+crc,+dit,+dotprod,+flagm,+fp-armv8,+fp16fml,+fptoint,+fullfp16,+jsconv,+lse,+neon,+pauth,+perfmon,+predres,+ras,+rcpc,+rdm,+sb,+sha2,+sha3,+specrestrict,+ssbs,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8.5a,+v8a,+zcm,+zcz" }
attributes #1 = { mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite) }
attributes #2 = { mustprogress nocallback nofree nounwind willreturn memory(argmem: write) }
attributes #3 = { "frame-pointer"="non-leaf" "no-trapping-math"="true" "probe-stack"="__chkstk_darwin" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+altnzcv,+bti,+ccdp,+ccidx,+complxnum,+crc,+dit,+dotprod,+flagm,+fp-armv8,+fp16fml,+fptoint,+fullfp16,+jsconv,+lse,+neon,+pauth,+perfmon,+predres,+ras,+rcpc,+rdm,+sb,+sha2,+sha3,+specrestrict,+ssbs,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8.5a,+v8a,+zcm,+zcz" }
attributes #4 = { nounwind }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 2, !"SDK Version", [2 x i32] [i32 15, i32 5]}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 8, !"PIC Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 1}
!4 = !{i32 7, !"frame-pointer", i32 1}
!5 = !{!"Apple clang version 17.0.0 (clang-1700.0.13.5)"}
!6 = !{!7, !7, i64 0}
!7 = !{!"int", !8, i64 0}
!8 = !{!"omnipotent char", !9, i64 0}
!9 = !{!"Simple C/C++ TBAA"}
