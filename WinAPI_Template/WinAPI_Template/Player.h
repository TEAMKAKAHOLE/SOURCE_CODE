#pragma once
#include "SpritesObject.h"


class Player : public SpritesObject
{
private:
	int m_currStatus;
	ImageObject* m_imgTerrainBuffer;
	
public:
	Player();
	~Player();
	
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void PlayerController();

	//Set
	void SetTerrainBuffer(ImageObject* Terrain) { m_imgTerrainBuffer = Terrain; }
};

