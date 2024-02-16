
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>
#include <queue>
#include <chrono>
#include <unordered_map>
#include "BFS.hpp"
#include "../comparer.hpp"

#define MAX_RUN_TIME 420000

using namespace std::chrono;

enum COLOR {WHITE, GRAY, BLACK};


int64_t runtime(system_clock::time_point &from) {
    int64_t currentTime = duration_cast<milliseconds>(high_resolution_clock::now() - from).count();
    return currentTime > MAX_RUN_TIME ? currentTime : -1;
}

std::optional<int> BFS(state_t state){
	printf("Corriendo BFS...\n");
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
            printf("Estado final %d \n",size);
            printf("Tiempo: %ld",duration_cast<milliseconds>(high_resolution_clock::now() - start).count());
        }

        if ((auxTime = runtime(start)) != -1) {
            printf("Tiempo de corrida %ld \n",auxTime);
            break;
        }

        while ((rule = next_ruleid(&iter)) >= 0) {
                state_t s;
                apply_fwd_rule(rule, &currentVertex, &s);

                q.emplace(s);
                nextLevel += 1;
        }
        currentLevel--;

    }
	return 0;
}

std::optional<int> BFS_Prunning(state_t state){
	printf("Corriendo BFS con poda de duplicados...");
    int64_t auxTime;
    system_clock::time_point start = high_resolution_clock::now();


    std::queue<state_t> q;
    ruleid_iterator_t iter;
    std::unordered_map<state_t, COLOR> colors = {{}};
    
    colors[state] = COLOR::WHITE;
    q.emplace(state);


    int currentLevel = 1;
    int nextLevel = 1;
    int size = 0;
    int rule;

    while (!q.empty()){
        
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
            printf("Estado final %d \n",size);
            printf("Tiempo: %ld",duration_cast<milliseconds>(high_resolution_clock::now() - start).count());
        }
        if ((auxTime = runtime(start)) != -1) {
            printf("Tiempo de corrida %ld \n",auxTime);
            break;
        }
        while ((rule = next_ruleid(&iter)) >= 0) {
                state_t s;
                apply_fwd_rule(rule, &currentVertex, &s);

                if (colors.contains(s)) {
                    if (colors[s] == COLOR::WHITE) {
                        colors[s] = COLOR::GRAY;
                        q.emplace(s);
                        nextLevel += 1;
                    }
                }    
                else {
                    colors[s] = COLOR::GRAY;
                    q.emplace(s);
                    nextLevel += 1;
                }
        }
        colors[currentVertex] = COLOR::BLACK;
        currentLevel--;

    }
    return 0;
}