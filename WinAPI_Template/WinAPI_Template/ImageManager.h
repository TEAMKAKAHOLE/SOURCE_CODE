#pragma once
#include "SingletonBase.h"
#include "ImageObject.h"

#define g_pImgManager ImageManager::GetInstance()

class ImageManager : public SingletonBase<ImageManager>
{
private:
    map<string, ImageObject*>               m_mapImage;
    map<string, ImageObject*>::iterator     m_mapIter;

    LoadResult  m_stLoadResult;
    json        m_imgList;

public:
    LoadResult GetLoadResult() { return m_stLoadResult; }

    void    AddImageList(string Scene);
    bool    AddImageByJson(string Scene);

    //  Add image
    ImageObject* AddImage(string Key, int Width, int Height);
    ImageObject* AddImage(string Key, string Scene, int Width, int Height);
    ImageObject* AddImage(string Key, string Scene, string Filename, int Width, int Height);

    //  Search image and remove
    ImageObject* FindImage(string Key);
    void Release(string Key);
    void ReleaseByScene(string Scene);
    void ReleaseAll();

    //  Renderer
    void Render(string Key, HDC hdc);
    void Render(string Key, HDC hdc, UnitPos DestPos);
	void Render(string Key, HDC hdc, int destX, int destY, int destW, int destH, int srcX, int srcY, int srcW, int srcH, int alpha);
};