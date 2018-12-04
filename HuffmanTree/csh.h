#include<stdio.h>
#include"iomanip"
#include"bil.h"

void initHaffTree(HaffNode *HaffTree)
{
	int i=0;
	for(i=0;i<=510;i++)
	{
		HaffTree[i].byte=(unsigned char)i;
		HaffTree[i].weight=0;
		HaffTree[i].leftChild=-1;
		HaffTree[i].rightChild=-1;
		HaffTree[i].parent=-1;
		strcpy_s(HaffTree[i].code," ");
	}
}