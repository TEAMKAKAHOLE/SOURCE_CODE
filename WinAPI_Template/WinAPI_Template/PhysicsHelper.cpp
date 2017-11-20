#include "stdafx.h"
#include "PhysicsHelper.h"

bool PhysicsHelper::IsCollision(GameObject* Unit1, GameObject* Unit2)
{
    RECT tempRt;
    return IntersectRect(&tempRt, &Unit1->GetHBoxRect(), &Unit2->GetHBoxRect());
}

void PhysicsHelper::BoxCollider(GameObject* Unit1, vector<GameObject>* VecUnit2, int DmgDeal1, int DmgDeal2)
{
    for (auto iter2 = VecUnit2->begin(); iter2 != VecUnit2->end(); iter2++)
    {
        if (IsCollision(Unit1, iter2._Ptr))
        {
            Unit1->SumLife(DmgDeal1);
            iter2->SumLife(DmgDeal2);
        }
    }
}

void PhysicsHelper::BoxCollider(vector<GameObject>* VecUnit1, vector<GameObject>* VecUnit2, int DmgDeal1, int DmgDeal2)
{
    for (auto iter = VecUnit1->begin(); iter != VecUnit1->end(); iter++)
    {
        for (auto iter2 = VecUnit2->begin(); iter2 != VecUnit2->end(); iter2++)
        {
            if (IsCollision(iter._Ptr, iter2._Ptr))
            {
                iter->SumLife(DmgDeal1);
                iter2->SumLife(DmgDeal2);
            }
        }
    }
}