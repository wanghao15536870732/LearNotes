/*
��̳���ʵ��һ��������������ļ�������������ʵ������"a op1 b op2 c"�Ļ���������㣬
����a��b��c�ֱ��ǲ�������op1��op2�ֱ�������������Ҫ��

��1�������������Ǹ����ͣ�����������Ǽӣ�+��������-�����ˣ�*��������/����,
���ȼ�������˵�����ȳ˳���Ӽ��������ԣ�

��2�������ɶ���������ɣ�����main��������ʵ���������ʽ�����룬
����������������Ӻ�������ʵ���������ʽ�ļ��㣬
�Ӻ���������һ����Ҳ�����Ƕ�������û�������ƣ�

��3��������������λС����

��4����������ʱ���ɼ����������ݡ�

ʾ��1�� 
��������Ϊ��1+2+3<�س�>
��������6

ʾ��1�� 
��������Ϊ��1+2/3<�س�>
��������1.67


*/ 

#include<stdio.h>
double fun(double i,double j,char str1);
int main()
{
	double a,b,c;
	char s1,s2;
	double e = 0;
	scanf("%lf%c%lf%c%lf",&a,&s1,&b,&s2,&c);
	if(s2 == '*' || s2 == '/')
		e = fun(a,fun(b,c,s2),s1); 
	else 
		e = fun(fun(a,b,s1),c,s2);
	printf("%.2lf",e);
	return 0;
} 
double fun(double i,double j,char str)
{
	double n = 0;
	int t = (int)str;
	switch(t)
	{
	case 43:
		n = i + j;break;
	case 45:
		n = i - j;break;
	case 42:
		n = i * j;break;
	case 47:
		n = i / j;break;
	}
	return n;
}

