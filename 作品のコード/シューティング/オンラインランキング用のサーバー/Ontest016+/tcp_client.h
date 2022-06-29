//---------------------------------------
//�T�[�o�[�̕����񏈗�(�w�b�_�[
//Author:�����@�ĕ�
//---------------------------------------
#ifndef _TCP_CLIENT_H_
#define _TCP_CLIENT_H_

#include"main.h"

//TCP/IP �N���C�A���g�N���X�̒�`
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
