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


/// Check if current pattern is found
bool findPattern(const Coordinates& patternCoords, PackedImage& image, int currentH, int currentW) {
    // iterate over coordinates
    for (const auto & patternCoord : patternCoords) {
        int currImageX = currentW + patternCoord.first;
        int currImageY = currentH + patternCoord.second;

        Pixel* currPixel = &image.pixels[currImageY * image.resolution.width + currImageX];

        if (currPixel->red < 200) {
            return false;
        }
    }

    return true;
}


void handlePattern(const Coordinates& patternCoords, PackedImage &image, int currentH, int currentW) {
    // iterate over pattern map
    for (const auto & patternCoord : patternCoords) {
        int currImageX = currentW + patternCoord.first;
        int currImageY = currentH + patternCoord.second;

        Pixel* currPixel = &image.pixels[currImageY * image.resolution.width + currImageX];
        currPixel->red -= 200;
    }
}


bool checkCoordinates(CoordinateMap& patternMaps, PackedImage& image, int currentH, int currentW) {
    auto iter = patternMaps.cbegin();

    while (iter != patternMaps.cend()) {
        if (findPattern(iter->second, image, currentH, currentW)) {
            handlePattern(iter->second, image, currentH, currentW);
            return true;
        }
        iter++;
    }
    return false;
}


void searchImage(CoordinateMap &patternMaps, PackedImage &image) {
    for (int i = 0; i < (image.resolution.height - EYE_PATTERN_COL_SIZE); i++) {
        for (int j = 0; j < (image.resolution.width - EYE_PATTERN_COL_SIZE); j++) {
            if (checkCoordinates(patternMaps, image, i, j)) {
                j += 5;
            }
        }
    }
}

#endif
