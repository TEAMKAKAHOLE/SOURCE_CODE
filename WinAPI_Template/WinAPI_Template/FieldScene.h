#pragma once
#include "GameNode.h"
#include "Player.h"
#include "Enemy.h"



class FieldScene : public GameNode
{

private:
	ImageObject* m_imgWorldBuffer; // �� �̹����� �׸� ����
	ImageObject* m_imgWorldMap;  //���� �� �̹���
	ImageObject* m_imgTerrainBuffer; // ����Ÿ �� �׸� ����
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

