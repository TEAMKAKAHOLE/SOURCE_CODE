#include "stdafx.h"
#include "ProgressBarObject.h"


ProgressBarObject::ProgressBarObject()
    : gaugeRatioX(1.0f)
    , maxWidth(0)
    , m_bgImg(NULL)
{
    SpritesObject::SpritesObject();
}


ProgressBarObject::~ProgressBarObject()
{
}

void ProgressBarObject::Update()
{
    SpritesObject::Update();
}

void ProgressBarObject::Render(HDC hdc)
{
    //  gauge bar bg render
    if (m_bgImg != NULL)
        m_bgImg->TransRender(hdc, m_rtBody.left, m_rtBody.top, m_nSize.w, m_nSize.h, 1.0f);

    //  gauge bar render
    if (m_imgBody != NULL)
        m_imgBody->TransRender(hdc, m_rtBody.left, m_rtBody.top, m_nSize.w, m_nSize.h, gaugeRatioX);
}
