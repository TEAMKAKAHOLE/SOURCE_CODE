#include "stdafx.h"
#include "RatingHelper.h"


RatingHelper::RatingHelper()
{
}


RatingHelper::~RatingHelper()
{
}

void RatingHelper::EloCalc(int * Rating1, int * Rating2, int Winner)
{
    double varR1 = 10 ^ (*Rating1 / 400);
    double varR2 = 10 ^ (*Rating2 / 400);
    double varE1 = varR1 / (varR1 + varR2);
    double varE2 = varR2 / (varR1 + varR2);
    double varWDL1 = 0.0f;
    double varWDL2 = 0.0f;
    switch (Winner)
    {
    case 1:
        //	P1 Win
        varWDL1 = 1.0f;
        break;
    case 2:
        //	P2 Win
        varWDL2 = 1.0f;
        break;
    case 3:
        //	Draw
        varWDL1 = 0.5f;
        varWDL2 = 0.5f;
    default:
        break;
    }

    double varRating1 = *Rating1 + (CONST_K * (varWDL1 - varE1));
    double varRating2 = *Rating2 + (CONST_K * (varWDL2 - varE2));

    *Rating1 = (int)varRating1;
    *Rating2 = (int)varRating2;
}
