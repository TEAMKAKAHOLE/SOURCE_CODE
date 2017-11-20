#pragma once
#include "SpritesObject.h"

class ProgressBarObject : public SpritesObject
{
private:
    ImageObject*        m_bgImg;
    ImageObject*        m_frameImg;
    double              gaugeRatioX;
    int                 maxWidth;

public:
    ProgressBarObject();
    ~ProgressBarObject();

    virtual void Update() override;
    virtual void Render(HDC hdc) override;

    void SetGaugeRatioX(double RatioX) { gaugeRatioX = RatioX; }
    void SetBgBar(ImageObject* Image) { m_bgImg = Image; }
    void SetFrameBar(ImageObject* Image) { m_frameImg = Image; }
};