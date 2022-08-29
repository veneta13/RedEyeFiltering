#ifndef READEYEFILTERING_FUNCFINDPATTERN_HPP
#define READEYEFILTERING_FUNCFINDPATTERN_HPP

#include "EyePatterns.h"

// x and y-axis coordinates of character in pattern
// the origin of the coordinate system is the upper left corner
using Coordinate = std::pair<int, int>;

// vector of coordinates
using Coordinates = std::vector<Coordinate>;

// map of pattern and vector onto a vector of coordinates representing it
using CoordinateMap = std::map<EyePattern, Coordinates>;


/// Fill pattern maps
void mapPattern(const EyePattern& pattern, Coordinates& coordinates) {
    int rows = pattern.size();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < EYE_PATTERN_COL_SIZE; j++) {
            char currentSymbol = pattern[i][j];

            // if the current symbol is whitespace skip
            if (currentSymbol == ' ') {
                continue;
            }

            coordinates.emplace_back(Coordinate({i, j}));
        }
    }
}

#endif
