/*
һ��һάn*sizeof(int)����(��0�ͷ�0��)������0���ŵ�����ǰ�棬0�����ơ�
��Ҫ��ѭ��ִ�д���Խ��Խ��,n���Լ�����ģ��������Ҳ�Լ����룩 
*/

#include <stdio.h>
int main()
{
    int a[10000],n;
    int i,j,temp = 0;
	printf("�������������ĸ��� ��");
	scanf("%d",&n);
	for(i = 0;i < n;i ++)
	{ 
		scanf("%d",&a[i]);
	}
	for(i = 1;i <= n - 1;i ++)
	{
		for(j = 1;j <= n - 1;j ++)
		{
			if(a[j - 1] < a[j])
			{
				temp = a[j - 1];
				a[j - 1] = a[j];
				a[j] = temp;
			}
		}
	} 
	for(i = 0;i < n;i ++)
	{
        puts("���");
		printf("%d\t",a[i]);
	}
	printf("\n");
	return 0;
}

