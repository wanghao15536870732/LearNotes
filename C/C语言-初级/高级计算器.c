/*
���ʵ��һ��������������ļ�������������ʵ������"a op1 b op2 c"�Ļ���������㣬
����a��b��c�ֱ��ǲ�������op1��op2�ֱ�������������Ҫ��
��1�������������ǻ������ͣ�����������Ǽӣ�+��������-����ȡ�ࣨ%�������ݣ�^��,
���ȼ�������˵����ȡ�������������ͬ����ȡ�ࡢ���ݣ���ӡ����������ԣ�
��2�������ɶ���������ɣ�����main��������ʵ���������ʽ�����룬���������������
�Ӻ�������ʵ���������ʽ�ļ��㣬�Ӻ���������һ����Ҳ�����Ƕ�������û�������ƣ�
��3����������ʱ���ɼ����������ݡ�
*/ 

#include"stdio.h"
int fun(int x, char op, int y)
{
	switch (op)
	{
	case '+':return x + y;
	case '-':return x - y;
	case '%':return x % y;
	case '^':
		{
				int re=1;
				for (int i = 1; i <= y; i++)
					re *= x;
				return re;
		}
	}
}
int computer(int a, char op1, int b, char op2, int c)
{
	int op1sort=1, op2sort=1;
	if ((op1 == '+' || op1 == '-') && (op2 == '%' || op2 == '^'))
		op2sort = 2;
	if (op1sort == op2sort)
		return fun(fun(a, op1, b), op2, c);
	else
		return fun(a,op1,fun(b,op2,c));
}
int main()
{
	int a, b, c;
	int result;
	char op1, op2;
	scanf("%d",&a);
	op1 = getchar();
	scanf("%d", &b);
	op2 = getchar();
	scanf("%d", &c);
	result = computer(a, op1, b, op2, c);
	printf("%d\n",result);
}


