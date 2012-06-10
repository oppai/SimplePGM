#include "pgm.h"

/*
	PGM領域確保

	x:横幅
	y:縦幅
	max:最大光度
	type:ファイルタイプ
*/
PGMFILE *createPGM(int x,int y,int max,int type){
	PGMFILE *pgm;

	if(x < 1 || y < 1) return NULL;

	pgm = malloc(sizeof(PGMFILE));
	if(pgm==NULL) return NULL;
	/*データ読み込み用変数確保*/
	pgm->data = (BYTE *)malloc(sizeof(BYTE)*x*y);

	pgm->x   = x;
	pgm->y   = y;
	pgm->max = max;
	pgm->type= type;
	pgm->ratio = 255 / (float)max;

	return pgm;
}

/*
	PGMファイル読み込み

	fname:ファイルネーム
	pgm:PGMファイルポインタ

*/
int readPGMfile(char* fname,PGMFILE **pgm){
	FILE *fp;
	char fhead[256];	//ヘッドバッファ
	int ftype;			//ファイルタイプ
	int fx,fy;			//x,yのサイズ
	int fmax;			//最大光度
	double fratio;		//最大光度(255)のに対する割合
	BYTE *data;//データ量
	int i;

	/*ファイルをバイナリモードで読み込み*/
	fp = fopen(fname,"rb");
	if(fp==NULL){
		//printf("FileOpenError\n");
		return 1;
	}

	/*ファイルタイプ*/
	fgets(fhead,255,fp);
	if(fhead[0]!='P'){
		//printf("FileType1Error\n");
		return 2;
	}
	sscanf(fhead,"P%d",&ftype);
	if(ftype < 1 || ftype > 6){
		//printf("FileType2Error\n");
		return 3;
	}
	/*コメント*/
	do fgets(fhead,255,fp); while(fhead[0]=='#');

	/*ファイルサイズ*/
	sscanf(fhead,"%d%d",&fx,&fy);
	if(fx < 1 || fy < 1){
		//printf("FileSizeError\n");
		return 4;
	}

	if(ftype == 2 || ftype == 3 || ftype == 5 || ftype == 6){
		do fgets(fhead,255,fp); while(fhead[0]=='#');
		sscanf(fhead,"%d",&fmax);
		if(fmax < 1 || fmax > 255){
			//printf("LightRaleError\n");
			return 5;
		}
	}


	*pgm = createPGM(fx,fy,fmax,ftype);

	/*データ読み出し*/
	data = (*pgm)->data;
	for(i=0;i < fy*fx;i++){
			data[i] = (BYTE)fgetc(fp);
	}

	fclose(fp);
	return 0;
}

/*
	データ補正

	dat:データ値
	max:マックスのデータ値
*/
BYTE correctValue(BYTE dat,BYTE max){

	if(max < dat) return max;

	return dat;
}

/*
	データのセット

	pgm:PGMファイルポインタ
	x,y:座標
	dat:データ値
*/
int setPixData(PGMFILE *pgm,int x,int y,BYTE dat){

	if(x < 0 || y < 0) return 1;
	if(x > pgm->x || y > pgm->y) return 1;

	pgm->data[x+pgm->x*y] = correctValue(dat,pgm->max);
	return 0;
}

/*
	データの取得

	pgm:PGMファイルポインタ
	x,y:座標
*/
BYTE getPixData(PGMFILE *pgm,int x,int y){

	if(x < 0)		x = 0;
	if(x > pgm->x)	x = pgm->x;
	if(y < 0)		y = 0;
	if(y > pgm->y)  y = pgm->y;

	return pgm->data[x+pgm->x*y];
}


/*
	PGMファイル書き込み

	fname;ファイルネーム
	pgm:PGMファイルポインタ
*/
int writePGMfile(char* fname,PGMFILE *pgm){
	FILE *fp;

	/*ファイルの書き出し*/
	fp = fopen(fname,"wb");
	if(fp==NULL){
		printf("FileWriteError\n");
		return 1;
	}

	/*ヘッダ書き出し*/
	fprintf(fp,"P%d\n",pgm->type);
	fprintf(fp,"#Out Put Sample by c\n");
	fprintf(fp,"%d %d\n",pgm->x,pgm->y);
	fprintf(fp,"%d\n",pgm->max);


	/*データ書き出し*/
	if((unsigned int)(pgm->x*pgm->y) != fwrite(pgm->data, sizeof(BYTE), pgm->x*pgm->y, fp)){
		//printf("FileWriteError\n");
		fclose(fp);
		return 2;
	}

	fclose(fp);

	return 0;
}

/*
	PGMファイルメモリ開放

	pgm:PGMファイルポインタ
*/
void freePGM(PGMFILE *pgm){
	/*メモリの開放*/
	if(pgm->data != NULL) free(pgm->data);
	free(pgm);

	return;
}