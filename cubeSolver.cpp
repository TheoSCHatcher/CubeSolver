#include <array>
#include <cstdlib>
#include <vector>
#include <set>
#include "cube.h"
#include <time.h>
#include <iostream>
#include <algorithm>
#include <map>


// R  L  F  B  U  D  R2 L2 F2 B2 U2  D2  R'  L'  F'  B'  U'  D'
std::array<int, 18> G0_MOVES = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17};
std::array<int, 14> G1_MOVES = {2,3,4,5,6,7,8,9,10,11,14,15,16,17};
std::array<int, 18> G2_MOVES = {};
std::array<int, 18> G3_MOVES = {};
std::map<int, std::string> MOVE_MAP = {
    { 0, "R"},
    { 1, "L" },
    { 2, "F" },
    { 3, "B" },
    { 4, "U" },
    { 5, "D" },
    { 6, "R2" },
    { 7, "L2"},
    { 8, "F2"},
    { 9, "B2"},
    { 10, "U2"},
    { 11, "D2"},
    { 12, "R'"},
    { 13, "L'"},
    { 14, "F'"},
    { 15, "B'"},
    { 16, "U'"},
    { 17, "D'"}
};


CubeState GenerateRandomCube(int depth){
    
    std::vector<int> solvedCornerPerm = {0, 1, 2, 3, 4, 5, 6, 7};
    std::vector<int> solvedCornerOrient = {0, 0, 0, 0, 0, 0, 0, 0};
    std::vector<int> solvedEdgePerm = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    std::vector<int> solvedEdgeOrient = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    CubeState Cube = {solvedCornerPerm, solvedCornerOrient, solvedEdgePerm, solvedEdgeOrient};

    for (int i = 0; i < depth; i++){
        int move = rand()%18;
        std::cout << MOVE_MAP[move] << " ";
        applyMove(Cube, move);
    }

    std::cout << "\n";
    return Cube;
}

CubeState SOLVEDCUBE = GenerateRandomCube(0);
EncodedCubeState ENCODEDSOLVEDCUBE = encodeCubeState(SOLVEDCUBE);


bool DFS(std::vector<EncodedCubeState> visited, CubeState node, int depth, int maxDepth){
    if (node==SOLVEDCUBE){
        std::cout << "SOLVED\n";
        return true;
    }
    if (std::find(visited.begin(), visited.end(), encodeCubeState(node)) == visited.end() && depth < maxDepth){
        visited.push_back(encodeCubeState(node));
        for (int move : G0_MOVES){
            CubeState newNode = node;
            applyMove(newNode, move);
            if (DFS(visited, newNode, depth+1, maxDepth)){return true;};
        }   
    }
    return false;
}


int main() {
    srand( time(NULL) );
    //std::vector<int> solvedCornerPerm = {0, 1, 2, 3, 4, 5, 6, 7};
    //std::vector<int> solvedCornerOrient = {0, 0, 0, 0, 0, 0, 0, 0};
    //std::vector<int> solvedEdgePerm = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    //std::vector<int> solvedEdgeOrient = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    //CubeState SolvedCube = {solvedCornerPerm, solvedCornerOrient, solvedEdgePerm, solvedEdgeOrient};

    CubeState randomCube = GenerateRandomCube(6);

    bool Solved = false;
    std::vector<int> moves = {0,0,0,0,0,0};
    std::vector<EncodedCubeState> visited = {};
    int maxDepth = 7;
    DFS(visited, randomCube, 0, 6);

    printCubeNet(randomCube);
    return 0;
}



