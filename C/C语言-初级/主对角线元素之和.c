/*
��д������һ3��3�е��������������ɼ������룩�����㲢������������Խ���Ԫ��֮�͡�
*/

#include <stdio.h>
int main()
{ 
	int num[3][3];
	int i,j,sum;
	puts("������һ�����׾��� ��\n");
	for(i = 0;i < 3;i ++)
	{
		for(j = 0;j < 3;j ++)
			scanf("%d",&num[i][j]);
	}
	sum = 0;
	for(i = 0;i < 3;i ++)
		sum += num[i][i];
	printf("���������Խ���֮��Ϊ ��%d",sum);
	return 0;
}

