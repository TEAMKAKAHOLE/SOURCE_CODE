#include "stdafx.h"
#include "SoundManager.h"


SoundManager::SoundManager()
{
    System_Create(&m_pSystem);

    m_pSystem->init(TOTAL_SOUND_BUFFER, FMOD_INIT_NORMAL, NULL);
}


SoundManager::~SoundManager()
{
    if (m_pSystem != NULL)
    {
        m_pSystem->release();
        m_pSystem->close();
    }
}

void SoundManager::Update()
{
    m_pSystem->update();
}

void SoundManager::AddSound(string Key, string Scene, string Filename, bool IsBgm, bool IsLoop)
{
    g_pLogManager->WriteLog(EL_INFO, "Add new sound");
    g_pLogManager->WriteLog(EL_INFO, Key + " : " + Filename);

    SoundObject* newSound = new SoundObject;
    newSound->SetFilename(Filename);
    newSound->SetScnName(Scene);
    newSound->SetBgm(IsBgm);
    newSound->SetLoop(IsLoop);

    if (IsLoop)
        if (IsBgm)
            m_pSystem->createStream(Filename.c_str(), FMOD_LOOP_NORMAL, NULL, &newSound->m_pSound);
        else
            m_pSystem->createSound(Filename.c_str(), FMOD_LOOP_NORMAL, NULL, &newSound->m_pSound);
    else
        m_pSystem->createSound(Filename.c_str(), FMOD_DEFAULT, NULL, &newSound->m_pSound);
    
    m_mapSounds.insert(make_pair(Key, newSound));
    newSound = NULL;
    SAFE_DELETE(newSound);
}

void SoundManager::Play(string Key, float volume)
{
    m_iterSounds = m_mapSounds.find(Key);
    if (m_iterSounds != m_mapSounds.end())
    {
        m_pSystem->playSound(FMOD_CHANNEL_FREE
            , m_iterSounds->second->m_pSound
            , false
            , &m_iterSounds->second->m_pChannel);
    }
    else
    {
        string szError = Key + " NO CHANNEL TO PLAY";
        g_pLogManager->WriteLog(EL_ERROR, szError);
    }
    
}

void SoundManager::Stop(string Key)
{
    m_iterSounds = m_mapSounds.find(Key);
    if (m_iterSounds != m_mapSounds.end())
    {
        m_iterSounds->second->m_pChannel->stop();
    }
    else
    {
        string szError = Key + " NO CHANNEL TO STOP";
        g_pLogManager->WriteLog(EL_ERROR, szError);
    }
}

void SoundManager::Pause(string Key)
{
    m_iterSounds = m_mapSounds.find(Key); 
    if (m_iterSounds != m_mapSounds.end())
    {
        m_iterSounds->second->m_pChannel->setPaused(true);
    }
    else
    {
        string szError = Key + " NO CHANNEL TO PAUSE";
        g_pLogManager->WriteLog(EL_ERROR, szError);
    }
}

void SoundManager::Resume(string Key)
{
    m_iterSounds = m_mapSounds.find(Key);
    if (m_iterSounds != m_mapSounds.end())
    {
        m_iterSounds->second->m_pChannel->setPaused(false);
    }
    else
    {
        string szError = Key + " NO CHANNEL TO RESUME";
        g_pLogManager->WriteLog(EL_ERROR, szError);
    }
}

bool SoundManager::IsPlay(string Key)
{
    bool isPlay = false;
    m_iterSounds = m_mapSounds.find(Key);
    if (m_iterSounds != m_mapSounds.end())
    {
        m_iterSounds->second->m_pChannel->isPlaying(&isPlay);
    }
    else
    {
        string szError = Key + " NO CHANNEL PLAYING";
        g_pLogManager->WriteLog(EL_ERROR, szError);
    }

    return isPlay;
}

bool SoundManager::IsPause(string Key)
{
    bool isPause = false;
    m_iterSounds = m_mapSounds.find(Key);
    if (m_iterSounds != m_mapSounds.end())
    {
        m_iterSounds->second->m_pChannel->getPaused(&isPause);
    }
    else
    {
        string szError = Key + " NO CHANNEL PAUSED";
        g_pLogManager->WriteLog(EL_ERROR, szError);
    }

    return isPause;
}

void SoundManager::PlayAndPause(string Key)
{
    if (IsPause(Key))
        Resume(Key);
    else
        Pause(Key);
}

void SoundManager::AddSoundList(string Scene)
{
    m_sndList = g_pFileManager->JsonFind(RSC_LIST_KEY);
    m_stLoadResult.nHead = 0;
    m_stLoadResult.nMax = (int)m_sndList[Scene]["sounds"].size();
    g_pLogManager->WriteLog(EL_INFO, Scene);
}

bool SoundManager::AddSoundByJson(string Scene)
{
    int idx = m_stLoadResult.nHead;
    if (idx < m_stLoadResult.nMax)
    {
        //  Add images
        string key = m_sndList[Scene]["sounds"][idx]["key"];
        string filename = m_sndList[Scene]["sounds"][idx]["filename"];
        bool isBgm = m_sndList[Scene]["sounds"][idx]["bgm"];
        bool isLoop = m_sndList[Scene]["sounds"][idx]["loop"];
        filename = "resources/" + Scene + "/sounds/" + filename;
        AddSound(key, Scene, filename, isBgm, isLoop);
        g_pLogManager->WriteLog(EL_INFO, key);
        g_pLogManager->WriteLog(EL_INFO, filename);
        ++m_stLoadResult.nHead;
        return true;
    }
    else
    {
        return false;
    }
}

void SoundManager::ReleaseAll()
{
    m_iterSounds = m_mapSounds.begin();
    while (m_iterSounds != m_mapSounds.end())
    {
        if (m_iterSounds->second != NULL)
        {
            m_iterSounds->second->m_pChannel->stop();
            m_iterSounds->second->Release();
            SAFE_DELETE(m_iterSounds->second);
            m_iterSounds = m_mapSounds.erase(m_iterSounds);
        }
        else
        {
            ++m_iterSounds;
        }
    }
}

void SoundManager::ReleaseByScene(string Scene)
{
    g_pLogManager->WriteLog(EL_INFO, "Sound release by scene " + Scene);
    m_iterSounds = m_mapSounds.begin();
    while (m_iterSounds != m_mapSounds.end())
    {
        if (m_iterSounds->second != NULL &&
            m_iterSounds->second->GetScnName() == Scene)
        {
            m_iterSounds->second->m_pChannel->stop();
            m_iterSounds->second->Release();
            m_iterSounds = m_mapSounds.erase(m_iterSounds);
        }
        else
        {
            ++m_iterSounds;
        }
    }
}