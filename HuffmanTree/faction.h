#include"bil.h"
//#include"stdio.h"
#include"string.h"
#include "algorithm"
#include<fstream>
#include<iostream>
using namespace std;
//比较权值(不知是否需要修改，待定，可改)
bool compare (HaffNode a,HaffNode b)
{
	return a.weight>b.weight;
}
//初始化哈夫曼树
void initHaffTree(HaffNode HaffTree[])
{	
	int i=0;
	for(i=0;i<=510;i++)
	{
		HaffTree[i].byte=(unsigned char)i;
		HaffTree[i].weight=0;
		HaffTree[i].leftChild=-1;
		HaffTree[i].rightChild=-1;
		HaffTree[i].parent=-1;
		strcpy_s(HaffTree[i].code,"\0");
	}
}
//构造哈夫曼编码
void creatHaffCode(HaffNode HaffTree[])
{
	if (NULL == HaffTree)																	//如果树为空则直接返回
		return;
	int root = 0, i = 0;
	root = bytes_count * 2 - 2;	
	HaffTree[root].code[0] = '\0';

	for (i = root - 1; i >= 0; i--)
	{
		if (i == HaffTree[HaffTree[i].parent].leftChild)
		{
			for (int k = 0; HaffTree[HaffTree[i].parent].code[k] != '\0' && HaffTree[HaffTree[i].parent].code[k] != ' '; k++)
			{
					strcpy(HaffTree[i].code, HaffTree[HaffTree[i].parent].code);			//取双亲的哈夫曼编码
//					HaffTree[i].code[k] = HaffTree[HaffTree[i].parent].code[k];			
			}
			if (HaffTree[i].code[0] == '\0')												//如果双亲的哈夫曼编码为空串则运行
				HaffTree[i].code[0] = '0';
			else
			{
				HaffTree[i].code_len = strlen(HaffTree[i].code);							//如果双亲的哈夫曼编码不为空则运行
				HaffTree[i].code[HaffTree[i].code_len] = '0';								//在双亲的哈夫曼编码后加 '0'（因为是左孩子）
			}
		}
		else
		{
			for (int k = 0; HaffTree[HaffTree[i].parent].code[k] != '\0' && HaffTree[HaffTree[i].parent].code[k] != ' '; k++)
			{
				strcpy(HaffTree[i].code, HaffTree[HaffTree[i].parent].code);
			}
			if (HaffTree[i].code[0] == '\0')
				HaffTree[i].code[0] = '1';
			else
			{
				HaffTree[i].code_len = strlen(HaffTree[i].code);
				HaffTree[i].code[HaffTree[i].code_len] = '1';
			}
		}
	}
}
//读取源文件，统计源文件中字节出现次数(while函数的判断条件不确定是否需要更改，可能会少判断一次或多判断一次)（需要传两个参数，分别为文件的名称和结构体数组）
void Statistics(char fileName[],HaffNode HaffTree[])
{
	ifstream file;
	file.open(source_filename,ios::binary);
	if(!file)
	{
		cout << "打开文件失败" << endl;
		exit(0);
	}
	char t;
	while(file>>t)					//EOF!=file.peek() 待定判断条件
	{
		HaffTree[t].weight++;
		file_lenght++;
	}
	for(int i=0;i<511;i++)
	{
		if(HaffTree[i].weight!=0)
			bytes_count++;
	}
	file.close();
}
//降序排序（未完成）
void HaffTreesort()
{
	sort(HaffTree,HaffTree+511,compare);
}
//构造哈夫曼树(未完成,降序还未实现)
void creatHaffTree(HaffNode HaffTree[])
{
	int tempweight1,tempweight2,min1,min2;
	initHaffTree(HaffTree);															//直接传结构体数组
//	降序排序与统计源文件中字节的出现次数（文档没有要求,但排序完以后下面的合并才能确定合并后新的结点存放在哪）
//	求哈夫曼树叶子结点树bytes_count；
	 for(int i=1;i<bytes_count;i++)	//经过bytes_count -1 次树的合并。
	{ 
		min1 = min2 = -1;
		tempweight1 = tempweight2 = 20000;
		for(int k=0;k<bytes_count;k++)
		{
			if(HaffTree[k].parent=-1)
			{
				if (HaffTree[k].weight<tempweight1)
				{
					tempweight2=tempweight1;
					tempweight1=HaffTree[k].weight;
					min2=min1;
					min1=k;
				}
				else if(HaffTree[k].weight<tempweight2)
				{
					tempweight2=HaffTree[k].weight;
					min2=k;
				}
			}
		HaffTree[bytes_count+i-1].weight=HaffTree[min1].weight+HaffTree[min2].weight;
		HaffTree[min1].parent= bytes_count+i-1 ;
		HaffTree[min2].parent= bytes_count+i-1 ;
		HaffTree[bytes_count+i-1].leftChild = min1 ;
		HaffTree[bytes_count+i-1].rightChild= min2 ;
		}
	}
}
//生成压缩文件(未完成,与文档格式不一样，应该需要更改)
void writeCompressFile()
{
	ifstream ifp;
	ofstream ofp;
	char *temp;															//temp用来指向文件名中'.'以及其后面的字符
	int len;															//len用来记录文件后缀名的长度
	ifp.open(source_filename,ios::binary);
	ofp.open(compress_filename,ios::binary);
	temp = strrchr(source_filename,'.');
	if(temp)
	{
		*temp='\0';
		temp++;
	}
	strcpy(suffix_filename,temp);										//suffix_filename为后缀名
	len = strlen(suffix_filename);										//len为后缀长度

}
