#ifndef UTILS
#define UTILS

#include <vector>
#include <set>
#include <numeric>
using std::vector;
using std::set;
using std::pair;

pair<set<int>, set<int>> two_agent_part2bundle (vector<int>& ind_partition) {
    set<int> bundle1, bundle2;
    for (int i = 0; i < ind_partition.size(); i++) {
        if (ind_partition[i] == 1) {
            bundle1.insert(i);
        } else {
            bundle2.insert(i);
        }
    }
    return {bundle1, bundle2};
}

vector<set<int>> part2bundle (vector<int>& ind_partition, int agents_amount) {
    vector<set<int>> bundles(agents_amount);
    for (int i = 0; i < ind_partition.size(); i++) {
        bundles[ind_partition[i] - 1].insert(i);
    }
    return bundles;
}

set<int> set02n(int n) {
    vector<int> vec(n);
    std::iota(vec.begin(), vec.end(), 0);
    return set<int>(vec.begin(), vec.end());
}

#include <chrono>

class TimerClock {
public:
    TimerClock() {
        update();
    }

    void update() {
        _start = std::chrono::high_resolution_clock::now();
    }

    double getTimerSecond() {
        return getTimerMicroSec()*0.000001;
    }

    double getTimerMilliSec() {
        return getTimerMicroSec()*0.001;
    }

    long long getTimerMicroSec() {
        return std::chrono::duration_cast<std::chrono::microseconds>
            (std::chrono::high_resolution_clock::now() - _start).count();
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> _start;
};

#include <cstdlib>
vector<double> gen_utility_profile(int goods_amount, int mu, int r) {
    vector<double> vec;
    for (int i = 0; i < goods_amount; i++) {
        vec.push_back(rand() % (2 * r) + mu - r);
    }
    return vec;
}

#endif