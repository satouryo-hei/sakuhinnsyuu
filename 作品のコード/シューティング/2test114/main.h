//=============================================================================
//
// ���C������ [main.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#define DIRECTINPUT_VERSION (0x0800)	//�r���h���x���Ώ����p�}�N��
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include<WinSock2.h>
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "d3dx9.h"
#include<stdio.h>
#include<stdlib.h>
#include "dinput.h"						//���͏����ɕK�v
#include "xaudio2.h"
#include<time.h>
//#include<thread>

//*****************************************************************************
// ���C�u�����t�@�C���̃����N
//*****************************************************************************
#pragma comment(lib,"d3d9.lib")			//�`��ɕK�v
#pragma comment(lib,"d3dx9.lib")		//[d3d9.lib]�̊g�����C�u����
#pragma comment(lib,"dxguid.lib")		//DirectX�R���|�[�l���g�g�p�ɕK�v
#pragma comment(lib,"dinput8.lib")		//���͏����ɕK�v
#pragma comment(lib,"winmm.lib")		
#pragma comment(lib,"ws2_32.lib")
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCREEN_WIDTH (1280)				//�E�B���h�E�̕�  
#define SCREEN_HEIGHT (720)				//�E�B���h�E�̍���
#define ID_TIMER		(121)			//�^�C�}�[��ID
#define TIMER_INTERVAL	(1000/60)		//�^�C�}�[�̔����Ԋu(�~���b) (1000000/60)(�}�C�N���b)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
int GetFPS(void);						// FPS�\������

//���Z����
template<class T, class P> T add(T data0, P data1)
{
	T answer;
	answer = data0 + data1;
	return answer;
}

//����ւ�����
template<class T> void swap(T &data0, T &data1)
{
	T dataWk;
	dataWk = data0;
	data0 = data1;
	data1 = dataWk;
}
#endif