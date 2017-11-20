#pragma once
#include "SingletonBase.h"

class RandomHelper : public SingletonBase<RandomHelper>
{
private:

public:
    RandomHelper();
    ~RandomHelper();

    int GetRandomNumber();
    int GetRandomNumber(bool IsReverseSign);
    int GetRandomNumber(int Max, bool IsReverseSign);
    int GetRandomNumber(int Begin, int End, bool IsReverseSign);

    

};

