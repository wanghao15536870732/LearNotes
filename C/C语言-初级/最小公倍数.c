/*
��д���������������������Լ������С��������
��������ʱ����������������������Լ������С��������
*/

#include <stdio.h>
int main()
{
	int i,j,x,y;
	printf("���������������� ��");
	scanf("%d %d",&i,&j);
	x = i;
	y = j;
	int temp1,temp2;
	if(i > j)
	{
		temp1 = i;
		i = j;
		j = temp1;
	}
	temp2 = j % i;
	while(temp2 != 0)
	{
		j = i;
		i = temp2;
		temp2 = j % i;
	}
	printf("���Լ���� ��%d\n",i);
	printf("��С�������� ��%d\n\n",x*y/i);
	return 0;
}

