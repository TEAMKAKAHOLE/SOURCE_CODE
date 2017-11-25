#pragma once
#include "GameNode.h"
#include "SpritesObject.h"

class TitleScene : public GameNode
{
private:
    json            m_playerData;
    ImageObject*    m_imgTitleBg;
    SpritesObject    m_imgSword;
    SpritesObject*    m_imgStar[5];

    int                m_nOnStar;
    int                m_nRanIndex;
    int                m_nRanIndex2;
public:
    TitleScene();
    virtual ~TitleScene();

    // GameNode을(를) 통해 상속됨
    virtual void Start() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;

    void InputController();
};