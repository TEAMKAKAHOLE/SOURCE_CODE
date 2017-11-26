#pragma once
#include "SingletonBase.h"
#include "SoundObject.h"

#define SOUND_BUFFER 512
#define EXTRA_CHANNEL_BUFFER 128
#define TOTAL_SOUND_BUFFER (SOUND_BUFFER + EXTRA_CHANNEL_BUFFER)

#define g_pSndManager  SoundManager::GetInstance()

class SoundManager : public SingletonBase<SoundManager>
{
private:
    map<string, SoundObject*>            m_mapSounds;
    map<string, SoundObject*>::iterator  m_iterSounds;

    System*     m_pSystem;

    LoadResult  m_stLoadResult;
    json        m_sndList;

public:
    SoundManager();
    ~SoundManager();

    void Update();
    void AddSound(string Key, string Scene, string Filename, bool IsBgm = false, bool IsLoop = false);

    void Play(string Key, float volume = 1.0f);
    void Stop(string Key);
    void Pause(string Key);
    void Resume(string Key);
    bool IsPlay(string Key);
    bool IsPause(string Key);

    void PlayAndPause(string Key);
    LoadResult GetLoadResult() { return m_stLoadResult; }

    void    AddSoundList(string Scene);
    bool    AddSoundByJson(string Scene);

    void    ReleaseAll();
    void    ReleaseByScene(string Scene);
};

