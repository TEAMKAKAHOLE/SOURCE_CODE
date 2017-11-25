#pragma once
#include "GameNode.h"
#include "SpritesObject.h"

#define CREDIT_SCROLL_SPEED     1.0f
#define CREDIT_WIDTH            W_WIDTH
#define CREDIT_HEIGHT           9000

class EndingCreditScene : public GameNode
{
private:
    ImageObject*    m_imgEndingCreditBuffer;
    SpritesObject*  m_sprEndingCredit;
    UnitPos         m_dViewPortPos;
    RectMargin      m_nVpMargin;

public:
    EndingCreditScene();
    ~EndingCreditScene();

    // GameNode을(를) 통해 상속됨
    virtual void Start() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;
};