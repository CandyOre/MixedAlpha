#ifndef UtilityQueryModel
#define UtilityQueryModel

#include <vector>
#include <set>
#include <algorithm>

class UtilityQueryable {
    public:
        // Robertson-Webb Query
        virtual const double eval(double left, double right) = 0;
        virtual const double cut(double left, double target) = 0;
        // Indivisible Goods Query
        const double get(int idx) {
            if (idx >= ind_amount || idx < 0) {
                return -1;
            }
            return ind_utility[idx];
        }
        const double get(std::set<int> idxes) {
            double sum = 0;
            for (const auto& idx : idxes) {
                if (idx >= ind_amount || idx < 0) {
                    return -1;
                }
                sum += ind_utility[idx];
            }
            return sum;
        }
    protected:
        int ind_amount;
        std::vector<int> ind_utility;
};

#endif