#pragma once
#include "SingletonBase.h"

#define g_pDbManager DbManager::GetInstance()

#import "C:\\Program Files\\Common Files\\System\\ado\\msado15.dll" no_namespace rename("EOF", "EndOfFile")

#include <oledb.h>
#include <stdio.h>
#include <conio.h>
#include "icrsint.h"
class CAdo;
class DbManager : public SingletonBase<DbManager>
{
private:
    CAdo*        _db;

public:
    DbManager();
    virtual ~DbManager();
};

class CAdo
{
private:
    BOOL m_bIsConnected;
    HRESULT m_hresult;
    _ConnectionPtr m_pConn;
    _RecordsetPtr m_pRset;

public:
    CAdo();
    virtual ~CAdo();

#pragma region CONNECT
    BOOL        Connect(char* szDBServerIP, char* szDBName, char* szUserID, char* szUserPW);
    BOOL        Disconnect();
#pragma endregion

#pragma region CRUD
    void*       SQLExecute(char *szSQL);
    BOOL        SQLInsert(char* szTableName, char* szValues);
    _RecordsetPtr SQLSelect(char* szTableName);
    BOOL        SQLUpdate(char* szTableName, char* szSet, char* szWhere);
    BOOL        SQLDelete(char *szTableName, char *szWhere);
#pragma endregion
};