#include "stdafx.h"
#include "Timer.h"


Timer::Timer()
{
    //  고성능 타이머 지원 여부 체크
    if (QueryPerformanceFrequency((LARGE_INTEGER*)&m_nPeriodFrequency))
    {
        m_isHardware = true;
        QueryPerformanceCounter((LARGE_INTEGER*)&m_nLastTime);

        m_fTimeScale = 1.0f / m_nPeriodFrequency;
    }
    else
    {
        m_isHardware = false;
        m_nLastTime = timeGetTime();
        m_fTimeScale = 0.001000f;           //  FIXED VALUE 1ms
    }

    //  타이머 관련 변수들 초기화
    m_nFrameRate = 0;
    m_nFpsCount = 0;
    m_fFpsTimeElapsed = 0.0f;
    m_fWorldTime = 0.0f;
}


Timer::~Timer()
{
}

void Timer::Tick(float lockFPS)
{
    //  고성능 타이머 확인
    if (m_isHardware)
    {
        //  마이크로세컨드 단위로 계산
        QueryPerformanceCounter((LARGE_INTEGER*)&m_nCurrTime);
    }
    else
    {
        m_nCurrTime = timeGetTime();
    }

    //  DELTA TIME
    m_fTimeElapsed = (m_nCurrTime - m_nLastTime) * m_fTimeScale;

    if (lockFPS > 0.0f)
    {
        while (m_fTimeElapsed < (1.0f / lockFPS))
        {
            if (m_isHardware)
            {
                QueryPerformanceCounter((LARGE_INTEGER*)&m_nCurrTime);
            }
            else
            {
                m_nCurrTime = timeGetTime();
            }

            m_fTimeElapsed = (m_nCurrTime - m_nLastTime) * m_fTimeScale;
        }
    }

    m_nLastTime = m_nCurrTime;
    m_nFpsCount++;
    m_fFpsTimeElapsed += m_fTimeElapsed;
    m_fWorldTime += m_fTimeElapsed;

    if (m_fFpsTimeElapsed > 1.0f)
    {
        m_nFrameRate = m_nFpsCount;
        m_nFpsCount = 0;
        m_fFpsTimeElapsed = 0.0f;
    }
}

unsigned int Timer::GetFPS(char * str) const
{
    return m_nFrameRate;
}
