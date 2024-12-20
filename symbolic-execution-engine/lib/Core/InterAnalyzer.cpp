#include "Executor.h"

#include "Context.h"
#include "CoreStats.h"
#include "ExecutionState.h"
#include "ExternalDispatcher.h"
#include "GetElementPtrTypeIterator.h"
#include "ImpliedValue.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "PTree.h"
#include "Searcher.h"
#include "SeedInfo.h"
#include "SpecialFunctionHandler.h"
#include "StatsTracker.h"
#include "TimingSolver.h"
#include "UserSearcher.h"

#include "klee/ADT/KTest.h"
#include "klee/ADT/RNG.h"
#include "klee/Config/Version.h"
#include "klee/Core/Interpreter.h"
#include "klee/Expr/ArrayExprOptimizer.h"
#include "klee/Expr/Assignment.h"
#include "klee/Expr/Expr.h"
#include "klee/Expr/ExprPPrinter.h"
#include "klee/Expr/ExprSMTLIBPrinter.h"
#include "klee/Expr/ExprUtil.h"
#include "klee/Module/Cell.h"
#include "klee/Module/InstructionInfoTable.h"
#include "klee/Module/KCallable.h"
#include "klee/Module/KInstruction.h"
#include "klee/Module/KModule.h"
#include "klee/Solver/Common.h"
#include "klee/Solver/SolverCmdLine.h"
#include "klee/Solver/SolverStats.h"
#include "klee/Statistics/TimerStatIncrementer.h"
#include "klee/Support/Casting.h"
#include "klee/Support/ErrorHandling.h"
#include "klee/Support/FileHandling.h"
#include "klee/Support/FloatEvaluation.h"
#include "klee/Support/ModuleUtil.h"
#include "klee/Support/OptionCategories.h"
#include "klee/System/MemoryUsage.h"
#include "klee/System/Time.h"

#include "llvm/ADT/SmallPtrSet.h"
#include "llvm/ADT/StringExtras.h"
#include "llvm/IR/Attributes.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/InlineAsm.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/IntrinsicInst.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Operator.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/Path.h"
#include "llvm/Support/Process.h"
#if LLVM_VERSION_CODE >= LLVM_VERSION(10, 0)
#include "llvm/Support/TypeSize.h"
#else
typedef unsigned TypeSize;
#endif
#include "llvm/Support/raw_ostream.h"

#include <algorithm>
#include <cassert>
#include <cerrno>
#include <cstring>
#include <cxxabi.h>
#include <fstream>
#include <iomanip>
#include <iosfwd>
#include <limits>
#include <sstream>
#include <string>
#include <sys/mman.h>
#include <vector>

// add sxh
#include "TestInfoRecord.h"
#include "ArchAddressSpaceInfo.h"
#include "klee/Core/InterAnalysis.h"



using namespace klee;



// We test if the pointer pointing to mo1 can pointing to mo2 or partial of mo2.

bool InterAnalysis::canPointToOtherMemoryObject(MemoryObjectV2 &mo1, MemoryObjectV2 &mo2){
    memoryObjectConstruct(mo1);
    for(int ptrOffset=0; i<mo2.size; i++){
        for(locationInMemoryObject lmo : mo1.locations){
            //bool isSatisfied = constraintSolve(lmo.cs, mo1, mo2, ptrOffset);
            if(isSatisfied){
                return true;
                break;
            }else{
                continue;
            }
        }
    }
    
    return false;
}

// Test if the constraint in srcMo can be satified in dstMo in the case they overlap with a certain offset.
// bool constraintSolve(ConstrainsSet &cs, MemoryObjectV2 &srcMo, MemoryObjectV2 &dstMo, usize_t offset){
    
//     // Convert the constraints
//     constrainsConvert

//     //Solve the constraints



//   std::string name = j["dereference location"]["name"];
//   uint64_t relativeOffset = j["dereference location"]["offset"];
//   relativeOffset = offset - relativeOffset;
//   bool isUnderflow = (relativeOffset > offset)? true : false;

//   std::vector<ref<Expr>> constraints;
//   for (auto &constraintJson: j["constraints"]){
//     ref<Expr> constraint = jsontoExpr(state, mo, name, relativeOffset, constraintJson, isUnderflow);
//     if (!constraint){
//       klee_second_test_info("The constaint exceeds the mo range %s: . The second test teminates",
//                             constraintJson.dump(4).c_str());
//       return false;
//     }
//     constraints.push_back(constraint);
//   }

//   bool mayBeTrue = false;
//   for (auto &constraint: constraints){
//     bool success =
//         solver->mayBeTrue(state.constraints, constraint,
//                            mayBeTrue, state.queryMetaData);
//     assert(success && "FIXME: Unhandled solver failure");


//   }
//   return true;
    
// }

MemoryObject* InterAnalysis::memoryObjectConstruct(MemoryObjectV2 &v2Mo){
  
    MemoryObject *mo = NULL;
    mo = memory->allocate(v2Mo.size, isLocal, 1, allocSite,
                          allocationAlignment);
    if (!mo) {
      bindLocal(target, state,
                ConstantExpr::alloc(0, Context::get().getPointerWidth()));
      terminateStateOnError(
        state, "FIX ME: Allocate MO failed",
        StateTerminationType::Ptr);
    } else {
      ObjectState *os = bindObjectInState(state, mo, isLocal);
      os->initializeToZero();
      bindLocal(target, state, mo->getBaseExpr());
    }

  std::string name =
      "V2MoAlloc" + llvm::utostr(++V2allocNameCount); // address->toString();
  klee_debug_message("DEBUG: Memory object V2 alloc name: %s",name.c_str());
  state.addressSpace.record.push_back(mo);

  for (auto location : v2Mo.locations){
    uint64_t size = location.size;
    MemoryObject *newMo = memory->allocate(size, isLocal, ,1, allocSite, allocationAlignment);
    ObjectState *nos = bindObjectInState(state, newMo, isLocal);
    nos->initializeToZero();
    std::string locationName = "locationAlloc" + llvm::utostr(++allocLocationCount);
    executeMakeSymbolic(state, newMo, locationName);
    ref<Expr> value = nos->read(newMo->getOffsetAddress(newMo->getBaseAddress()),location.width);
    ObjectState *wos = state.addressSpace.getWriteable(mo, os);
    wos->write(offset, value);
  }

  return mo;

}