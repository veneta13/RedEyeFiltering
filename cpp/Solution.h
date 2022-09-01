#ifndef SOLUTION_H_
#define SOLUTION_H_

#include <cstdint>
#include <map>

#include "utils/Image.h"
#include "utils/FunctionTracer.h"
#include "utils/SolutionUtilFuncs.h"

class Solution {
public:
  void compute([[maybe_unused]]std::vector<PackedImage> &images) {
      FunctionTracer<std::chrono::milliseconds> tracer("compute", "ms");

      // Coordinates vector representations of the patterns
      PatternCoordinates patternCoordinates;

      // Create coordinate vectors for each pattern
      for (int i = 0; i < EYE_PATTERNS_COUNT; i++) {
          Coordinates coordinates;
          mapPattern(EYE_PATTERNS[i], coordinates);
          patternCoordinates.emplace_back(coordinates);
      }

      // Iterate over images
      for (auto & image : images) {
          searchAndReplaceImage(patternCoordinates, image);
      }
  }
};

#endif /* SOLUTION_H_ */
