#ifndef READEYEFILTERING_SOLUTIONUTILFUNCS_H
#define READEYEFILTERING_SOLUTIONUTILFUNCS_H

#include <vector>
#include <map>

#include "EyePatterns.h"
#include "Image.h"

// x and y-axis coordinates of character in pattern
// the origin of the coordinate system is the upper left corner
using Coordinate = std::pair<int, int>;

// vector of coordinates
using Coordinates = std::vector<Coordinate>;

// Patterns turned into their coordinate vector representations
using PatternCoordinates = std::vector<Coordinates>;


/// Create vector representations
void mapPattern(const EyePattern& pattern, Coordinates& coordinates) {

    // Iterate over pattern symbols
    for (int y = 0; y < EYE_PATTERN_ROW_SIZE; y++) {
        for (int x = 0; x < EYE_PATTERN_COL_SIZE; x++) {

            // Get the current symbol
            char currentSymbol = pattern[x][y];

            // If the current symbol is whitespace - skip
            if (currentSymbol == ' ') {
                continue;
            }

            // Add the coordinates of the current pixel in coordinate vector
            coordinates.emplace_back(Coordinate({x, y}));
        }
    }
}


/// Check if current pattern is found on these coordinates
bool findPattern(const Coordinates& patternCoords, PackedImage& image, int currentX, int currentY) {

    // For each pixel in pattern check if the red value is over 200
    for (const auto & patternCoord : patternCoords) {

        // Calculate absolute coordinates of pixel
        int currImageX = currentX + patternCoord.first;
        int currImageY = currentY + patternCoord.second;

        Pixel* currPixel = &image.pixels[currImageY * image.resolution.width + currImageX];

        // If the red value is less than 200 the pixel is not a part of a pattern
        if (currPixel->red < 200) {
            return false;
        }
    }

    // Pattern is found
    return true;
}


/// Go over pixels in pattern and reduce red value by 150
void handlePattern(const Coordinates& patternCoords, PackedImage& image, int currentX, int currentY) {

    // Reduce red value of all pixels mapped onto pattern by 150
    for (const auto & patternCoord : patternCoords) {

        // Calculate absolute coordinates of pixel
        int currImageX = currentX + patternCoord.first;
        int currImageY = currentY + patternCoord.second;

        Pixel* currPixel = &image.pixels[currImageY * image.resolution.width + currImageX];

        // Reduce red value by 150
        currPixel->red -= 150;
    }
}


/// Check if any of the patterns is found on coordinates
bool checkCoordinates(PatternCoordinates& patternMaps, PackedImage& image, int currentX, int currentY) {

    // Iterate over available patterns
    for (int i = EYE_PATTERNS_COUNT - 1; i >= 0; i--) {

        // Check if the current pattern is found
        if (findPattern(patternMaps[i], image, currentX, currentY)) {

            // If there is a pattern - reduce red value
            handlePattern(patternMaps[i], image, currentX, currentY);
            return true;
        }
    }

    // No pattern is found
    return false;
}


/// Search for and replace red value in patterns in image
void searchAndReplaceImage(PatternCoordinates &patternMaps, PackedImage& image) {

    // Iterate over image pixels
    for (int y = 0; y <= (image.resolution.height - EYE_PATTERN_COL_SIZE); y++) {
        for (int x = 0; x <= (image.resolution.width - EYE_PATTERN_ROW_SIZE); x++) {

            // If pattern is found on current coordinates skip its pixels
            if (checkCoordinates(patternMaps, image, x, y)) {
                x += EYE_PATTERN_COL_SIZE;
            }
        }
    }
}

#endif
