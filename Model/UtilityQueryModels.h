#ifndef UtilityQueryModel
#define UtilityQueryModel

#include "../Utils.h"
#include <vector>
#include <set>
#include <algorithm>

class UtilityQueryable {
    public:
        // Robertson-Webb Query
        virtual double eval (double left, double right) const = 0;
        virtual double cut(double left, double target) const = 0;
        // Indivisible Goods Query
        double get(int idx) const {
            if (idx >= ind_amount || idx < 0) {
                return -1;
            }
            return ind_utility[idx];
        }
        double get(std::set<int> idxes) const {
            double sum = 0;
            for (const auto& idx : idxes) {
                if (idx >= ind_amount || idx < 0) {
                    return -1;
                }
                sum += ind_utility[idx];
            }
            return sum;
        }
        double alpha() const {
            double uM = get(set02n(ind_amount)), uC = eval(0, 1);
            return uM / (uM + uC);
        }
    protected:
        int ind_amount;
        std::vector<double> ind_utility;
};

#endif