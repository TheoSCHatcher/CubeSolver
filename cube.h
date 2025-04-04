// cube.hpp
#ifndef CUBE_HPP
#define CUBE_HPP

#include <array>
#include <string>
#include <cstdint>
#include <vector>



// SOLVED CUBE
//
// Corner Permutations   {0, 1, 2, 3, 4, 5, 6, 7}
// Corner Orientations   {0, 0, 0, 0, 0, 0, 0, 0}
// Edge Permutations     {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}
// Edge Orientatiosn     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}

// Shared structs
struct __attribute__((packed)) EncodedCubeState {
    uint16_t cornerPermutation;  // 0 to 8! - 1 (13 bits)
    uint16_t cornerOrientation;  // 0 to 3^7 - 1 (11 bits)
    uint32_t edgePermutation;    // 0 to 12! - 1 (24 bits)
    uint16_t edgeOrientation;    // 0 to 2^11 - 1 (11 bits)
};

struct CubeState {
    std::vector<int> cornerPermutation; // Indices 0-7 for corners
    std::vector<int> cornerOrientation; // Values 0-2 (twists)
    std::vector<int> edgePermutation;  // Indices 0-11 for edges
    std::vector<int> edgeOrientation;  // Values 0-1 (flips)
};


inline int mod1(int a, int b)
{
  const int r = a % b;
  return r < 0 ? r + b : r;
}


// Declare functions implemented in test.cpp
void printCubeNet(CubeState& cube);
void printEncodedCube(EncodedCubeState& cube);

#endif
