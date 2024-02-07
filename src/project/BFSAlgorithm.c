
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>


int BFS(state_t root){
	state_t state;
	char string[256];
	ssize_t len;
	
	/* convert a state to a string*/
	// len = sprint_state(string,256,&state);
	
	/* convert a string to a state */
	len = read_state(string,&state);
	return 0;
}

int BFS_Prunning(state_t root){
	return 0;
}