#include "StdAfx.h"
#include "ModbusClient.h"


CModbusClient::CModbusClient(HWND hNotifyWnd) 
: m_hNotifyWnd(hNotifyWnd)
{
    m_hThread = (HANDLE)_beginthreadex(NULL, 0, ThreadRefresh, this, NULL, &m_nThreadID);
    if(NULL == m_hThread)
    {
        TRACE("failed to create thread of refresh.");
    }
}

CModbusClient::~CModbusClient(void)
{
    if (m_hThread)
    {
        ::PostThreadMessage(m_nThreadID, WM_QUIT, NULL, NULL);
        if (::WaitForSingleObject(m_hThread, 500) == WAIT_TIMEOUT)
        {
            ::TerminateThread(m_hThread, 0xFF);
        }

        ::CloseHandle(m_hThread);
        m_hThread = NULL;
    }
}

int CModbusClient::fnConnect(int nComID, CString strSetting)
{
    int nRetCode = -1;
    if (nComID < 0 || strSetting.IsEmpty())
    {
        return nRetCode;
    }

    //�򿪴���
    fnInitCom(nComID, strSetting);

    return fnIsOpen() ? 0 : -1;
}

void CModbusClient::OnDataReceived(ByteBuffer* pBuffer)
{
#define MODBUS_ERROR_REQUERY 0x83

    uint8_t nRet = 0;
    pBuffer->ReadUInt8(nRet);
    if (MODBUS_ERROR_REQUERY == nRet)
    {
        return;
    }

	//dummy
	pBuffer->ReadUInt8(nRet);
    uint8_t nRetByteNum = 0;
    pBuffer->ReadUInt8(nRetByteNum);

    CString* strMsg = new CString;
    for (int n = 0; n < nRetByteNum/2; n++)
    {
        uint16 nValue = 0;
        pBuffer->ReadUInt16(nValue);

        CString strFmt;
        strFmt.Format("%d", nValue);

        *strMsg += strFmt;
    }

	if (m_hNotifyWnd && !::IsWindowVisible(m_hNotifyWnd))
	{
		delete strMsg;
		return;
	}	

    if (m_hNotifyWnd && ::IsWindow(m_hNotifyWnd))
    {
        ::PostMessage(m_hNotifyWnd, WM_UPDATE_AMMETER, (WPARAM)strMsg, NULL);
    }  
}

int CModbusClient::fnSendCmd(ByteBuffer& Command, bool bWriteMode)
{
    int nRetByteNum = 0;
    scoped_ptr<char> BuffOut(new char[MAX_PATH]);

    int nRetCode = fnSendBytes(Command.Data(), Command.Length(), BuffOut.use(), MAX_PATH, nRetByteNum);
    if (!nRetCode)
    {
        // �ɹ���������
        ByteBuffer Temp;
        Temp.WriteBytes(BuffOut.get(), nRetByteNum);
        OnDataReceived(&Temp);
    }

    return nRetCode;
}

int CModbusClient::fnReadProperty(short nDeviceID, DataType nType)
{
    int nResult = 0;

    //��ȷ���Ƿ��Ѿ��򿪴���
    if (!fnIsOpen())
    {
        return -1;
    }

    // ת����Ӧ���͵���ַ
    short nAddr = 0x03, nNumRet = 0x0001;
    switch (nType)
    {
    case DATA_TYPE_POWER:
        nAddr = 0x030A;
        nNumRet = 0x0001;
        break;
    case DATA_TYPE_VOLTAGE:
        nAddr = 0x030E;
        nNumRet = 0x0003;
        break;
    case DATA_TYPE_CURRENT:
        nAddr = 0x0309;
        nNumRet = 0x0001;
        break;
    default:
        nAddr = 0x03;
        nNumRet = 0x0001;
        break;    
    }

    ByteBuffer Command;

    // �豸ID
    Command.WriteUInt8(nDeviceID);
    // ��ѯ����
    Command.WriteUInt8(0x03);
    // �Ĵ�����ַ
    Command.WriteUInt16(nAddr);
    // ���ص���
    Command.WriteUInt16(nNumRet);

    // ����CRC
    uint16_t nCRC = fnCrcWith16((uint8_t*)Command.Data(), Command.Length());
    Command.WriteUInt8(nCRC);
	Command.WriteUInt8((nCRC>>8)&0xFF);

    fnSendCmd(Command); //���Ͷ�ȡ����

    return nResult;
}

uint16_t CModbusClient::fnCrcWith16(uint8_t *data, uint32_t length)
{
    uint8_t i = 0;
    uint16_t nCRC = 0xffff;        // Initial value
    while (length--)
    {
        nCRC ^= *data++;            // crc ^= *data; data++;
        for (i = 0; i < 8; ++i)
        {
            if (nCRC & 1)
                nCRC = (nCRC >> 1) ^ 0xA001;        // 0xA001 = reverse 0x8005
            else
                nCRC = (nCRC >> 1);
        }
    }

    return nCRC;
}

unsigned int __stdcall CModbusClient::ThreadRefresh(void *pParam)
{
    CModbusClient* pThis = (CModbusClient*)pParam;
    if (pThis == NULL)
    {
        return 0;
    }

    // ���1500ms ����
    int nIDEvent = 0x1234;
    ::SetTimer(NULL, nIDEvent, 1500, NULL);

    MSG Msg;

    while (true)
    {
        ::GetMessage(&Msg, NULL, NULL, NULL);

        switch (Msg.message)
        {
        case WM_TIMER:
            {
                pThis->fnReadProperty(1, DATA_TYPE_POWER);
            }
            break;
        case WM_QUIT:
            {
                goto EXIT;
            }
            break;
        }
    }

EXIT:

    TRACE(_T("succeed to exit work thread 0x%0x."), pThis->m_nThreadID);

    return 0;
}