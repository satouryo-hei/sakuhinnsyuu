//---------------------------------------
//サーバーの文字列処理(ヘッダー
//Author:佐藤　瞭平
//---------------------------------------
#ifndef _TCP_LISTENER_H_
#define _TCP_LISTENER_H_

#include"main.h"

class CTcpClient;						//前方宣言

//TCP/IP クライアントクラスの定義
class CTcpListener
{
public:
	CTcpListener();
	~CTcpListener();
	bool Init(int nPurtNum);
	CTcpClient*Accept(void);
	void Uninit(void);

private:
	SOCKET m_sockServer;

};

#endif
