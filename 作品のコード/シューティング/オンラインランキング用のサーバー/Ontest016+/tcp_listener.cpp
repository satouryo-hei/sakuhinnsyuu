//---------------------------------------
//�T�[�o�[�̏���(���C��
//Author:�����@�ĕ�
//---------------------------------------
#include"tcp_listener.h"
#include"tcp_client.h"

//�}�N����`
#define MAX_SIZE (100)

//�R���X�g���N�^
CTcpListener::CTcpListener()
{
	m_sockServer = INVALID_SOCKET; //������
}

//�f�X�g���N�^
CTcpListener::~CTcpListener()
{

}

//����������
bool CTcpListener::Init(int nPurtNum)
{
	//�\�P�b�g�쐬	
	m_sockServer = socket(AF_INET, SOCK_STREAM, 0);

	if (m_sockServer == INVALID_SOCKET)
	{
		printf("�G���[\n");
		return false;
	}

	//�ڑ����󂯕t���邽�߂̏���
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(nPurtNum);
	addr.sin_addr.S_un.S_addr = INADDR_ANY;
	bind(m_sockServer, (struct sockaddr*)&addr, sizeof(addr));
	listen(m_sockServer, MAX_SIZE);

	return true;
}

//�ڑ��̎�t
CTcpClient* CTcpListener::Accept(void)
{
	//�ڑ���҂�
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

//�I������
void CTcpListener::Uninit(void)
{
	if (m_sockServer == INVALID_SOCKET)
	{
		return;
	}
	//�҂��󂯃\�P�b�g�ؒf
	closesocket(m_sockServer);

	m_sockServer = INVALID_SOCKET;
}