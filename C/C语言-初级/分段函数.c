/*
��д����Ҫ���������ʱ���Ӽ�������x��ֵ��
���ݷֶκ������㲢���y��ֵ�����������λС������
�ֶκ������¡�����ʾ����ʹ����ƽ����������sqrt()��
*/ 

#include <stdio.h>
#include <math.h> 
int main()
{                        
	int x;
	double y;
	printf("���x��ֵ ��");
	scanf("%d",&x);
	if(x < 1)
	{
		y = x * x + 2 * x + sin(x);
		printf("���y��ֵ ��%.2lf\n",y); 
	}
	else if(x >= 1 && x <= 10)
	{
		y = 2 * x - 1;
		printf("���y��ֵ ��%.2lf\n",y);
	}
	else
	{
		y = sqrt(2 * x * x * x - 11);
		printf("���y��ֵ ��%.2lf\n",y);
	}
	return 0;
}



