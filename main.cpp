#include "./Model/UtilityFunctions.h"
#include "Demos.h"
#include "Tests.h"

#include <iomanip>

void run() {
    // homo_div_unit_ind_test();
    // homo_div_inc_ind_test();
    
    int goods_amount = 100000, agents_amount = 100, test_cnt = 5;
    ind_ef1_time_test(goods_amount, agents_amount, test_cnt);
    // ind_ef1_set_time_component(goods_amount, agents_amount, test_cnt);

    // ind_ef1_order_test();

    // int goods_amount = 5;
    // UtilityQueryable* agent1 = new HomoDivUnitIndFunction(goods_amount);
    // UtilityQueryable* agent2 = new HomoDivUnitIndFunction(goods_amount);
    // two_agent_EFa_demo(agent1, agent2, goods_amount);

    // int goods_amount = 10, agents_amount = 4;
    // auto agent = new HomoDivIncIndFunction(goods_amount, 0, 10);
    // identical_agents_EFfa_demo(agent, 4, goods_amount);

    // int goods_amount = 20, agents_amount = 4;
    // auto agent1 = new HomoDivCustIndFunction(vector<double>({4, 5, 5, 6, 5, 4, 5, 4, 3, 4, 5, 5, 6, 5, 4, 5, 4, 3, 5, 6}), 8);
    // auto agent2 = new HomoDivCustIndFunction(vector<double>({6, 4, 5, 3, 4, 7, 4, 6, 5, 6, 4, 5, 3, 4, 7, 4, 6, 5, 3, 5}), 2);
    // auto agent3 = new HomoDivCustIndFunction(vector<double>({3, 4, 5, 3, 4, 6, 5, 4, 6, 3, 4, 5, 3, 4, 6, 5, 4, 6, 6, 4}), 6);
    // auto agent4 = new HomoDivCustIndFunction(vector<double>({7, 6, 4, 6, 7, 4, 6, 7, 5, 6, 5, 7, 5, 7, 4, 7, 3, 5, 6, 4}), 8);
    // propa_demo({agent1, agent2, agent3, agent4}, agents_amount, goods_amount);
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