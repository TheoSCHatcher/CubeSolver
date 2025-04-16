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

    bool operator==(EncodedCubeState state){
        return (cornerOrientation == state.cornerOrientation) && (cornerPermutation == state.cornerPermutation) && \
                (edgeOrientation == state.edgeOrientation) && (edgePermutation == state.edgePermutation);
    }
};

struct CubeState {
    std::vector<int> cornerPermutation; // Indices 0-7 for corners
    std::vector<int> cornerOrientation; // Values 0-2 (twists)
    std::vector<int> edgePermutation;  // Indices 0-11 for edges
    std::vector<int> edgeOrientation;  // Values 0-1 (flips)
    
    bool operator==(const CubeState& state) const{
        return (cornerOrientation == state.cornerOrientation) && (cornerPermutation == state.cornerPermutation) && \
                (edgeOrientation == state.edgeOrientation) && (edgePermutation == state.edgePermutation);
    }
};


inline int mod1(int a, int b)
{
  const int r = a % b;
  return r < 0 ? r + b : r;
}


// Declare functions implemented in test.cpp
void printCubeNet(CubeState& cube);
void printEncodedCube(EncodedCubeState& cube);
int orientationToIndex(const std::vector<int>& orientations, int base);
int permutationToIndex(const std::vector<int>& perm);
EncodedCubeState encodeCubeState(
    const std::vector<int>& cornerPerm, 
    const std::vector<int>& cornerOrient, 
    const std::vector<int>& edgePerm, 
    const std::vector<int>& edgeOrient);
EncodedCubeState encodeCubeState(CubeState& state);
void applyMove(CubeState& state, int move);
bool Check_G1(CubeState& state);
bool Check_G2(CubeState& state);

#endif
