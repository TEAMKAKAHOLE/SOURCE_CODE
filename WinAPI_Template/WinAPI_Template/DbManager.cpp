#include "stdafx.h"
#include "DbManager.h"

#pragma region CAdo
CAdo::CAdo()
{
    g_pLogManager->WriteLog(EL_INFO, "CAdo constructor called");
    m_pConn = NULL;
    m_bIsConnected = NULL;
    m_pRset = NULL;
    m_hresult = S_OK;
}

CAdo::~CAdo()
{
    g_pLogManager->WriteLog(EL_INFO, "CAdo destructor called");
    if (m_bIsConnected)
    {
        g_pLogManager->WriteLog(EL_INFO, "CAdo has connection. Will close it");
        m_pConn->Close();
        CoInitialize(NULL);
    }
}

BOOL CAdo::Connect(char * szDBServerIP, char * szDBName, char * szUserID, char * szUserPW)
{
    g_pLogManager->WriteLog(EL_INFO, "CAdo::Connect called");
    if (m_bIsConnected)
    {
        g_pLogManager->WriteLog(EL_WARNING, "DB is Already connected");
        return TRUE;
    }
    g_pLogManager->WriteLog(EL_INFO, "DB will connected");

    char szCon[256];
    memset(szCon, 0x00, sizeof(szCon));
    sprintf_s(szCon
        , "Provider=SQLOLEDB;Data Source=%s; Initial catalog=%s;User ID=%s;Password=%s;"
        , szDBServerIP, szDBName, szUserID, szUserPW);

    //Initialize the COM Library
    CoInitialize(NULL);


    m_hresult = m_pConn.CreateInstance((__uuidof(Connection)));
    if (FAILED(m_hresult))
    {
        g_pLogManager->WriteLog(EL_ERROR, "Instantiating failed Connection Object");
        CoUninitialize();
        return FALSE;
    }

    m_hresult = m_pConn->Open(szCon, "", "", 0);
    if (FAILED(m_hresult))
    {
        g_pLogManager->WriteLog(EL_ERROR, "Opening failed DB object using Ado _Connection");
        CoUninitialize();
        return FALSE;
    }
    g_pLogManager->WriteLog(EL_INFO, "DB Conntected");
    g_pLogManager->WriteLog(EL_INFO, szDBServerIP);
    g_pLogManager->WriteLog(EL_INFO, szDBName);

    m_bIsConnected = TRUE;
    return TRUE;
}

BOOL CAdo::Disconnect()
{
    g_pLogManager->WriteLog(EL_INFO, "CAdo::Disconnect called");
    if (!m_bIsConnected)
    {
        g_pLogManager->WriteLog(EL_ALERT, "DB is Already disconnected");
        return TRUE;
    }
    m_pConn->Close();
    g_pLogManager->WriteLog(EL_INFO, "DB Closed");
    CoUninitialize();
    m_bIsConnected = FALSE;
    return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////
//Excute 하는방법 (쿼리문을 직접 작성하여 실행)
// Excute에 실패하면 NULL 리턴, 성공할경우 NULL 이외의 값(Select 의 경우 (_Recordset*) 리턴)
void * CAdo::SQLExecute(char * szSQL)
{
    g_pLogManager->WriteLog(EL_INFO, "CAdo::SQLExecute called");
    if (!m_bIsConnected)
    {
        g_pLogManager->WriteLog(EL_WARNING, "DB DISCONNECTED");
        return 0;
    }

    try
    {
        g_pLogManager->WriteLog(EL_INFO, "TRY SQL EXECUTE");
        m_pRset = m_pConn->Execute(szSQL, NULL, adCmdText);
    }
    catch (...)
    {
        g_pLogManager->WriteLog(EL_ERROR, "SQL EXECUTE FAILED : try catch error");
        return 0;
    }
    g_pLogManager->WriteLog(EL_INFO, "SQL EXECUTED");
    return m_pRset;
}

////////////////////////////////////////////////////////////////////////////////////
//Insert 하는방법
//Insert into szTableName Values(szValues) 의 형태로 사용
//예) Insert into dbo.Test values(1, 'hell world!') 의 경우는
//    SQLInsert("dbo.Test", "1, 'hell world!'"); 처럼 사용하면 됩니다.
//
//데이터가 올바르게 저장되면 TRUE 리턴, 저장 실패시 FALSE 리턴
BOOL CAdo::SQLInsert(char * szTableName, char * szValues)
{
    g_pLogManager->WriteLog(EL_INFO, "CAdo::SQLInsert called");
    if (!m_bIsConnected)
    {
        g_pLogManager->WriteLog(EL_WARNING, "DB DISCONNECTED");
        printf("DB is disconnected!\n");
        return FALSE;
    }

    try
    {
        g_pLogManager->WriteLog(EL_INFO, "TRY SQL INSERT");
        char szSQL[256];
        memset(szSQL, 0x00, sizeof(szSQL));
        sprintf_s(szSQL
            , "Insert into %s Values(%s)"
            , szTableName, szValues);

        //Execute the insert statement
        m_pConn->Execute(szSQL, NULL, adExecuteNoRecords);
    }
    catch (...)
    {
        g_pLogManager->WriteLog(EL_ERROR, "SQL INSERT FAILED : try catch");
        return FALSE;
    }

    g_pLogManager->WriteLog(EL_INFO, "SQL INSERTED");
    return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////
//Select 하는방법
//Select * from szTableName 의 형태로 사용
//예) Select * from dbo.Test 의 경우는
//    rs = SQLSelect("dbo.Test"); 처럼 사용하면 됩니다.
//
// Select에 성공하면 _RecordsetPtr 리턴, 실패시 0 리턴
//
//
//예) int형, varchar형의 컬럼을 가지는 테이블의 모든 데이터를 읽는 예
//_bstr_t bKeyContents;
//while(!pRs->EndOfFile)
//{
//	szNum[count]=pRs->GetCollect("nNum").intVal;  //정수형 일때 
//	bKeyContents=pRs->Fields->GetItem("szString")->Value;  //문자형 일때 
// 	szString[count].Format("%s",(LPCSTR)bKeyContents);
//	printf(szNum[count], szString[count]); .........
// 	pRs->MoveNext();
// 	count++;
// }
_RecordsetPtr CAdo::SQLSelect(char * szTableName)
{
    g_pLogManager->WriteLog(EL_INFO, "CAdo::SQLSelect called");
    if (!m_bIsConnected)
    {
        g_pLogManager->WriteLog(EL_WARNING, "DB DISCONNECTED");
        return 0;
    }

    try
    {
        g_pLogManager->WriteLog(EL_INFO, "TRY SQL SELECT");
        char szSQL[256];
        memset(szSQL, 0x00, sizeof(szSQL));
        sprintf_s(szSQL
            , "select * from %s"
            , szTableName);

        m_pRset = m_pConn->Execute(szSQL, NULL, adCmdText);
    }
    catch (...)
    {
        g_pLogManager->WriteLog(EL_ERROR, "SQL SELECT FAILED : try catch");
        return 0;
    }
    g_pLogManager->WriteLog(EL_INFO, "SQL SELECTED");
    return m_pRset;
}

////////////////////////////////////////////////////////////////////////////////////
//Update 하는방법
//UPDATE szTableName set szSet where szWhere 의 형태로 사용
//예) UPDATE dbo.Test set szString='stupid' where nNum=2 의 경우는
//    SQLUpdate("dbo.Test", "szString='stupid'", "nNum=2"); 처럼 사용하면 됩니다.
//
//데이터가 올바르게 저장되면 TRUE 리턴, 실패시 FALSE 리턴
BOOL CAdo::SQLUpdate(char * szTableName, char * szSet, char * szWhere)
{
    g_pLogManager->WriteLog(EL_INFO, "CAdo::SQLUpdate called");
    if (!m_bIsConnected)
    {
        g_pLogManager->WriteLog(EL_WARNING, "DB DISCONNECTED");
        return FALSE;
    }

    try
    {
        g_pLogManager->WriteLog(EL_INFO, "TRY SQL UPDATE");
        char szSQL[256];
        memset(szSQL, 0x00, sizeof(szSQL));
        sprintf_s(szSQL
            , "UPDATE %s set %s where %s"
            , szTableName, szSet, szWhere);

        //		m_pConn->BeginTrans();
        m_pConn->Execute(szSQL, NULL, adExecuteNoRecords);
        //		m_pConn->CommitTrans();
    }
    catch (...)
    {
        g_pLogManager->WriteLog(EL_ERROR, "SQL UPDATE FAILED : try catch");
        return FALSE;
    }
    g_pLogManager->WriteLog(EL_INFO, "SQL UPDATED");
    return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////
//Delete 하는방법
//Delete from szTableName where szWhere 의 형태로 사용
//예) Delete from dbo.Test where nNum=2 의 경우는
//    SQLDelete("dbo.Test", "nNum=2"); 처럼 사용하면 됩니다.
//
//데이터가 올바르게 삭제되면 TRUE 리턴, 실패시 FALSE 리턴
BOOL CAdo::SQLDelete(char * szTableName, char * szWhere)
{
    if (!m_bIsConnected)
    {
        g_pLogManager->WriteLog(EL_WARNING, "DB DISCONNECTED");
        return FALSE;
    }

    try
    {
        char szSQL[256];
        memset(szSQL, 0x00, sizeof(szSQL));
        sprintf_s(szSQL
            , "DELETE from %s where %s"
            , szTableName, szWhere);

        //		m_pConn->BeginTrans();
        m_pConn->Execute(szSQL, NULL, adExecuteNoRecords);
        //		m_pConn->CommitTrans();
    }
    catch (...)
    {
        return FALSE;
    }
    return TRUE;
}

/*
CODE SAMPLE
int nTemp;	// select문 잘 되는지 디버깅용 임시 변수

_RecordsetPtr rs = NULL;
CADO myADO;
if(!myADO.Connect(DB_SERVER_IP, DB_NAME, DB_USER_ID, DB_USER_PW))
printf("Fail to connect\n");
else
printf("Connection success\n");


if(!myADO.SQLInsert("dbo.TEST", "4, 'babo'"))
printf("Insert Fail\n");
else
printf("Effected query successfully\n");


rs = myADO.SQLSelect("dbo.TEST");
if(rs==0)
printf("Select Fail\n");
else
nTemp = rs->GetCollect("nNum").intVal;
//	else
//		printf("Effected query successfully\n");

if(!myADO.SQLUpdate("dbo.TEST", "szString='nice'", "nNum=1"))
printf("Update Fail\n");
else
printf("Effected query successfully\n");


if(!myADO.SQLDelete("dbo.TEST", "nNum=5"))
printf("Delete Fail\n");
else
printf("Effected query successfully\n");

rs = (_Recordset*)myADO.SQLExecute("select * from dbo.TEST");
if(rs==0)
printf("Select Fail\n");
else
nTemp = rs->GetCollect("nNum").intVal;
//	else
//		printf("Effected query successfully\n");

if(!myADO.SQLExecute("Insert into dbo.TEST values(100,'lion')"))
printf("Insert Fail\n");
else
printf("Effected query successfully\n");


if(!myADO.Disconnect())
printf("Fail to disconnect\n");
else
printf("Disconnected\n");
return 0;
*/
#pragma endregion

DbManager::DbManager()
{
    _db = new CAdo;
}

DbManager::~DbManager()
{
    SAFE_DELETE(_db);
}