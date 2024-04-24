#ifndef DEMOS
#define DEMOS

#include "UtilityQueryModels.h"
#include "Agent2EFa.h"
#include "IdenticalAgentsEFfa.h"
#include <vector>
#include <set>
#include <iostream>

using std::vector;
using std::set;
using std::cin, std::cout, std::endl;

void print() {
    cout << endl;
}
template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    for (auto& ele : vec) {
        os << ele << ' ';
    }
    return os;
}
template<typename T>
std::ostream& operator<<(std::ostream& os, const std::set<T>& vec) {
    for (auto& ele : vec) {
        os << ele << ' ';
    }
    return os;
}
template <typename Head, typename... Tail>
void print(Head head, Tail... tail) {
    cout << head << ' ';
    print(tail...);
}

void two_agent_EFa_demo (UtilityQueryable* agent1, UtilityQueryable* agent2, int goods_amount) {
    print("==== 两位参与者的EFa分配算法的演示 ====");


    print("1. 参与者的物品效用表格：");
    cout << "物品编号\t";
    for (int i = 0; i < goods_amount; i++) {
        cout << i << "\t";
    }
    print("可分割物品[0,1]");

    cout << "参与者1效用\t";
    for (int i = 0; i < goods_amount; i++) {
        cout << agent1->get(i) << "\t";
    }
    print(agent1->eval(0, 1));

    cout << "参与者2效用\t";
    for (int i = 0; i < goods_amount; i++) {
        cout << agent2->get(i) << "\t";
    }
    print(agent2->eval(0, 1));


    print("2. 算法分配结果");
    Allocation allocation = two_agent_EFa(agent1, agent2, goods_amount);
    set<int> bundle1 = allocation.get_ind_bundle(1);
    set<int> bundle2 = allocation.get_ind_bundle(2);
    set<pair<int,int>> div_bundle1 = allocation.get_div_bundle(1);
    set<pair<int,int>> div_bundle2 = allocation.get_div_bundle(2);

    cout << "参与者1的包裹： ";
    for (const auto& idx : bundle1) {
        cout << idx << " ";
    }
    for (const auto& [l, r] : div_bundle1) {
        cout << "[" << l << ", " << r << ")" << " ";
    }
    print("");

    cout << "参与者2的包裹： ";
    for (const auto& idx : bundle2) {
        cout << idx << " ";
    }
    for (const auto& [l, r] : div_bundle2) {
        cout << "[" << l << ", " << r << ")" << " ";
    }
    print("");


    print("3. 效用函数水平，检查是否满足公平指标");
    std::cerr << "run utility level\n";
    cout << "包裹编号\t" << "包裹1\t" << "包裹2" << endl;;
    cout << "参与者1效用\t"
         << allocation.get_utility(1, agent1) << "\t"
         << allocation.get_utility(2, agent1) << endl;
    cout << "参与者2效用\t" 
         << allocation.get_utility(1, agent2) << "\t" 
         << allocation.get_utility(2, agent2) << endl;
}

void identical_agents_EFfa_demo (UtilityQueryable* agent, int agents_amount, int goods_amount) {
    print("==== 求解参与者效用相同的实例的最佳EFf(a)分配算法的演示 ====");


    print("1. 参与者的物品效用表格：");
    cout << "物品编号\t";
    for (int i = 0; i < goods_amount; i++) {
        cout << i << "\t";
    }
    print("可分割物品[0,1]");

    cout << "效用值\t";
    for (int i = 0; i < goods_amount; i++) {
        cout << agent->get(i) << "\t";
    }
    print(agent->eval(0, 1));

    print("2. 算法分配结果");
    Allocation allocation = identical_agents_EFfa(agent, agents_amount, goods_amount);
    for (int i = 0; i < agents_amount; i++) {
        cout << "参与者 " << i << " 的包裹：";
        for (const auto& e : allocation.get_ind_bundle(i + 1)) {
            cout << e << " ";
        }
        for (const auto& [l, r] : allocation.get_div_bundle(i + 1)) {
            cout << "[" << l << ", " << r << ")" << " ";
        }
        cout << endl;
    }

    print("3. 效用函数水平");

    cout << "包裹编号\t";
    for (int i = 0; i < agents_amount; i++) {
        cout << "包裹" << i << "\t";
    }
    cout << endl;
    cout << "效用值\t";
    for (int i = 0; i < agents_amount; i++) {
        cout << allocation.get_utility(i + 1, agent);
    }
    cout << endl;
}


#endif