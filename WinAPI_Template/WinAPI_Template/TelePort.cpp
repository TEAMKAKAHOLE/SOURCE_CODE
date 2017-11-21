#include "stdafx.h"
#include "TelePort.h"


TelePort::TelePort()
{
	//시작과 동시에  위치 이동 세팅을 한다.
	//if out일 경우에는 센터에서 이격거리를 준다
	//안그러면 충돌체크 다시 발생해서 이상한 위치로 이동
	AGateIn.x  = 385*4;
	AGateIn.y  = 300 * 4;

	AGateOut.x = 250 * 4;
	AGateOut.y = 250 * 4;


	BGateIn.x = 418*4;
	BGateIn.y = 208*4;

	BGateOut.x = 92 * 4;
	BGateOut.y = 290 * 4;

	CGateIn.x = 250 * 4;
	CGateIn.y = 250 * 4;

	CGateOut.x = 80*4;
	CGateOut.y = 170*4;

	DGateIn.x = 92 * 4;
	DGateIn.y = 290 * 4;

	DGateOut.x = 385 * 4;
	DGateOut.y = 300 * 4;





	GameObject::GameObject();


}


TelePort::~TelePort()
{

}

void TelePort::Update()
{
	GameObject::Update();
}

void TelePort::Render(HDC hdc)
{
	//부모오브젝트의  랜더를 사용하겠다.
	GameObject::Render(hdc);
}

void TelePort::telePort(int x, int y)
{

}
