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
    SpritesObject*  m_sprFadeout;
    GameObject      m_objExit;

    UnitPos m_startPos;
    UnitPos m_entrancePos;

    UnitPos m_viewportPos;

    int     m_scnLevel;
    double  m_dFadeoutAlpha;

    Player  m_player;
    Chief   m_chief;
    bool    m_isBossLevel;

    vector<Item>        m_vecItems;
    vector<Projectile>  m_vecBullet;

    float   m_fEndTimer;

    bool    m_isGameClear;
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