#pragma once
#include "GameNode.h"
#include "Player.h"
#include "Enemy.h"



class FieldScene : public GameNode
{

private:
	ImageObject* m_imgWorldBuffer; // 맵 이미지를 그릴 버퍼
	ImageObject* m_imgWorldMap;  //원본 맵 이미지
	ImageObject* m_imgTerrainBuffer; // 마젠타 맵 그릴 버퍼
	Player		 m_player;
	Enemy		 m_enemy;


public:
	FieldScene();
	virtual ~FieldScene();

	virtual void Start() override;
	virtual void Update();
	virtual void Render() override;
	virtual void Release() override;

};

