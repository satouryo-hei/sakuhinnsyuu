//---------------------------------------
//�T�[�o�[�̕����񏈗�(�w�b�_�[
//Author:�����@�ĕ�
//---------------------------------------
#ifndef _TCP_LISTENER_H_
#define _TCP_LISTENER_H_

#include"main.h"

class CTcpClient;						//�O���錾

//TCP/IP �N���C�A���g�N���X�̒�`
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
