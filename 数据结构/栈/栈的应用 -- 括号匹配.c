#include <stdio.h>
#include <stdlib.h>
# define MAXSIZE 100


typedef int datatype;
typedef struct{
	datatype a[MAXSIZE];
	int top;
}sequence_stack;

//ջ�ĳ�ʼ��
void init(sequence_stack *st);
//�ж�ջ�Ƿ�Ϊ��
int empty(sequence_stack st);
//��ջ���Ľڵ�ֵ 
datatype read(sequence_stack st);
//ջ�Ĳ������(��ջ)
void push(sequence_stack *st,datatype x);
//ջ��ɾ������(��ջ)
void pop(sequence_stack *st);
//����ƥ��
int match_kouhao(char c[]); 

int main()
{
	char c1[100];
	printf("����c1(��һ��������'#'):");
	scanf("%s", c1);
	char c2[100];
	printf("����c2(��һ��������'#'):");
	scanf("%s", c2);
	if (match_kouhao(c1))
		printf("\n\nc1 ����ƥ��ɹ���\n");
	else
		printf("\n\nc1 ����ƥ��ʧ�ܣ�\n");
	if (match_kouhao(c2))
		printf("\n\nc2 ����ƥ��ɹ���\n");
	else
		printf("\n\nc2 ����ƥ��ʧ�ܣ�\n");
	return 0;
}

/********************************/
/*�������ܣ�ջ�ĳ�ʼ�� ***********/
/*******************************/

void init(sequence_stack *st)
{
	st->top = 0;
}


/********************************/
/*�������ܣ��ж�ջ�Ƿ�Ϊ�� *****/
/*******************************/

int empty(sequence_stack st)
{
	return(st.top ? 0 : 1);
}

/********************************/
/*�������ܣ���ջ���Ľڵ�ֵ *****/
/*******************************/

datatype read(sequence_stack st)
{
	if(empty(st))
	{
		printf("\nջ�ǿյģ�");
		exit(1);
	}
	else
		return st.a[st.top - 1];
}

/***************************************/
/*�������ܣ�ջ�Ĳ������(��ջ) ********/
/**************************************/

void push(sequence_stack *st,datatype x)
{
	if(st->top == MAXSIZE)
	{
		printf("\nջ�Ѿ����ˣ�");
		exit(1);
	}
	st->a[st->top] = x;
	st->top ++;
}


/***************************************/
/*�������ܣ�ջ��ɾ������(��ջ) ********/
/**************************************/

void pop(sequence_stack *st)
{
	if(st->top == 0)
	{
		printf("\n����һ���յ�ջ��");
		exit(0);
	}
	st->top --;
}

/***************************************/
/*�������ܣ�ջ��ɾ������(��ջ) ********/
/**************************************/

int match_kouhao(char c[])
{
	int i = 0;
	sequence_stack s;
	init(&s);
	while(c[i] != '#')
	{
		switch(c[i])
		{
			case '{':
			case '[':
			case '(': 
				push(&s,c[i]); 
				break;
			case '}': 
				if(!empty(s) && read(s) == '{')
				{
					pop(&s);
					break;
				}
				else
					return 0;
			case ']':
				if(!empty(s) && read(s) == '[')
				{
					pop(&s);
					break;
				}
				else
					return 0;
			case ')':
				if(!empty(s) && read(s) == '(')
				{
					pop(&s);
					break;
				}
				else
					return 0;
		}
		i ++;
	}
	return (empty(s));
}

