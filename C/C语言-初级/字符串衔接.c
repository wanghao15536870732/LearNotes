/*
���ʵ���ַ����Ĵ�����������ʱ�Ӽ�������һ���ַ������ַ�����С��20��
��һ��ָ���ַ���Ҫ���ַ����и�ָ���ַ��ƶ��ַ�����ĩβ���������������ַ�����
Ҫ�󣺳����������������ɣ�main�����������������ַ�����ָ���ַ���
�Ӻ�����������ʵ��ָ���ַ����ƶ�������
*/ 
#include"stdio.h"
#include"string.h"
void fun(char s[],char c)
{
	int count = 0;
	int i = 0,j = 0;
	int l;
	l = strlen(s);
	while (s[i])
	{
		if (s[i++] == c)
			count++;
	}
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
			s[j++] = s[i];
		i++;
	}
	for (i = 0; i < count;i++)
		s[j ++] = c;
	s[j] = '\0';
}

int main()
{
	char s[80], c;
	gets(s);
	c = getchar();
	fun(s, c);
	puts(s);
}



