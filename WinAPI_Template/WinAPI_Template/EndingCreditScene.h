#pragma once
#include "GameNode.h"
#include "SpritesObject.h"

class EndingCreditScene : public GameNode
{
private:
    SpritesObject*  m_sprEndingCredit;

public:
    EndingCreditScene();
    ~EndingCreditScene();

    // GameNode을(를) 통해 상속됨
    virtual void Start() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;
};