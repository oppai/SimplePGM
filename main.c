#include "pgm.h"
#pragma comment(lib, "pgm.lib")

int main(){

	PGMFILE *pgm;
	int tmp;

	if((tmp=readPGMfile("LENNA.pgm",&pgm)) > 0){
		printf("Read File Error:%d",tmp);
		return 0;
	}

	/*ヘッダ情報*/
	printf("TYPE:P%d\n",pgm->type);
	printf("SIZE:%d*%d=%d\n",pgm->x,pgm->y,pgm->x*pgm->y);
	printf("MAXLIGHT:%d\n",pgm->max);
	printf("LIGHTRATE:%f\n",pgm->ratio);

	if((tmp=writePGMfile("out1.pgm",pgm)) > 0){
		printf("Write File Error:%d",tmp);
	}
	printf("Finished!!\n");

	freePGM(pgm);

	return 0;
}
