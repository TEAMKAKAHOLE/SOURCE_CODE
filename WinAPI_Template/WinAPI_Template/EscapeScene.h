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

	bool         m_bIsAct; //�浹�� ī��Ʈ����
	bool         m_bIngAct; //��� �浹������ �Ǵ�
	json         m_playerData;


	//������ Ż��� �ʿ��� ��������� RECT�̹���
	SpritesObject m_KeyItem1;
	//SpriteObject m_KeyItem2;
	//�ڷ� ���ư��� ��
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

