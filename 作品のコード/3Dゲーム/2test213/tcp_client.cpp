//=============================================================================
//
// クライアントの文字列処理 [tcp_client.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"tcp_client.h"

//=============================================================================
//コンストラクタ
//=============================================================================
CTcpClient::CTcpClient()
{
	m_sock = INVALID_SOCKET; //初期化
}

//=============================================================================
//デストラクタ
//=============================================================================
CTcpClient::~CTcpClient()
{

}

//=============================================================================
//初期化処理
//=============================================================================
bool CTcpClient::Init(const char *pIPAddress, int nPurtNum)
{
	//ソケット作成
	m_sock = socket(AF_INET, SOCK_STREAM, 0);

	//ソケット生成されたか
	if (m_sock == INVALID_SOCKET)
	{
		printf("エラー\n");
		return false;
	}

	//接続を受け付けるための準備
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(nPurtNum);
	pIPAddress[100];

	addr.sin_addr.S_un.S_addr = inet_addr(pIPAddress);

	if (connect(m_sock, (struct sockaddr*)&addr, sizeof(addr)) != 0)
	{
		printf("初期化でエラーが起きました\n");
		return false;
	}
	printf("初期化が成功しました\n");
	return true;
}

//=============================================================================
//初期化処理
//=============================================================================
bool CTcpClient::Init(SOCKET sock)
{
	//接続済みソケットをメンバ変数に設定
	m_sock = sock;

	return true;
}

//=============================================================================
//送信処理
//=============================================================================
int CTcpClient::Send(char *pSendData, int nSendDataSize)
{
	//接続済みかチェック
	if (m_sock == INVALID_SOCKET)
	{
		printf("送信時にエラーが起きました\n");
		return 0;
	}

	int nSendByte = 0; //初期化
	nSendByte = send(m_sock, pSendData, nSendDataSize, 0);

	printf("送信が成功しました\n");
	return nSendByte;
}

//=============================================================================
//受信処理
//=============================================================================
int CTcpClient::Recv(char *pRecvData, int nRecvDataSize)
{
	//接続済みかチェック
	if (m_sock== INVALID_SOCKET)
	{
		printf("受信時にエラーが起きました\n");
		return 0;
	}

	//受信
	int nRecvByte = recv(m_sock, pRecvData, nRecvDataSize, 0);

	//もし0以下が返ってきたら(切断されたら0以下が返ってくる)
	if (nRecvByte <= 0)
	{
		//接続を切断する
		Uninit();
		//※以降送受信できない	
	}

	printf("受信が成功しました\n");
	return nRecvByte;
}

//=============================================================================
//終了処理
//=============================================================================
void CTcpClient::Uninit(void)
{
	printf("終了します\n");
	if (m_sock == INVALID_SOCKET)
	{
		return;
	}
	//接続を切断する
	//ソケットのクローズ処理を行う
	closesocket(m_sock);
	m_sock = INVALID_SOCKET;
}
