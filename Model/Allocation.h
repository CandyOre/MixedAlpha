#ifndef ALLOCATION
#define ALLOCATION

#include "UtilityQueryModels.h"
#include "../Utils.h"
#include <vector>
#include <set>
using std::vector;
using std::set;
using std::pair;

class Allocation {
    public:
        Allocation(int _ind_amount) 
        : ind_amount(_ind_amount), ind_partition(_ind_amount, 1), div_partition(1, {0, 0}) {}

        // modify functions
        int set_ind_partition(int idx, int agent_idx) {
            if (idx >= ind_amount || idx < 0) return -1;
            ind_partition[idx] = agent_idx;
            return 0;
        }

        int set_div_next_piece(double r, int agent_idx) {
            if (r > 1 || r <= div_partition.back().first) return -1;
            div_partition.back().second = agent_idx;
            div_partition.push_back({r, 0});
            return 0;
        }

        int swap_bundle(int agent_idx1, int agent_idx2) {
            for (auto& idx : ind_partition) {
                if (idx == agent_idx1) {
                    idx = agent_idx2;
                } else if (idx == agent_idx2) {
                    idx = agent_idx1;
                }
            }
            for (auto& [r, idx] : div_partition) {
                if (idx == agent_idx1) {
                    idx = agent_idx2;
                } else if (idx == agent_idx2) {
                    idx = agent_idx1;
                }
            }
            return 0;
        }

        // query functions
        int get_ind_partition(int idx) {
            if (idx >= ind_amount || idx < 0) return -1;
            return ind_partition[idx];
        }

        set<int> get_ind_bundle(int agent_idx) {
            set<int> bundle;
            for (int i = 0; i < ind_amount; i++) {
                if (ind_partition[i] == agent_idx) {
                    bundle.insert(i);
                }
            }
            return bundle;
        }

        set<pair<double, double>> get_div_bundle(int agent_idx) {
            set<pair<double, double>> bundle;
            double r = 1;
            for (int i = div_partition.size() - 2; i > -1; i--) {
                auto [l, idx] = div_partition[i];
                if (idx == agent_idx) {
                    bundle.insert({l, r});
                }
                r = l;
            }
            return bundle;
        }

        double get_utility(int agent_idx, UtilityQueryable* agent) {
            auto ind_bundle = get_ind_bundle(agent_idx);
            auto div_bundle = get_div_bundle(agent_idx);
            double utility = 0;
            utility += agent->get(ind_bundle);
            for (auto [l, r] : div_bundle) {
                utility += agent->eval(l, r);
            }
            return utility;
        }

    private:
        int ind_amount;
        vector<int> ind_partition;
        vector<pair<double,int>> div_partition;
};


#endif