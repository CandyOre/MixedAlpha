#ifndef UTILITY_FUNCTIONS
#define UTILITY_FUNCTIONS

#include "UtilityQueryModels.h"

class HomoDivUnitIndFunction: public UtilityQueryable {
    public:
        // init
        HomoDivUnitIndFunction(int _ind_amount) {
            ind_amount = _ind_amount;
            ind_utility.resize(ind_amount);
            for (auto& e : ind_utility) e = 1;
        }
        // divisible goods
        const double eval(double left, double right) {
            return right - left;
        }
        const double cut(double left, double target) {
            return std::min(1., left + target);
        }
};

class HomoDivIncIndFunction : public UtilityQueryable {
    public:
        // init
        HomoDivIncIndFunction(int _ind_amount, int start, double _div_value) {
            ind_amount = _ind_amount;
            div_value = _div_value;
            ind_utility.resize(ind_amount);
            for (int i = 0; i < ind_amount; i++) {
                ind_utility[(start + i) % ind_amount] = i + 1;
            }
        }
        // divisible goods
        const double eval(double left, double right) {
            return (right - left) * div_value;
        }
        const double cut(double left, double target) {
            return std::min(1., left + target / div_value);
        }
    private:
        double div_value;
};


#endif