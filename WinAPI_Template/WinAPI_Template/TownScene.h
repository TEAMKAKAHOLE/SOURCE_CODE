﻿#pragma once
#include "GameNode.h"
#include "Player.h"

class TownScene : public GameNode
{
private:
    ImageObject*    m_imgWorldBuffer;
    ImageObject*    m_imgWorldMap;
    ImageObject*    m_imgTerrainBuffer;
    ImageObject*    m_imgHud;
    ImageObject*    m_imgUiBuffer;
    SpritesObject*  m_sprHudNumber;
    SpritesObject*  m_sprHudLife;

    Player  m_player;

public:
    TownScene();
    ~TownScene();

    // GameNode을(를) 통해 상속됨
    virtual void Start() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;
};