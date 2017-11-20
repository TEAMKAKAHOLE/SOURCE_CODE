#pragma once
#include "SingletonBase.h"

#define g_pFileManager FileDataManager::GetInstance()

class FileDataManager : public SingletonBase<FileDataManager>
{
private:
    map<string, json>   m_mapJsonData;

public:
    void    TextSave(string Filename, string JsonString);
    void    JsonSave(string Filename, json JsonData);
    json    JsonLoad(string Filename);
    json    JsonLoad(string Key, string Filename);
    json    JsonFind(string Key);
    void    JsonUpdate(string Key, json JsonData);
    void    JsonRelease(string Key);
    void    FileAppend(string Filename, string StringData);

    string  MakeCsvString(vector<string> VecArray);
    vector<string>  CharArraySeperation(char CharArray[]);
    void Tokenizer(const string& str, vector<string>& tokens, const string& token = ",");
};