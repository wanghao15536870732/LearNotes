/*
���������Խ������.��nά�����������һ��һ�����븳ֵ��̫�鷳�Ļ����Կ��ǻ���i��j��
*/ 
#include <stdio.h>
int main()
{
	int i,n,j;
	int c1 = 0,c2 = 0,c = 0,k = 0;
	int a[100][100];
	printf("���������Ľ��� n ��");
	scanf("%d",&n); 
	for( i = 0;i < n;i ++ )
	{
		for(j = 0;j < n;j ++ )
		{
			scanf("%d",&a[i][j]);
	    }
	    k = a[i][i];
	    c1 = c1 + k;
	    c = a[i][n - i - 1];
	    c2 = c2 + c;
    }
	printf("��n�׾���ĶԽ���֮��Ϊ ��%d",c1 + c2);
	return 0;
}

