#pragma once
#include "SerialPort.h"
#include "../Tools/bytebuffer.h"

class CModbusClient : public CSerialPort
{
public:
    CModbusClient(HWND hNotifyWnd);
    ~CModbusClient(void);

    typedef enum {
        DATA_TYPE_POWER = 0,
        DATA_TYPE_VOLTAGE,
        DATA_TYPE_CURRENT,
    } DataType;

    virtual void OnDataReceived(ByteBuffer* pBuffer);

public:
    int fnConnect(int nComID, CString strSetting);
    int fnReadProperty(short nDeviceID, DataType nType);

protected:
    int fnSendCmd(ByteBuffer& Command, bool bWriteMode = false);
    uint16_t fnCrcWith16(uint8_t *data, uint32_t length);

private:
	static unsigned int WINAPI ThreadRefresh(void* pParam);
private:
    HWND m_hNotifyWnd;
    HANDLE m_hThread;
    unsigned m_nThreadID;
};
