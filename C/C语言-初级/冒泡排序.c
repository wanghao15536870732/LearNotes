/*
��д������һ����10�������������У���������ʱ�������ɼ������룩��
��ɶԸ����д�С����������������Ľ����
*/
 #include <stdio.h>
int main()	
{
	int num[10];
	int n,i,j;
	puts("������ʮ������ ��"); 
	for(n = 0;n < 10;n ++)
		scanf("%d",&num[n]);
	int temp;
	for(i = 1;i <= 10 - 1;i ++)
	{
		for(j = 1;j <= 10 - i;j ++)
		{
			if(num[j - 1] > num[j])
			{	
				temp = num[j - 1];
				num[j - 1] = num[j];
				num[j] = temp;
			}
		}
	}
	puts("�������С��������� ");
	for(j = 0;j < 10;j ++)
		printf("%d ",num[j]);
	printf("\n\n");
	return 0;
}

