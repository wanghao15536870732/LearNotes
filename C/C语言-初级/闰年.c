/*
��д����Ҫ���������ʱ���Ӽ�������һ����ݣ����������жϲ����������Ƿ�Ϊ���ꡣ
��������꣬���1���������0��

������ж������ǣ��ܱ�4�����Ҳ��ܱ�100�����������ܱ�400������
*/ 

#include <stdio.h>
#include <stdlib.h>
int main()
{
	int year;
	printf("������һ����� ��"); 
	scanf("%d",&year);
	if(( year % 4 == 0 && year % 100 != 0 ) || year % 400 == 0 )
	{
		printf("1");
	} 
	else
	{
		printf("0");
	}
	system("pause");
	return 0;
}

