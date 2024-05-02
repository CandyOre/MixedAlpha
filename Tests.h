#ifndef TESTS
#define TESTS

#include "./Model/UtilityFunctions.h"
#include "./Algoithm/IdenticalAgentsEFfa.h"
#include "./Algoithm/IndivisibleEF1.h"
#include <iostream>

using std::cin, std::cout, std::endl;

// expect: 1 0.5
void homo_div_unit_ind_test() {
    HomoDivUnitIndFunction agent(5);
    cout << agent.get(2) << " " << agent.eval(0, 0.5) << endl;
}

// expect: 4 5 1 2 3
void homo_div_inc_ind_test() {
    HomoDivIncIndFunction agent(5, 2, 1);
    for (int i = 0; i < 5; i++) {
        cout << agent.get(i) << " ";
    }
}

// expect:
// 4 3 2 1 0 
// 1 0 4 3 2
// 3 2 1 0 4
void ind_ef1_order_test() { 
    int goods_amount = 5;
    // 1 2 3 4 5
    // 4 5 1 2 3
    // 2 3 4 5 1
    auto agent1 = new HomoDivIncIndFunction(goods_amount, 0, 1);
    auto agent2 = new HomoDivIncIndFunction(goods_amount, 2, 1);
    auto agent3 = new HomoDivIncIndFunction(goods_amount, 4, 1);
    auto result = ind_EF1({agent1, agent2, agent3}, 3, goods_amount);
    
    for (auto e : result) cout << e << " "; cout << endl;
    
    // for (auto e : ordered_items.back()) {
    //     cout << e << " ";
    // } cout << endl;
}

void ind_ef1_time_test(int goods_amount, int agents_amount, int t) {
    TimerClock tc;
    double time = 0, times = 0;
    
    auto agent = new HomoDivIncIndFunction(goods_amount, 0, 1);
    vector<UtilityQueryable*> agents(agents_amount, agent);

    cout << "naive: ";
    times = 0;
    for (int i = 0; i < t; i++) {
        tc.update();
        ind_EF1_naive(agents, agents_amount, goods_amount);
        time = tc.getTimerMilliSec();
        times += time;
        cout << time << " ";
    }
    cout << "- avg: " << times / t << endl;

    cout << "set: ";
    times = 0;
    for (int i = 0; i < t; i++) {
        tc.update();
        ind_EF1_set(agents, agents_amount, goods_amount);
        time = tc.getTimerMilliSec();
        times += time;
        cout << time << " ";
    }
    cout << "- avg: " << times / t << endl;

    cout << "ptr: ";
    times = 0;
    for (int i = 0; i < t; i++) {
        tc.update();
        ind_EF1_ptr(agents, agents_amount, goods_amount);
        time = tc.getTimerMilliSec();
        times += time;
        cout << time << " ";
    }
    cout << "- avg: " << times / t << endl;
}

void ind_ef1_set_time_component(int goods_amount, int agents_amount, int t) {
    TimerClock tc;
    double time1 = 0, time2 = 0;
    double time1s = 0, time2s = 0;
    
    auto agent = new HomoDivIncIndFunction(goods_amount, 0, 1);
    vector<UtilityQueryable*> agents(agents_amount, agent);

    cout << "set: ";
    for (int i = 0; i < t; i++) {
        tc.update();

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

        time1 = tc.getTimerMilliSec();
        tc.update();

        // round robin
        for (int i = 0; i < goods_amount; i++) {
            int cur_agent = i % agents_amount;
            int cur_good = *ordered_items[cur_agent].begin();
            result_partition[cur_good] = cur_agent + 1;
            for (int j = 0; j < agents_amount; j++) {
                ordered_items[j].erase(cur_good);
            }
        }

        time2 = tc.getTimerMilliSec();
        cout << (time1 + time2) << " ";
        cout << "(" << time1 << ", " << time2 << ") ";
        time1s += time1;
        time2s += time2;
    }
    cout << "- avg: " << (time1s + time2s) / t << " (" << time1s / t << ", " << time2s / t << ") " << endl;
}

#endif