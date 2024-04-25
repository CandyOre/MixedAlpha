#include "UtilityFunctions.h"
#include "Demos.h"
#include "Tests.h"
#include "IdenticalAgentsEFfa.h"

#include <iomanip>

void run() {
    // homo_div_unit_ind_test();
    // homo_div_inc_ind_test();

    // ind_ef1_order_test();

    int goods_amount = 5;
    UtilityQueryable* agent1 = new HomoDivUnitIndFunction(goods_amount);
    UtilityQueryable* agent2 = new HomoDivUnitIndFunction(goods_amount);
    two_agent_EFa_demo(agent1, agent2, goods_amount);

    // int goods_amount = 10, agents_amount = 4;
    // auto agent = new HomoDivIncIndFunction(goods_amount, 0, 10);
    // identical_agents_EFfa_demo(agent, 4, goods_amount);
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