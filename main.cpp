#include "./Model/UtilityFunctions.h"
#include "Demos.h"
#include "Tests.h"

#include <iomanip>

void run() {
    // homo_div_unit_ind_test();
    // homo_div_inc_ind_test();
    
    // int goods_amount = 100, agents_amount = 100, test_cnt = 5;
    // ind_ef1_time_test(goods_amount, agents_amount, test_cnt);
    // ind_ef1_set_time_component(goods_amount, agents_amount, test_cnt);

    // ind_ef1_order_test();

    // int goods_amount = 5;
    // UtilityQueryable* agent1 = new HomoDivUnitIndFunction(goods_amount);
    // UtilityQueryable* agent2 = new HomoDivUnitIndFunction(goods_amount);
    // UtilityQueryable* agent1 = new HomoDivCustIndFunction(vector<double>({7, 4, 1, 6, 5}), 10);
    // UtilityQueryable* agent2 = new HomoDivCustIndFunction(vector<double>({5, 1, 3, 2, 9}), 10);
    // two_agent_EFa_demo(agent1, agent2, goods_amount);

    // int goods_amount = 10, agents_amount = 4;
    // auto agent = new HomoDivIncIndFunction(goods_amount, 0, 10);
    // UtilityQueryable* agent = new HomoDivCustIndFunction(vector<double>({6, 2, 4, 8, 1, 6, 8, 4, 5, 9}), 10);
    // identical_agents_EFfa_demo(agent, 4, goods_amount);

    // int goods_amount = 10, agents_amount = 4;
    // auto agent1 = new HomoDivCustIndFunction(vector<double>({4, 5, 5, 6, 5, 4, 5, 4, 3, 4, 5, 5, 6, 5, 4, 5, 4, 3, 5, 6}), 8);
    // auto agent2 = new HomoDivCustIndFunction(vector<double>({6, 4, 5, 3, 4, 7, 4, 6, 5, 6, 4, 5, 3, 4, 7, 4, 6, 5, 3, 5}), 2);
    // auto agent3 = new HomoDivCustIndFunction(vector<double>({3, 4, 5, 3, 4, 6, 5, 4, 6, 3, 4, 5, 3, 4, 6, 5, 4, 6, 6, 4}), 6);
    // auto agent4 = new HomoDivCustIndFunction(vector<double>({7, 6, 4, 6, 7, 4, 6, 7, 5, 6, 5, 7, 5, 7, 4, 7, 3, 5, 6, 4}), 8);
    auto agent1 = new HomoDivCustIndFunction(vector<double>({4, 5, 5, 6, 5, 4, 5, 4, 3, 4}), 10);
    auto agent2 = new HomoDivCustIndFunction(vector<double>({6, 4, 5, 3, 4, 7, 4, 6, 5, 6}), 10);
    auto agent3 = new HomoDivCustIndFunction(vector<double>({3, 4, 5, 3, 4, 6, 5, 4, 6, 3}), 10);
    auto agent4 = new HomoDivCustIndFunction(vector<double>({7, 6, 4, 6, 7, 4, 6, 7, 5, 6}), 10);
    
    
    int goods_amount = 100, agents_amount = 4;
    vector<double> tmp;
    for (int i = 0; i < goods_amount; i++) {
        tmp.push_back(agent1->get(i % 10));
    }
    agent1 = new HomoDivCustIndFunction(tmp, 10);
    tmp.clear();
    for (int i = 0; i < goods_amount; i++) {
        tmp.push_back(agent2->get(i % 10));
    }
    agent2 = new HomoDivCustIndFunction(tmp, 10);
    tmp.clear();
    for (int i = 0; i < goods_amount; i++) {
        tmp.push_back(agent3->get(i % 10));
    }
    agent3 = new HomoDivCustIndFunction(tmp, 10);
    tmp.clear();
    for (int i = 0; i < goods_amount; i++) {
        tmp.push_back(agent4->get(i % 10));
    }
    agent4 = new HomoDivCustIndFunction(tmp, 10);
    propa_demo({agent1, agent2, agent3, agent4}, agents_amount, goods_amount);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);std::cout.tie(0);

	cout << std::fixed << std::setprecision(1);

    freopen("./io_file/input", "r", stdin);
    freopen("./io_file/output", "w", stdout);

    run();

    return 0;
}