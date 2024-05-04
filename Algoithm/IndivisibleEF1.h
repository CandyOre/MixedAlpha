#ifndef INDEF1
#define INDEF1

#include "../Model/UtilityQueryModels.h"
#include <vector>
#include <set>
#include <functional>
#include <numeric>
using std::vector;
using std::set;
using std::pair;
using std::function;


vector<int> ind_EF1_naive (vector<UtilityQueryable*>& agents, int agents_amount, int goods_amount) {
    vector<int> result_partition(goods_amount, 1);

    vector<bool> allocated(goods_amount, false);
    for (int i = 0; i < goods_amount; i++) {
        int cur_agent = i % agents_amount;
        auto agent = agents[cur_agent];
        int cur_good = 0, cur_utility = agent->get(0);
        for (int j = 0; j < goods_amount; j++) {
            if (allocated[j]) {
                continue;
            }
            if (agent->get(j) > cur_utility) {
                cur_good = j;
                cur_utility = agent->get(j);
            }
        }
        result_partition[cur_good] = cur_agent + 1;
        allocated[cur_good] = true;
    }

    return result_partition;
}

vector<int> ind_EF1_set (vector<UtilityQueryable*>& agents, int agents_amount, int goods_amount) {
    vector<int> result_partition(goods_amount, 1);

    // order preprocess
    vector<set<int, function<bool(int, int)>>> ordered_items;
    for (const auto& agent : agents) {
        ordered_items.push_back(set<int, std::function<bool(int, int)>>(
            [&agent] (int a, int b) {
                return agent->get(a) > agent->get(b);
            }
        ));
        for (int i = 0; i < goods_amount; i++) {
            ordered_items.back().insert(i);
        }
    }

    // round robin
    for (int i = 0; i < goods_amount; i++) {
        int cur_agent = i % agents_amount;
        int cur_good = *ordered_items[cur_agent].begin();
        result_partition[cur_good] = cur_agent + 1;
        for (int j = 0; j < agents_amount; j++) {
            ordered_items[j].erase(cur_good);
        }
    }

    return result_partition;
}

vector<int> ind_EF1_ptr (vector<UtilityQueryable*>& agents, int agents_amount, int goods_amount) {
    vector<int> result_partition(goods_amount, 1);

    vector<vector<int>> table(agents_amount, vector<int>(goods_amount));
    for (int i = 0; i < agents_amount; i++) {
        for (int j = 0; j < goods_amount; j++) {
            table[i][j] = j;
        }
        sort(table[i].begin(), table[i].end(), [&](int a, int b) {return agents[i]->get(a) > agents[i]->get(b);});
    }
    vector<int> p(agents_amount, 0);
    vector<bool> allocated(goods_amount, false);

    for (int i = 0; i < goods_amount; i++) {
        int cur_agent = i % agents_amount;
        auto agent = agents[cur_agent];
        while (allocated[table[cur_agent][p[cur_agent]]]) {
            p[cur_agent]++;
        }
        int cur_good = table[cur_agent][p[cur_agent]];
        result_partition[cur_good] = cur_agent + 1;
        allocated[cur_good] = true;
    }

    return result_partition;
}

vector<int> ind_EF1 (vector<UtilityQueryable*> agents, int agents_amount, int goods_amount) {
    // return ind_EF1_naive(agents, agents_amount, goods_amount);
    // return ind_EF1_set(agents, agents_amount, goods_amount);
    return ind_EF1_ptr(agents, agents_amount, goods_amount);
}

#endif
