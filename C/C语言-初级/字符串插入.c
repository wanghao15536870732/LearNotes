/*
���ʵ���ַ����Ĵ�����������ʱ�Ӽ�������һ���ַ������ַ�����С��20����һ��ָ���ַ���
Ҫ�����ַ�����ÿ�����ַ�֮������ָ���ַ����������������ַ�����
Ҫ�󣺳����������������ɣ�main�����������������ַ�����ָ���ַ���
�Ӻ�����������ʵ��ָ���ַ��Ĳ������
*/ 

#include <stdio.h>
void insert_main(char s[],char n);
int main()
{	
	char c;	
	char str[100];
	puts("������һ���ַ���(�ַ�����С��20):");
	gets(str);
	puts("��������Ҫ������ַ�:");
	scanf("%c",&c);	
	insert_main(str,c);
	return 0;
} 
void insert_main(char s[],char n)
{
	
	int i,j = 0;
	while(s[j] != '\0')
		j ++;
	for(i = j - 1;i > 0;i --)
	{
		s[2 * i] = s[i];
		s[2 * i - 1] = n;
	}
	for(i = 0;i < 2 * j;i ++)
		printf("%c",s[i]);
	printf("\n");
}

