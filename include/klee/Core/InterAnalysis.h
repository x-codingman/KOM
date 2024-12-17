#ifndef KLEE_INTERANALYSIS_H
#define KLEE_INTERANALYSIS_H


#define KLEE_UNITTEST

#include "klee/Expr/Expr.h"
#include "klee/Expr/Constraints.h"

#include <vector>
#include <nlohmann/json.hpp>
namespace klee {
  class ExecutionState;
  class MemoryObject;
  class ObjectState;
  class TimingSolver;
  struct locationInMemoryObject{
        uint64_t offset;
        Expr::Width width;
        ConstraintSet cs;

        bool isWritable;
  };

  struct MemoryObjectV2{
      std::vector<locationInMemoryObject> locations;
      std::string name;
      uint64_t size;
  };
}

#endif