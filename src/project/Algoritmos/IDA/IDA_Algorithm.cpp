#include <limits>
#include <iostream>
#include <utility> 
#include "IDA.hpp"
#include <chrono>

using namespace std::chrono;

#define MAX_RUN_TIME 420000


int64_t runtime(system_clock::time_point &from) {
    int64_t currentTime = duration_cast<milliseconds>(high_resolution_clock::now() - from).count();
    return currentTime > MAX_RUN_TIME ? currentTime : -1;
}

typedef int long long bound;

typedef std::pair<std::optional<state_t>, bound> paired;

int nodes = 0;
bound g = 0ULL;

typedef std::pair<bool, bound> par;

paired f_bounded_dfs_visit(state_t &n, bound b, PDB pdb){
	bound f = g + pdb.h(n);
	if (f > b){
		return paired(std::nullopt, f);
	}
	if (is_goal(&n)){
		return paired(std::optional<state_t>{n}, f);
	}

    int rule;
    ruleid_iterator_t iter;
    init_fwd_iter(&iter, &n);

    bound t = std::numeric_limits<bound>::max();
    
    while ((rule = next_ruleid(&iter)) >= 0) {
        nodes++;

        state_t m;
        int cost = get_fwd_rule_cost(rule);
        g += cost;

        apply_fwd_rule(rule, &n, &m);
        paired p = f_bounded_dfs_visit(m, b,pdb);

        g -= cost;
        if (p.first.has_value()) return p;
        t = std::min<bound>(t, p.second);
    }
     return paired(std::nullopt, t); 
}

std::optional<int> ida_search(state_t state, PDB pdb){
	int64_t auxTime;
    system_clock::time_point start = high_resolution_clock::now();

	bound b = 1ULL;
	while (true){
		g=0ULL;
		paired p = f_bounded_dfs_visit(state,b,pdb);
		if (p.first.has_value()){
			printf("Nodos totales: %d\n", nodes);
			print_state(stdout, &p.first.value());
			return -1;
		}
		b = p.second;
		if ((auxTime = runtime(start)) != -1) {
            printf("Tiempo de corrida %ld \n",auxTime);
            break;
        }
	}
	return 0;
}