#include "stdafx.h"
#include "MapObject.h"


MapObject::MapObject()
{
    GameObject::GameObject();
    m_imgBody = g_pImgManager->FindImage("world-map-buffer");
    m_imgMapBuffer = NULL;
}

MapObject::~MapObject()
{
}

void MapObject::Start()
{
}

void MapObject::Update()
{
}

void MapObject::Render(HDC hdc)
{
}

void MapObject::AddObject(GameObject GameObj)
{
    m_vecObjs.push_back(GameObj);
}

void MapObject::ApplyGravity(GameObject * GameObj)
{
    GameObj->SumBodySpeedY(1.0f);
    UnitPos ProbePos = GameObj->GetBodyPos();
    ProbePos.y += GameObj->GetBodySize().h * 0.5f;
    if (g_pPixelManager->CheckPixelMagenta(m_imgMapBuffer, ProbePos) == false)
    {
        GameObj->SetBodySpeedY(0.0f);
        while (g_pPixelManager->CheckPixelMagenta(m_imgMapBuffer, ProbePos) == false)
        {
            GameObj->SumBodyPosY(-1.0f);
        }
    }
}
