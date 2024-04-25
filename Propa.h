#ifndef PROPa
#define PROPa

#include "UtilityQueryModels.h"
#include "Allocation.h"
#include "Utils.h"
#include <vector>
#include <set>
using std::vector;
using std::set, std::multiset;

#include <iostream>
using std::cin, std::cout, std::endl;

Allocation propa (vector<UtilityQueryable*> agents, int agents_amount, int goods_amount) {
    Allocation allocation(goods_amount);

    set<int> agents_set = set02n(agents_amount - 1);
    int good_idx = 0;
    double cake_left = 0;
    while (agents_set.size() > 1) {
        set<int> bundle;
        int satisfied_agent = *agents_set.begin();
        while (good_idx < goods_amount) {
            bundle.insert(good_idx);
            if (good_idx == goods_amount - 1) {
                bundle.erase(good_idx);
                break;
            } 
            for (const auto& i : agents_set) {
                for (int j = 0; j < goods_amount; j++) {
                    if (bundle.count(j)) continue;
                    if (agents[i]->get(bundle) >= 1. / agents_amount - agents[i]->alpha() * agents[i]->get(j)) {
                        satisfied_agent = i;
                        bundle.erase(good_idx);
                        break;
                    }
                }
            }
            good_idx++;
        }
        bool enough_cake = false;
        int feasible_agent = *agents_set.begin();
        for (const auto& i : agents_set) {
            for (int j = 0; j < goods_amount; j++) {
                if (bundle.count(j)) continue;
                if (agents[i]->get(bundle) + agents[i]->eval(cake_left, 1) >= 1. / agents_amount - agents[i]->alpha() * agents[i]->get(j)) {
                    feasible_agent = i;
                    enough_cake = true;
                    break;
                }
            }
        }
        if (enough_cake) {
            int tiny_i = feasible_agent;
            double tiny_y = 1;
            for (const auto& i : agents_set) {
                for (int j = 0; j < goods_amount; j++) {
                    if (bundle.count(j)) continue;
                    double y = agents[i]->cut(cake_left, 1. / agents_amount - agents[i]->alpha() * agents[i]->get(j) - agents[i]->get(bundle));
                    if (y < tiny_y) {
                        tiny_i = i;
                        tiny_y = y;
                    }
                }
            }
            for (const auto& j : bundle) {
                allocation.set_ind_partition(j, tiny_i);
            }
            allocation.set_div_next_piece(cake_left, tiny_y);
            cake_left = tiny_y;
            agents_set.erase(tiny_i);
        } else {
            bundle.insert(good_idx);
            good_idx++;
            for (const auto& i : bundle) {
                allocation.set_ind_partition(i, satisfied_agent);
            }
            agents_set.erase(satisfied_agent);
        }
    }
    int last_agent = *agents_set.begin();
    for (int i = good_idx; i < goods_amount; i++) {
        allocation.set_ind_partition(i, last_agent);
    }
    allocation.set_div_next_piece(cake_left, 1);
    return allocation;
}


#endif