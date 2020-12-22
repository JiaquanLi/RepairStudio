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
	BOOL		m_bServer;       //创建服务器端
	HANDLE	m_hSocketOpen;	//打开socket
	HANDLE	m_hSocketThread;	//创建socket线程
	HANDLE	m_hListen;		//监听socket
	CString	m_strRecvData;   //接收数据
	BOOL		m_bExitThread;	//退出线程
protected:
	//接收数据事件
	virtual void OnDataReceived(const LPBYTE lpBuffer, DWORD dwCount);

	//socket通讯线程
	static UINT WINAPI fnSocketThread(LPVOID pParam);

	//客户端或服务端socket是否创建
	BOOL fnIsOpen();

	//创建socket线程
	BOOL fnCreateSocketThread();

	//断开客户端或服务端的连接
	BOOL fnShutdownConnection(SOCKET sock);

	//读取通讯数据
	DWORD fnReadData(LPBYTE lpBuffer, DWORD dwSize, DWORD dwTimeout);

	//发送数据
	DWORD fnSendData(const LPBYTE lpBuffer, DWORD dwCount, DWORD dwTimeout);
	
public:
	CSocketManager();
	virtual ~CSocketManager();
	
	//创建服务器端
	BOOL fnCreateServer(int nPort);

	//客户端连接服务器
	BOOL fnClientConnect(CString strIP, int nPort);

	//关闭连接
	void fnCloseConnect();
	
	//获取接收的数据
	CString fnGetMessage(int nTimeOut = 0, BOOL bWait = FALSE);

	//清空接收的数据
	void fnClearMessage();
	
	//发送消息
	BOOL fnSendMessage(CString strMsg);
};

#endif 
