/*
��д�����ж��������Ƿ�Ϊ��Ȼ���ԡ�Ҫ���������ʱ���Ӽ�������������Ȼ����
����Ƿ�Ϊ��Ȼ���ԡ���Ȼ���ԣ���������Ȼ���ֱ�ΪA��B������A>B��
���A+B��A-B����ƽ��������ôA��B������Ȼ���ԡ�Ҫ����A��B����Ȼ���ԣ������1��
��A��B������Ȼ���ԣ������0����A<B���������error!��
*/ 
#include <stdio.h> 
#include <math.h> 
int main()
{
	int i,j,temp1,temp2;
	printf("����������Ȼ�� ��");
	scanf("%d%d",&i,&j);
	temp1 = (int)sqrt(i + j);
	temp2 = (int)sqrt(i - j);
	if(i < j)
        printf("error!");
	else if(temp1 * temp1 == i + j && temp2 * temp2 == i - j)
	    printf("1");
	else
	    printf("0");
	return 0;
}

