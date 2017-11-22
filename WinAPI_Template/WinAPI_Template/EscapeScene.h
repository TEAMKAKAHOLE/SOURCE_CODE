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

	Player   m_player;
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
};

