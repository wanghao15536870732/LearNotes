#include "stdio.h"
#include "stdlib.h"
#include "string.h"
int is_operation(char op);
int priority(char op);
void postfix(char e[], char f[]);

int main()
{

	char a[20] = "";
	char b[20] = { 0 };
	printf("��������\"#\"��β����׺���ʽ��\n");
	scanf("%s",a);
	postfix(a, b);
	printf("��Ӧ�ĺ�׺���ʽΪ��\n");
	for (int i = 0; i < 10; i++)
		printf("%c", b[i]);
	printf("\n");
	system("pause");
	return 0;
}

/****************************************/
/****** �ж�һ���ַ����Ƿ�Ϊ����� ******/
/****************************************/
int is_operation(char op)
{
	switch (op)
	{
	case '+':
	case '-':
	case '*':
	case '/': return 1;
	default:return 0;
	}
}

/****************************************/
/*********** ������������ȼ� ***********/
/****************************************/
int priority(char op)
{
	switch (op)
	{
	case '#': return -1;
	case '(': return 0;
	case '+':
	case '-': return 1;
	case '*':
	case '/': return 2;
	default: return -1;
	}
}


/***************************************************/
/* ��һ����׺���ʽ e ת���������ȼ۵ĺ�׺���ʽ f */
/***************************************************/

void postfix(char e[], char f[])
{
	int i = 0, j = 0;
	char opst[100] = { 0 };
	int top, t;
	top = 0;
	opst[top] = ' ';
	top++;
	while (e[i] != '#')
	{
		if ((e[i] >= '0' && e[i] <= '9') || e[i] == '.')
			f[j++] = e[i];  // �������ֻ���С���ֱ��д���׺���ʽ
		else if (e[i] == '(')  // ���������Ž��������ջ
		{
			opst[top] = e[i];
			top++;
		}
		else if (e[i] == ')')
			//���������Ž����Ӧ�������ź�Ĳ�����ȫ��д���׺���ʽ 
		{
			t = top - 1;
			while (opst[t] != '(')
			{
				f[j++] = opst[--top];
				t = top - 1;
			}
			top--; // '( ' ��ջ
		}
		else if (is_operation(e[i])) // '+ ��-��*��/ '
		{
			f[j++] = ' '; // �ÿո�ֿ�����������
			while (priority(opst[top - 1]) >= priority(e[i]))
				f[j++] = opst[--top];
			opst[top] = e[i];
			top++;// ��ǰԪ����ջ
		}
		i++;// ������һ��Ԫ��	
	}
	while (top)
		f[j++] = opst[--top];
}