#include"bil.h"
//#include"stdio.h"
#include"string.h"
#include "algorithm"
#include<fstream>
#include<iostream>
using namespace std;
//�Ƚ�Ȩֵ(��֪�Ƿ���Ҫ�޸ģ��������ɸ�)
bool compare (HaffNode a,HaffNode b)
{
	return a.weight>b.weight;
}
//��ʼ����������
void initHaffTree()
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
//�������������
void creatHaffCode()
{
	if (NULL == HaffTree)																	//�����Ϊ����ֱ�ӷ���
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
					strcpy(HaffTree[i].code, HaffTree[HaffTree[i].parent].code);			//ȡ˫�׵Ĺ���������
//					HaffTree[i].code[k] = HaffTree[HaffTree[i].parent].code[k];			
			}
			if (HaffTree[i].code[0] == '\0')												//���˫�׵Ĺ���������Ϊ�մ�������
				HaffTree[i].code[0] = '0';
			else
			{
				HaffTree[i].code_len = strlen(HaffTree[i].code);							//���˫�׵Ĺ��������벻Ϊ��������
				HaffTree[i].code[HaffTree[i].code_len] = '0';								//��˫�׵Ĺ����������� '0'����Ϊ�����ӣ�
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
//��ȡԴ�ļ���ͳ��Դ�ļ����ֽڳ��ִ���(while�������ж�������ȷ���Ƿ���Ҫ���ģ����ܻ����ж�һ�λ���ж�һ��)
void Statistics(char fileName[])
{
	ifstream file;
	file.open(source_filename,ios::binary);
	if(!file)
	{
		cout << "���ļ�ʧ��" << endl;
		exit(0);
	}
	char t;
	while(file>>t)					//EOF!=file.peek() �����ж�����
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
//��������δ��ɣ�
void HaffTreesort()
{
	sort(HaffTree,HaffTree+511,compare);
}
//�����������(δ���)
void creatHaffTree()
{
	int tempweight1,tempweight2,min1,min2;
	initHaffTree();
//	����������ͳ��Դ�ļ����ֽڵĳ��ִ������ĵ�û��Ҫ��,���������Ժ�����ĺϲ�����ȷ���ϲ����µĽ�������ģ�
//	���������Ҷ�ӽ����bytes_count��
	 for(int i=1;i<bytes_count;i++)	//����bytes_count -1 �����ĺϲ���
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
//����ѹ���ļ�(δ���,���ĵ���ʽ��һ����Ӧ����Ҫ����)
void writeCompressFile()
{
	char *temp;															//temp����ָ���ļ�����'.'�Լ��������ַ�
	int len;															//len������¼�ļ���׺���ĳ���
	temp = strrchr(source_filename,'.');
	if(temp)
	{
		*temp='\0';
		temp++;
	}
	strcpy(suffix_filename,temp);										//suffix_filenameΪ��׺��
	len = strlen(suffix_filename);										//lenΪ��׺����
}
