//����ȫ�ֱ���
//--------------------------------------------------------
int bytes_count = 0;	//����������Ҷ�ӽڵ���
long long file_lenght = 0;	//�����ļ��ֽ�������ʼΪ0
const int FILENAMEMAX = 128;	//�ļ���������·���������Ȳ�����127
const int SUFFIXNAMEMAX = 10;	//�ļ���׺�����Ȳ�����9���ַ� 
char source_filename[FILENAMEMAX] = "test.doc";	//Դ�ļ�����
char compress_filename[FILENAMEMAX] = "test.buf"; 	//ѹ���ļ����� 
char decompress_filename[FILENAMEMAX] = "detest";	//��ѹ�ļ�����
char prefix_filename[128];	//�ļ�ǰ׺��
char suffix_filename[128];	//�ļ���׺��
const int BUFF_MAXSIZE = 1024 * 1024;	//�ļ����������뻺�����Ĵ�С
char buff[BUFF_MAXSIZE] = "";	//�ļ����������뻺����������ѹ���ļ�ʱ�����ֽڵı����ȴ���buff�У�Ȼ��8����ѹ����һ���ֽڴ浽buff_string�л�������
char buff_string[BUFF_MAXSIZE / 8] = "";	//ѹ���ļ�д�뻺����
const int BLOCK_MAXSIZE = 1024 * 1024;	//��д���ѹ�ļ��Ļ������Ĵ�С
char block[BLOCK_MAXSIZE] = "";	//д���ѹ�ļ��Ļ�����
int block_current = 0;	//д��ѹ�ļ��������ĵ�ǰ��дλ��
struct HaffNode {
	unsigned char byte;	//�������
	long long weight;	//Ȩֵ
	int parent;	//˫�׽���±�
	int leftChild;	//�����±�
	int rightChild;	//�Һ����±�
	char code[256];	//����������
	int code_len;	//���볤��
};
HaffNode HaffTree[511];	//��������
