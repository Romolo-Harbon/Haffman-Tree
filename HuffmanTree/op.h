#include<stdio.h>
#include"csh.h"

void outputhafftree(int n)
	{
		for(int i=0;i<=n;i++)
		{
			printf("%d,%lld,%d,%d,%d,%s",HaffTree[i].byte,HaffTree[i].weight,HaffTree[i].leftChild,HaffTree[i].rightChild,HaffTree[i].parent,HaffTree[i].code);
			printf("\n");
		}
	}