#pragma once
#include <mmsystem.h>
#pragma comment (lib, "winmm.lib")
//  timeGetTime 함수 사용을 위한 라이브러리
//  윈도우 시간 기준

class Timer
{
private:
    bool            m_isHardware;           //  고성능 타이머 지원 여부 확인
    float           m_fTimeScale;           //  시간 경과량
    float           m_fTimeElapsed;         //  프레임당 경과 시간
    __int64         m_nCurrTime;            //  현재 시간
    __int64         m_nLastTime;            //  마지막 시간
    __int64         m_nPeriodFrequency;     //  시간 주기

    unsigned int    m_nFrameRate;           //  FPS
    unsigned int    m_nFpsCount;            //  FPS counter
    float           m_fFpsTimeElapsed;      //  FPS 마지막 시간 - 현재 시간
    float           m_fWorldTime;           //  전체 경과 시간

public:
    Timer();
    ~Timer();

    
    void Tick(float lockFPS = 0.0f);                            //  현재 시간 계산
    unsigned int GetFPS(char* str = NULL) const;                //  현재 FPS 가져오기
    float GetElpasedTime() const { return m_fFpsTimeElapsed; }  //  한 프레임당 경과 시간 (1/ 60)
    float GetWorldTime() const { return m_fWorldTime; }         //  전체 경과 시간 가져오기
};

