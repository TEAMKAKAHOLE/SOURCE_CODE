#pragma once
#include "GameNode.h"
#include "SpritesObject.h"

class SplashScene : public GameNode
{
private:
    bool    m_isStart;
    float   m_fDestTime;
public:
    SplashScene();
    virtual ~SplashScene();

    // GameNode��(��) ���� ��ӵ�
    virtual void Start() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;
};