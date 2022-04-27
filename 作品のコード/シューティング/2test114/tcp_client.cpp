//---------------------------------------
//�T�[�o�[�̏���(���C��
//Author:�����@�ĕ�
//---------------------------------------
#include"tcp_client.h"

//�R���X�g���N�^
CTcpClient::CTcpClient()
{
	m_sock = INVALID_SOCKET; //������
}

//�f�X�g���N�^
CTcpClient::~CTcpClient()
{

}

//����������
bool CTcpClient::Init(const char *pIPAddress, int nPurtNum)
{
	//�\�P�b�g�쐬
	m_sock = socket(AF_INET, SOCK_STREAM, 0);

	//�\�P�b�g�������ꂽ��
	if (m_sock == INVALID_SOCKET)
	{
		printf("�G���[\n");
		return false;
	}

	//�ڑ����󂯕t���邽�߂̏���
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(nPurtNum);
	pIPAddress[100];

	addr.sin_addr.S_un.S_addr = inet_addr(pIPAddress);

	if (connect(m_sock, (struct sockaddr*)&addr, sizeof(addr)) != 0)
	{
		printf("�������ŃG���[���N���܂���\n");
		return false;
	}
	printf("���������������܂���\n");
	return true;
}

//����������
bool CTcpClient::Init(SOCKET sock)
{
	//�ڑ��ς݃\�P�b�g�������o�ϐ��ɐݒ�
	m_sock = sock;

	return true;
}

//���M����
int CTcpClient::Send(char *pSendData, int nSendDataSize)
{
	//�ڑ��ς݂��`�F�b�N
	if (m_sock == INVALID_SOCKET)
	{
		printf("���M���ɃG���[���N���܂���\n");
		return 0;
	}

	int nSendByte = 0; //������
	nSendByte = send(m_sock, pSendData, nSendDataSize, 0);

	printf("���M���������܂���\n");
	return nSendByte;
}

//��M����
int CTcpClient::Recv(char *pRecvData, int nRecvDataSize)
{
	//�ڑ��ς݂��`�F�b�N
	if (m_sock== INVALID_SOCKET)
	{
		printf("��M���ɃG���[���N���܂���\n");
		return 0;
	}

	//��M
	int nRecvByte = recv(m_sock, pRecvData, nRecvDataSize, 0);

	//����0�ȉ����Ԃ��Ă�����(�ؒf���ꂽ��0�ȉ����Ԃ��Ă���)
	if (nRecvByte <= 0)
	{
		//�ڑ���ؒf����
		Uninit();
		//���ȍ~����M�ł��Ȃ�	
	}

	printf("��M���������܂���\n");
	return nRecvByte;
}

//�I������
void CTcpClient::Uninit(void)
{
	printf("�I�����܂�\n");
	if (m_sock == INVALID_SOCKET)
	{
		return;
	}
	//�ڑ���ؒf����
	//�\�P�b�g�̃N���[�Y�������s��
	closesocket(m_sock);
	m_sock = INVALID_SOCKET;
}
