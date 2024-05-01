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

    set<int> agents_set = set02n(agents_amount);
    int good_idx = 0;
    double cake_left = 0;
    while (agents_set.size() > 1) {
        cout << agents_set.size() << endl;
        set<int> bundle;
        // Bag-Filling
        int satisfied_agent = *agents_set.begin();
        bool bag_filling_finish = false;
        while (good_idx < goods_amount) {
            // cout << "On good " << good_idx << endl;
            bundle.insert(good_idx);
            if (good_idx == goods_amount - 1) {
                bundle.erase(good_idx);
                break;
            } 
            for (const auto& i : agents_set) {
                // cout << "Check agent " << i << " holding " << agents[i]->get(bundle) << endl;
                for (int j = 0; j < goods_amount; j++) {
                    if (bundle.count(j)) {
                    continue;
                    }
                    // cout << "Alleviate with " << j << " at " 
                    //     << agents[i]->get(set02n(goods_amount)) / agents_amount - agents[i]->alpha() * agents[i]->get(j) 
                    //     << endl;
                    if (
                        agents[i]->get(bundle) 
                        >= agents[i]->get(set02n(goods_amount)) / agents_amount - agents[i]->alpha() * agents[i]->get(j)
                    ) {
                        satisfied_agent = i;
                        bundle.erase(good_idx);
                        for (auto e : bundle) cout << e << " "; cout << endl;
                        bag_filling_finish = true;
                        break;
                    }
                }
                if (bag_filling_finish) break;
            }
            if (bag_filling_finish) break;
            good_idx++;
        }
        cout << "Bag Filling Exit " << bag_filling_finish 
            << " with good " << good_idx 
            << " at agent " << satisfied_agent
            << endl;
        bool enough_cake = false;
        int feasible_agent = *agents_set.begin();
        for (const auto& i : agents_set) {
            for (int j = 0; j < goods_amount; j++) {
                if (bundle.count(j)) {
                    continue;
                }
                if (
                    agents[i]->get(bundle) + agents[i]->eval(cake_left, 1)
                    >= agents[i]->get(set02n(goods_amount)) / agents_amount - agents[i]->alpha() * agents[i]->get(j)
                ) {
                    feasible_agent = i;
                    enough_cake = true;
                    break;
                }
            }
            if (enough_cake) break;
        }
        cout << "Found Enough Cake " << enough_cake
            << " with agent " << feasible_agent
            << endl;
        if (enough_cake) {
            int tiny_i = feasible_agent;
            double tiny_y = 1;
            for (const auto& i : agents_set) {
                for (int j = 0; j < goods_amount; j++) {
                    if (bundle.count(j)) continue;
                    double y = agents[i]->cut(
                        cake_left, 
                        agents[i]->get(set02n(goods_amount)) / agents_amount 
                            - agents[i]->alpha() * agents[i]->get(j) 
                            - agents[i]->get(bundle)
                    );
                    if (y < tiny_y) {
                        tiny_i = i;
                        tiny_y = y;
                    }
                }
            }
            cout << "Allocate Cake to agent " << tiny_i
                << " with right " << tiny_y
                << endl;
            for (const auto& j : bundle) {
                allocation.set_ind_partition(j, tiny_i + 1);
            }
            allocation.set_div_next_piece(tiny_y, tiny_i + 1);
            cake_left = tiny_y;
            agents_set.erase(tiny_i);
            for (auto e : agents_set) cout << e << " " ; cout << endl;
        } else {
            bundle.insert(good_idx);
            good_idx++;
            for (const auto& i : bundle) {
                allocation.set_ind_partition(i, satisfied_agent + 1);
            }
            agents_set.erase(satisfied_agent);
        }
    }
    int last_agent = *agents_set.begin();
    for (int i = good_idx; i < goods_amount; i++) {
        allocation.set_ind_partition(i, last_agent + 1);
    }
    allocation.set_div_next_piece(1, last_agent + 1);
    return allocation;
}


#endif