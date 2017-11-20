#pragma once
#include "GameNode.h"

class ExitScene : public GameNode
{
private:
    float m_fCurrTime;

public:
    ExitScene();
    virtual ~ExitScene();

    // GameNode을(를) 통해 상속됨
    virtual void Start() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;
};

