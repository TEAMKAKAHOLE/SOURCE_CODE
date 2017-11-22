#pragma once
#include "GameNode.h"
#include "Player.h"
#include "TelePort.h"


class EscapeScene:public GameNode
{

private:
	ImageObject* m_imgWorldBuffer;
	ImageObject* m_imgWorldMap;
	ImageObject* m_imgTerrainBuffer;
	GameObject  m_EndPoint;   // 80,170
	GameObject  m_StartPoint; // 350,390 
	Player   m_player;


	//마지막 탈출시 필요한 열쇠아이템 RECT이미지
	SpritesObject m_KeyItem1;
	//GameObject m_KeyItem2;
	bool m_bKeyItem1;
	//bool m_bKeyItme2;

	TelePort m_teleportA;
	TelePort m_teleportB;
	TelePort m_teleportC;
	TelePort m_teleportD;


public:
	EscapeScene();
	virtual ~EscapeScene();

	virtual  void  Start()    override;
	virtual  void  Update()   override;
	virtual  void  Render()   override;
	virtual  void  Release()  override;
	void  SceneChange();
};

