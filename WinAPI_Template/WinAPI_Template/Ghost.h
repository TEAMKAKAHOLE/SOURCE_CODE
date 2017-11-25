#pragma once
#include "SpritesObject.h"

enum EG_DIRECTION { E_LEFT, E_TOP, E_RIGHT, E_BOTTOM, E_MAX };

class Ghost :public SpritesObject
{
private:
    int m_currStatus;
    EG_DIRECTION m_egDirection;
    float m_fGoalsTime;
    bool  m_isCheck;
    RECT  m_rtAwareness;

    ImageObject*    m_imgTerrainBuffer;

public:
    Ghost();
    ~Ghost();

    virtual void Update() override;
    virtual void Render(HDC hdc) override;

    void GhostMove();
    int GetRandom(int min, int max);

    RECT  GetAwarenessRect() { return m_rtAwareness; }
    void SetTerrainBuffer(ImageObject* ImgTerrain) { m_imgTerrainBuffer = ImgTerrain; }
    int GetDirection() { return m_egDirection; }
    void SetDirection(enum EG_DIRECTION direction) { m_egDirection = direction; }

    void CheckCollision();
};
