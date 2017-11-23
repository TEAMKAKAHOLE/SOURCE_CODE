#pragma once
#include "GameNode.h"
#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"

class FieldScene : public GameNode
{
private:
	json		 m_playerData;
	ImageObject* m_imgWorldBuffer; // 맵 이미지를 그릴 버퍼
	ImageObject* m_imgWorldMap;  //원본 맵 이미지
	ImageObject* m_imgTerrainBuffer; // 마젠타 맵 그릴 버퍼
	Player		 m_player;
	Enemy		 m_enemy;

	RECT m_rtTownPortal;
	RECT m_rtEscapePortal;
	RECT m_rtAwareness;  //적이 플레이어를 인식하는 렉트

    bool m_isClear;
	bool m_isDie;
	bool m_isTrackingPlayer;

	int m_nEnemyPosY[5];
	int m_nscnLevel;

	double m_dbAngle;
	double m_dbCoordFromeAngle;

	vector<Enemy>       m_vecEnemy;
    vector<Projectile>  m_vecBullets;

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