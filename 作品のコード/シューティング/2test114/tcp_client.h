//---------------------------------------
//クライアントの文字列処理(ヘッダー
//Author:佐藤　瞭平
//---------------------------------------
#ifndef _TCP_CLIENT_H_
#define _TCP_CLIENT_H_

#include"main.h"

//TCP/IP クライアントクラスの定義
class CTcpClient
{
public:
	CTcpClient();
	~CTcpClient();
	bool Init(const char *pIPAddress, int nPurtNum);
	bool Init(SOCKET sock);
	int Send(char *pSendData, int nSendDataSize);
	int Recv(char *pRecvData, int nRecvDataSize);
	void Uninit(void);

private:
	SOCKET m_sock;

};

#endif
