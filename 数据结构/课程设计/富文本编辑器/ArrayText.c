#define _CRT_SECURE_NO_WARNINGS

#include "textstruct.h"
#include "stdio.h"

//���ڽӱ�ת��������
void TableToArray(TextCompiler *text, seqstring *str)
{
	int count = 0; //�����±�
	for (int i = 0; i < text->count; i++)
	{
		int mn = 0; //�ڽӱ��ÿһ��������±�
		while (text->column[i].FirstWord->data[mn] != '\0')
		{
			char letter = text->column[i].FirstWord->data[mn];
			str->str[count] = letter;
			count++; //����������±��1
			mn++;	//�ڽӱ�������±��1
			str->length++;
		}
	}
	str->str[count] = '\0'; //�������һλ��ֵ'\0'
}

//�ڽӱ�д���ļ�
void TableToFile(TextCompiler *text, char *filename)
{
	FILE *fp;
	int save = 0;			   //����д���ļ��ķ���ֵ
	fp = fopen(filename, "w"); //��д��ķ�ʽ���ļ�
	if (fp)
	{
		for (int i = 0; i < text->count; i++)
		{
			save = fprintf(fp, "%s", text->column[i].FirstWord->data);
			if (save == -1) //�������-1,�����ļ�д��ʧ��
			{
				printf("д���ļ�ʧ�ܣ�����\n");
				exit(0); //�˳�
			}
			fputc('\n', fp); //д��س��Ѵﵽ�����û��ķ�ʽ�洢�ı�
		}
		fputc('\n', fp);
	}
	else
		printf("�ļ���ʧ�ܣ���\n");
	fclose(fp); //�ر��ļ�
}

/*
�ַ����Ĳ���
@ Str ĸ��
@ Ttr ��Ҫƥ����Ӵ�
*/

void strinsert(Word *Str, int i, Word *Ttr)
{
	int k;
	if (i < 1 || i > Str->length + 1 || Str->length + Ttr->length > MAXSIZWE - 1) //�Ƿ�����Ĵ���
		printf("�ַ����������޷����в����������\n");
	else
	{
		for (k = Str->length - 1; k >= i - 1; k--) //Str�дӵ�i��Ԫ����������
			Str->data[Ttr->length + k] = Str->data[k];
		for (k = 0; k < Ttr->length; k++) //��д��S�еĵ�i���ַ���ʼ��λ��
			Str->data[i + k - 1] = Ttr->data[k];
		Str->length = Str->length + Ttr->length;
		Str->data[Str->length] = '\0'; //�����ַ���S�µĽ�����
	}
}

/*
�ַ�����ɾ��
@ Str ĸ��
@ i ��Ҫɾ����λ��
@ len ��Ҫɾ���ĳ���
*/

void strdelete(Word *Str, int i, int len)
{
	int k;
	if (i < 1 || i > Str->length || i + len - 1 > Str->length) //�Ƿ�����Ĵ���
	{
		printf("�޷�����ɾ����������\n");
		exit(0);
	}
	else
	{
		for (k = i + len - 1; k < Str->length; k++)
			Str->data[k - len] = Str->data[k]; //Str���±�Ϊi + len -1��ʼ��Ԫ��ǰ��
		Str->length = Str->length - len;
		Str->data[Str->length] = '\0'; //���ַ���Str�µĽ�����
	}
}

/*
�ַ���������
@ S1 ��һ���ַ���
@ S2 �ڶ����ַ���
*/

Word *strconcat(Word *S1, Word *S2)
{
	int i;
	Word *r;
	if (S1->length + S2->length > MAXSIZWE - 1) //�����ַ����ռ䲻������
	{
		printf("�޷��������ӣ�\n");
		return NULL;
	}
	else
	{
		r = (Word *)malloc(sizeof(Word));
		for (i = 0; i < S1->length; i++)
			r->data[i] = S1->data[i]; //��S1���Ƶ��ַ�����r��ǰ��
		for (i = 0; i < S2->length; i++)
			r->data[S1->length + i] = S2->data[i]; //��S2���Ƶ��ַ�����r�ĺ��
		r->data[r->length] = '\0';
	}
	return r;
}

//��S2�滻S1�е�iλ�õ��ַ���
void strreplace(Word *S1, int i, Word *S2, int length)
{
	if (S2->length == length) //����滻���ַ�����Ԫ�ַ����������
	{
		for (int j = 0; j < S2->length; j++)
			S1->data[i + j] = S2->data[j]; //ֱ�Ӹ�ֵ�滻
	}
	else if (S2->length > length) //�滻�ַ�����ԭ�ַ���Ҫ��
	{

		for (int k = S1->length - 1; k >= i - 1; k--) //Str�дӵ�i��Ԫ�ؿ�ʼ����
			S1->data[S2->length - length + k] = S1->data[k];
		for (int j = 0; j < S2->length; j++) //��ֵ�滻
			S1->data[i + j] = S2->data[j];
		S1->length += S2->length - length; //�����һ�³���
		S1->data[S1->length] = '\0';
	}
	else
	{ //�滻�ַ�����Ԫ�ַ���Ҫ��
		for (int k = i + length - 1; k < S1->length; k++)
			S1->data[k - (length - S2->length)] = S1->data[k]; //Str���±�Ϊi + len -1��ʼ��Ԫ��ǰ��
		for (int j = 0; j < S2->length; j++)
			S1->data[i + j] = S2->data[j];   //�����ַ������滻
		S1->length -= (length - S2->length); //�����һ�³���
		S1->data[S1->length] = '\0';		 //���ֵ'\0'
	}
}

//���ÿһ���ı���next[]����
void get_next(int *n, char *b, int next[])
{
	int i, j;
	i = 0;
	n[0] = j = -1; //ָ��j��������޷��ƶ�ʱ��ָ��i����
	while (i < strlen(b))
	{
		while (j != -1 && b[i] != b[j]) //��������ƥ��ʱ,j����һ���ƶ�λ��next��j��=j
		{
			j = next[j];
		}
		next[++i] = ++j; //��ƥ��ɹ�ʱb[0 ~ i]=b[j-i ~ j]��next[ ++i ] = ++ j��
	}
}

//kmp�ַ���ƥ��
int kmp(char *vis1, char *vis2, int next[], int length)
{
	int i, j;
	int ans = 0;
	i = j = 0;			  //������ģʽ����λ��
	int n = strlen(vis1); //��������
	int m = strlen(vis2); //ģʽ������
	while (i < n)
	{
		while (j != -1 && vis1[i] != vis2[j]) //������ģʽ�����ֲ�ƥ��
			j = next[j];					  //ָ��j�����л���
		if (j == m - 1)						  //���ƥ��ɹ�
		{
			printf("ƥ��ɹ���λ��Ϊ����%d��,��%d��\n", (i - m) / length + 1, (i - m) % length + 2);
			ans++;
			j = next[j]; //jָ�뷵�ص���ȷλ��
		}
		i++; //i��jָ�����Ѱ����һģʽ��
		j++;
	}
	return ans; //����ƥ��Ĵ���
}
