#include "stdafx.h"
#include "ImageManager.h"


void ImageManager::AddImageList(string Scene)
{
    m_imgList = g_pFileManager->JsonFind(RSC_LIST_KEY);
    m_stLoadResult.nHead = 0;
    m_stLoadResult.nMax = (int)m_imgList[Scene]["images"].size();
    g_pLogManager->WriteLog(EL_INFO, Scene);
}

bool ImageManager::AddImageByJson(string Scene)
{
    int idx = m_stLoadResult.nHead;
    if (idx < m_stLoadResult.nMax)
    {
        //  Add images
        string key =        m_imgList[Scene]["images"][idx]["key"];
        string filename =   m_imgList[Scene]["images"][idx]["filename"];
        int width =         m_imgList[Scene]["images"][idx]["width"];
        int height =        m_imgList[Scene]["images"][idx]["height"];
        filename = "resources/" + Scene + "/images/" + filename;
        AddImage(key, Scene, filename, width, height);
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

ImageObject * ImageManager::AddImage(string Key, int Width, int Height)
{

    ImageObject* image = new ImageObject;
    image = AddImage(Key, "global", Width, Height);

    return image;
}

ImageObject * ImageManager::AddImage(string Key, string Scene, int Width, int Height)
{
    ImageObject* image = new ImageObject;
    image->Setup(Width, Height);
    image->SetSceneName(Scene);

    m_mapImage.insert(pair<string, ImageObject*>(Key, image));

    return image;
}

ImageObject * ImageManager::AddImage(string Key, string Scene, string Filename, int Width, int Height)
{
    //  overlapping check by tagname
    ImageObject* image = FindImage(Key);
    if (image == NULL)
    {
        g_pLogManager->WriteLog(EL_INFO, "Add new image");
        g_pLogManager->WriteLog(EL_INFO, Filename);
        image = new ImageObject;
        image->Setup(Filename.c_str(), Width, Height);
        image->SetSceneName(Scene);
        m_mapImage.insert(pair<string, ImageObject*>(Key, image));
    }
    else
    {
        g_pLogManager->WriteLog(EL_DEBUG, "Return already exist image");
    }

    return image;
}

ImageObject * ImageManager::FindImage(string Key)
{
    m_mapIter = m_mapImage.find(Key);
    //  Find correct
    if (m_mapIter != m_mapImage.end())
        return m_mapIter->second;
    else
        return NULL;
}

void ImageManager::Release(string Key)
{
    m_mapIter = m_mapImage.find(Key);
    if (m_mapIter != m_mapImage.end())
    {
        //  release memory of image
        SAFE_DELETE(m_mapIter->second);

        //  erase map data
        m_mapImage.erase(Key);
    }
}

void ImageManager::ReleaseByScene(string Scene)
{
    g_pLogManager->WriteLog(EL_INFO, "Image release by scene " + Scene);
    m_mapIter = m_mapImage.begin();
    while (m_mapIter != m_mapImage.end())
    {
        if (m_mapIter->second->IsSceneContain(Scene))
        {
            SAFE_DELETE(m_mapIter->second);
            m_mapIter = m_mapImage.erase(m_mapIter);
        }
        else
        {
            ++m_mapIter;
        }
    }
}

void ImageManager::ReleaseAll()
{
    m_mapIter = m_mapImage.begin();
    while (m_mapIter != m_mapImage.end())
    {
        SAFE_DELETE(m_mapIter->second);
        m_mapIter = m_mapImage.erase(m_mapIter);
    }
}

void ImageManager::Render(string Key, HDC hdc)
{
    Render(Key, hdc, UnitPos{ 0.0f, 0.0f });
}

void ImageManager::Render(string Key, HDC hdc, UnitPos DestPos)
{
    ImageObject* image = FindImage(Key);
    if (image)
    {
        image->Render(hdc, (int)DestPos.x, (int)DestPos.y);
    }
}

void ImageManager::Render(string Key, HDC hdc, int destX, int destY, int destW, int destH, int srcX, int srcY, int srcW, int srcH, int alpha)
{
	ImageObject* image = FindImage(Key);
	if (image)
	{
		image->Render(hdc, destX, destY, destW, destH, srcX, srcY, srcW, srcH, alpha);
	}
}
