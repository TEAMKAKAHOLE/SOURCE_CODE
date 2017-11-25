#pragma once
#include "GameNode.h"
#include "Player.h"
#include "Ghost.h"

class HardwayScene : public GameNode
{
private:
    json            m_playerData;

    ImageObject*    m_imgWorldBuffer;
    ImageObject*    m_imgWorldMap;
    ImageObject*    m_imgTerrainBuffer;
    ImageObject*    m_imgGhostShot;
    ImageObject*    m_imgUiBuffer;

    SpritesObject*    m_rtExit;

    bool            m_isDead;
    bool            m_isEventStart;
    bool            m_isStartGhost;
    bool            m_isPursuing;
    bool            m_isGoingX;
    int                m_nPusuingDelay;
    int                m_nRenderShotTime;
    int                m_nSoundPlayerCount;
    int                m_nShakePosX;
    int                m_nShakePosY;

    Player            m_Player;
    Ghost            m_Ghost;




public:
    HardwayScene();
    virtual ~HardwayScene();

    virtual void Start() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;
};

