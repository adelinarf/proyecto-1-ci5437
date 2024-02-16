
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>
#include <queue>
#include "BFS.hpp"


int main(int argc, char **argv){
    state_t state; 
    BFS(state);
    BFS_Prunning(state);
	return 0;
}