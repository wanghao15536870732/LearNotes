/*
��д����Ҫ���������ʱ���Ӽ�����һԪ���η���ax2+bx+c=0��ϵ��a��b��c��
���㲢����÷���ʵ���ĸ�����Ҫ����a =0�����error!��
*/ 

#include <stdio.h>
int main()
{
	int a,b,c;
	int temp = 0;
	printf("������һԪ���η���a*x*x + b*x + c = 0��ϵ��a,b,c : ");
	scanf("%d%d%d",&a,&b,&c);
	temp = b * b - 4 * a * c; 
	if(a == 0)
	    printf("error!");
	else if(temp > 0)
		printf("�÷���������ʵ��\n");
	else if(temp = 0)
	    printf("�÷�����һ��ʵ��\n");
	else
	    printf("�÷���û��ʵ��\n");
	return 0;
}

