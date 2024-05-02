#ifndef IDENTICAL_AGENT_EFfa
#define IDENTICAL_AGENT_EFfa

#include "../Model/UtilityQueryModels.h"
#include "../Model/Allocation.h"
#include "IndivisibleEF1.h"
#include <vector>
#include <set>
using std::vector;
using std::set, std::multiset;

Allocation identical_agents_EFfa (UtilityQueryable* agent, int agents_amount, int goods_amount) {
    Allocation allocation(goods_amount);

    // initialize with EF1 allocation
    vector<UtilityQueryable*> agents(agents_amount, agent);
    auto partition = ind_EF1(agents, agents_amount, goods_amount);
    auto bundles = part2bundle(partition, agents_amount);
    sort(bundles.begin(), bundles.end(), [&agent] (set<int>& a, set<int>& b) {return agent->get(a) > agent->get(b);});
    for (int i = 0; i < agents_amount; i++) {
        for (const auto& e : bundles[i]) {
            allocation.set_ind_partition(e, i + 1);
        }
    }

    // water filling
    double cake_utility = agent->eval(0, 1), target_utility = agent->get(bundles[agents_amount - 1]);
    for (int i = agents_amount - 1; i > -1; i--) {
        if ((agents_amount - i) * (agent->get(bundles[i - 1]) - agent->get(bundles[i])) > cake_utility || i == 0) {
            target_utility = agent->get(bundles[i]) + cake_utility / (agents_amount - i);
            break;
        } else {
            cake_utility -= (agents_amount - i) * (agent->get(bundles[i - 1]) - agent->get(bundles[i]));
        }
    }

    double left = 0;
    for (int i = 0; i < agents_amount; i++) {
        double gap = target_utility - agent->get(bundles[i]);
        if (gap > 0) {
            double right = agent->cut(left, gap);
            allocation.set_div_next_piece(right, i + 1);
            left = right;
        }
    }

    return allocation;
}


#endif