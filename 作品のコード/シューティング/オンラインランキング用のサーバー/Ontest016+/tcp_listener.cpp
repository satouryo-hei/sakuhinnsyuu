//---------------------------------------
//サーバーの処理(メイン
//Author:佐藤　瞭平
//---------------------------------------
#include"tcp_listener.h"
#include"tcp_client.h"

//マクロ定義
#define MAX_SIZE (100)

//コンストラクタ
CTcpListener::CTcpListener()
{
	m_sockServer = INVALID_SOCKET; //初期化
}

//デストラクタ
CTcpListener::~CTcpListener()
{

}

//初期化処理
bool CTcpListener::Init(int nPurtNum)
{
	//ソケット作成	
	m_sockServer = socket(AF_INET, SOCK_STREAM, 0);

	if (m_sockServer == INVALID_SOCKET)
	{
		printf("エラー\n");
		return false;
	}

	//接続を受け付けるための準備
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(nPurtNum);
	addr.sin_addr.S_un.S_addr = INADDR_ANY;
	bind(m_sockServer, (struct sockaddr*)&addr, sizeof(addr));
	listen(m_sockServer, MAX_SIZE);

	return true;
}

//接続の受付
CTcpClient* CTcpListener::Accept(void)
{
	//接続を待つ
	struct sockaddr_in clientaddr;
	int nLength = sizeof(clientaddr);
	SOCKET sock = accept(m_sockServer, (struct sockaddr*)&clientaddr, &nLength);


	CTcpClient*pTcpClient = new CTcpClient;
	if (pTcpClient != NULL)
	{
		pTcpClient->Init(sock);
	}

	return pTcpClient;
}

//終了処理
void CTcpListener::Uninit(void)
{
	if (m_sockServer == INVALID_SOCKET)
	{
		return;
	}
	//待ち受けソケット切断
	closesocket(m_sockServer);

	m_sockServer = INVALID_SOCKET;
}