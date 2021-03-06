#pragma once
#include "GameNode.h"
#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"
#include "Item.h"

class FieldScene : public GameNode
{
private:
    json         m_playerData;
    ImageObject* m_imgWorldBuffer; // 맵 이미지를 그릴 버퍼
    ImageObject* m_imgWorldMap;  //원본 맵 이미지
    ImageObject* m_imgTerrainBuffer; // 마젠타 맵 그릴 버퍼
    ImageObject*    m_imgUiBuffer;

    SpritesObject* m_imgAutoButton;
    SpritesObject* m_imgClose;
    SpritesObject* m_imgXbox;
    ImageObject* m_imgBill;
    ImageObject* m_imgError;

    Player         m_player;
    Enemy         m_enemy;

    RECT m_rtTownPortal;
    RECT m_rtEscapePortal;
    RECT m_rtAwareness;  //적이 플레이어를 인식하는 렉트
    
    bool m_isTutorial;
    bool m_isClear;
    bool m_isDie;
    bool m_isTrackingPlayer;
    bool m_isBill;
    bool m_isError;

    int m_scnLevel;
    int m_nEnemyPosY[5];
    int m_nscnLevel;
	int m_nSoundPlayCount;

    double m_dbAngle;
    double m_dbCoordFromeAngle;

    vector<Enemy>       m_vecEnemy;
    vector<Projectile>  m_vecBullets;
    vector<Item>        m_vecItems;

public:
    FieldScene();
    virtual ~FieldScene();

    virtual void Start() override;
    virtual void Update();
    virtual void Render() override;
    virtual void Release() override;

    void MakeEnemy(int count);

    int GetRandom(int min, int max);
    void SaveGame();

    void CheckClear();
};