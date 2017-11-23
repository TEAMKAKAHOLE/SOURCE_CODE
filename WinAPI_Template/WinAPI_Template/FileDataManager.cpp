#include "stdafx.h"
#include "FileDataManager.h"

void FileDataManager::TextSave(string Filename, string JsonString)
{
    ofstream fileOut;
    fileOut.open(Filename, ios_base::out);
    fileOut << JsonString;
    fileOut.close();
}

void FileDataManager::JsonSave(string Filename, json JsonData)
{
    ofstream fileOut;
    fileOut.open(Filename, ios_base::out);
    fileOut << JsonData.dump(4);
    fileOut.close();
}

json FileDataManager::JsonLoad(string Filename)
{
    json loadData;     //  remove comments
    ifstream i(Filename);
    if (!i.bad())   //  file loaded
        i >> loadData;
    return loadData;
}

json FileDataManager::JsonLoad(string Key, string Filename)
{
    json loadData;     //  remove comments
    ifstream i(Filename);
    if (!i.bad())   //  file loaded
    {
        auto releaseIter = m_mapJsonData.find(Key);
        if (releaseIter != m_mapJsonData.end())
            return releaseIter->second;

        i >> loadData;

        m_mapJsonData.insert(pair<string, json>(Key, loadData));
        return loadData;
    }
    else
    {
        return loadData;
    }
}

void FileDataManager::JsonRelease(string Key)
{
    auto releaseIter = m_mapJsonData.find(Key);
    if (releaseIter != m_mapJsonData.end())
        m_mapJsonData.erase(releaseIter);
}

json FileDataManager::JsonFind(string Key)
{
    auto findIter = m_mapJsonData.find(Key);
    if (findIter != m_mapJsonData.end())
        return m_mapJsonData.find(Key)->second;
    else
        return nullptr;
}

void FileDataManager::JsonUpdate(string Key, json JsonData)
{
    m_mapJsonData.find(Key)->second = JsonData;
}

void FileDataManager::FileAppend(string Filename, string StringData)
{
    ofstream fileOut;
    fileOut.open(Filename, ios_base::app);
    fileOut << StringData;
    fileOut.close();
}

string FileDataManager::MakeCsvString(vector<string> VecArray)
{
    string szBuffer = "";

    for (int i = 0; i < (int)VecArray.size(); i++)
    {
        szBuffer.append(VecArray[i]);
        szBuffer.append(",");
    }

    return szBuffer;
}

vector<string> FileDataManager::CharArraySeperation(char CharArray[])
{
    vector<string> vecArray;
    char* temp = NULL;
    char* separator = ",";
    char* token;

    token = strtok_s(CharArray, separator, &temp);
    if (token != NULL)
        vecArray.push_back(token);

    while ((token = strtok_s(NULL, separator, &temp)) != NULL)
    {
        vecArray.push_back(token);
    }

    return vecArray;
}

void FileDataManager::Tokenizer(const string & str, vector<string>& tokens, const string & token)
{
    // 맨 첫 글자가 구분자인 경우 무시
    string::size_type lastPos = str.find_first_not_of(token, 0);
    // 구분자가 아닌 첫 글자를 찾는다
    string::size_type pos = str.find_first_of(token, lastPos);

    while (string::npos != pos || string::npos != lastPos)
    {
        // token을 찾았으니 vector에 추가한다
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // 구분자를 뛰어넘는다.  "not_of"에 주의하라
        lastPos = str.find_first_not_of(token, pos);
        // 다음 구분자가 아닌 글자를 찾는다
        pos = str.find_first_of(token, lastPos);
    }
}
