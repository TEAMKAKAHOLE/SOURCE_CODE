#pragma once
#include "SpritesObject.h"


class Player:public SpritesObject
{

private:
	
	

public:
	Player();
	~Player();
	virtual void Update();
	void Start();
	virtual void Render(HDC hdc);
	void PlayerController();

	
};

