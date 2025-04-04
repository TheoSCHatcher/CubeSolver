#include <array>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdint>

// SOLVED CUBE
//
// Corner Permutations   {0, 1, 2, 3, 4, 5, 6, 7}
// Corner Orientations   {0, 0, 0, 0, 0, 0, 0, 0}
// Edge Permutations     {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}
// Edge Orientatiosn     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}


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


struct move {
    int cornerPerm[8];
    int cornerOrient[8];
    int edgePerm[12];
    int edgeOrient[12];
};



inline int mod1(int a, int b)
{
  const int r = a % b;
  return r < 0 ? r + b : r;
}

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

void printCubeNet(CubeState& state){
    std::vector<std::string> corners = {"UFR", "URB", "ULB", "ULF", "DFR", "DRB", "DLB", "DLF"};
    std::vector<std::vector<std::string>> cornerColours = {{"W","G","R"},{"W","R","B"},{"W","B","O"},{"W","O","G"},{"Y","R","G"},{"Y","B","R"},{"Y","O","B"},{"Y","G","O"}}; 
    std::vector<std::string> edges  = {"UR", "UF", "UL", "UB", "DR", "DF", "DL", "DB", "FR", "FL", "BR", "BL"};
    std::vector<std::vector<std::string>> edgeColours = {{"W","R"},{"W","G"},{"W","O"},{"W","B"},{"Y","R"},{"Y","G"},{"Y","O"},{"Y","B"},{"G","R"},{"G","O"},{"B","R"},{"B","O"}}; 

    auto stateCorners = state.cornerPermutation;
    auto sCO = state.cornerOrientation;
    auto stateEdges = state.edgePermutation;
    auto sEO = state.edgeOrientation;

    std::cout << "          " << cornerColours[stateCorners[2]][sCO[2]] << "  " << edgeColours[stateEdges[3]][sEO[3]] << "  " << cornerColours[stateCorners[1]][sCO[1]] << "\n";
    std::cout << "          " << edgeColours[stateEdges[2]][sEO[2]] << "  W  " << edgeColours[stateEdges[0]][sEO[0]] << "\n";
    std::cout << "          " << cornerColours[stateCorners[3]][sCO[3]] << "  " << edgeColours[stateEdges[1]][sEO[1]] << "  " << cornerColours[stateCorners[0]][sCO[0]] << "\n";
    std::cout << "         " << "---------\n"; 

    std::cout <<  cornerColours[stateCorners[2]][mod1(sCO[2]+2,3)] << "  " << edgeColours[stateEdges[2]][mod1(sEO[2]+1,2)] << "  " << cornerColours[stateCorners[3]][mod1(sCO[3]+1,3)]  << " | " << cornerColours[stateCorners[3]][mod1(sCO[3]+2,3)] << "  " << edgeColours[stateEdges[1]][mod1(1+sEO[1],2)] << "  " << cornerColours[stateCorners[0]][mod1(sCO[0]+1,3)] << " | " \
                <<  cornerColours[stateCorners[0]][mod1(2+sCO[0],3)] << "  " << edgeColours[stateEdges[0]][mod1(sEO[0]+1,2)] << "  " << cornerColours[stateCorners[1]][mod1(sCO[1]+1,3)]  << " | " << cornerColours[stateCorners[1]][mod1(sCO[1]+2,3)] << "  " << edgeColours[stateEdges[3]][mod1(sEO[0]+1,2)] << "  " << cornerColours[stateCorners[2]][mod1(sCO[2]+1,3)]  << "\n";

    std::cout <<  edgeColours[stateEdges[11]][mod1(sEO[11]+1,2)] << "  O  " << edgeColours[stateEdges[9]][mod1(sEO[9]+1,2)] << " | " \
                << edgeColours[stateEdges[9]][sEO[9]] << "  G  " << edgeColours[stateEdges[8]][sEO[8]] << " | "\
                << edgeColours[stateEdges[8]][mod1(1+sEO[8],2)] << "  R  " << edgeColours[stateEdges[10]][mod1(1+sEO[10],2)] << " | " \
                << edgeColours[stateEdges[10]][sEO[10]] << "  B  " << edgeColours[stateEdges[11]][sEO[11]] << "\n";

    std::cout <<  cornerColours[stateCorners[6]][mod1(sCO[6]+1,3)] << "  " << edgeColours[stateEdges[6]][mod1(sCO[6]+1,2)] << "  " << cornerColours[stateCorners[7]][mod1(sCO[7]+2,3)]  << " | " << cornerColours[stateCorners[7]][mod1(1+sCO[7],3)] << "  " << edgeColours[stateEdges[5]][mod1(1+sEO[5],2)] << "  " << cornerColours[stateCorners[4]][mod1(sCO[0]+2,3)] << " | " \
                <<  cornerColours[stateCorners[4]][mod1(sCO[4]+1, 3)] << "  " << edgeColours[stateEdges[4]][mod1(sEO[4]+1,2)] << "  " << cornerColours[stateCorners[5]][mod1(sCO[5]+2,3)]  << " | " << cornerColours[stateCorners[5]][mod1(sCO[5]+1,3)] << "  " << edgeColours[stateEdges[7]][mod1(sEO[7]+1,2)] << "  " << cornerColours[stateCorners[6]][mod1(sCO[6]+2,3)] << "\n";
    
    std::cout << "         " << "---------\n"; 
    std::cout << "          " << cornerColours[stateCorners[7]][sCO[7]] << "  " << edgeColours[stateEdges[5]][sEO[5]] << "  " << cornerColours[stateCorners[4]][sCO[4]] << "\n";
    std::cout << "          " << edgeColours[stateEdges[6]][sEO[6]] << "  Y  " << edgeColours[stateEdges[4]][sEO[4]] << "\n";
    std::cout << "          " << cornerColours[stateCorners[6]][sCO[6]] << "  " << edgeColours[stateEdges[7]][sEO[7]] << "  " << cornerColours[stateCorners[5]][sCO[5]] << "\n"; 
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


void printEncodedCube(EncodedCubeState& state){
    std::cout << "Corner Permutation Index: " << state.cornerPermutation << "\n";
    std::cout << "Corner Orientation Index: " << state.cornerOrientation << "\n";
    std::cout << "Edge Permutation Index: " << state.edgePermutation << "\n";
    std::cout << "Edge Orientation Index: " << state.edgeOrientation << "\n";
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



