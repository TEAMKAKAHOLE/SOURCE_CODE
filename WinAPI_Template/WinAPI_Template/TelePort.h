#pragma once
#include "GameObject.h"

class TelePort:public GameObject
{

private:


	POINT  AGateIn;
	POINT  AGateOut;
	POINT  BGateIn;
	POINT  BGateOut;
	POINT  CGateIn;
	POINT  CGateOut;
	POINT  DGateIn;
	POINT  DGateOut;
	




    RECT  m_rtAGate;
	RECT  m_rtBGate;


public:
	TelePort();
	~TelePort();
	void Update();
	virtual void Render(HDC hdc);
	void  telePort(int x,int y);
};

