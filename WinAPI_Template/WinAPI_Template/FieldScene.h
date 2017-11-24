#pragma once
#include "GameNode.h"
#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"

class FieldScene : public GameNode
{
private:
	json		 m_playerData;
	ImageObject* m_imgWorldBuffer; // �� �̹����� �׸� ����
	ImageObject* m_imgWorldMap;  //���� �� �̹���
	ImageObject* m_imgTerrainBuffer; // ����Ÿ �� �׸� ����
	SpritesObject* m_imgAutoButton;
	SpritesObject* m_imgClose;
	ImageObject* m_imgBill;
	Player		 m_player;
	Enemy		 m_enemy;

	RECT m_rtTownPortal;
	RECT m_rtEscapePortal;
	RECT m_rtAwareness;  //���� �÷��̾ �ν��ϴ� ��Ʈ
	

    bool m_isClear;
	bool m_isDie;
	bool m_isTrackingPlayer;
	bool m_isBill;

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