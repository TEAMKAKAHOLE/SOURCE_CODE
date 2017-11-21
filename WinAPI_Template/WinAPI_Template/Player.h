#pragma once
#include "SpritesObject.h"
class Player : public SpritesObject
{
private:

public:
	Player();
	~Player();

	void Start();
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void PlayerController();
};

