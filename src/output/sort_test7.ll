; ModuleID = 'llvm-link'
source_filename = "llvm-link"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%struct.timeval = type { i64, i64 }

@n = global i32 0
@llvm.global_ctors = appending global [1 x { i32, ptr, ptr }] [{ i32, ptr, ptr } { i32 65535, ptr @before_main, ptr null }]
@llvm.global_dtors = appending global [1 x { i32, ptr, ptr }] [{ i32, ptr, ptr } { i32 65535, ptr @after_main, ptr null }]
@.str = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.str.1 = private unnamed_addr constant [3 x i8] c"%c\00", align 1
@.str.2 = private unnamed_addr constant [4 x i8] c"%d:\00", align 1
@.str.3 = private unnamed_addr constant [4 x i8] c" %d\00", align 1
@.str.4 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@_sysy_us = dso_local global [1024 x i32] zeroinitializer, align 16
@_sysy_s = dso_local global [1024 x i32] zeroinitializer, align 16
@_sysy_m = dso_local global [1024 x i32] zeroinitializer, align 16
@_sysy_h = dso_local global [1024 x i32] zeroinitializer, align 16
@_sysy_idx = dso_local global i32 0, align 4
@stderr = external global ptr, align 8
@.str.5 = private unnamed_addr constant [35 x i8] c"Timer@%04d-%04d: %dH-%dM-%dS-%dus\0A\00", align 1
@_sysy_l1 = dso_local global [1024 x i32] zeroinitializer, align 16
@_sysy_l2 = dso_local global [1024 x i32] zeroinitializer, align 16
@.str.6 = private unnamed_addr constant [25 x i8] c"TOTAL: %dH-%dM-%dS-%dus\0A\00", align 1
@_sysy_start = dso_local global %struct.timeval zeroinitializer, align 8
@_sysy_end = dso_local global %struct.timeval zeroinitializer, align 8

define i32 @Merge(ptr %r100, i32 %r101, i32 %r103, i32 %r105) {
Merge:
  %r102 = alloca i32, align 4
  %r148 = alloca i32, align 4
  store i32 %r101, ptr %r102, align 4
  %r104 = alloca i32, align 4
  store i32 %r103, ptr %r104, align 4
  %r106 = alloca i32, align 4
  store i32 %r105, ptr %r106, align 4
  %r107 = alloca i32, align 4
  %r108 = load i32, ptr %r104, align 4
  %r109 = load i32, ptr %r102, align 4
  %r110 = sub i32 %r108, %r109
  %r111 = add i32 %r110, 1
  store i32 %r111, ptr %r107, align 4
  %r112 = alloca i32, align 4
  %r113 = load i32, ptr %r106, align 4
  %r114 = load i32, ptr %r104, align 4
  %r115 = sub i32 %r113, %r114
  store i32 %r115, ptr %r112, align 4
  %r116 = alloca [10 x i32], align 4
  %r117 = alloca [10 x i32], align 4
  %r118 = alloca i32, align 4
  store i32 0, ptr %r118, align 4
  %r119 = alloca i32, align 4
  store i32 0, ptr %r119, align 4
  %r120 = alloca i32, align 4
  br label %bb1

bb1:                                              ; preds = %bb2, %Merge
  %r121 = load i32, ptr %r118, align 4
  %r122 = load i32, ptr %r107, align 4
  %r123 = icmp slt i32 %r121, %r122
  br i1 %r123, label %bb2, label %bb3

bb2:                                              ; preds = %bb1
  %r124 = load i32, ptr %r118, align 4
  %r125 = load i32, ptr %r102, align 4
  %r126 = add i32 %r124, %r125
  store i32 %r126, ptr %r120, align 4
  %r128 = load i32, ptr %r120, align 4
  %r127 = getelementptr [10 x i32], ptr %r100, i32 0, i32 %r128
  %r129 = load i32, ptr %r127, align 4
  %r131 = load i32, ptr %r118, align 4
  %r130 = getelementptr [10 x i32], ptr %r116, i32 0, i32 %r131
  store i32 %r129, ptr %r130, align 4
  %r132 = load i32, ptr %r118, align 4
  %r133 = add i32 %r132, 1
  store i32 %r133, ptr %r118, align 4
  br label %bb1

bb3:                                              ; preds = %bb1
  br label %bb4

bb4:                                              ; preds = %bb5, %bb3
  %r134 = load i32, ptr %r119, align 4
  %r135 = load i32, ptr %r112, align 4
  %r136 = icmp slt i32 %r134, %r135
  br i1 %r136, label %bb5, label %bb6

bb5:                                              ; preds = %bb4
  %r137 = load i32, ptr %r119, align 4
  %r138 = load i32, ptr %r104, align 4
  %r139 = add i32 %r137, %r138
  %r140 = add i32 %r139, 1
  store i32 %r140, ptr %r120, align 4
  %r142 = load i32, ptr %r120, align 4
  %r141 = getelementptr [10 x i32], ptr %r100, i32 0, i32 %r142
  %r143 = load i32, ptr %r141, align 4
  %r145 = load i32, ptr %r119, align 4
  %r144 = getelementptr [10 x i32], ptr %r117, i32 0, i32 %r145
  store i32 %r143, ptr %r144, align 4
  %r146 = load i32, ptr %r119, align 4
  %r147 = add i32 %r146, 1
  store i32 %r147, ptr %r119, align 4
  br label %bb4

bb6:                                              ; preds = %bb4
  store i32 0, ptr %r118, align 4
  store i32 0, ptr %r119, align 4
  %r149 = load i32, ptr %r102, align 4
  store i32 %r149, ptr %r148, align 4
  br label %bb7

bb7:                                              ; preds = %bb13, %bb6
  %r151 = load i32, ptr %r118, align 4
  %r152 = load i32, ptr %r107, align 4
  %r153 = icmp ne i32 %r151, %r152
  br i1 %r153, label %bb10, label %bb9

bb10:                                             ; preds = %bb7
  %r154 = load i32, ptr %r119, align 4
  %r155 = load i32, ptr %r112, align 4
  %r156 = icmp ne i32 %r154, %r155
  br i1 %r156, label %bb8, label %bb9

bb8:                                              ; preds = %bb10
  %r158 = load i32, ptr %r118, align 4
  %r157 = getelementptr [10 x i32], ptr %r116, i32 0, i32 %r158
  %r159 = load i32, ptr %r157, align 4
  %r161 = load i32, ptr %r119, align 4
  %r160 = getelementptr [10 x i32], ptr %r117, i32 0, i32 %r161
  %r162 = load i32, ptr %r160, align 4
  %r163 = add i32 %r162, 1
  %r164 = icmp slt i32 %r159, %r163
  br i1 %r164, label %bb11, label %bb12

bb11:                                             ; preds = %bb8
  %r166 = load i32, ptr %r118, align 4
  %r165 = getelementptr [10 x i32], ptr %r116, i32 0, i32 %r166
  %r167 = load i32, ptr %r165, align 4
  %r169 = load i32, ptr %r148, align 4
  %r168 = getelementptr [10 x i32], ptr %r100, i32 0, i32 %r169
  store i32 %r167, ptr %r168, align 4
  %r170 = load i32, ptr %r148, align 4
  %r171 = add i32 %r170, 1
  store i32 %r171, ptr %r148, align 4
  %r172 = load i32, ptr %r118, align 4
  %r173 = add i32 %r172, 1
  store i32 %r173, ptr %r118, align 4
  br label %bb13

bb12:                                             ; preds = %bb8
  %r175 = load i32, ptr %r119, align 4
  %r174 = getelementptr [10 x i32], ptr %r117, i32 0, i32 %r175
  %r176 = load i32, ptr %r174, align 4
  %r178 = load i32, ptr %r148, align 4
  %r177 = getelementptr [10 x i32], ptr %r100, i32 0, i32 %r178
  store i32 %r176, ptr %r177, align 4
  %r179 = load i32, ptr %r148, align 4
  %r180 = add i32 %r179, 1
  store i32 %r180, ptr %r148, align 4
  %r181 = load i32, ptr %r119, align 4
  %r182 = add i32 %r181, 1
  store i32 %r182, ptr %r119, align 4
  br label %bb13

bb13:                                             ; preds = %bb12, %bb11
  br label %bb7

bb9:                                              ; preds = %bb10, %bb7
  br label %bb14

bb14:                                             ; preds = %bb15, %bb9
  %r183 = load i32, ptr %r118, align 4
  %r184 = load i32, ptr %r107, align 4
  %r185 = icmp slt i32 %r183, %r184
  br i1 %r185, label %bb15, label %bb16

bb15:                                             ; preds = %bb14
  %r187 = load i32, ptr %r118, align 4
  %r186 = getelementptr [10 x i32], ptr %r116, i32 0, i32 %r187
  %r188 = load i32, ptr %r186, align 4
  %r190 = load i32, ptr %r148, align 4
  %r189 = getelementptr [10 x i32], ptr %r100, i32 0, i32 %r190
  store i32 %r188, ptr %r189, align 4
  %r191 = load i32, ptr %r148, align 4
  %r192 = add i32 %r191, 1
  store i32 %r192, ptr %r148, align 4
  %r193 = load i32, ptr %r118, align 4
  %r194 = add i32 %r193, 1
  store i32 %r194, ptr %r118, align 4
  br label %bb14

bb16:                                             ; preds = %bb14
  br label %bb17

bb17:                                             ; preds = %bb18, %bb16
  %r195 = load i32, ptr %r119, align 4
  %r196 = load i32, ptr %r112, align 4
  %r197 = icmp slt i32 %r195, %r196
  br i1 %r197, label %bb18, label %bb19

bb18:                                             ; preds = %bb17
  %r199 = load i32, ptr %r119, align 4
  %r198 = getelementptr [10 x i32], ptr %r117, i32 0, i32 %r199
  %r200 = load i32, ptr %r198, align 4
  %r202 = load i32, ptr %r148, align 4
  %r201 = getelementptr [10 x i32], ptr %r100, i32 0, i32 %r202
  store i32 %r200, ptr %r201, align 4
  %r203 = load i32, ptr %r148, align 4
  %r204 = add i32 %r203, 1
  store i32 %r204, ptr %r148, align 4
  %r205 = load i32, ptr %r119, align 4
  %r206 = add i32 %r205, 1
  store i32 %r206, ptr %r119, align 4
  br label %bb17

bb19:                                             ; preds = %bb17
  ret i32 0
}

define i32 @MergeSort(ptr %r207, i32 %r208, i32 %r210) {
MergeSort:
  %r209 = alloca i32, align 4
  %r220 = alloca i32, align 4
  %r215 = alloca i32, align 4
  store i32 %r208, ptr %r209, align 4
  %r211 = alloca i32, align 4
  store i32 %r210, ptr %r211, align 4
  %r212 = load i32, ptr %r209, align 4
  %r213 = load i32, ptr %r211, align 4
  %r214 = icmp slt i32 %r212, %r213
  br i1 %r214, label %bb20, label %bb21

bb20:                                             ; preds = %MergeSort
  %r216 = load i32, ptr %r209, align 4
  %r217 = load i32, ptr %r211, align 4
  %r218 = add i32 %r216, %r217
  %r219 = sdiv i32 %r218, 2
  store i32 %r219, ptr %r215, align 4
  %r221 = load i32, ptr %r209, align 4
  %r222 = load i32, ptr %r215, align 4
  %r223 = call i32 @MergeSort(ptr %r207, i32 %r221, i32 %r222)
  store i32 %r223, ptr %r220, align 4
  %r224 = load i32, ptr %r215, align 4
  %r225 = add i32 %r224, 1
  store i32 %r225, ptr %r220, align 4
  %r226 = load i32, ptr %r220, align 4
  %r227 = load i32, ptr %r211, align 4
  %r228 = call i32 @MergeSort(ptr %r207, i32 %r226, i32 %r227)
  store i32 %r228, ptr %r220, align 4
  %r229 = load i32, ptr %r209, align 4
  %r230 = load i32, ptr %r215, align 4
  %r231 = load i32, ptr %r211, align 4
  %r232 = call i32 @Merge(ptr %r207, i32 %r229, i32 %r230, i32 %r231)
  store i32 %r232, ptr %r220, align 4
  br label %bb22

bb21:                                             ; preds = %MergeSort
  br label %bb22

bb22:                                             ; preds = %bb21, %bb20
  ret i32 0
}

define i32 @main() {
main:
  store i32 10, ptr @n, align 4
  %r233 = alloca [10 x i32], align 4
  %r234 = getelementptr [10 x i32], ptr %r233, i32 0, i32 0
  store i32 4, ptr %r234, align 4
  %r235 = getelementptr [10 x i32], ptr %r233, i32 0, i32 1
  store i32 3, ptr %r235, align 4
  %r236 = getelementptr [10 x i32], ptr %r233, i32 0, i32 2
  store i32 9, ptr %r236, align 4
  %r237 = getelementptr [10 x i32], ptr %r233, i32 0, i32 3
  store i32 2, ptr %r237, align 4
  %r238 = getelementptr [10 x i32], ptr %r233, i32 0, i32 4
  store i32 0, ptr %r238, align 4
  %r239 = getelementptr [10 x i32], ptr %r233, i32 0, i32 5
  store i32 1, ptr %r239, align 4
  %r240 = getelementptr [10 x i32], ptr %r233, i32 0, i32 6
  store i32 6, ptr %r240, align 4
  %r241 = getelementptr [10 x i32], ptr %r233, i32 0, i32 7
  store i32 5, ptr %r241, align 4
  %r242 = getelementptr [10 x i32], ptr %r233, i32 0, i32 8
  store i32 7, ptr %r242, align 4
  %r243 = getelementptr [10 x i32], ptr %r233, i32 0, i32 9
  store i32 8, ptr %r243, align 4
  %r244 = alloca i32, align 4
  store i32 0, ptr %r244, align 4
  %r245 = alloca i32, align 4
  %r246 = load i32, ptr @n, align 4
  %r247 = sub i32 %r246, 1
  store i32 %r247, ptr %r245, align 4
  %r248 = load i32, ptr %r244, align 4
  %r249 = load i32, ptr %r245, align 4
  %r250 = call i32 @MergeSort(ptr %r233, i32 %r248, i32 %r249)
  store i32 %r250, ptr %r244, align 4
  br label %bb23

bb23:                                             ; preds = %bb24, %main
  %r251 = load i32, ptr %r244, align 4
  %r252 = load i32, ptr @n, align 4
  %r253 = icmp slt i32 %r251, %r252
  br i1 %r253, label %bb24, label %bb25

bb24:                                             ; preds = %bb23
  %r255 = load i32, ptr %r244, align 4
  %r254 = getelementptr [10 x i32], ptr %r233, i32 0, i32 %r255
  %r256 = load i32, ptr %r254, align 4
  store i32 %r256, ptr %r245, align 4
  %r257 = load i32, ptr %r245, align 4
  call void @putint(i32 %r257)
  store i32 10, ptr %r245, align 4
  %r258 = load i32, ptr %r245, align 4
  call void @putch(i32 %r258)
  %r259 = load i32, ptr %r244, align 4
  %r260 = add i32 %r259, 1
  store i32 %r260, ptr %r244, align 4
  br label %bb23

bb25:                                             ; preds = %bb23
  ret i32 0
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @before_main() #0 {
  %1 = alloca i32, align 4
  store i32 0, ptr %1, align 4
  br label %2

2:                                                ; preds = %18, %0
  %3 = load i32, ptr %1, align 4
  %4 = icmp slt i32 %3, 1024
  br i1 %4, label %5, label %21

5:                                                ; preds = %2
  %6 = load i32, ptr %1, align 4
  %7 = sext i32 %6 to i64
  %8 = getelementptr inbounds [1024 x i32], ptr @_sysy_us, i64 0, i64 %7
  store i32 0, ptr %8, align 4
  %9 = load i32, ptr %1, align 4
  %10 = sext i32 %9 to i64
  %11 = getelementptr inbounds [1024 x i32], ptr @_sysy_s, i64 0, i64 %10
  store i32 0, ptr %11, align 4
  %12 = load i32, ptr %1, align 4
  %13 = sext i32 %12 to i64
  %14 = getelementptr inbounds [1024 x i32], ptr @_sysy_m, i64 0, i64 %13
  store i32 0, ptr %14, align 4
  %15 = load i32, ptr %1, align 4
  %16 = sext i32 %15 to i64
  %17 = getelementptr inbounds [1024 x i32], ptr @_sysy_h, i64 0, i64 %16
  store i32 0, ptr %17, align 4
  br label %18

18:                                               ; preds = %5
  %19 = load i32, ptr %1, align 4
  %20 = add nsw i32 %19, 1
  store i32 %20, ptr %1, align 4
  br label %2, !llvm.loop !6

21:                                               ; preds = %2
  store i32 1, ptr @_sysy_idx, align 4
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @after_main() #0 {
  %1 = alloca i32, align 4
  store i32 1, ptr %1, align 4
  br label %2

2:                                                ; preds = %63, %0
  %3 = load i32, ptr %1, align 4
  %4 = load i32, ptr @_sysy_idx, align 4
  %5 = icmp slt i32 %3, %4
  br i1 %5, label %6, label %66

6:                                                ; preds = %2
  %7 = load ptr, ptr @stderr, align 8
  %8 = load i32, ptr %1, align 4
  %9 = sext i32 %8 to i64
  %10 = getelementptr inbounds [1024 x i32], ptr @_sysy_l1, i64 0, i64 %9
  %11 = load i32, ptr %10, align 4
  %12 = load i32, ptr %1, align 4
  %13 = sext i32 %12 to i64
  %14 = getelementptr inbounds [1024 x i32], ptr @_sysy_l2, i64 0, i64 %13
  %15 = load i32, ptr %14, align 4
  %16 = load i32, ptr %1, align 4
  %17 = sext i32 %16 to i64
  %18 = getelementptr inbounds [1024 x i32], ptr @_sysy_h, i64 0, i64 %17
  %19 = load i32, ptr %18, align 4
  %20 = load i32, ptr %1, align 4
  %21 = sext i32 %20 to i64
  %22 = getelementptr inbounds [1024 x i32], ptr @_sysy_m, i64 0, i64 %21
  %23 = load i32, ptr %22, align 4
  %24 = load i32, ptr %1, align 4
  %25 = sext i32 %24 to i64
  %26 = getelementptr inbounds [1024 x i32], ptr @_sysy_s, i64 0, i64 %25
  %27 = load i32, ptr %26, align 4
  %28 = load i32, ptr %1, align 4
  %29 = sext i32 %28 to i64
  %30 = getelementptr inbounds [1024 x i32], ptr @_sysy_us, i64 0, i64 %29
  %31 = load i32, ptr %30, align 4
  %32 = call i32 (ptr, ptr, ...) @fprintf(ptr noundef %7, ptr noundef @.str.5, i32 noundef %11, i32 noundef %15, i32 noundef %19, i32 noundef %23, i32 noundef %27, i32 noundef %31)
  %33 = load i32, ptr %1, align 4
  %34 = sext i32 %33 to i64
  %35 = getelementptr inbounds [1024 x i32], ptr @_sysy_us, i64 0, i64 %34
  %36 = load i32, ptr %35, align 4
  %37 = load i32, ptr @_sysy_us, align 16
  %38 = add nsw i32 %37, %36
  store i32 %38, ptr @_sysy_us, align 16
  %39 = load i32, ptr %1, align 4
  %40 = sext i32 %39 to i64
  %41 = getelementptr inbounds [1024 x i32], ptr @_sysy_s, i64 0, i64 %40
  %42 = load i32, ptr %41, align 4
  %43 = load i32, ptr @_sysy_s, align 16
  %44 = add nsw i32 %43, %42
  store i32 %44, ptr @_sysy_s, align 16
  %45 = load i32, ptr @_sysy_us, align 16
  %46 = srem i32 %45, 1000000
  store i32 %46, ptr @_sysy_us, align 16
  %47 = load i32, ptr %1, align 4
  %48 = sext i32 %47 to i64
  %49 = getelementptr inbounds [1024 x i32], ptr @_sysy_m, i64 0, i64 %48
  %50 = load i32, ptr %49, align 4
  %51 = load i32, ptr @_sysy_m, align 16
  %52 = add nsw i32 %51, %50
  store i32 %52, ptr @_sysy_m, align 16
  %53 = load i32, ptr @_sysy_s, align 16
  %54 = srem i32 %53, 60
  store i32 %54, ptr @_sysy_s, align 16
  %55 = load i32, ptr %1, align 4
  %56 = sext i32 %55 to i64
  %57 = getelementptr inbounds [1024 x i32], ptr @_sysy_h, i64 0, i64 %56
  %58 = load i32, ptr %57, align 4
  %59 = load i32, ptr @_sysy_h, align 16
  %60 = add nsw i32 %59, %58
  store i32 %60, ptr @_sysy_h, align 16
  %61 = load i32, ptr @_sysy_m, align 16
  %62 = srem i32 %61, 60
  store i32 %62, ptr @_sysy_m, align 16
  br label %63

63:                                               ; preds = %6
  %64 = load i32, ptr %1, align 4
  %65 = add nsw i32 %64, 1
  store i32 %65, ptr %1, align 4
  br label %2, !llvm.loop !8

66:                                               ; preds = %2
  %67 = load ptr, ptr @stderr, align 8
  %68 = load i32, ptr @_sysy_h, align 16
  %69 = load i32, ptr @_sysy_m, align 16
  %70 = load i32, ptr @_sysy_s, align 16
  %71 = load i32, ptr @_sysy_us, align 16
  %72 = call i32 (ptr, ptr, ...) @fprintf(ptr noundef %67, ptr noundef @.str.6, i32 noundef %68, i32 noundef %69, i32 noundef %70, i32 noundef %71)
  ret void
}

declare i32 @fprintf(ptr noundef, ptr noundef, ...) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @getint() #0 {
  %1 = alloca i32, align 4
  %2 = call i32 (ptr, ...) @__isoc99_scanf(ptr noundef @.str, ptr noundef %1)
  %3 = load i32, ptr %1, align 4
  ret i32 %3
}

declare i32 @__isoc99_scanf(ptr noundef, ...) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @getch() #0 {
  %1 = alloca i8, align 1
  %2 = call i32 (ptr, ...) @__isoc99_scanf(ptr noundef @.str.1, ptr noundef %1)
  %3 = load i8, ptr %1, align 1
  %4 = sext i8 %3 to i32
  ret i32 %4
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @getarray(ptr noundef %0) #0 {
  %2 = alloca ptr, align 8
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  store ptr %0, ptr %2, align 8
  %5 = call i32 (ptr, ...) @__isoc99_scanf(ptr noundef @.str, ptr noundef %3)
  store i32 0, ptr %4, align 4
  br label %6

6:                                                ; preds = %16, %1
  %7 = load i32, ptr %4, align 4
  %8 = load i32, ptr %3, align 4
  %9 = icmp slt i32 %7, %8
  br i1 %9, label %10, label %19

10:                                               ; preds = %6
  %11 = load ptr, ptr %2, align 8
  %12 = load i32, ptr %4, align 4
  %13 = sext i32 %12 to i64
  %14 = getelementptr inbounds i32, ptr %11, i64 %13
  %15 = call i32 (ptr, ...) @__isoc99_scanf(ptr noundef @.str, ptr noundef %14)
  br label %16

16:                                               ; preds = %10
  %17 = load i32, ptr %4, align 4
  %18 = add nsw i32 %17, 1
  store i32 %18, ptr %4, align 4
  br label %6, !llvm.loop !9

19:                                               ; preds = %6
  %20 = load i32, ptr %3, align 4
  ret i32 %20
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @putint(i32 noundef %0) #0 {
  %2 = alloca i32, align 4
  store i32 %0, ptr %2, align 4
  %3 = load i32, ptr %2, align 4
  %4 = call i32 (ptr, ...) @printf(ptr noundef @.str, i32 noundef %3)
  ret void
}

declare i32 @printf(ptr noundef, ...) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @putch(i32 noundef %0) #0 {
  %2 = alloca i32, align 4
  store i32 %0, ptr %2, align 4
  %3 = load i32, ptr %2, align 4
  %4 = call i32 (ptr, ...) @printf(ptr noundef @.str.1, i32 noundef %3)
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @putarray(i32 noundef %0, ptr noundef %1) #0 {
  %3 = alloca i32, align 4
  %4 = alloca ptr, align 8
  %5 = alloca i32, align 4
  store i32 %0, ptr %3, align 4
  store ptr %1, ptr %4, align 8
  %6 = load i32, ptr %3, align 4
  %7 = call i32 (ptr, ...) @printf(ptr noundef @.str.2, i32 noundef %6)
  store i32 0, ptr %5, align 4
  br label %8

8:                                                ; preds = %19, %2
  %9 = load i32, ptr %5, align 4
  %10 = load i32, ptr %3, align 4
  %11 = icmp slt i32 %9, %10
  br i1 %11, label %12, label %22

12:                                               ; preds = %8
  %13 = load ptr, ptr %4, align 8
  %14 = load i32, ptr %5, align 4
  %15 = sext i32 %14 to i64
  %16 = getelementptr inbounds i32, ptr %13, i64 %15
  %17 = load i32, ptr %16, align 4
  %18 = call i32 (ptr, ...) @printf(ptr noundef @.str.3, i32 noundef %17)
  br label %19

19:                                               ; preds = %12
  %20 = load i32, ptr %5, align 4
  %21 = add nsw i32 %20, 1
  store i32 %21, ptr %5, align 4
  br label %8, !llvm.loop !10

22:                                               ; preds = %8
  %23 = call i32 (ptr, ...) @printf(ptr noundef @.str.4)
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @_sysy_starttime(i32 noundef %0) #0 {
  %2 = alloca i32, align 4
  store i32 %0, ptr %2, align 4
  %3 = load i32, ptr %2, align 4
  %4 = load i32, ptr @_sysy_idx, align 4
  %5 = sext i32 %4 to i64
  %6 = getelementptr inbounds [1024 x i32], ptr @_sysy_l1, i64 0, i64 %5
  store i32 %3, ptr %6, align 4
  %7 = call i32 @gettimeofday(ptr noundef @_sysy_start, ptr noundef null) #3
  ret void
}

; Function Attrs: nounwind
declare i32 @gettimeofday(ptr noundef, ptr noundef) #2

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @_sysy_stoptime(i32 noundef %0) #0 {
  %2 = alloca i32, align 4
  store i32 %0, ptr %2, align 4
  %3 = call i32 @gettimeofday(ptr noundef @_sysy_end, ptr noundef null) #3
  %4 = load i32, ptr %2, align 4
  %5 = load i32, ptr @_sysy_idx, align 4
  %6 = sext i32 %5 to i64
  %7 = getelementptr inbounds [1024 x i32], ptr @_sysy_l2, i64 0, i64 %6
  store i32 %4, ptr %7, align 4
  %8 = load i64, ptr @_sysy_end, align 8
  %9 = load i64, ptr @_sysy_start, align 8
  %10 = sub nsw i64 %8, %9
  %11 = mul nsw i64 1000000, %10
  %12 = load i64, ptr getelementptr inbounds (%struct.timeval, ptr @_sysy_end, i32 0, i32 1), align 8
  %13 = add nsw i64 %11, %12
  %14 = load i64, ptr getelementptr inbounds (%struct.timeval, ptr @_sysy_start, i32 0, i32 1), align 8
  %15 = sub nsw i64 %13, %14
  %16 = load i32, ptr @_sysy_idx, align 4
  %17 = sext i32 %16 to i64
  %18 = getelementptr inbounds [1024 x i32], ptr @_sysy_us, i64 0, i64 %17
  %19 = load i32, ptr %18, align 4
  %20 = sext i32 %19 to i64
  %21 = add nsw i64 %20, %15
  %22 = trunc i64 %21 to i32
  store i32 %22, ptr %18, align 4
  %23 = load i32, ptr @_sysy_idx, align 4
  %24 = sext i32 %23 to i64
  %25 = getelementptr inbounds [1024 x i32], ptr @_sysy_us, i64 0, i64 %24
  %26 = load i32, ptr %25, align 4
  %27 = sdiv i32 %26, 1000000
  %28 = load i32, ptr @_sysy_idx, align 4
  %29 = sext i32 %28 to i64
  %30 = getelementptr inbounds [1024 x i32], ptr @_sysy_s, i64 0, i64 %29
  %31 = load i32, ptr %30, align 4
  %32 = add nsw i32 %31, %27
  store i32 %32, ptr %30, align 4
  %33 = load i32, ptr @_sysy_idx, align 4
  %34 = sext i32 %33 to i64
  %35 = getelementptr inbounds [1024 x i32], ptr @_sysy_us, i64 0, i64 %34
  %36 = load i32, ptr %35, align 4
  %37 = srem i32 %36, 1000000
  store i32 %37, ptr %35, align 4
  %38 = load i32, ptr @_sysy_idx, align 4
  %39 = sext i32 %38 to i64
  %40 = getelementptr inbounds [1024 x i32], ptr @_sysy_s, i64 0, i64 %39
  %41 = load i32, ptr %40, align 4
  %42 = sdiv i32 %41, 60
  %43 = load i32, ptr @_sysy_idx, align 4
  %44 = sext i32 %43 to i64
  %45 = getelementptr inbounds [1024 x i32], ptr @_sysy_m, i64 0, i64 %44
  %46 = load i32, ptr %45, align 4
  %47 = add nsw i32 %46, %42
  store i32 %47, ptr %45, align 4
  %48 = load i32, ptr @_sysy_idx, align 4
  %49 = sext i32 %48 to i64
  %50 = getelementptr inbounds [1024 x i32], ptr @_sysy_s, i64 0, i64 %49
  %51 = load i32, ptr %50, align 4
  %52 = srem i32 %51, 60
  store i32 %52, ptr %50, align 4
  %53 = load i32, ptr @_sysy_idx, align 4
  %54 = sext i32 %53 to i64
  %55 = getelementptr inbounds [1024 x i32], ptr @_sysy_m, i64 0, i64 %54
  %56 = load i32, ptr %55, align 4
  %57 = sdiv i32 %56, 60
  %58 = load i32, ptr @_sysy_idx, align 4
  %59 = sext i32 %58 to i64
  %60 = getelementptr inbounds [1024 x i32], ptr @_sysy_h, i64 0, i64 %59
  %61 = load i32, ptr %60, align 4
  %62 = add nsw i32 %61, %57
  store i32 %62, ptr %60, align 4
  %63 = load i32, ptr @_sysy_idx, align 4
  %64 = sext i32 %63 to i64
  %65 = getelementptr inbounds [1024 x i32], ptr @_sysy_m, i64 0, i64 %64
  %66 = load i32, ptr %65, align 4
  %67 = srem i32 %66, 60
  store i32 %67, ptr %65, align 4
  %68 = load i32, ptr @_sysy_idx, align 4
  %69 = add nsw i32 %68, 1
  store i32 %69, ptr @_sysy_idx, align 4
  ret void
}

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { nounwind "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { nounwind }

!llvm.ident = !{!0}
!llvm.module.flags = !{!1, !2, !3, !4, !5}

!0 = !{!"Ubuntu clang version 14.0.0-1ubuntu1.1"}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 8, !"PIC Level", i32 2}
!3 = !{i32 7, !"PIE Level", i32 2}
!4 = !{i32 7, !"uwtable", i32 1}
!5 = !{i32 7, !"frame-pointer", i32 2}
!6 = distinct !{!6, !7}
!7 = !{!"llvm.loop.mustprogress"}
!8 = distinct !{!8, !7}
!9 = distinct !{!9, !7}
!10 = distinct !{!10, !7}
