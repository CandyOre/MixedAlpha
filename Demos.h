#ifndef DEMOS
#define DEMOS

#include "./Model//UtilityQueryModels.h"
#include "./Algoithm/Agent2EFa.h"
#include "./Algoithm/IdenticalAgentsEFfa.h"
#include "./Algoithm/Propa.h"
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
    print("[0,1]\t不可分割比例");

    cout << "参与者1效用\t";
    for (int i = 0; i < goods_amount; i++) {
        cout << agent1->get(i) << "\t";
    }
    print(agent1->eval(0, 1), "\t", agent1->alpha());

    cout << "参与者2效用\t";
    for (int i = 0; i < goods_amount; i++) {
        cout << agent2->get(i) << "\t";
    }
    print(agent2->eval(0, 1), "\t", agent2->alpha());


    print("2. 算法分配结果");
    Allocation allocation = two_agent_EFa(agent1, agent2, goods_amount);
    set<int> bundle1 = allocation.get_ind_bundle(1);
    set<int> bundle2 = allocation.get_ind_bundle(2);
    set<pair<double,double>> div_bundle1 = allocation.get_div_bundle(1);
    set<pair<double,double>> div_bundle2 = allocation.get_div_bundle(2);

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
    print("[0,1]\t不可分割比例");

    cout << "参与者效用\t";
    for (int i = 0; i < goods_amount; i++) {
        cout << agent->get(i) << "\t";
    }
    print(agent->eval(0, 1), "\t", agent->alpha());
    print(agent->get(set02n(goods_amount)));

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

    cout << "参与者效用\t";
    for (int i = 0; i < agents_amount; i++) {
        cout << allocation.get_utility(i + 1, agent) << "\t";
    }
    cout << endl;
}

void propa_demo (vector<UtilityQueryable*> agents, int agents_amount, int goods_amount) {
    print("==== 求解实例满足PROPa指标的分配算法的演示 ====");


    print("1. 参与者的物品效用表格：");
    cout << "物品编号\t\t";
    for (int i = 0; i < goods_amount; i++) {
        cout << i << "\t";
    }
    print("[0,1]\t不可分割比例");

    for (int i = 0; i < agents_amount; i++) {
        cout << "参与者" << i + 1 << "的效用\t";
        auto& agent = agents[i];
        for (int i = 0; i < goods_amount; i++) {
            cout << agent->get(i) << "\t";
        }
        print(agent->eval(0, 1), "\t", agent->alpha());
        // print(agent->get(set02n(goods_amount)));
    }

    print("2. 算法分配结果");
    Allocation allocation = propa(agents, agents_amount, goods_amount);
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
        cout << "B" << i << "\t";
    }
    cout << endl;

    for (int i = 0; i < agents_amount; i++) {
        cout << "参与者" << i + 1 << "效用\t";
        auto& agent = agents[i];
        for (int i = 0; i < agents_amount; i++) {
            cout << allocation.get_utility(i + 1, agent) << "\t";
        }
        cout << endl;
    }
}


#endif