#pragma once
#include "GameNode.h"
class CookieScene : public GameNode
{
public:
    CookieScene();
    ~CookieScene();

    // GameNode을(를) 통해 상속됨
    virtual void Start() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;
};