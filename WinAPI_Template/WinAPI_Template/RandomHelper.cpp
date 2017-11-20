#include "stdafx.h"
#include "RandomHelper.h"


RandomHelper::RandomHelper()
{
}


RandomHelper::~RandomHelper()
{
}

int RandomHelper::GetRandomNumber()
{
    srand((unsigned int)time(NULL));
    return rand();
}

int RandomHelper::GetRandomNumber(bool IsReverseSign)
{
    int retRandomNumber = GetRandomNumber();
    if (IsReverseSign)
    {
        retRandomNumber = -retRandomNumber;
    }

    return retRandomNumber;
}

int RandomHelper::GetRandomNumber(int Max, bool IsReverseSign)
{
    int retRandomNumber = GetRandomNumber() % Max;
    if (IsReverseSign)
    {
        retRandomNumber = -retRandomNumber;
    }

    return retRandomNumber;
}

int RandomHelper::GetRandomNumber(int Begin, int End, bool IsReverseSign)
{
    int retRandomNumber = (GetRandomNumber() % (End - Begin) + Begin);

    if (IsReverseSign)
    {
        retRandomNumber = -retRandomNumber;
    }

    return retRandomNumber;
}

