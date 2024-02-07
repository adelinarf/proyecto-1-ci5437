
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>
#include <queue>
#include "BFS.hpp"


int main(int argc, char **argv){
    state_t state; 
    printf("EMPIEZA\n");

    BFS(state);
    BFS_Prunning(state);


    std::queue<state_t> q;
    ruleid_iterator_t iter;
    q.emplace(state);


    int currentLevel = 1;
    int nextLevel = 1;
    int size = 0;
    int action;

    while (!q.empty()){
        printf("Aun no esta vacia, nodo %d\n",size);
        
        state_t currentVertex = q.front(); q.pop();
        init_fwd_iter(&iter, &currentVertex);

        if (currentLevel == 0) 
            {
                currentLevel = nextLevel;
                nextLevel = 0;
                printf("Profundidad : %d \n",size);
            }

        if (is_goal(&currentVertex)){
            printf("Llego al final %d \n",size);
        }
        while ((action = next_ruleid(&iter)) >= 0) {
                state_t s;
                apply_fwd_rule(action, &currentVertex, &s);

                q.emplace(s);
                nextLevel += 1;
                size +=1;
        }
        currentLevel--;

    }

	return 0;
}