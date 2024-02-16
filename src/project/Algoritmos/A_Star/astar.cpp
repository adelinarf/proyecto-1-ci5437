
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>
#include <queue>
#include "Astar.hpp"

int main(int argc, char **argv){
    state_t state; 
    PDB_MODE select;
    if (strcmp(argv[2], "ADD")==0){
    select = PDB_MODE :: ADD;
    }
    else if (strcmp(argv[2], "MAX")==0){
    select = PDB_MODE :: MAX;
    }
    else if (strcmp(argv[2], "MANHATTAN")==0){
    select = PDB_MODE :: MANHATTAN;
    }
    else{
    printf("Parametro invalido\n");
    return -1;
    }
    std::vector<std::string> names{"pd"};
    PDB pdb{names,select};
    printf("Corriendo A*...\n");
    AStar(state,pdb);
	return 0;
}