#pragma once
#include "SingletonBase.h"

#define g_pPixelManager PixelCollision::GetInstance()

class PixelCollision : public SingletonBase<PixelCollision>
{
private:
public:
    //  IF PIXEL == MAGENTA -> TRUE
    bool    CheckPixelMagenta(ImageObject* ImageObj, UnitPos Pos);
    bool    CheckPixelMagenta(ImageObject * ImageObj, int x, int y);
    //  Calculate angle between 2 Points
    void    GetAngle(ImageObject* ImageObj, double& Angle, UnitPos Probe, double Dist, double Precision = 1.0f);

    //  REMOVE PIXEL
    void    RemovePixel(ImageObject* ImageObj, UnitPos Pos);
    //  REMOVE AREA RECT
    void    RemoveRect(ImageObject* ImageObj, RECT Rt);
    //  REMOVE AREA ELLIPSE
    void    RemoveEllipse(ImageObject* ImageObj, RECT Rt);
};

