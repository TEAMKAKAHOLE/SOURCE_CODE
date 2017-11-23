#pragma once
#include "GameNode.h"
#include "SpritesObject.h"

class TitleScene : public GameNode
{
private:
    ImageObject*    m_imgTitleBg;

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