#include "stdafx.h"
#include "SpritesObject.h"
#include "ImageObject.h"

SpritesObject::SpritesObject()
    : frameX(0)
    , frameY(0)
    , maxFrameX(1)
    , maxFrameY(1)
    , triggerFrameX(-1)
    , delayCounter(0)
    , frameDelay(0)
    , isAnimate(false)
    , isHorizonSprites(false)
{
    GameObject::GameObject();
}

SpritesObject::~SpritesObject()
{
}

bool SpritesObject::IsTriggerFrame()
{
    if (triggerFrameX == GetFrameX()) 
        return true; 
    else 
        return false;
}

void SpritesObject::NextFrame()
{
    if (isAnimate)
    {
        ++delayCounter;
        if (delayCounter > frameDelay)
        {
            delayCounter = DELAY_RESET_VAL;
            if (isHorizonSprites == false)
            {
                ++frameX;
                frameX = frameX > maxFrameX ? 0 : frameX;
            }
            else
            {
                ++frameY;
                frameY = frameY > maxFrameY ? 0 : frameY;
            }
        }
    }
}

void SpritesObject::SetupForSprites(int MaxFrameX, int MaxFrameY)
{
    m_imgBody->SetSpritesSize({ m_imgBody->GetWidth() / MaxFrameX
                              , m_imgBody->GetHeight() / MaxFrameY });
    maxFrameX = MaxFrameX - 1;
    maxFrameY = MaxFrameY - 1;
}

void SpritesObject::Update()
{
    NextFrame();
    GameObject::Update();
}

void SpritesObject::Render(HDC hdc)
{
    if (m_isVisible == true)
    {
        if (m_imgBody != NULL)
        {
            m_imgBody->SpritesRender(hdc, m_rtBody, frameX, frameY, m_dAlpha);
        }
    }
    GameObject::Render(hdc);
}