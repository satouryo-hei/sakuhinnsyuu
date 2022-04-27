//---------------------------------------
//サーバーの文字列処理(ヘッダー
//Author:佐藤　瞭平
//---------------------------------------
#ifndef _PROTOCOL_RANKING_H_
#define _PROTOCOL_RANKING_H_

// タイプ判定をするための列挙型構造体
typedef enum 
{
	COMMAND_TYPE_NONE = 0,
	COMMAND_TYPE_GET_RANKING,
	COMMAND_TYPE_SET_RANKING,
	COMMAND_TYPE_MAX
} COMMAND_TYPE;

#endif
