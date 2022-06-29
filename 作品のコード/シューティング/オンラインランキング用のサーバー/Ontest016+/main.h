//---------------------------------------
//サーバーの文字列処理(ヘッダー
//Author:佐藤　瞭平
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


//マクロ定義
#define PORT_NUMBER (12345)	//ポート番号
#define RANKING_TEXT "data/TEXT/ranking.txt"
#define MAX_RANKING (10)
#define EXIT "exit"		//終了文字

//ランキングとかでできそう
//入れ替え処理
template<class T> void swap(T &data0, T &data1)
{
	T dataWk;
	dataWk = data0;
	data0 = data1;
	data1 = dataWk;
}

#endif
