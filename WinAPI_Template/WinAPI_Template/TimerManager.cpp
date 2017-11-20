#include "stdafx.h"
#include "TimerManager.h"

bool TimerManager::AddSimpleTimer(string Key)
{
    m_mapSimpleIter = m_mapSimpleTimer.find(Key);
    if (m_mapSimpleIter != m_mapSimpleTimer.end())
    {
        return false;
    }
    else
    {
        m_mapSimpleTimer.insert(make_pair(Key, 0));
        return true;
    }
}

bool TimerManager::AddOnOffTimer(string Key, UnitPos ShiftPos, float Tick, float Multiplier)
{
    m_mapOnOffIter = m_mapOnOffTimer.find(Key);
    if (m_mapOnOffIter != m_mapOnOffTimer.end())
    {
        return false;
    }
    else
    {
        m_mapOnOffTimer.insert(make_pair(Key, (0.0f + (float)ShiftPos.x)));
        m_mapOnOffTick.insert(make_pair(Key, Tick));
        m_mapOnOffMltply.insert(make_pair(Key, Multiplier));
        m_mapOnOffShiftY.insert(make_pair(Key, (float)ShiftPos.y));
        return true;
    }
}

int TimerManager::FindSimpleTick(string Key)
{
    m_mapSimpleIter = m_mapSimpleTimer.find(Key);
    if (m_mapSimpleIter != m_mapSimpleTimer.end())
    {
        return m_mapSimpleIter->second;
    }
    else
    {
        return -1;  //   -1 find fail
    }
}

float TimerManager::FindOnOffTick(string Key)
{
    m_mapOnOffIter = m_mapOnOffTimer.find(Key);
    if (m_mapOnOffIter != m_mapOnOffTimer.end())
    {
        //  found
        float angle = m_mapOnOffIter->second;
        m_mapOnOffIter->second += m_mapOnOffTick.find(Key)->second;
        if (m_mapOnOffIter->second > 360.0f)
            m_mapOnOffIter->second = 0.0f;
        float result = sinf(angle);
        return (result * m_mapOnOffMltply.find(Key)->second ) + m_mapOnOffShiftY.find(Key)->second;
    }
    else
    {
        return 0.0f;
    }
}

bool TimerManager::SetSimpleTick(string Key, int Tick)
{
    m_mapSimpleIter = m_mapSimpleTimer.find(Key);
    if (m_mapSimpleIter != m_mapSimpleTimer.end())
    {
        m_mapSimpleIter->second = Tick;
        return true;
    }
    else
    {
        return false;
    }
}

int TimerManager::TickSimpleTimer(string Key)
{
    if (SetSimpleTick(Key, FindSimpleTick(Key) + 1))
    {
        return FindSimpleTick(Key);
    }
    else
    {
        return -1;
    }
}

bool TimerManager::ResetSimpleTimer(string Key)
{
    m_mapSimpleIter = m_mapSimpleTimer.find(Key);
    if (m_mapSimpleIter != m_mapSimpleTimer.end())
    {
        m_mapSimpleIter->second = 0;
        return true;
    }
    else
    {
        return false;
    }
}

bool TimerManager::TickOnOffTimer(string Key)
{
    float tick = FindOnOffTick(Key);

    //  -1.0f ~ tick ~ +1.0f
    if (tick >= m_mapOnOffShiftY.find(Key)->second)
        return true;
    else
        return false;
}

bool TimerManager::DeleteSimpleTimerByKey(string Key)
{
    m_mapSimpleIter = m_mapSimpleTimer.find(Key);
    if (m_mapSimpleIter != m_mapSimpleTimer.end())
    {
        m_mapSimpleTimer.erase(m_mapSimpleIter);
        return true;
    }
    else
    {
        return false;
    }
}

void TimerManager::DeleteTimerAll()
{
    m_mapSimpleIter = m_mapSimpleTimer.begin();
    while (m_mapSimpleIter != m_mapSimpleTimer.end())
    {
        m_mapSimpleIter = m_mapSimpleTimer.erase(m_mapSimpleIter);
    }
}

TimerManager::TimerManager()
{
    m_pTimer = new Timer;
}

TimerManager::~TimerManager()
{
    SAFE_DELETE(m_pTimer);
}

void TimerManager::Update(float lock)
{
    if (m_pTimer)
    {
        m_pTimer->Tick(lock);
    }
}

void TimerManager::Render()
{
#ifdef _DEBUG
    if (m_pTimer)
    {
        char str[128];
        string strFrame;

        SetBkMode(g_hDC, BKMODE_LAST);
        SetTextColor(g_hDC, RGB(0, 0, 255));
        SetTextAlign(g_hDC, TA_LEFT);
        //  FPS
        sprintf_s(str, "FPS : %d", m_pTimer->GetFPS());
        TextOut(g_hDC, 0, 0, str, (int)strlen(str));
#ifdef FPS_TEST
        g_pLogManager->WriteLog(EL_DEBUG, str);
#endif // FPS_TEST
        //  World Time
        sprintf_s(str, "World Time : %f", m_pTimer->GetWorldTime());
        TextOut(g_hDC, 0, 15, str, (int)strlen(str));
        //  Elapsed Time
        sprintf_s(str, "Elapsed Time : %f", m_pTimer->GetElpasedTime());
        TextOut(g_hDC, 0, 30, str, (int)strlen(str));
    }
#endif // _DEBUG
}
