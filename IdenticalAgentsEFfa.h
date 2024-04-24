#ifndef IDENTICAL_AGENT_EFfa
#define IDENTICAL_AGENT_EFfa

#include "UtilityQueryModels.h"
#include "Allocation.h"
#include "Utils.h"
#include <vector>
#include <set>
#include <functional>
using std::vector;
using std::set, std::multiset;
using std::function;

#include <iostream>
using std::cin, std::cout, std::endl;

Allocation identical_agents_EFfa (UtilityQueryable* agent, int agents_amount, int goods_amount) {
    Allocation allocation(goods_amount);

    // initialize with EF1 allocation
    vector<UtilityQueryable*> agents(agents_amount, agent);
    auto partition = ind_EF1(agents, agents_amount, goods_amount);
    auto bundles = part2bundle(partition, agents_amount);
    sort(bundles.begin(), bundles.end(), [&agent] (set<int>& a, set<int>& b) {return agent->get(a) > agent->get(b);});

    return allocation;
}


#endif