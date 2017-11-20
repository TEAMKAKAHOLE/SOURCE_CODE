#pragma once

#include "SingletonBase.h"
#include <bitset>

#define g_pKeyManager KeyManager::GetInstance()
#define KEYMAX 256

class KeyManager : public SingletonBase<KeyManager>
{
private:
    bitset<KEYMAX> m_bitKeyUp;
    bitset<KEYMAX> m_bitKeyDown;

public:
    void Setup();

    bool isOnceKeyDown(int key);
    bool isOnceKeyUp(int key);
    bool isStayKeyDown(int key);
    bool isToggleKy(int key);
};

