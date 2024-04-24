#ifndef TESTS
#define TESTS

#include "UtilityFunctions.h"
#include "IdenticalAgentsEFfa.h"
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

#endif