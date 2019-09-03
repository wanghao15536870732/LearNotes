/*
1707004716--����
��������: vs2010 + Easy-X
*/

/*
1.����Ctrl  + ������  ��ɫ�ַ���
2.����Shift + ������   ��ɫԲ����
3.����Ctrl  + ����Ҽ�   �򵥵�̰������Ϸ
*/
#include <stdio.h>
#include <graphics.h>
#include <time.h>
#include <conio.h>
#include <dos.h>
#define N 30  //�ߵ���󳤶�Ϊ30

//�����ߵ�����
struct Snack
{
	int X[N];
	int Y[N];
	int node;   //�ߵĽ���
	int dir;   //�ߵķ���
	int life;   //�ߵ�����
}snack;

//�������������
struct Food
{
	int x1;      //ʳ��ĺ�����
	int y1;      //ʳ���������
	int temp;  //�ж��Ƿ�Ҫ������һ��ʳ�� 
}food;

//�Զ��庯��wall()�����������ǽ��ש


void wall(int x,int y)
{
	int sizx = 9;
	int sizy = 9;
	//����ש����ɫΪ��ɫ
	setcolor(BLUE);  
	//���滭�����������һ������
	//������
	line(x,y,x + sizx,y);
	line(x + 1,y + 1,x + sizx - 1,y + 1);
	//������
	line(x,y,x,y + sizy);
	line(x + 1,y + 1,x + 1,y + sizy - 1);
	setcolor(YELLOW);
	//������
	line(x + sizx,y,x + sizx,y + sizy);
	line(x + sizx - 1,y + 1,x + sizx - 1,y + sizy - 1);
	//������
	line(x,y + sizy,x + sizx,y + sizy);
	line(x + 1,y + sizy - 1,x + sizx - 1,y + sizy - 1);
	setfillstyle(1,12);    //���ש���м䲿��,�ù�ʵ���
	setcolor(GREEN);
	bar(x + 2,y + 2,x + sizx - 2,y + sizy - 2);  //������ͼ
}

//���庯��dowall(),�����л�ǽ

void dowall()
{
	int j;
	for(j = 40;j <= 600;j += 10)
	{
		wall(j,40);  //������ǽ
		wall(j,441);  //������ǽ
	}
	for(j = 40;j <= 440;j += 10)
	{
		wall(40,j);  //������ǽ
		wall(601,j);  //������ǽ
	}
}

//����������������ʾ��Ϸ����

void Gameover1(int score)
{
	TCHAR c1[] = _T("���ź���ײ��ǽ�ˣ�GAME  OVER!!!");
	cleardevice();  //����
	setcolor(YELLOW);  //����ǰ��ɫΪ��ɫ
	settextstyle(50, 0, _T("����"));  //��������Ϊ50������
	outtextxy(50,200,c1);              //��ָ��λ�����
	settextcolor(RGB(155, 51, 68));
	TCHAR b[10];
	//������ת����ַ�д������
	_stprintf(b, _T("%d"), score);
	//�ڴ������������
	outtextxy(540, 300, _T("��ķ���:"));
	//�����������ɫΪ��ɫ
	settextcolor(RED);
	outtextxy(790, 300, b);
	Sleep(3);
}
void Gameover2()
{
	TCHAR c2[] = _T("���ź����Ե��Լ��ˣ�GAME  OVER!!!");
	setbkcolor(BLACK);
	cleardevice();  //����
	setcolor(RED);  //����ǰ��ɫΪ��ɫ
	settextstyle(50, 0, _T("����"));  //��������Ϊ50������
	outtextxy(50,200,c2);              //��ָ��λ�����
	Sleep(3);
}

//��Ϸ��ʵ�ֹ���

void Play()
{
	int i;
	int score = 0;  //������Ϸ����
	int speed = 300;
	char key;  //���������Ϣ
	srand((unsigned long)time(0));   //Ϊʳ��ĳ����ṩ�����
	food.temp = 1;   //����ʳ��,Ϊ�����߳Ե�ʳ����ٴγ���ʳ��
	//����һ��ʼ�ߵķ�������
	snack.dir = 1;
	//��ͷ��λ��
	snack.X[0] = 300;   //�����ߵĵ�һ�ڵ�λ��
	snack.Y[0] = 240;

	snack.X[1] = 290;   //�����ߵĵڶ��ڵ�λ��
	snack.Y[1] = 240;
	snack.life = 0;   //�߻���
	//�����ߵĽ���
	snack.node = 2;  
	do
	{	
		while(!kbhit())    //��û�а�����Ϣ������£����Լ��ƶ�
		{
			//������ֵ�һ��ʳ��

			if(food.temp == 1)     //�ж��Ƿ���Ҫ��ʳ��ĳ���
			do
			{
				food.x1 = (rand() % 520) + 60;  //��������ĺ�����
				food.y1 = (rand() % 270) + 60;  //����ʳ���������
				food.temp = 0;               //ʳ��Ĳ���	
			}while(food.x1 % 10 != 0 || food.y1 % 10 != 0 ||
				food.x1 > 600 || food.x1 < 40 || food.y1 < 40 || food.y1 > 440);
			//�ߵ�һ�ڳ�Ϊ�߳�Ϊ10�������Σ�����ֻ�ܳԵ�����Ϊ10�ı�������������ǽ֮�ڵ�ʳ��
			if(food.temp == 0)    //�ж��Ƿ�Ҫ��ʳ��
			{
				setcolor(LIGHTBLUE);  //���õ�һ��ʳ�����ɫΪ����ɫ
				setlinestyle(PS_DASH,PS_ENDCAP_ROUND); //����Ϊ���ߣ����Ӵ�ΪԲ��
				rectangle(food.x1,food.y1,food.x1 + 10,food.y1 + 10);   //����ʳ�� 
			}
			for(i = snack.node;i > 0;i --)  //ʵ������ǰ�ƶ�
			{
				//�����������ǰ��
				snack.X[i] = snack.X[i - 1];         
				snack.Y[i] = snack.Y[i - 1];  
			}
			//�ߵķ���
			switch(snack.dir)
			{
			case 1:
				snack.X[0] += 10;   //��ͷ������
				break;
			case 2:
				snack.X[0] -= 10;   //��ͷ������
				break;
			case 3:
				snack.Y[0] -= 10;   //��ͷ������
				break;
			case 4:
				snack.Y[0] += 10;   //��ͷ������
				break;
			}
			
			//����߳Ե��Լ�������Ϸ����
			for(i = 3;i < snack.node;i ++)
			{
				//�����Ե��Լ��ĵ��ĶΣ�i��3��ʼ
				if((snack.X[0] == snack.X[i]) && (snack.Y[0] == snack.Y[i]))  
				//�����ͷ�������ĳһ��������ͬ
				{
					Gameover2();
					snack.life = 1;  //�߳Ե��Լ�����
					break;
				}
			}
			if(snack.X[0] == food.x1 && snack.Y[0] == food.y1)  //�ж��Ƿ�Ե���ʳ��
			{
				//�ñ���ɫ�������ڸǵ�ʳ��
				setcolor(BLACK);
				//rectangle(food.x1,food.y1,food.x1 + 10,food.y1 + 10);
				snack.node ++;   //������һ��
				food.temp = 1;     //�ٳ���ʳ��
				speed = speed - 10;  //�ߵ��ٶ�����
				score ++; //������һ
			}
			//��ʾ��Ϸ����
			//����������ɫ
			settextcolor(LIGHTRED);
			TCHAR b[10];

			//������д������,����int��ת���char����
			_stprintf(b, _T("%d"), score);
			outtextxy(660, 300, _T("��ķ���:"));
			//��ָ��λ���������score
			settextcolor(LIGHTRED);
			outtextxy(780, 300, b);

			//�����ײ��ǽ�ڣ�����Ϸ����
			if(snack.X[0] < 50 || snack.X[0] > 590 || snack.Y[0] < 50 || snack.Y[0] > 430)
			{
				Gameover1(score);
				snack.life = 1;  //��ײǽ����
					break;      
			}

			//�����ߵķ���ͼ��

			setcolor(YELLOW);
			for(i = 0;i < snack.node;i ++)
			{
				//�����ߵĸ�ʽΪʵ�ߣ��˵�ΪԲ��
				setlinestyle(PS_SOLID,PS_ENDCAP_ROUND);

				//ͨ��ѭ��������ͬ��������
				rectangle(snack.X[i],snack.Y[i],snack.X[i] + 10,snack.Y[i] + 10);
			}
			Sleep(speed);   //�ӳ�ʱ�䣬�������ǿ������ߵ��ƶ��ٶ�

			//����������ɫΪ����ɫ��ɫ
			setcolor(BLACK);
			//�ñ���ɫ���ǵ��ߵ����һ��
			rectangle(snack.X[snack.node - 1],snack.Y[snack.node - 1],snack.X[snack.node - 1] + 10,snack.Y[snack.node - 1] + 10);
		}
		if(snack.life == 1)  //�������
		{ 
			break;			//������ѭ��
		}
		key = _getch();      //���ܼ��̰�����Ϣ

		//����������ͨ������������Ϣ���ı��ߵķ���

		if(key == 'p')  //�������p��������ͣ
		{
			system("pause");   //����ֹͣ
		}
		if(key == 'w' && snack.dir != 4)   //����w�����Ҵ�ʱ��������
		{
			snack.dir = 3;                //������
		}
		else                              
		{
			if(key == 's' && snack.dir != 3)		//����s�����Ҵ�ʱ��������
			{										
				snack.dir = 4;            //������
			}
			else
			{
				if(key == 'd' && snack.dir != 2)    //����d�����Ҵ�ʱ��������
				{
					snack.dir = 1;			//������
				}
				else
				{
					if(key = 'a' && snack.dir != 1)  //����a�����Ҵ�ʱ��������
					{
						snack.dir = 2;	     //������
					}
				}
			}
		}
	}
	while (key != 'o');   //����o��������Ϸ
}

int main()
{
	//���������������
	srand((unsigned) time(NULL));
	initgraph(640,480);
	//������ҳ�����
	settextstyle(25, 0, _T("����"));  //��������Ϊ30������
	TCHAR s0[] = _T("1 .����Ctrl  + ������  ��ɫ�ַ���");
	outtextxy(80,100,s0);
	TCHAR s1[] = _T("2 .����Shift + ������   ��ɫԲ����");
	outtextxy(80,130,s1);
	TCHAR s2[] = _T("3 .����Ctrl  + ����Ҽ�   �򵥵�̰������Ϸ");
	outtextxy(80,160,s2);
	TCHAR s3[] = _T("̰������Ϸ��");
	outtextxy(130,190,s3);
	TCHAR s4[] = _T("��Ϸ����");
	outtextxy(130,220,s4);
	TCHAR s5[] = _T("'w'---������������");
	outtextxy(160,250,s5);
	TCHAR s6[] = _T("'a'---������������");
	outtextxy(160,280,s6);
	TCHAR s7[] = _T("'s'---������������");
	outtextxy(160,310,s7);
	TCHAR s8[] = _T("'d'---������������");
	outtextxy(160,340,s8);
	TCHAR s9[] = _T("'p'---��ͣ(�ٰ�����������)");
	outtextxy(160,370,s9);
	TCHAR s10[] = _T("��׼���ã�����Ϸ������ʼ����");
	outtextxy(140,410,s10);
	//�����ַ�������x,y
	int x,y;
	//�����ַ�
	char c;
	//����СԲ��İ뾶
	int f = 10;
	//������ɫ
	float T = 190;  //����ɫ��
	float H = 190;  //����ɫ��
	float S = 1;	//���ñ��Ͷ�
	float L = 0.7f;   //��������
	//��������
	settextstyle(16,8,_T("����"));
	MOUSEMSG m;		// ���������Ϣ
	while(true)
	{
		// ��ȡһ��������Ϣ
		m = GetMouseMsg();
		switch(m.uMsg)
		{
			case WM_LBUTTONDOWN:
				// ����������ͬʱ������ Ctrl ��
				if (m.mkCtrl)
				{
					//�Ѹղŵ�ҳ����������
					setbkcolor(BLACK);
					cleardevice();
					int i;
					for(i = 0;i <= 240;i ++)
					{
						//��ɫ����仯���ַ�
						//��ɫ�࣬���ȣ��ͱ��Ͷ���ɵ���ɫ
						settextcolor( HSLtoRGB(H,S,L));
						//���λ����ʾ���������ĸ
						for(int j = 0;j < 3;j ++)
						{
							//�������ֵ�λ��
							x = (rand() % 80) * 10;  //���������
							y = (rand() % 20) * 25;  //���������
							c = (rand() % 20) + 65;   //�����ַ�
							//�ڴ���������������ַ�
							outtextxy(x,y,c);
						}
						//����ɫ���ߴ������²���
						setlinecolor(YELLOW);
				    //  setlinestyle(PS_DOT | PS_ENDCAP_ROUND,5);
						line(0,i,640,i);  //line(��ʼ����x,y,��������x,y)
						Sleep(3);    
						//����ɫ���ߴ������ϲ���
						setlinecolor( HSLtoRGB(H,S,L));
						H += 5;
						if(H == 790)
							H = 190;
				    //  setlinestyle(PS_DASHDOT | PS_ENDCAP_SQUARE,3);
						line(0,480 - i,640,480 - i);
						Sleep(3);
						if(i >= 240)    //�ظ����в���
							i = -1;
						if(kbhit())  //������̰�������������˳�
							break;
					}
				}
				//����������ͬʱ������ Shift ��
				if(m.mkShift)
				{ 
					//�Ѹղŵ�ҳ����������
					setbkcolor(BLACK);
					cleardevice();
					int i,j;
					for(i = 0;i <= 320;i ++)
					{
						//���λ����ʾԲ
						for(j = 0;j < 3;j ++)
						{
							x = (rand() % 70) * 15; 
							y = (rand() % 20) * 35; 
							//���ʵ��Բ
							fillcircle(x,y,10);	
							/*
							//�����һ�ִ�С�ɱ��Բ���õ���һ����Ч��
							fillcircle(x,y,f);
							f += 5;
							if(f == 80)
								f = 10;
							*/
							//����������ɫ
							setfillcolor(HSLtoRGB(T,S,L));
							T += 5;  //��ɫ������
							if(T == 790)
								T = 190;
							setfillstyle(BS_HATCHED,HS_DIAGCROSS);  //����Բ��Ϊ��ʵ��� 
							//���� HS_CROSS, ��б HS_FDIAGONAL, б���� HS_DIAGCROSS

						}
						//����ɫ���ߴ������Ҳ���	
						setlinecolor(YELLOW);
				//      setlinestyle(PS_DOT | PS_ENDCAP_ROUND,5);
						line(i,0,i,480);
						Sleep(3);//˯��3����
						//����ɫ���ߴ����������
						setlinecolor( HSLtoRGB(H,S,L));
						H += 5;
						if(H == 790)
							H = 190;
				    //  setlinestyle(PS_DASHDOT | PS_ENDCAP_SQUARE,3);
						line(640 - i,0,640 - i,480);
						Sleep(3);
						if(i >= 320)    //�ظ����в���
							i = -1;
						if(kbhit())  //������̰�������������˳�
							break;
					}
				}
			case WM_RBUTTONUP:
				if(m.mkCtrl)  //������Ҽ� + Ctrl
				{	
					//����Ļ����С
					initgraph(940,480);
					
					//����ǰ��ɫΪ��ɫ
					setcolor(YELLOW);
					/*
					//����ɫ����Ϊ��ɫ���Ա���Թ۲쵽����ԭ��
					setbkcolor(GREEN);
					cleardevice();
					*/
					//�䴦��Ϸ���淨
					settextstyle(20, 0, _T("����"));  //��������Ϊ20������
					TCHAR c3[] = _T("̰������Ϸ");
					outtextxy(730,40,c3);
					TCHAR c4[] = _T("��Ϸ����");
					outtextxy(630,60,c4);
					TCHAR c5[] = _T("'w'---������������");
					outtextxy(660,100,c5);
					TCHAR c6[] = _T("'a'---������������");
					outtextxy(660,140,c6);
					TCHAR c7[] = _T("'s'---������������");
					outtextxy(660,180,c7);
					TCHAR c8[] = _T("'d'---������������");
					outtextxy(660,220,c8);
					TCHAR c9[] = _T("'p'---��ͣ(�ٰ�����������)");
					outtextxy(660,260,c9);
					settextstyle(25, 10, _T("Verdana"));
					dowall();			//��ʼ��ǽ
					Play();				//��ʼ����Ϸ
					getch();            //�˳���Ϸ����
					closegraph();		
				}
				if(m.mkShift)
					return 0;	// ������Ҽ� + Shift �˳�����
		}
	}
	closegraph();
	return 0;
}



