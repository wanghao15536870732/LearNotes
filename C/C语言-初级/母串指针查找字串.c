/*
�������ַ������ֱ�Ϊĸ�����Ӵ�������ָ����ʵ����ĸ���в����Ӵ����ֵĴ�����
Ҫ�󣺳�������ʱ��ĸ�����Ӵ��ɼ������롣
*/ 

#include <stdio.h>
#include <string.h>
int main()
{	
	char s1[80],s2[80];
	char ss1[80],ss2[80];
	puts("������һ���ַ�ĸ����");
	gets(s1);
	puts("������һ���ַ��Ӵ���");
	gets(ss1);
	int i,j,k,count = 0;
	int m,n;
	i = 0;
	m = 0;
	while(s1[i])
	{
		j = 0;
		k = i;
		while(ss1[j])
		{
			if(ss1[j] != s1[k])
			{
				break;
			}
			else
			{
				k ++;
				j ++;
			}
		}
		if(ss1[j] == 0)
		{
			n = 0;
			count ++;
			i = i + strlen(ss1);
		}
		else
		{
			s2[m ++] = s1[i];
			i ++;
		}
	}
	printf("���ַ���������%d��\n",count);
	return 0;
}

