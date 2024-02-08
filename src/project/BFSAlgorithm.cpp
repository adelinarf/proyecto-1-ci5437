
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>
#include <queue>
#include <chrono>

#include "BFS.hpp"
#define MAX_RUN_TIME 420000

using namespace std::chrono;


int64_t runtime(system_clock::time_point &from) {
    int64_t currentTime = duration_cast<milliseconds>(high_resolution_clock::now() - from).count();
    return currentTime > MAX_RUN_TIME ? currentTime : -1;
}

std::optional<int> BFS(state_t state){
	printf("entra a bfs");
	int64_t auxTime;
    system_clock::time_point start = high_resolution_clock::now();


	std::queue<state_t> q;
    ruleid_iterator_t iter;
    q.emplace(state);


    int currentLevel = 1;
    int nextLevel = 1;
    int size = 0;
    int rule;

    while (!q.empty()){
        // printf("Aun no esta vacia, nodo %d\n",size);
        
        state_t currentVertex = q.front(); q.pop();
        init_fwd_iter(&iter, &currentVertex);

        if (currentLevel == 0) 
            {
            	size +=1;
                currentLevel = nextLevel;
                nextLevel = 0;
                printf("Profundidad : %d \n",size);
                printf("Nodos : %d \n",currentLevel);
            }

        if (is_goal(&currentVertex)){
            printf("Llego al final %d \n",size);
            printf("Tiempo: %ld",duration_cast<milliseconds>(high_resolution_clock::now() - start).count());
        }
        while ((rule = next_ruleid(&iter)) >= 0) {
                state_t s;
                apply_fwd_rule(rule, &currentVertex, &s);

                q.emplace(s);
                nextLevel += 1;
        }
        printf("This node has %d children\n",size);
        currentLevel--;

    }
	return 0;
}

std::optional<int> BFS_Prunning(state_t root){
	return 0;
}