/*
 ��д����Ҫ���������ʱ���Ӽ��������������������������С��һ������
*/
#include <stdio.h>
#include <math.h>
int main()
{
	int a,b,c,temp = 0;
	printf("������������ ��");
	scanf("%d%d%d",&a,&b,&c);
	if(a > b)
	{
		temp = a;
		a = b;
		b = temp;
    }
	if(a > c)
	{
		temp = a;
		c = a;
		a = temp;
	}
    printf("������С��һ����Ϊ : %d",a);
    return 0; 
}

