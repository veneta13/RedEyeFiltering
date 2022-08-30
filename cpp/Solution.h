#ifndef SOLUTION_H_
#define SOLUTION_H_

#include <cstdint>
#include <map>

#include "utils/Image.h"
#include "utils/FunctionTracer.h"
#include "utils/SolutionUtilFuncs.hpp"

class Solution {
public:
  void compute([[maybe_unused]]std::vector<PackedImage> &images) {
      FunctionTracer<std::chrono::milliseconds> tracer("compute", "ms");

      // Mapping patterns onto their coordinates vector representations
      CoordinateMap patternMap;

      // For each pattern calculate coordinate vector and map
      for (int i = 0; i < EYE_PATTERNS_COUNT; i++) {
          Coordinates coordinates;
          mapPattern(EYE_PATTERNS[i], coordinates);
          patternMap[EYE_PATTERNS[i]] = coordinates;
      }

      // Iterate over images
      for (auto & image : images) {
          searchImage(patternMap, image);
      }
  }
};

#endif /* SOLUTION_H_ */
