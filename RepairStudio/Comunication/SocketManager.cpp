// SocketManager.cpp: implementation of the CSocketManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <atlconv.h>
#include "SocketManager.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//��������ͻ���
CRITICAL_SECTION g_SocketCritical;
const DWORD DEFAULT_TIMEOUT = 100L;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSocketManager::CSocketManager()
{
	m_bServer = FALSE;
	m_hSocketOpen = INVALID_HANDLE_VALUE;
	m_hSocketThread = NULL;
	m_hListen = NULL;

	m_bExitThread = FALSE;

	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	//�����׽�������
	wVersionRequested = MAKEWORD(1, 1);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err == 0)
	{
		if (LOBYTE(wsaData.wVersion) != 1 ||
			HIBYTE(wsaData.wVersion) != 1)
		{
			WSACleanup();
		}
	}

	//��ʼ���ٽ���
	InitializeCriticalSection(&g_SocketCritical);
}

CSocketManager::~CSocketManager()
{
	fnCloseConnect();
	//ɾ���ٽ���
	DeleteCriticalSection(&g_SocketCritical);
}

//������������
BOOL CSocketManager::fnCreateServer(int nPort)
{
	CString strIPAddress;

	strIPAddress = "127.0.0.1";
	if (fnIsOpen())
		return FALSE;

	SOCKET sockServer = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
	if (INVALID_SOCKET != sockServer)
	{
		SOCKADDR_IN sockAddr;
		sockAddr.sin_family = AF_INET;
		sockAddr.sin_port = htons((short)nPort);
		sockAddr.sin_addr.s_addr = inet_addr(strIPAddress);

		if (SOCKET_ERROR == bind(sockServer, (LPSOCKADDR)&sockAddr, sizeof(SOCKADDR_IN)))
		{
			closesocket(sockServer);
			return FALSE;
		}

		if (SOCK_STREAM == SOCK_STREAM)
		{
			if (SOCKET_ERROR == listen(sockServer, SOMAXCONN))
			{
				closesocket(sockServer);
				return FALSE;
			}
		}
		m_hSocketOpen = (HANDLE)sockServer;
	}

	//����socket�߳�
	BOOL bResult = fnCreateSocketThread();

	//�ö���Ϊ��������
	m_bServer = TRUE;

	return bResult;
}

//�ͻ������ӷ�����
BOOL CSocketManager::fnClientConnect(CString strIP, int nPort)
{
	//�ȹر�һ�Σ�
	fnCloseConnect();

	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr(strIP);//�������˵ĵ�ַ
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(nPort);

	//����
	if (SOCKET_ERROR == connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR)))
	{
		closesocket(sockClient);
		return false;
	}

	m_hSocketOpen = (HANDLE)sockClient;

	//����socket�߳�
	BOOL bResult = fnCreateSocketThread();

	//�ö���Ϊ�ͻ���
	m_bServer = FALSE;

	return bResult;
}

void CSocketManager::fnCloseConnect()
{
	//����socket�߳�
	if (NULL != m_hSocketThread)
	{
		m_bExitThread = TRUE;
		m_hSocketThread = NULL;
	}

	//�Ͽ�socket����
	if (fnIsOpen())
	{
		fnShutdownConnection((SOCKET)m_hSocketOpen);
		m_hSocketOpen = INVALID_HANDLE_VALUE;
	}	
}

BOOL CSocketManager::fnShutdownConnection(SOCKET sock)
{
	shutdown(sock, SD_BOTH);
	return (0 == closesocket(sock));
}

//�ͻ��˻�����socket�Ƿ񴴽�
BOOL CSocketManager::fnIsOpen()
{
	return (INVALID_HANDLE_VALUE != m_hSocketOpen);
}

//����socket�߳�
BOOL CSocketManager::fnCreateSocketThread()
{
	if (fnIsOpen())
	{
		UINT uiThreadId = 0;
		m_hSocketThread = (HANDLE)_beginthreadex(NULL, 0, fnSocketThread, this, CREATE_SUSPENDED, &uiThreadId);

		if (NULL != m_hSocketThread)
		{
			ResumeThread(m_hSocketThread);
			m_hSocketThread = m_hSocketThread;
			m_bExitThread = FALSE;
			return TRUE;
		}
	}
	return FALSE;
}

//socketͨѶ�߳�
UINT WINAPI CSocketManager::fnSocketThread(LPVOID pParam)
{
	BYTE byData[BUFFER_SIZE];
	DWORD   dwBytes = 0L;
	DWORD   dwTimeout = INFINITE;
	LPBYTE  lpData = (LPBYTE)&byData;
	DWORD   dwSize = sizeof(byData);

	CSocketManager* pSocketManager = reinterpret_cast<CSocketManager*>(pParam);
	
	//���Ϊ�������ˣ� �ȴ��ͻ�������
	if (pSocketManager->m_bServer)
	{
		SOCKET sock = (SOCKET)pSocketManager->m_hSocketOpen;
		sock = accept(sock, 0, 0);

		if (sock != INVALID_SOCKET)
		{
			pSocketManager->m_hListen = (HANDLE)sock;			
		}
		else
		{
			return 0;
		}
	}
	else
	{
		//�ͻ��˽�������socket���
		pSocketManager->m_hListen = pSocketManager->m_hSocketOpen;
	}

	//���socket�������ӣ� ��ʼ��ȡ����
	while (!pSocketManager->m_bExitThread)
	{
		dwBytes = pSocketManager->fnReadData(lpData, dwSize, dwTimeout);

		//�Ͽ����ӣ��յ����ݴ���
		if (dwBytes == (DWORD)-1L)
		{
			if (pSocketManager->fnIsOpen())
			{
				break;
			}
		}
		else if (dwBytes > 0L)
		{
			pSocketManager->OnDataReceived(lpData, dwBytes);
		}
	}

	return 1;
} 

DWORD CSocketManager::fnReadData(LPBYTE lpBuffer, DWORD dwSize, DWORD dwTimeout)
{
	if (lpBuffer == NULL || dwSize < 1L)
		return 0L;

	fd_set  fdRead = { 0 };
	TIMEVAL stTime;
	TIMEVAL *pstTime = NULL;

	if (INFINITE != dwTimeout) {
		stTime.tv_sec = dwTimeout / 1000;
		stTime.tv_usec = (dwTimeout % 1000) * 1000;
		pstTime = &stTime;
	}

	SOCKET s = (SOCKET)m_hListen;
	if (!FD_ISSET(s, &fdRead))
		FD_SET(s, &fdRead);

	DWORD dwBytesRead = 0L;
	int res = select(s + 1, &fdRead, NULL, NULL, pstTime);
	if (res > 0)
	{
		res = recv(s, (LPSTR)lpBuffer, dwSize, 0);

		//���Ͽ����ӵ�ʱ�򣬷�������Ϊ0
		if (res == 0)
		{
			//�ȹص��Ѵ�����listen
			fnShutdownConnection((SOCKET)m_hListen);

			//�ٴεȴ�����
			m_hListen = (HANDLE)accept((SOCKET)m_hSocketOpen, 0, 0);

			return res;
		}
	}
	dwBytesRead = (DWORD)((res > 0) ? (res) : (-1L));

	return dwBytesRead;
}

DWORD CSocketManager::fnSendData(const LPBYTE lpBuffer, DWORD dwCount, DWORD dwTimeout)
{
	fd_set  fdWrite = { 0 };
	TIMEVAL stTime;
	TIMEVAL *pstTime = NULL;

	if (INFINITE != dwTimeout) {
		stTime.tv_sec = dwTimeout / 1000;
		stTime.tv_usec = (dwTimeout % 1000) * 1000;
		pstTime = &stTime;
	}

	SOCKET s = (SOCKET)m_hListen;
	if (!FD_ISSET(s, &fdWrite))
		FD_SET(s, &fdWrite);

	DWORD dwBytesWritten = 0L;
	int res = select(s + 1, NULL, &fdWrite, NULL, pstTime);
	if (res > 0)
	{
		res = send(s, (LPCSTR)lpBuffer, dwCount, 0);
	}
	dwBytesWritten = (DWORD)((res >= 0) ? (res) : (-1L));

	return dwBytesWritten;
}

BOOL CSocketManager::fnSendMessage(CString strMsg)
{
	//�����ٽ���
	EnterCriticalSection(&g_SocketCritical);

	m_strRecvData.Empty();

	BYTE byBuffer[1000] = { 0 };
	CString strText = strMsg;

	int nLen = strText.GetLength();

	//��������֮ǰ�������ԭ��������
	//fnClearMessage();

    //��ȷ���Ƿ��Ѿ���������
    if (!fnIsOpen())
    {
        return FALSE;
    }

	if (nLen > 0)
	{
		USES_CONVERSION;
		strcpy(reinterpret_cast<LPSTR>(byBuffer),T2CA(strText));
		if (-1 == fnSendData(byBuffer, nLen, 5000))
		{
			return FALSE;
		}
	}

	//�뿪�ٽ���
	LeaveCriticalSection(&g_SocketCritical);

	return TRUE;
}

CString CSocketManager::fnGetMessage(int nTimeOut, BOOL bWait)
{
	//��ȡ��ʼʱ��
	clock_t startTime = clock();
	//����Ƿ���Ҫ�ȴ�
	if (bWait)
	{
		MSG   msg;

		do
		{
			//��Ϣ����
			PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (!m_strRecvData.IsEmpty())
			{
				break;
			}

			clock_t endTime = clock();

			//��¼ʱ���
			double dbPassTime = (double)(endTime - startTime);

			//����Ƿ�ʱ
			if (1 == fnCompareDouble(dbPassTime, nTimeOut))
			{
				break;
			}

			Sleep(50);

		} while (TRUE);
	}

	return m_strRecvData;
}

void CSocketManager::fnClearMessage()
{
	m_strRecvData.Empty();
}

void CSocketManager::OnDataReceived(const LPBYTE lpBuffer, DWORD dwCount)
{
	LPBYTE lpData = lpBuffer;
	CString strData;

	//��������ת��
	USES_CONVERSION;
	memcpy(strData.GetBuffer(dwCount), A2CT((LPSTR)lpData), dwCount);
	strData.ReleaseBuffer(dwCount);

	m_strRecvData = strData;
}

