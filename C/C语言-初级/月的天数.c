/*
��д����Ҫ���������ʱ���Ӽ�������һ���·ݣ����2017������ж����졣
��������·ݲ���1��12�����error!��
*/

#include <stdio.h>
int main()
{
	int i;
	printf("������2017���һ���·� ��");
	scanf("%d",&i);
	if(i >= 1 && i <= 12) 
	{
		switch(i)
		{
        case 1:case 3:case 5:case 7:case 8:case 10:case 12: 
        	printf("������31��\n");break;
        case 4:case 6:case 9:case 11: 
        	printf("������30��\n");break;
        case 2:
        	printf("������28��\n");break;
		}
	}
	else
	{
		printf("error!");
	}
	return 0;
}

