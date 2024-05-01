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
        double eval(double left, double right) const {
            return right - left;
        }
        double cut(double left, double target) const {
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
        double eval(double left, double right) const {
            return (right - left) * div_value;
        }
        double cut(double left, double target) const {
            return std::min(1., left + target / div_value);
        }
    private:
        double div_value;
};

class HomoDivCustIndFunction : public UtilityQueryable {
    public:
        // init
        HomoDivCustIndFunction(vector<double> _ind_utility, double _div_value) {
            ind_amount = _ind_utility.size();
            ind_utility = _ind_utility;
            div_value = _div_value;
        }
        // divisible goods
        double eval(double left, double right) const {
            return (right - left) * div_value;
        }
        double cut(double left, double target) const {
            return std::min(1., left + target / div_value);
        }
    private:
        double div_value;
};


#endif