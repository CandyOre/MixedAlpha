#ifndef INDEF1
#define INDEF1

#include "UtilityQueryModels.h"
#include <vector>
#include <set>
#include <functional>
#include <numeric>
using std::vector;
using std::set;
using std::pair;
using std::function;

vector<int> ind_EF1 (vector<UtilityQueryable*> agents, int agents_amount, int goods_amount) {
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

#endif
