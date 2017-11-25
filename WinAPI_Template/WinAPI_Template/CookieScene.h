#pragma once
#include "GameNode.h"
#include "SpritesObject.h"

#define COOKIE_FADE_OUT_STEP    4.0f

class CookieScene : public GameNode
{
private:
    ImageObject*        m_imgBuffer;
    SpritesObject*      m_sprHotsLogo;
    SpritesObject*      m_sprHotsSpinner;
    SpritesObject*      m_sprFadeout;

    double m_dFadeoutAlpha;
    double m_dSpinnerAngle;

    bool    m_isFadeout;
    float   m_showingTime;
public:
    CookieScene();
    ~CookieScene();

    // GameNode을(를) 통해 상속됨
    virtual void Start() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;
};