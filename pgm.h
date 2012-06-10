/*

	PGM基本I/Oライブラリ	 09/7/26

*/
#include <stdio.h>
#include <stdlib.h>

#define BYTE unsigned char

typedef struct{
	/*ヘッダ読み込み用変数*/
	int type;			//ファイルタイプ
	int x,y;			//x,yのサイズ
	int max;			//最大光度
	double ratio;		//最大光度(255)のに対する割合
	/*データ読み込み用ポインタ*/
	BYTE *data;
}PGMFILE;


////////////////////////////////////////////
//	プロトタイプ宣言
//
/*
	PGM領域確保

	@return: 引数で指定した大きさのPGMポインタ
	x:横幅
	y:縦幅
	max:最大光度
	type:ファイルタイプ
*/
PGMFILE *createPGM(int x,int y,int max,int type);


/*
	PGMファイル読み込み

	@return: 正常なら0それ以外はエラーコード
	fname:ファイルネーム
	pgm:PGMファイルポインタ

*/
int readPGMfile(char* fname,PGMFILE **pgm);


/*
	データ補正

	@return: 規定外の値だった場合MAXもしくは0にする
	dat:データ値
	max:マックスのデータ値
*/
BYTE correctValue(BYTE dat,BYTE max);


/*
	データのセット

	pgm:PGMファイルポインタ
	x,y:座標
	dat:データ値
*/
int setPixData(PGMFILE *pgm,int x,int y,BYTE dat);


/*
	データの取得

	@return: 正常なら0それ以外はエラーコード
	pgm:PGMファイルポインタ
	x,y:座標
*/
BYTE getPixData(PGMFILE *pgm,int x,int y);


/*
	PGMファイル書き込み

	@return: 正常なら0それ以外はエラーコード
	fname;ファイルネーム
	pgm:PGMファイルポインタ
*/
int writePGMfile(char* fname,PGMFILE *pgm);


/*
	PGMファイルメモリ開放

	pgm:PGMファイルポインタ
*/
void freePGM(PGMFILE *pgm);