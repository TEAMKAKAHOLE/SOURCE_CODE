#include "stdafx.h"
#include "ViewPortObject.h"


ViewPortObject::ViewPortObject()
{
}


ViewPortObject::~ViewPortObject()
{
}

void ViewPortObject::MoveStart(UnitPos Dest)
{
    m_destPos = Dest;
    m_bIsArrive = false;
    m_dT = 0.0f;
}

void ViewPortObject::Update()
{
    if (m_bIsArrive)
    {
    }
    else
    {
        //  linear interpolation
        if (m_currPos.x <= m_destPos.x + DBL_EPSILON &&
            m_currPos.x >= m_destPos.x - DBL_EPSILON &&
            m_currPos.y <= m_destPos.y + DBL_EPSILON &&
            m_currPos.y >= m_destPos.y - DBL_EPSILON)
        {
            m_bIsArrive = true;
            m_currPos = m_destPos;
        }
        
    }
    g_pGeoHelper->LinearInterpolation(m_currPos, m_startPos, m_destPos, m_dT);
    m_dT += 0.1f;
    if (m_dT > 1.0f)
    {
        m_dT = 1.0f;
    }
}

RECT ViewPortObject::MakeViewPort(UnitSize LimitSize)
{
    RECT rtViewPort = g_pDrawHelper->MakeRect(m_currPos, { W_WIDTH, W_HEIGHT });
    if (rtViewPort.left < 0)
    {
        rtViewPort.left = 0;
        rtViewPort.right = rtViewPort.left + W_WIDTH;
    }
    else if (rtViewPort.right > LimitSize.w)
    {
        rtViewPort.right = LimitSize.w;
        rtViewPort.left = rtViewPort.right - W_WIDTH;
    }

    if (rtViewPort.top < 0)
    {
        rtViewPort.top = 0;
        rtViewPort.bottom = rtViewPort.top + W_HEIGHT;
    }
    else if (rtViewPort.bottom > LimitSize.h)
    {
        rtViewPort.bottom = LimitSize.h;
        rtViewPort.top = rtViewPort.bottom - W_HEIGHT;
    }

    return rtViewPort;
}
