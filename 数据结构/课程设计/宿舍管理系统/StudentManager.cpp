#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define  HEAD printf("\t|%-21s %-10s %-10s %-8s %-8s %-5s %-5s %-5s %-8s %-9s %-5s|\n","ѧ��","����","רҵ","�༶","��Ԣ��","����","��λ","�Ա�","����","�ֻ���","����")

//�����¼ 
//�����¼��Ϣ 

typedef struct EN{ //���û������� 
	char userName1[10];
	char passWorld1[10];
}EN;

void enter();

//�������
void encryption(char passWorld[])
{
	int i; 
	//��ÿһλ�����Ascall��ֵ�ı� 
	for(i = 0;i < strlen(passWorld);i ++)
	{
		passWorld[i] += 20;
	} 
} 

//ע��
void  sign_in(char userName[],char passWorld[])
{
	FILE *fp;
	int flag = 0;
	char userName1[10];
	char passWorld1[10];
	printf("\tע��\n");
	printf("\t�û���:");
	fflush(stdin);
	gets(userName);
	printf("\t����:");
	gets(passWorld);
	//�ж��ļ��Ƿ���� 
	if((fp = fopen("enter.txt","rt")) == NULL)
	{
		//��������ھ�ֱ���˳� 
		exit(0);
	}
	while(!feof(fp))
	{
		fscanf(fp,"%s %s",userName1,passWorld1);
		
		//�ж�userName��userName1�Ƿ���ͬ 
		if(!strcmp(userName,userName1))
		{
			printf("�û����ظ�\n");
			flag = 1;
			break;
		}
	}
	//�ر��ļ��� 
	fclose(fp);
	if(flag == 1)
	{
		enter(); 
	} 
	else
	{ 
		if((fp = fopen("enter.txt","at")) == NULL)
			exit(0);
		encryption(passWorld); //����
		
		//��userName��passWorldд��enter.txt�ļ����� 
		fprintf(fp,"%s %s\n",userName,passWorld);
	}
	
	//�ر��ļ��� 
	
	fclose(fp);
	enter(); 
}

//ɾ�����Ϸ��û�
void alter()
{
	FILE *fp;
	int n = 0;
	
	//���� 
	EN en[1000];
	//��enter.txt�ļ� 
	fp = fopen("enter.txt","rt");
	if(fp == NULL)
	{
		printf("\t���ļ�ʧ��\n");
		exit(0);
	}
	//�ж϶�ȡ�Ƿ��ļ��Ľ�β 
	while(!feof(fp))
	{
		//��ȡenter.txt�ļ����е�userName��passWorld 
		fscanf(fp,"%s %s",en[n].userName1,en[n].passWorld1);
		n ++;
	}
	
	printf("\t%-8s\t%-8s\n","�û���","����");
	int i;
	for(i = 0;i < n;i ++)
	{
		printf("\t%-8s\t%-8s\n",en[i].userName1,en[i].passWorld1);
	}
	fclose(fp);
	printf("\t������Ҫɾ�����û���\n");
	printf("\t�û���:");
	char ch[10];
	printf("\t");
	scanf("%s",ch);
	for(i = 0;strcmp(ch,en[i].userName1);i ++)
	{
		
	}
	int k = i;
	for(i = k;i < n - 1;i ++)
	{
		en[i] = en[i + 1];
	}
	n --;
	fp = fopen("enter.txt","wt");
	if(fp == NULL)
	{
		printf("\t���ļ�ʧ��\n");
		exit(0);
	}
	//�Ѳ��Ϸ����û�ɾ����д���ļ� 
	for(i = 0;i < n;i ++)
	{
		fprintf(fp,"%s %s\n",en[i].userName1,en[i].passWorld1);
	}
	fclose(fp);	
}

//��¼��� 

void enter()		
{
	printf("\t=================================\n");
	printf("\t|\t��¼:\t\t\t|\n");
	printf("\t=================================\n");
	FILE *fp;
	int i;
	printf("\t1.�������Ա\t2.��¼\n");
	char userName[10];
	char passWorld[10];
	char userName1[10];
	char passWorld1[10];
	int choice;
	printf("\t");
	scanf("%d",&choice);
	int flag = 0;
	switch(choice)
	{
		case 1:{        //����Ա��ע���û���ɾ�� 
			char adm[10]; 
			printf("\t�����������Ա����\n");
			printf("\t");
			scanf("%s",adm);
			//������Ա�����1���жԱȣ���ζ�Ź���Ա�������1 
			if(strcmp(adm,"1"))
			{
				printf("\t�������Ա�������\n");
				enter();
			}
			printf("\t");
			printf("1.ע��\t2.�޸�\n");
			int j;
			printf("\t");
			scanf("%d",&j);
			switch(j)
			{
				case 1:{
					//ע�� 
					sign_in(userName,passWorld);
					break;
				}
				case 2:{
					//�޸� 
					int flag1 = 0;
					do
					{
						alter();
						flag1 = 0;
						printf("\t�Ƿ����ɾ����1.��  2.��\n");
						printf("\t");
						scanf("%d",&flag1);
					}
					while(flag1 == 1);
					//���������� 
					enter();
					break;
				}
				default:{
					break;
				}
			}			
			break;
		}
		
		//�û���¼ 
		case 2:{     
			printf("\t��¼\n");
			printf("\t�û���:");
			//����fflush���ڽ�������������������ļ���ȥ
			//����ɹ�ˢ�£�fflush����0��ָ������û�л���������ֻ����ʱҲ����0ֵ
			fflush(stdin);
			printf("\t");
			gets(userName);
			printf("\t����:");
			printf("\t");
			gets(passWorld);
			if((fp = fopen("enter.txt","rt")) == NULL)
			{
				exit(0);
			}
			//feof(FILE *stream) ���Ը����� stream ���ļ�������ʶ����
			//���û�е����ļ���β 
			while(!feof(fp))
			{
				fscanf(fp,"%s %s",userName1,passWorld1);
				
				//����
				encryption(passWorld);
				
				//����˺Ÿ��������Ѿ�ע�����
				if(!strcmp(userName,userName1) && !strcmp(passWorld,passWorld1))
				{
					flag = 1;
					break;
				}
			}
			if(flag == 0)
			{
				printf("\t�����û������벻ƥ����ߴ���\n");
				enter();
			}
			printf("\t�ɹ�\n");
			break;
		}
		default:{
			printf("����ѡ�񲻷��ϸ�ʽ\n");
			break;
		}
	}
}

//�������� �������� 

//������Ϣ�ṹ�� 
typedef struct stu{ 

	int enUniversity;  //��ѧ��� 
	char major[20];		//רҵ 
	int banji;  		// �༶  	
	char id[10];   		//ѧ�� 
	char name[10];  	 //���� 
	char sex[3]; 		//�Ա� 
	int age; 			//���� 
	char number[12];   //�ֻ���
	char dorm[50]; 		//����¥��
	int dorm_num;  		//������ 
	int dorm_num_id;  	//���� 
	struct stu *next; 	//β�ڵ� 
	
}stu;

void print(stu *head);

void interface()//������ 
{
	printf("\n\n");
	printf("\t---------------------------------------------------------\n"); 
	printf("\t|\t\t��ӭʹ��������Ϣ����ϵͳ\t\t|\n");
	printf("\t---------------------------------------------------------\n");
	
	// ����¼�� 
	
	printf("\t|\t\t\t1-¼������\t\t\t|\n"); 
	
	//������ɾ�Ĳ�
	
	printf("\t|\t\t\t2-��������\t\t\t|\n");  
	printf("\t|\t\t\t3-����ɾ��\t\t\t|\n");
	printf("\t|\t\t\t4-�����޸�\t\t\t|\n");
	printf("\t|\t\t\t5-���ݲ�ѯ\t\t\t|\n");
	
	//����ͳ�� 
 
	printf("\t|\t\t\t6-����ͳ��\t\t\t|\n");
	
	//���� 
	
	printf("\t|\t\t\t7-���ݱ���\t\t\t|\n");
	printf("\t---------------------------------------------------------\n");
}

//ѧ�Ų���,�ظ�����0������1
int find_id(char id[],stu *head)
{
	stu *i;
	//������� 
	for(i = head->next;i != NULL;i = i->next)
	{
		//�ж�ѧ���Ƿ���� 
		if(strcmp(id,i->id) == 0)
		{
			printf("\tѧ���ظ�\n");
			return 0;
		}
	}
	return 1;
}

//��������Ƿ����ظ���,���Ϸ���1�������Ϸ���0 
int find_check(stu *head,stu *p) 
{
	stu *i;
	for(i = head->next;i != NULL;i = i->next)
	{
		if(! strcmp(p->dorm,i->dorm) && (p->dorm_num_id == i->dorm_num_id) && (p->dorm_num == i->dorm_num))
		{
			printf("\t������Ϣ�ظ�!!!\n");
			printf("\t����������:\n");
			
			return 0;
		}
	}
	return 1;
}


//��������
stu *creat() 
{
	int i = 1;
	stu *head,*end,*p;
	char id[10];
	head = NULL;
	head = (stu*)malloc(sizeof(stu));
	head->next = NULL;
	end = head;
	printf("¼���%d��ѧ������Ϣ:",i);
	printf("\t����ѧ��:");
	
	// fflush(stdin)ˢ�±�׼���뻺�����������뻺������Ķ������� 
	//fflush(stdout)ˢ�±�ע������������������������Ķ�����ӡ����׼����豸�� 
	
	fflush(stdin);
	gets(id);
	//���get����id�Ǵ���0�� 
	while(strlen(id) > 0)
	{
		//ѧ�Ų���,�ظ�����0������1
		if(find_id(id,head)) 
		{
			p = (stu*)malloc(sizeof(stu));
			strcpy(p->id,id);
			printf("\t��������:");	
			gets(p->name);
			printf("\t���빫Ԣ����:");		
			scanf("%s",p->dorm);
			printf("\t������������:");
			scanf("%d",&p->dorm_num);
			printf("\t���봲λ��:");
			scanf("%d",&p->dorm_num_id);
			
			/*
				int enUniversity;  //��ѧ����	
				char major[20];	//רҵ 
				int banji;  // �༶  	
				char id[10];   //ѧ�� 
				char name[10];   //���� 
				char sex[3]; 	//�Ա� 
				int age;        //���� 
				char number[12];   //�ֻ��� 
				char dorm[50]; //����¥��
				int dorm_num;  //������ 
				int dorm_num_id;  //���� 
				struct stu *next; //β�ڵ� 
			*/
			
			//��������Ƿ���Ա,���Ϸ���1�������Ϸ���0 
			if(find_check(head,p)) 
			{		
				printf("\t�ֻ���:");
				fflush(stdin);
				gets(p->number); 
				printf("\t����:");
				scanf("%d",&p->age); 
				printf("\t�Ա�:");
				scanf("%s",p->sex); 
				printf("\tרҵ:");
				scanf("%s",p->major);
				printf("\t�༶:");
				scanf("%d",&p->banji);
				printf("\t������ѧ���:");
				scanf("%d",&p->enUniversity);
				end->next = p;
				end = p;
				p->next = NULL;
			} 	
		}
		printf("\n\n");
		i ++; 
		printf("¼���%d��ѧ������Ϣ:\n",i);
		printf("\t����ѧ��:");
		//����fflush���ڽ�������������������ļ���ȥ
		//����ɹ�ˢ�£�fflush����0��ָ������û�л���������ֻ����ʱҲ����0ֵ
		fflush(stdin);
		gets(id);
	}
	return head;
}

//�����ӡ��� 
void print(stu *head)
{
	
	stu *i;
	for(i = head->next;i != NULL;i = i->next)
	{
		printf("\t|%-20s %-10s %-9s %-5d %-10s %-5d %-5d %-5s %-5d %-12s %-5d|\n",i->id,i->name,i->major,i->banji,i->dorm,i->dorm_num,i->dorm_num_id,i->sex,i->age,i->number,i->enUniversity);
	}
}

//�ļ��������� 
stu *write_linked()  
{
	
	FILE *fp;
	fp = fopen("student.txt","rt");
	stu *i;
	stu *head;
	head = NULL;
	head = (stu*)malloc(sizeof(stu));
	stu *end,*p;
	end = head;
	
	//feof�ü�����ϵ��ļ����������䷵��ֵ�����������
	//��������ļ�����������ֵΪ����ֵ��������ֵΪ0
	//���û�е��ļ���β 
	while(!feof(fp))
	{
		p = (stu*)malloc(sizeof(stu));
		//���¶�ȡ�����ݴ�ŵ��ڴ� ��һ��һ���Ķ�ȡ 
		fread(p,sizeof(stu),1,fp);
		fgetc(fp);
		end->next = p;
		end = p;
		p->next = NULL;
	}
	//�رն�д���� 
	fclose(fp);
	//����ͷ�ڵ� 
	return head; 
}

//�����������ļ� ���� 
void write_file(stu *head)  
{
	FILE *fp;
	
	//��student.txt,������ǰ����Ŀ�ļ������½�student.txt�ļ� 
	fp = fopen("student.txt","wt");
	stu *i;
	
	for(i = head->next;i != NULL;i = i->next)
	{
		fwrite(i,sizeof(stu),1,fp);
		if(i->next != NULL)
		fputc('\n',fp);
	}
	fclose(fp);
}

//���ݱ�ͷ
void header()
{
	printf("\t-------------------------------------------------------------------------------------------------------\n");
	
	HEAD;//"ѧ��","����","רҵ","�༶","��Ԣ��","����","��λ","�Ա�","���","�ֻ���","����"
	
	printf("\t-------------------------------------------------------------------------------------------------------\n");
}

//����int
void exchange_num(int *x,int *y) 
{
	int t = *x;
	*x = *y;
	*y = t;
}

//�����ַ��� 
void exchange_string(char a[],char b[])
{
	char t[20];
	strcpy(t,a);
	strcpy(a,b);
	strcpy(b,t);
}

//����stu�ṹ������ 
void exchange(stu *ec1,stu *ec2) 
{
	exchange_num(&ec1->age,&ec2->age);
	exchange_num(&ec1->banji,&ec2->banji);
	exchange_string(ec1->dorm,ec2->dorm);
	exchange_num(&ec1->dorm_num,&ec2->dorm_num);
	exchange_num(&ec1->dorm_num_id,&ec2->dorm_num_id);
	exchange_string(ec1->id,ec2->id);
	exchange_num(&ec1->enUniversity,&ec2->enUniversity);
	exchange_string(ec1->major,ec2->major);
	exchange_string(ec1->name,ec2->name);
	exchange_string(ec1->number,ec2->number);
	exchange_string(ec1->sex,ec2->sex);
}

//���ݹ�Ԣ ���� ��λ ���� 
void sort(stu *head) 
{
	//���ݹ�Ԣ ����
	stu *i,*j;
	for(i = head->next;i != NULL;i = i->next)
	{
		for(j = i->next;j != NULL;j = j->next)
		{
			// i->dorm > j->dorm
			if(strcmp(i->dorm,j->dorm) > 0)
			{
				exchange(i,j);
			}
		}
	}
	
	//�������� ����
	for(i = head->next;i != NULL;i = i->next)
	{
		for(j = i->next;j != NULL;j = j->next)
		{
			//������¥��ȵ�����£��ȼ�����ı�� 
			if(!strcmp(i->dorm,j->dorm) && i->dorm_num > j->dorm_num)
			{
				exchange(i,j);
			}
		}
	}
	
	//���ݴ�λ ����
	for(i = head->next;i != NULL;i = i->next)
	{
		for(j = i->next;j != NULL;j = j->next)
		{
			//������¥�Ÿ��������ȵ�����£��ڱȽ��������洲�ŵ�˳�� 
			if(strcmp(i->dorm,j->dorm) == 0 && i->dorm_num == j->dorm_num && i->dorm_num_id > j->dorm_num_id)
			{
				exchange(i,j);
			}
		}
	}
	
}

//������� 
void add(stu *head)
{
	stu *end;
	for(end = head->next;end->next != NULL;end = end->next)
	{
		
	}
	int i = 0;
	stu *p;
	char id[20];
	printf("\t����ѧ��:");
	//fflush(stdin)ˢ�±�׼���뻺�����������뻺������Ķ�������
	fflush(stdin);
	gets(id);
	while(strlen(id) > 0)
	{
		
		if(find_id(id,head))//ѧ�Ų���,�ظ�����0������1 
		{
			p=(stu*)malloc(sizeof(stu));
			p->next = NULL;
			strcpy(p->id,id);
			printf("\t��������:");	
			gets(p->name);
			printf("\t���빫Ԣ����:");			
			scanf("%s",p->dorm);
			printf("\t������������:");
			scanf("%d",&p->dorm_num);
			printf("\t���봲λ��:");
			scanf("%d",&p->dorm_num_id);
			
			//��������Ƿ���Ա,���Ϸ���1�������Ϸ���0
			if(find_check(head,p))   
			{		
				printf("\t�ֻ���:");
				fflush(stdin);
				gets(p->number); 
				printf("\t����:");
				scanf("%d",&p->age); 
				printf("\t�Ա�:");
				scanf("%s",p->sex); 
				printf("\tרҵ:");
				scanf("%s",p->major);
				printf("\t�༶:");
				scanf("%d",&p->banji);
				printf("\t������ѧ���:");
				scanf("%d",&p->enUniversity);	
				end->next = p;
				end = p;	
			} 	
		}
		printf("\n\n");
		printf("\t����ѧ��:");
	
		//fflush(stdin)ˢ�±�׼���뻺�����������뻺������Ķ�������
		fflush(stdin);
		gets(id);
	}
	printf("\t����\n");
}

//��ѧ��ɾ������
void dele(stu *head) 
{
	printf("\t������Ҫɾ����ѧ��:");
	char id[20];
	fflush(stdin);
	gets(id);
	//�����ڶ��� 	
	stu *end1;
	stu *i;
	while(strlen(id) > 0)
	{
		//�ҵ�����һ���ڵ� 
		for(end1 = head->next;end1->next->next != NULL;end1 = end1->next)
		{
			
		}
		i = head;
		while((i=i->next) != NULL)
		{
			if(strcmp(id,i->id) == 0)
			{
				exchange(i,end1->next);
				free(end1->next);
				end1->next = NULL;
				sort(head);
				printf("\t�ɹ�\n");
				break;
			}
			else if(i->next == NULL)
			{
				printf("\t->δ�ҵ���ƥ���ѧ��<-\n");
			}
		}
		printf("\t������Ҫɾ����ѧ��:");
		gets(id);
	}	
}

//��ѧ���޸�����
void modify(stu *head) 
{
	char flag[5];
	printf("\t������Ҫ�޸ĵ�ѧ��:");
	char id[20];
	char new_id[20];
	fflush(stdin);
	gets(id);
	stu *i;
	stu *k;
	k = (stu*)malloc(sizeof(stu));
	k->next = NULL;
	while(strlen(id) > 0)
	{	
		i = head;
		while((i = i->next) != NULL)
		{
			if(strcmp(id,i->id) == 0)
			{
				printf("\t�Ƿ��޸�ѧ��(yes/no?):") ;
				gets(flag);
				if(strcmp(flag,"yes") == 0)
				{
					printf("\t�����޸ĵ�ѧ��:");
					gets(new_id);
					//�ж��µ�ѧ�Ÿ�֮ǰ��ѧ���Ƿ���ͬ 
					if(find_id(new_id,head) || strcmp(id,new_id) == 0)
					{
						//�����µ�new_id 
						strcpy(k->id,new_id);
					}
					else
					{
						printf("\t��ѧ���ظ�");
						break;
					}
				}
				else
				{
					strcpy(k->id,i->id);
				} 
				printf("\t��������:");	
				gets(k->name);
				printf("\t���빫Ԣ����:");	
				scanf("%s",k->dorm);
				printf("\t������������:");
				scanf("%d",&k->dorm_num);
				printf("\t���봲λ��:");
				scanf("%d",&k->dorm_num_id);
				//��������Ƿ���Ա,���Ϸ���1�������Ϸ���0 
				//���ж� 
				if(find_check(head,k) || (!strcmp(k->dorm,i->dorm) && 
					i->dorm_num == k->dorm_num && 
					i->dorm_num_id == k->dorm_num_id))  
				{		
					printf("\t�ֻ���:");
					fflush(stdin);
					gets(k->number); 
					printf("\t����:");
					scanf("%d",&k->age); 
					printf("\t�Ա�:");
					scanf("%s",k->sex); 
					printf("\tרҵ�༶:");
					scanf("%s",k->major);
					printf("\t�༶:");
					scanf("%d",&k->banji);
					printf("\t������ѧ���:");
					scanf("%d",&k->enUniversity);
					//��֮ǰ����Ĳ��ҵ���������k�ڵ�������滻 
					exchange(i,k);
				} 				
			}
			else if(i->next ==  NULL)
			{
				printf("\t->δ�ҵ���ƥ���ѧ��<-\n");
			}
		}
		printf("\t������Ҫ�޸ĵ�ѧ��:");
		fflush(stdin);
		gets(id);
	}	
	free(k);
}

//���ݲ�ѯ�ӽ��� 
void interface1()
{
	printf("\t\t------------------\n");
	printf("\t\t|1.��ѧ�Ų�ѯ    |\n");
	printf("\t\t|2.��������ѯ    |\n");
	printf("\t\t|3.����Ԣ�����ѯ|\n");
	printf("\t\t------------------\n");
}

//��ѧ�Ų��� 
void lookup_id(stu *head)
{
	char id[20];
	printf("\t����ѧ��:");
	fflush(stdin);
	gets(id);
	stu *i;
	while(strlen(id) > 0)
	{	
		i = head;
		while((i = i->next) != NULL)
		{
			if(strcmp(id,i->id) == 0)
			{
				header();
				printf("\t|%-10s%-8s%-9s%-5d%-10s%-5d%-5d%-5s%-5d%-12s%-5d|\n",i->id,i->name,i->major,i->banji,i->dorm,i->dorm_num,i->dorm_num_id,i->sex,i->age,i->number,i->enUniversity);
				printf("\t---------------------------------------------------------------------------------\n");
				break;
			}
			else if(i->next == NULL)
			{
				printf("\tδ�ҵ���Ӧѧ��\n");
			}
		}
		printf("\t����ѧ��:");
		fflush(stdin);
		gets(id);
	}
}

//���������� 
void lookup_name(stu *head)
{
	char name[20];
	printf("\t��������:");
	fflush(stdin);
	gets(name);
	stu *i;
	int flag;//�ж��Ƿ��ҵ����ݣ�1�ҵ���0ö�ҵ� 
	int flag1;//�ж��Ƿ������ͷ ��1�����0�����
	flag1 = 1; 
	while(strlen(name) > 0)
	{	
		flag = 0;
		i = head;
		while((i = i->next) != NULL)
		{
			if(strcmp(name,i->name) == 0)
			{
				if(flag1 == 1)
				{
					header();
					flag1 = 0;
				}				
				printf("\t|%-10s%-8s%-9s%-5d%-10s%-5d%-5d%-5s%-5d%-12s%-5d|\n",i->id,i->name,i->major,i->banji,i->dorm,i->dorm_num,i->dorm_num_id,i->sex,i->age,i->number,i->enUniversity);
				flag = 1;
			}
			else if(i->next == NULL && flag == 0)
			{
				printf("\tδ�ҵ���Ӧ����\n");
			}
		}
		printf("\t---------------------------------------------------------------------------------\n");
		printf("\n");
		printf("\t��������:");
		fflush(stdin);
		gets(name);
	}
}

//����Ԣ������� 
void lookup_dorm_num(stu *head)
{
	int  num = 0;
	char dorm[20];
	printf("\t���빫Ԣ�������:");
	scanf("%s %d",dorm,&num);
	stu *i;
	int flag;//�ж��Ƿ��ҵ����ݣ�1�ҵ���0ö�ҵ� 
	int flag1;//�ж��Ƿ������ͷ ��1�����0�����
	flag1 = 1; 
	while(strlen(dorm) > 0 && num != 0)
	{	flag = 0;
		i = head;
		while((i = i->next) != NULL)
		{
			if(num == i->dorm_num && strcmp(dorm,i->dorm) == 0)
			{
				if(flag1 == 1)
				{
					header();
					flag1 = 0;
				}				
				printf("\t|%-10s%-8s%-9s%-5d%-10s%-5d%-5d%-5s%-5d%-12s%-5d|\n",i->id,i->name,i->major,i->banji,i->dorm,i->dorm_num,i->dorm_num_id,i->sex,i->age,i->number,i->enUniversity);
				flag = 1;
			}
			else if(i->next == NULL&&flag == 0)
			{
				printf("\tδ�ҵ���Ӧ�����\n");
			}
		}
		printf("\t---------------------------------------------------------------------------------\n");
		printf("\n");
		num = 0;
		printf("\t���빫Ԣ�������:");
		scanf("%s %d",dorm,&num);
	}
}

//�������ѯ���� 
void son_operation(stu *head)
{
	
	printf("\t����ѡ��(0�˳�):");
	int choice;
	scanf("%d",&choice);
	//����0��ֱ���˳� 
	if(choice == 0)
	{
		return;
	}
	switch(choice)
	{
		case 1:{
			//��id��ѯ 
			lookup_id(head);
			break;
		}
		case 2:{
			//��������ѯ 
			lookup_name(head);
			break;
		}
		case 3:{
			//����Ԣ�����ѯ 
			lookup_dorm_num(head);
			break;
		}
		default :{
			printf("\t->�����ʽ����<-\n");
			break;
		} 
	}
}

//ͳ�Ʋ�������Ŀ¼ 
void son_statistical()
{
	printf("\t\t----------------\n");
	printf("\t\t|1.ͳ��������  |\n");
	printf("\t\t|2.ͳ�Ƶ�����Ԣ|\n");
	printf("\t\t|3.ͳ�ƹ�Ԣ����|\n");
	printf("\t\t----------------\n");
}

//ͳ��������
void  statistical_total(stu *head)
{
	stu *i;
	int n = 0;
	for(i = head->next;i != NULL;i = i->next)
	{
		n ++;
	}
	printf("\t->��%d��<-\n",n); 
}

//ͳ�Ƶ�����Ԣ
void statistical_dorm(stu *head)
{
	int n=0;
	char dorm[20];
	printf("\t���빫Ԣ:");
	fflush(stdin);
	gets(dorm);
	stu *i;
	while(strlen(dorm) > 0)
	{	
		i=head;
		n=0;
		while((i = i->next) != NULL)
		{
			if(strcmp(dorm,i->dorm) == 0)
				n++;	
		}
		printf("\t->�ù�Ԣ��%d��<-\n",n);
		printf("\t���빫Ԣ:");
		fflush(stdin);
		gets(dorm);
	}
}

//ͳ�ƹ�Ԣ����
void statistical_dorm_num(stu *head)
{
	int  num=0;
	int n;
	char dorm[20];
	printf("\t���빫Ԣ�������:");
	scanf("%s %d",dorm,&num);
	stu *i;
	while(strlen(dorm) > 0 && num != 0)
	{	
		n = 0;
		i = head;
		while((i = i->next) != NULL)
		{
			if(num == i->dorm_num && strcmp(dorm,i->dorm) == 0)			
				n++;
			
		}		
		printf("\t->�����Ṳ%d��<-\n",n);
		num = 0;
		printf("\t���빫Ԣ�������:");
		scanf("%s %d",dorm,&num);
	}
}


//�����ַ�ʽͳ������ 
void statistical_operation(stu *head) 
{
	printf("\t����ѡ��(0�˳�):");
	int choice;
	scanf("%d",&choice);
	if(choice == 0)
	{
		return;
	}
	switch(choice)
	{
		case 1:{
			statistical_total(head);//ͳ�������� 
			break;
		}
		case 2:{
			statistical_dorm(head);//ͳ�Ƶ�����Ԣ
			break;
		}
		case 3:{
			statistical_dorm_num(head);//ͳ�ƹ�Ԣ����
			break;
		}
		default :{
			printf("\t->�����ʽ����<-\n");
			break;
		} 
	}
} 

//������ 
int main() 
{	
	//��¼ 
	enter();
	system("cls");
	printf("\t��½�ɹ�\n");
	int choice;
	while(1)
	{
		//���� 
		interface();
		stu *head;
		printf("\t����1~7��");
		scanf("%d",&choice);
		switch(choice)
		{
			//¼��ѧ����Ϣ 
			case 1:{
				head = creat();//��������
				write_file(head);//д���ļ� 
				break;
			}
			
			//����ѧ����Ϣ 
			case 2:{
				head = write_linked();
				//�����Ϣ 
				add(head);
				//�����ݽ������� 
				sort(head);
				//���޸ĺõ�����д���ļ� 
				write_file(head);
				break;
			}
			
			//��ѧ����ѧ�Ž���ɾ�� 
			case 3:{ 
				//�����ļ���ȡѧ����Ϣ 
				head = write_linked();
				//ɾ�����ҵ�ѧ�ŵ�ѧ�� 
				dele(head);
				//���޸Ĺ�������д���ļ� 
				write_file(head);
				break;
			}
			
			//��ѧ����ѧ�Ž����޸� 
			case 4:{
				head = write_linked();
				//��ѧ���޸����� 
				modify(head);
				//�޸ĺ������д���ļ� 
				write_file(head);
				break;
			}
			
			//��ѧ�������������ᣬѧ�Ų��� 
			case 5:{
				interface1();//��Ŀ¼ 
				 //��������
				head = write_linked();
				//�������ѯ�����ķ��� 
				son_operation(head);
				break;
			}
			
			//ͳ�ƣ���������ÿ������������һ��¥������
			case 6:{  
			   //�ļ��������� �����ļ���ȡ��ѧ������ 
				head = write_linked();
				son_statistical();
				//ͳ�������ķ��� 
				statistical_operation(head); 
				break;
			}
			
			//���� 
			case 7:{
				//�ļ��������� �����ļ���ȡ��ѧ������ 
				head = write_linked();
				//��ӡ�����ݱ�ͷ 
				header(); 
				//���� 
				sort(head);
				//�����ӡ��� 
				print(head);
				printf("\t-------------------------------------------------------------------------------------------------------\n");
				break;
			}
			default :{
				printf("\t->��������,��������<-\n");
				break;
			}
		}
		printf("\t�����������");
		//ˢ�±�׼���뻺�����������뻺������Ķ�������
		fflush(stdin);
		getchar();
		//ÿ����������������ʾ����Ϣ
		system("cls");
	}
}
