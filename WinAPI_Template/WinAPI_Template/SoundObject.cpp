#include "stdafx.h"
#include "SoundObject.h"


void SoundObject::Setup()
{
    m_pSound = NULL;
    m_pChannel = NULL;
    m_szScnName = "";
    m_isBgm = false;
    m_isLoop = false;
    m_szFilename = "";
}

void SoundObject::Release()
{
    if (m_pSound != NULL)
    {
        m_pSound = NULL;
        SAFE_DELETE(m_pSound);
    }

    if (m_pChannel != NULL)
    {
        m_pChannel = NULL;
        SAFE_DELETE(m_pChannel);
    }
}

SoundObject::SoundObject()
{
    Setup();
}


SoundObject::~SoundObject()
{
}