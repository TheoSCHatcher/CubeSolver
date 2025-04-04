#include <array>
#include <vector>
#include <algorithm>
#include "cube.h"






int orientationToIndex(const std::vector<int>& orientations, int base) {
    int index = 0;
    for (size_t i = 0; i < orientations.size() - 1; i++) { // Last orientation is dependent
        index = index * base + orientations[i];
    }
    return index;
}


int permutationToIndex(const std::vector<int>& perm) {
    int n = perm.size();
    int index = 0;
    std::vector<int> factorial(n, 1);
    
    // Precompute factorials
    for (int i = 1; i < n; i++) {
        factorial[i] = factorial[i - 1] * i;
    }

    std::vector<int> elements(n);
    for (int i = 0; i < n; i++) {
        elements[i] = i;
    }

    for (int i = 0; i < n; i++) {
        int pos = std::find(elements.begin(), elements.end(), perm[i]) - elements.begin();
        index += pos * factorial[n - 1 - i];
        elements.erase(elements.begin() + pos);
    }

    return index;
}


EncodedCubeState encodeCubeState(
    const std::vector<int>& cornerPerm, 
    const std::vector<int>& cornerOrient, 
    const std::vector<int>& edgePerm, 
    const std::vector<int>& edgeOrient) 
{
    EncodedCubeState state;
    state.cornerPermutation = permutationToIndex(cornerPerm);
    state.cornerOrientation = orientationToIndex(cornerOrient, 3);
    state.edgePermutation = permutationToIndex(edgePerm);
    state.edgeOrientation = orientationToIndex(edgeOrient, 2);
    return state;
}

EncodedCubeState encodeCubeState(CubeState& state){
    
    EncodedCubeState encodedState;
    encodedState.cornerPermutation = permutationToIndex(state.cornerPermutation);
    encodedState.cornerOrientation = orientationToIndex(state.cornerOrientation, 3);
    encodedState.edgePermutation = permutationToIndex(state.edgePermutation);
    encodedState.edgeOrientation = orientationToIndex(state.edgeOrientation, 2);
    return encodedState;
}





//  (UFR, URB, ULB, ULF, DFR, DRB, DLB, DLF)
//  (UR, UF, UL, UB, DR, DF, DL, DB, FR, FL, BR, BL)

void applyMoves(CubeState& state, int move){
    // 0  1  2  3  4  5  6  7  8  9  10  11  12  13  14  15  16  17
    // R  L  F  B  U  D  R2 L2 F2 B2 U2  D2  R'  L'  F'  B'  U'  D'
    
    if (move > 5){
        applyMoves(state, move % 6);
        applyMoves(state, move - 6);
        return;
    }

    // Define Corner cycling Array - ORDER IMPORTANT
    static constexpr std::array<std::array<int, 4>, 6> corner_cycles = {{
        {0,4,5,1},  // R
        {2,6,7,3},  // L
        {3,7,4,0},  // F
        {1,5,6,2},  // B
        {0,1,2,3},  // U
        {4,7,6,5}   // D
    }};


    // Define Edge Cycling Array
    static constexpr std::array<std::array<int, 4>, 6> edge_cycles = {{
        {0,8,4,10},  // R
        {2,11,6,9},  // L
        {1,9,5,8},   // F
        {3,10,7,11}, // B
        {3,2,1,0},   // U
        {4,5,6,7}    // D
    }};

    // Swap corner permutation
    const auto& cc = corner_cycles[move]; // Get cycle for the move
    std::swap(state.cornerPermutation[cc[0]], state.cornerPermutation[cc[1]]);
    std::swap(state.cornerPermutation[cc[1]], state.cornerPermutation[cc[2]]);
    std::swap(state.cornerPermutation[cc[2]], state.cornerPermutation[cc[3]]);

    std::swap(state.cornerOrientation[cc[0]], state.cornerOrientation[cc[1]]);
    std::swap(state.cornerOrientation[cc[1]], state.cornerOrientation[cc[2]]);
    std::swap(state.cornerOrientation[cc[2]], state.cornerOrientation[cc[3]]);


    // Swap edge permutation
    const auto& ec = edge_cycles[move];
    std::swap(state.edgePermutation[ec[0]], state.edgePermutation[ec[1]]);
    std::swap(state.edgePermutation[ec[1]], state.edgePermutation[ec[2]]);
    std::swap(state.edgePermutation[ec[2]], state.edgePermutation[ec[3]]);

    std::swap(state.edgeOrientation[ec[0]], state.edgeOrientation[ec[1]]);
    std::swap(state.edgeOrientation[ec[1]], state.edgeOrientation[ec[2]]);
    std::swap(state.edgeOrientation[ec[2]], state.edgeOrientation[ec[3]]);
    



    // Change Corner Orientations for F, R, L, B (U and D don't change corner orientation)
    // For each move, the corners get orientated -1,+1,-1,+1 therefore order important
    if (move == 0 || move == 1 || move == 2 || move == 3){
        int count = 0;
        for (int i : cc) {
            state.cornerOrientation[i] = mod1(state.cornerOrientation[i] + 1 - 2 *(count == 0),3);
            count++;
            count = count%2;
        }
    }


    // Change Edge Orientations
    if (move == 2 || move == 3) {
        for (int i : ec) {
            state.edgeOrientation[i] ^= 1; // Flip (0 → 1, 1 → 0)
        }
    }


}



int main() {
    std::vector<int> solvedCornerPerm = {0, 1, 2, 3, 4, 5, 6, 7};
    std::vector<int> solvedCornerOrient = {0, 0, 0, 0, 0, 0, 0, 0};
    std::vector<int> solvedEdgePerm = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    std::vector<int> solvedEdgeOrient = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


    //EncodedCubeState state = encodeCubeState(solvedCornerPerm, solvedCornerOrient, solvedEdgePerm, solvedEdgeOrient);
    CubeState SolvedCube = {solvedCornerPerm, solvedCornerOrient, solvedEdgePerm, solvedEdgeOrient};


    //EncodedCubeState state = encodeCubeState(SolvedCube);
    //printEncodedCube(state);
    

    //applyMoves(SolvedCube, 14);
    applyMoves(SolvedCube, 1);
    applyMoves(SolvedCube, 0);
    applyMoves(SolvedCube, 2);


    //for (auto var : SolvedCube.cornerOrientation){
    //    std::cout << var << "  ";
    //}
    printCubeNet(SolvedCube);



    return 0;
}



