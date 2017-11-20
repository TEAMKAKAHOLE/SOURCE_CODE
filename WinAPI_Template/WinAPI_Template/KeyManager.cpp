#include "stdafx.h"
#include "KeyManager.h"

void KeyManager::Setup()
{
    for (int i = 0; i < KEYMAX; i++)
    {
        m_bitKeyUp.set(i, false);
        m_bitKeyDown.set(i, true);
    }
}

bool KeyManager::isOnceKeyDown(int key)
{
    if (GetAsyncKeyState(key) & 0x8000)
    {
        if (!m_bitKeyDown[key])
        {
            m_bitKeyDown.set(key, true);
            return true;
        }
    }
    else
    {
        m_bitKeyDown.set(key, false);
    }

    return false;
}

bool KeyManager::isOnceKeyUp(int key)
{
    if (GetAsyncKeyState(key) & 0x8000)
    {
        m_bitKeyUp.set(key, true);
    }
    else
    {
        if (m_bitKeyUp[key])
        {
            m_bitKeyUp.set(key, false);
            return true;
        }
    }

    return false;
}

bool KeyManager::isStayKeyDown(int key)
{
    if (GetAsyncKeyState(key) & 0x8000)
    {
        return true;
    }
    return false;
}

bool KeyManager::isToggleKy(int key)
{
    if (GetKeyState(key) & 0x0001)
    {
        return true;
    }
    return false;
}
