#pragma once
#include "GameNode.h"
#include "Player.h"
#include "TelePort.h"
#include "Enemy.h"


class EscapeScene:public GameNode
{

private:
	ImageObject* m_imgWorldBuffer;
	ImageObject* m_imgWorldMap;
	ImageObject* m_imgTerrainBuffer;
    ImageObject*    m_imgUiBuffer;

	GameObject   m_EndPoint;   // 80,170
	GameObject   m_StartPoint; // 350,390 
	GameObject   m_Back;       //
	Player       m_player;
	Enemy        m_cEnemy[3];
	int          m_HP;
	int          m_Level;
	int          m_potion;
	int          m_atk;
	int          m_def;

	bool         m_bIsAct; //충돌중 카운트중지
	bool         m_bIngAct; //계속 충돌중인지 판단
	json         m_playerData;


	//마지막 탈출시 필요한 열쇠아이템 RECT이미지
	SpritesObject m_KeyItem1;
	//SpriteObject m_KeyItem2;
	//뒤로 돌아가는 씬
	SpritesObject m_BackScene;
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
	void  SceneBack();
	void  JsonAdd();
	void  JsonView();
	void  SetData();
	

};

