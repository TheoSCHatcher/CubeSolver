#include <iostream>
#include "cube.h"
#include <vector>





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




void printEncodedCube(EncodedCubeState& state){
    std::cout << "Corner Permutation Index: " << state.cornerPermutation << "\n";
    std::cout << "Corner Orientation Index: " << state.cornerOrientation << "\n";
    std::cout << "Edge Permutation Index: " << state.edgePermutation << "\n";
    std::cout << "Edge Orientation Index: " << state.edgeOrientation << "\n";
}
