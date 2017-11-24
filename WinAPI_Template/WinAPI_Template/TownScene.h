#pragma once
#include "GameNode.h"
#include "Player.h"
#include "Chief.h"
#include "Item.h"

class TownScene : public GameNode
{
private:
    json    m_playerData;

    ImageObject*    m_imgWorldBuffer;
    ImageObject*    m_imgWorldMap;
    ImageObject*    m_imgTerrainBuffer;
    ImageObject*    m_imgUiBuffer;

    GameObject      m_objExit;

    UnitPos m_startPos;
    UnitPos m_entrancePos;
    
    int     m_scnLevel;

    Player  m_player;
    Chief   m_chief;
    bool    m_isBossLevel;

    vector<Item>        m_vecItems;
    vector<Projectile>  m_vecBullet;

public:
    TownScene();
    ~TownScene();

    // GameNode을(를) 통해 상속됨
    virtual void Start() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;

    void SaveGame();
};