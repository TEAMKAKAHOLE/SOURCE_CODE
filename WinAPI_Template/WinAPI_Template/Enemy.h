#pragma once
#include "SpritesObject.h"

enum E_DIRECTION{LEFT,TOP,RIGHT,BOTTOM,MAX};



class Enemy : public SpritesObject
{
private:
	int m_currStatus;
	E_DIRECTION m_eDirection;
	float m_fGoalsTime;
	bool  m_isCheck;
	bool m_isTrackingPlayer;
	RECT  m_rtAwareness;
	
	ImageObject*    m_imgTerrainBuffer;

public:
	Enemy();
	~Enemy();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void EnemyMove();
	int GetRandom(int min, int max);

	RECT  GetAwarenessRect() { return m_rtAwareness; }
	bool  GetTrackingPlayer() { return m_isTrackingPlayer; }

	void SetTerrainBuffer(ImageObject* ImgTerrain) { m_imgTerrainBuffer = ImgTerrain; }
	void SetTrackingPlayer(bool isTrackingPlayer) { m_isTrackingPlayer = isTrackingPlayer; }
	void CheckCollision();
	
};

