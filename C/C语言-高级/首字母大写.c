/*
����ĸ��д���磺�����룺bao qian yue   �����Bao Qian Yue��
*/

#include <stdio.h>
#include <string.h>

int main()
{
	char a[1000];
	printf("������Ӣ����� ��"); 
	gets(a);
	char c;
	int i;
	a[0] = a[0] - 32;
	printf("%c",a[0]);
	for(i = 1;a[i] != '\0';i ++)
	{
		if(a[i] != ' ' && a[i-1] == ' ')
		{
			a[i] = a[i] - 32;
			c = a[i];
			printf("%c",c);
		}
		else
		{
			c = a[i];
			printf("%c",c);
		}
	}
	return 0;
}

