#ifndef SOLUTION_H_
#define SOLUTION_H_

#include <cstdint>
#include <map>

#include "utils/Image.h"
#include "utils/FunctionTracer.h"
#include "utils/FuncFindPattern.hpp"

class Solution {
public:
  void compute([[maybe_unused]]std::vector<PackedImage> &images) {
      FunctionTracer<std::chrono::milliseconds> tracer("compute", "ms");
      CoordinateMap patternMap;

      for (int i = 0; i < EYE_PATTERNS_COUNT; i++) {
          Coordinates coordinates;
          mapPattern(EYE_PATTERNS[i], coordinates);
          patternMap[EYE_PATTERNS[i]] = coordinates;
      }

      for (auto & image : images) {
          searchImage(patternMap, image);
      }
  }

  void compute([[maybe_unused]]std::vector<StrideImage> &images) {
    FunctionTracer<std::chrono::milliseconds> tracer("compute", "ms");
    //TODO: fill solution
  }
};

#endif /* SOLUTION_H_ */
