#pragma once
#include "SingletonBase.h"
#include "GameObject.h"

#define g_pPhxsHelper PhysicsHelper::GetInstance()
#define _PERFECTLY_ELASTIC_COLLISION

#ifdef _PERFECTLY_ELASTIC_COLLISION             //  완전탄성충돌
    #define RESTITUTION_COEF    1.0f
#elif _PERFECTLY_INELASTIC_COLLISION            //  완전비탄성충돌
    #define RESTITUTION_COEF    0.0f
#else
    #define RESTITUTION_COEF    0.75f           //  충돌계수
#endif

class PhysicsHelper : public SingletonBase<PhysicsHelper>
{
public:
    bool    IsCollision(GameObject* Unit1, GameObject* Unit2);
    void    BoxCollider(GameObject* Unit1, vector<GameObject>* VecUnit2, int DmgDeal1, int DmgDeal2);
    void    BoxCollider(vector<GameObject>* VecUnit1, vector<GameObject>* VecUnit2, int DmgDeal1, int DmgDeal2);
};