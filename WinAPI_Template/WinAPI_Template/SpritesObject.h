#pragma once
#include "GameObject.h"

#define DELAY_RESET_VAL 0

class ImageObject;
class SpritesObject : public GameObject
{
protected:
    bool            isAnimate;
    bool            isHorizonSprites;
    int             frameX;           //  Current sprites X position
    int             frameY;           //  Current sprites Y position
    int             maxFrameX;            //  Current sprites max of X
    int             maxFrameY;            //  Current sprites max of Y
    int             triggerFrameX;          //  Event trigger frame's x position
    double          delayCounter;         //  Change value each frame
    int             frameDelay;          //  Delay key value each frame

public:
    SpritesObject();
    ~SpritesObject();

#pragma region GET
    int     GetFrameX() { return frameX; }
    int     GetFrameY() { return frameY; }
    int     GetMaxFrameX() { return maxFrameX; }
    int     GetMaxFrameY() { return maxFrameY; }
    double  GetFrameDelay() { return frameDelay; }
    bool    IsTriggerFrame();
#pragma endregion
#pragma region SET
    void StartAnimation() { isAnimate = true; }
    void StopAnimation() { isAnimate = false; }
    void SetupForSprites(int MaxFrameX = 1, int MaxFrameY = 1);
    void SetFrameX(int FrameX) { frameX = FrameX; }
    void SetFrameY(int FrameY) { frameY = FrameY; }
    void SetMaxFrameX(int MaxFrameX) { maxFrameX = MaxFrameX; }
    void SetMaxFrameY(int MaxFrameY) { maxFrameY = MaxFrameY; }
    void SetTriggerPos(int Pos) { triggerFrameX = Pos; }
    void SetFrameDelay(int Delay) { frameDelay = Delay; }
    void NextFrame();           //  Automatic move next frame
#pragma endregion

#pragma region OVERRIDE
    virtual void Update() override;
    virtual void Render(HDC hdc) override;
#pragma endregion
};

