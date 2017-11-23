#pragma once
#include "GameNode.h"
#include "SpritesObject.h"

class SplashScene : public GameNode
{
private:
    ImageObject*    m_imgLogo;

    bool    m_isStart;
    float   m_fDestTime;
	int		m_nAlpha;
	int		m_nAlphaPlus;

public:
    SplashScene();
    virtual ~SplashScene();

    // GameNode을(를) 통해 상속됨
    virtual void Start() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;
};