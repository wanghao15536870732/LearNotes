/*
��д�����ж��ַ����ͣ�Ҫ���������ʱ���Ӽ�������һ���ַ���������ַ������͡�
��������ַ�����ĸ�������It is an alphabetic character.��
��������ַ��������������It is a digit.��
��������ַ��������ַ��������It is other character.��
*/
#include <stdio.h>
int main()
{
	int c;
	printf("������һ���ַ� ��");
	c = getchar();
	if(c >= 48 && c <= 57)
		printf("It is a digit.\n");
	else if( (c >= 65 && c <= 90) || (c >= 97 && c <= 122) )
		printf("It is an alphabetic character.\n");
	else 

		printf("It is other character.");
	return 0;
}


