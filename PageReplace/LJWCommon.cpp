#include "LJWCommon.h"
#include <assert.h>
#include <iostream>

namespace LJWCode {
    LJWCommon* LJWCommon::_instance = nullptr;

    LJWCommon* LJWCommon::Instance() {
        if (_instance == nullptr) {
            _instance = new LJWCommon();

            _instance->rng = std::mt19937(_instance->dev());
            _instance->dist = std::uniform_real_distribution<float>(0., 1.);
        }
        return _instance;
    }

    void LJWCommon::ReleaseInstance() {
        if (_instance != nullptr) {
            delete _instance;
            _instance = nullptr;
        }
    }

    //LJWCommon::LJWCommon()
    //{
    //    // 这里会有问题, 就是如果this指向一个局部变量,那么会导致空指针问题
    //    if (Instance == nullptr) {
    //        Instance = this;
    //        this->rng = std::mt19937(this->dev());
    //        this->dist = std::uniform_real_distribution<float>(0., 1.);
    //    }
    //}
    
    int LJWCommon::Random(int left, int right)
    {
        float lerp = dist(rng);

        assert(0. <= lerp && lerp <= 1.);

        int result = left + std::floor((right - left) * lerp);
        return result == right ? right - 1 : result;
    }
    bool LJWCommon::LimitNumericalCin(int left, int right, int& result)
    {
        using namespace std;
        
        // cin receive input stream method I dont know clearly
        cin >> result;

        if (left <= result && result < right) {
            return true;
        }

        return false;
    }
}
