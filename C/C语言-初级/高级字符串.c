/*
��д����Ҫ���������ʱ���մӼ�������������ַ��������Ⱦ�������80����
��ֱ�������ַ���������λ���ϵ��ַ��γɵ������Ӵ��Ƚϴ�С������һ���Ӵ����ڵڶ����Ӵ������1��
����һ���Ӵ����ڵڶ����Ӵ������0���������-1���������ַ����ֱ�Ϊ"123abcdefg"��"12345678"��
����λ���ϵ��ַ��γɵ��Ӵ��ֱ�Ϊ"13bdf"��"1357"��������Ϊ1��
*/ 

#include <stdio.h>
int main()
{
	char num1[80],num2[80];
	char num3[40],num4[40];  
	int i,j;
	int m,n,pos;
	gets(num1);
	gets(num2);
	i = 0;
	m = 0;
	while(num1[i] != '\0')
	{
		num3[m] = num1[i];
		m ++;
		i ++;
		if(num1[i] == '\0')
			break;
		i ++;
		
	}
	num3[m + 1] = '\0';
	j = 0;n = 0;
	while(num2[j] != '\0')
	{
		num4[n] = num2[j];
		j ++;
		if(num2[j] == '\0')
			break;
		j ++;
		n ++;
	}
	num4[n + 1] = '\0';
	m = 0;n = 0;
	while(num3[m] != '\0' && num4[n] != '\0')
	{
		if(num3[m] > num4[n])
		{
			pos = 1;
			break;
		}
		else if(num3[m] < num4[n])
		{
			pos = -1;
			break;
		}
	}
	if(pos == 0)
	{
		if(num3[m + 1] != '\0')
			pos = 1;
		else if(num4[n + 1] != '\0')
			pos = -1;
		else
			pos = 0;
	}
	printf("%d\n",pos);
	return 0;
}

