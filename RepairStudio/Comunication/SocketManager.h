// SocketManager.h: interface for the CSocketManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOCKETMANAGER_H__7403BD71_338A_4531_BD91_3D7E5B505793__INCLUDED_)
#define AFX_SOCKETMANAGER_H__7403BD71_338A_4531_BD91_3D7E5B505793__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define BUFFER_SIZE MAX_PATH
class CSocketManager
{
protected:
	BOOL		m_bServer;       //������������
	HANDLE	m_hSocketOpen;	//��socket
	HANDLE	m_hSocketThread;	//����socket�߳�
	HANDLE	m_hListen;		//����socket
	CString	m_strRecvData;   //��������
	BOOL		m_bExitThread;	//�˳��߳�
protected:
	//���������¼�
	virtual void OnDataReceived(const LPBYTE lpBuffer, DWORD dwCount);

	//socketͨѶ�߳�
	static UINT WINAPI fnSocketThread(LPVOID pParam);

	//�ͻ��˻�����socket�Ƿ񴴽�
	BOOL fnIsOpen();

	//����socket�߳�
	BOOL fnCreateSocketThread();

	//�Ͽ��ͻ��˻����˵�����
	BOOL fnShutdownConnection(SOCKET sock);

	//��ȡͨѶ����
	DWORD fnReadData(LPBYTE lpBuffer, DWORD dwSize, DWORD dwTimeout);

	//��������
	DWORD fnSendData(const LPBYTE lpBuffer, DWORD dwCount, DWORD dwTimeout);
	
public:
	CSocketManager();
	virtual ~CSocketManager();
	
	//������������
	BOOL fnCreateServer(int nPort);

	//�ͻ������ӷ�����
	BOOL fnClientConnect(CString strIP, int nPort);

	//�ر�����
	void fnCloseConnect();
	
	//��ȡ���յ�����
	CString fnGetMessage(int nTimeOut = 0, BOOL bWait = FALSE);

	//��ս��յ�����
	void fnClearMessage();
	
	//������Ϣ
	BOOL fnSendMessage(CString strMsg);
};

#endif 
