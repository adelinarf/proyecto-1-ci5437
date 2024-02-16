#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <queue>
#include <sys/time.h>
#include <queue>
#include <unordered_map>
#include "Astar.hpp"
#include "../comparer.hpp"
#include <chrono>


enum COLOR {WHITE, GRAY, BLACK};

#define MAX_RUN_TIME 420000

using namespace std::chrono;

std::unordered_map<state_t, double> costs = {{}};

int64_t runtime(system_clock::time_point &from) {
    int64_t currentTime = duration_cast<milliseconds>(high_resolution_clock::now() - from).count();
    return currentTime > MAX_RUN_TIME ? currentTime : -1;
}

double get_distance(state_t t){
    if (costs.contains(t)){
        return costs[t];
    }
    else{
        return std::numeric_limits<double>::infinity();
    }
}

void set_distance(state_t current,double gpath){
    costs[current] = gpath;
}

std::optional<int> AStar(state_t state,PDB pdb){
    int64_t auxTime;
    system_clock::time_point start = high_resolution_clock::now();

    std::queue<state_t> q;
    ruleid_iterator_t iter;
    std::unordered_map<state_t, COLOR> colors = {{}};
    std::unordered_map<state_t, double> gpath = {{}};
    std::unordered_map<state_t, double> fscore = {{}};

    colors[state] = COLOR::GRAY;
    gpath[state] = 0;
    fscore[state] = pdb.h(state);
    costs[state] = 0;

    q.emplace(state);
    int rule;

    while (!q.empty()){    
        state_t currentVertex = q.front(); q.pop();
        init_fwd_iter(&iter, &currentVertex);

        if ((auxTime = runtime(start)) != -1) {
            printf("Tiempo de corrida %ld \n",auxTime);
            break;
        }
        if (gpath[currentVertex] <= get_distance(currentVertex)){
            set_distance(currentVertex,gpath[currentVertex]);

            if (is_goal(&currentVertex)){
                printf("Estado final alcanzado");
                printf("Tiempo de corrida %ld \n",auxTime);
                break;  
            }
            while ((rule = next_ruleid(&iter)) >= 0) {
                    state_t s;
                    apply_fwd_rule(rule, &currentVertex, &s);
                    if (pdb.h(s) < std::numeric_limits<double>::infinity()) {
                        colors[s] = COLOR :: GRAY;
                        q.emplace(s);
                        gpath[s] = gpath[currentVertex]+get_fwd_rule_cost(rule);
                        fscore[s] = gpath[currentVertex]+get_fwd_rule_cost(rule)+pdb.h(s); //c(currentVertex,s)+h(s);
                    }
            }
            colors[currentVertex] = COLOR :: BLACK;
        }
    }
	return 0;
}