//---------------------------------------
//�T�[�o�[�̕����񏈗�(�w�b�_�[
//Author:�����@�ĕ�
//---------------------------------------
#ifndef _MAIN_H_
#define _MAIN_H_

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include<winsock2.h>
#include<stdio.h>
#include<string.h>
#include<time.h>
#include<thread>

#pragma comment(lib,"ws2_32.lib")


//�}�N����`
#define PORT_NUMBER (12345)	//�|�[�g�ԍ�
#define RANKING_TEXT "data/TEXT/ranking.txt"
#define MAX_RANKING (10)
#define EXIT "exit"		//�I������

//�����L���O�Ƃ��łł�����
//����ւ�����
template<class T> void swap(T &data0, T &data1)
{
	T dataWk;
	dataWk = data0;
	data0 = data1;
	data1 = dataWk;
}

#endif
