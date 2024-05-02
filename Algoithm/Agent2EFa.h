#ifndef AGENT2_EFa
#define AGENT2_EFa

#include "../Model/UtilityQueryModels.h"
#include "../Model/Allocation.h"
#include "IndivisibleEF1.h"
#include <vector>
#include <set>
using std::vector;
using std::set;

Allocation two_agent_EFa (UtilityQueryable* agent1, UtilityQueryable* agent2, int goods_amount) {
    Allocation allocation(goods_amount);
    // initialize with EF1 allocation
    vector<int> EF1_partition = ind_EF1({agent1, agent2}, 2, goods_amount);
    auto [bundle1, bundle2] = two_agent_part2bundle(EF1_partition);
    // agent1 performs choose operation
    if (agent1->get(bundle1) < agent1->get(bundle2)) {
        swap(bundle1, bundle2);
    }
    // indivisible goods allocation
    for (const auto& e: bundle1) {
        allocation.set_ind_partition(e, 1);
    }
    for (const auto& e : bundle2) {
        allocation.set_ind_partition(e, 2);
    }
    // divisible goods allocation
    if (agent1->get(bundle1) > agent1->get(bundle2) + agent1->eval(0, 1)) {
        allocation.set_div_next_piece(1, 2);
    } else {
        double ind_utility_1 = allocation.get_utility(1, agent1);
        double cut = agent1->cut(0, 0.5 - ind_utility_1);
        allocation.set_div_next_piece(cut, 1);
        allocation.set_div_next_piece(1, 2);
    }
    // last swap
    if (allocation.get_utility(1, agent2) > allocation.get_utility(2, agent2)) {
        allocation.swap_bundle(1, 2);
    }
    return allocation;
}


#endif