; ModuleID = 'test_api_2.bc'
source_filename = "test_api_2.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.test_structure_2 = type { i32, i32, i32, i32* }

@.str = private unnamed_addr constant [11 x i8] c"test_ptr_2\00", align 1
@.str.1 = private unnamed_addr constant [7 x i8] c"test_b\00", align 1
@.str.2 = private unnamed_addr constant [7 x i8] c"test_c\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 !dbg !7 {
entry:
  %test_ptr_2 = alloca %struct.test_structure_2*, align 8
  %test_b = alloca i32, align 4
  %test_c = alloca i32, align 4
  call void @llvm.dbg.declare(metadata %struct.test_structure_2** %test_ptr_2, metadata !11, metadata !DIExpression()), !dbg !22
  call void @llvm.dbg.declare(metadata i32* %test_b, metadata !23, metadata !DIExpression()), !dbg !24
  call void @llvm.dbg.declare(metadata i32* %test_c, metadata !25, metadata !DIExpression()), !dbg !26
  %0 = bitcast %struct.test_structure_2** %test_ptr_2 to i8*, !dbg !27
  call void @klee_make_symbolic_controllable(i8* %0, i64 8, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str, i64 0, i64 0), i1 zeroext true), !dbg !28
  %1 = bitcast i32* %test_b to i8*, !dbg !29
  call void @klee_make_symbolic_controllable(i8* %1, i64 4, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.1, i64 0, i64 0), i1 zeroext true), !dbg !30
  %2 = bitcast i32* %test_c to i8*, !dbg !31
  call void @klee_make_symbolic_controllable(i8* %2, i64 4, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.2, i64 0, i64 0), i1 zeroext true), !dbg !32
  %3 = load %struct.test_structure_2*, %struct.test_structure_2** %test_ptr_2, align 8, !dbg !33
  %4 = load i32, i32* %test_b, align 4, !dbg !34
  %5 = load i32, i32* %test_c, align 4, !dbg !35
  call void @test_api_2(%struct.test_structure_2* %3, i32 %4, i32 %5), !dbg !36
  ret i32 0, !dbg !37
}

; Function Attrs: nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare dso_local void @klee_make_symbolic_controllable(i8*, i64, i8*, i1 zeroext) #2

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @test_api_2(%struct.test_structure_2* %test_ptr_2, i32 %b, i32 %c) #0 !dbg !38 {
entry:
  %test_ptr_2.addr = alloca %struct.test_structure_2*, align 8
  %b.addr = alloca i32, align 4
  %c.addr = alloca i32, align 4
  store %struct.test_structure_2* %test_ptr_2, %struct.test_structure_2** %test_ptr_2.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.test_structure_2** %test_ptr_2.addr, metadata !41, metadata !DIExpression()), !dbg !42
  store i32 %b, i32* %b.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %b.addr, metadata !43, metadata !DIExpression()), !dbg !44
  store i32 %c, i32* %c.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %c.addr, metadata !45, metadata !DIExpression()), !dbg !46
  %0 = load %struct.test_structure_2*, %struct.test_structure_2** %test_ptr_2.addr, align 8, !dbg !47
  %cmp = icmp ugt %struct.test_structure_2* %0, inttoptr (i64 2415919103 to %struct.test_structure_2*), !dbg !49
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !50

lor.lhs.false:                                    ; preds = %entry
  %1 = load %struct.test_structure_2*, %struct.test_structure_2** %test_ptr_2.addr, align 8, !dbg !51
  %cmp1 = icmp ult %struct.test_structure_2* %1, inttoptr (i64 2147483648 to %struct.test_structure_2*), !dbg !52
  br i1 %cmp1, label %if.then, label %if.end, !dbg !53

if.then:                                          ; preds = %lor.lhs.false, %entry
  %2 = load i32, i32* %b.addr, align 4, !dbg !54
  %3 = load %struct.test_structure_2*, %struct.test_structure_2** %test_ptr_2.addr, align 8, !dbg !56
  %b2 = getelementptr inbounds %struct.test_structure_2, %struct.test_structure_2* %3, i32 0, i32 1, !dbg !57
  store i32 %2, i32* %b2, align 4, !dbg !58
  %4 = load i32, i32* %c.addr, align 4, !dbg !59
  %5 = load %struct.test_structure_2*, %struct.test_structure_2** %test_ptr_2.addr, align 8, !dbg !60
  %c3 = getelementptr inbounds %struct.test_structure_2, %struct.test_structure_2* %5, i32 0, i32 2, !dbg !61
  store i32 %4, i32* %c3, align 8, !dbg !62
  br label %if.end, !dbg !63

if.end:                                           ; preds = %if.then, %lor.lhs.false
  ret void, !dbg !64
}

attributes #0 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone speculatable willreturn }
attributes #2 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!3, !4, !5}
!llvm.ident = !{!6}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 11.0.0 (https://github.com/llvm/llvm-project.git 60a25202a7dd1e00067fcfce512086ebf3788537)", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !2, splitDebugInlining: false, nameTableKind: None)
!1 = !DIFile(filename: "test_api_2.c", directory: "/home/klee/klee_test/threadx_test/evaluation/test_files")
!2 = !{}
!3 = !{i32 7, !"Dwarf Version", i32 4}
!4 = !{i32 2, !"Debug Info Version", i32 3}
!5 = !{i32 1, !"wchar_size", i32 4}
!6 = !{!"clang version 11.0.0 (https://github.com/llvm/llvm-project.git 60a25202a7dd1e00067fcfce512086ebf3788537)"}
!7 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 7, type: !8, scopeLine: 7, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !2)
!8 = !DISubroutineType(types: !9)
!9 = !{!10}
!10 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!11 = !DILocalVariable(name: "test_ptr_2", scope: !7, file: !1, line: 8, type: !12)
!12 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !13, size: 64)
!13 = !DIDerivedType(tag: DW_TAG_typedef, name: "test_structure_2_t", file: !14, line: 17, baseType: !15)
!14 = !DIFile(filename: "./test_api.h", directory: "/home/klee/klee_test/threadx_test/evaluation/test_files")
!15 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "test_structure_2", file: !14, line: 12, size: 192, elements: !16)
!16 = !{!17, !18, !19, !20}
!17 = !DIDerivedType(tag: DW_TAG_member, name: "a", scope: !15, file: !14, line: 13, baseType: !10, size: 32)
!18 = !DIDerivedType(tag: DW_TAG_member, name: "b", scope: !15, file: !14, line: 14, baseType: !10, size: 32, offset: 32)
!19 = !DIDerivedType(tag: DW_TAG_member, name: "c", scope: !15, file: !14, line: 15, baseType: !10, size: 32, offset: 64)
!20 = !DIDerivedType(tag: DW_TAG_member, name: "p", scope: !15, file: !14, line: 16, baseType: !21, size: 64, offset: 128)
!21 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !10, size: 64)
!22 = !DILocation(line: 8, column: 27, scope: !7)
!23 = !DILocalVariable(name: "test_b", scope: !7, file: !1, line: 9, type: !10)
!24 = !DILocation(line: 9, column: 9, scope: !7)
!25 = !DILocalVariable(name: "test_c", scope: !7, file: !1, line: 9, type: !10)
!26 = !DILocation(line: 9, column: 16, scope: !7)
!27 = !DILocation(line: 10, column: 37, scope: !7)
!28 = !DILocation(line: 10, column: 5, scope: !7)
!29 = !DILocation(line: 11, column: 37, scope: !7)
!30 = !DILocation(line: 11, column: 5, scope: !7)
!31 = !DILocation(line: 12, column: 37, scope: !7)
!32 = !DILocation(line: 12, column: 5, scope: !7)
!33 = !DILocation(line: 13, column: 16, scope: !7)
!34 = !DILocation(line: 13, column: 27, scope: !7)
!35 = !DILocation(line: 13, column: 34, scope: !7)
!36 = !DILocation(line: 13, column: 5, scope: !7)
!37 = !DILocation(line: 14, column: 1, scope: !7)
!38 = distinct !DISubprogram(name: "test_api_2", scope: !1, file: !1, line: 16, type: !39, scopeLine: 16, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !2)
!39 = !DISubroutineType(types: !40)
!40 = !{null, !12, !10, !10}
!41 = !DILocalVariable(name: "test_ptr_2", arg: 1, scope: !38, file: !1, line: 16, type: !12)
!42 = !DILocation(line: 16, column: 38, scope: !38)
!43 = !DILocalVariable(name: "b", arg: 2, scope: !38, file: !1, line: 16, type: !10)
!44 = !DILocation(line: 16, column: 54, scope: !38)
!45 = !DILocalVariable(name: "c", arg: 3, scope: !38, file: !1, line: 16, type: !10)
!46 = !DILocation(line: 16, column: 61, scope: !38)
!47 = !DILocation(line: 17, column: 8, scope: !48)
!48 = distinct !DILexicalBlock(scope: !38, file: !1, line: 17, column: 8)
!49 = !DILocation(line: 17, column: 19, scope: !48)
!50 = !DILocation(line: 17, column: 50, scope: !48)
!51 = !DILocation(line: 17, column: 53, scope: !48)
!52 = !DILocation(line: 17, column: 64, scope: !48)
!53 = !DILocation(line: 17, column: 8, scope: !38)
!54 = !DILocation(line: 18, column: 25, scope: !55)
!55 = distinct !DILexicalBlock(scope: !48, file: !1, line: 17, column: 97)
!56 = !DILocation(line: 18, column: 9, scope: !55)
!57 = !DILocation(line: 18, column: 21, scope: !55)
!58 = !DILocation(line: 18, column: 23, scope: !55)
!59 = !DILocation(line: 19, column: 25, scope: !55)
!60 = !DILocation(line: 19, column: 9, scope: !55)
!61 = !DILocation(line: 19, column: 21, scope: !55)
!62 = !DILocation(line: 19, column: 23, scope: !55)
!63 = !DILocation(line: 20, column: 5, scope: !55)
!64 = !DILocation(line: 21, column: 1, scope: !38)
