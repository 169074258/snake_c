#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<time.h>
#include<Windows.h>
#include<stdbool.h>

enum 
{
	east = 2, west = -2, north = -1, south = 1
};   //������

int direction = west;  //���ó�ʼ����

int speed = 300;       //���ó�ʼ�ٶ�

int score = 0;         //����

int foodX, foodY;      //ʳ������

struct snake
{
	int X;
	int Y;
	struct snake *next;
};   //�߽ṹ��

struct snake *node(void);                          //�����߽ڵ� 
void Welcome(void);                                //��ӭ���� 
void DrawBackground(void);                         //�������� 
struct snake *CreatSnake(void);                    //������ʼ��С�� 
void DrawSnake(struct snake *list);                //���� 
void RandomFood(struct snake* list);               //���ʳ�� 
struct snake *SnakeMove(struct snake *list);       //���ƶ� 
void TestKey(void);                                //������뷽�򰴼� 
struct snake *SnakeGrow(struct snake *list);       //������ 
struct snake *EatFood(struct snake *list);         //�ж��Ƿ�Ե�ʳ�� 
bool SnakeDie(struct snake *list);                 //�ж������� 

int main(void)
{
	Welcome();
	srand((unsigned)time(NULL));  	//�߽ṹ��ָ��
	struct snake *head;             
	head = CreatSnake();            //��ʼ���ߺͷ���
	direction = west;              
	DrawBackground();	            //������
	RandomFood(head);            	//���ʳ��
	while (true) 
	{
		TestKey();                  //��ⰴ��
		head = SnakeMove(head);    	//���ƶ�
		DrawSnake(head); 	    	//����
		head = EatFood(head);		//�ж�ʳ����û�б���
		if(SnakeDie(head))
		break;
		Sleep(speed);            	//��Ϸ�ٶ�
	}
    printf("\n                   ����:%d\n\n\n", score);

	return 0;
} 

struct snake *node(void)
{
	struct snake *n = (struct snake *) malloc(sizeof(struct snake));
	n->next = NULL;
	return n;
}    //�����߽ڵ�

void Welcome(void)
{
	printf("\n\n\n");
	printf("\t\t                      ̰����");
	printf("\n\n");
	printf("\t\t              �� W A S D �����ߵķ���");
	printf("\n\n");
	printf("\t\t                 ���ո����ʼ��Ϸ");
	printf("\n\n");
	printf("\t\t    ��y���������ٶ�,���ڵ��ٶ���%d,1000����1��.\n\n\t\t\t\t  ", speed);
	int ch;
	while (true)
	{
		ch = _getch();
		if (' ' == ch)
		{
			system("cls");
			break;
		}
		else if ('y' == ch)
		{
			printf("	\n\t\t\t      ����������س���  ");
			scanf("%d", &speed);
			system("cls");
			break;
		}
	}
}

void DrawBackground(void)
{
    printf("\n\n\n\n      ����������������������������������������������\n"
		   "      ��                                          ��\n"
		   "      ��                                          ��\n"
		   "      ��                                          ��\n"
		   "      ��                                          ��\n"
		   "      ��                                          ��\n"
		   "      ��                                          ��\n"
		   "      ��                                          ��\n"
		   "      ��                                          ��\n"
		   "      ��                                          ��\n"
		   "      ��                                          ��\n"
		   "      ��                                          ��\n"
           "      ��                                          ��\n"
		   "      ��                                          ��\n"
		   "      ��                                          ��\n"
		   "      ��                                          ��\n"
		   "      ��                                          ��\n"
		   "      ����������������������������������������������");

}

struct snake *CreatSnake(void)
{
	struct snake *head = NULL;
	struct snake *tail = NULL;
	int i;
	for (i = 0; i < 3; i++)
	{
		if (0 == i)
		{
			tail = head = node();
		}
		else
		{
			tail->next = node();
			tail = tail->next;
		}
		tail->X = 8;
		tail->Y = 10 * 2 + 2 * i;
	}
	tail->next = NULL;
	return head;
}  //������ʼ��

void DrawSnake(struct snake *list)
{
	struct snake *p;
	for(p = list; p != NULL; p = p->next)
	{
		COORD pos = { p->Y, p->X };
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(handle, pos);
		printf("��");
	}
}

void RandomFood(struct snake* list)
{
	foodX = rand() % 15 + 5;
	foodY = rand() % 21 * 2 + 8;
	struct snake *p;
	for (p = list; p != NULL; p = p->next)
	{
		if (p->X == foodX && p->Y == foodY)
		{
			RandomFood(list);
			return;
		}
	}
	COORD pos = { foodY, foodX };
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle, pos);
	printf("��");
}  //����ʳ��λ�� 

struct snake *SnakeMove(struct snake *list)
{
	bool snakeHead = true;
	struct snake *p;
	int qX, qY, tempX, tempY;
	for(p = list; p != NULL; p = p->next)
	{
		if(snakeHead)
		{
			snakeHead = false;
			qX = p->X;
			qY = p->Y;
			if(direction == west || direction == east)
			{
				p->Y += direction;
			}
			else
			{
				p->X += direction;
			}
		}
		else
		{
			tempX = qX;
			qX = p->X;
			p->X = tempX;
			
			tempY = qY;
			qY = p->Y;
			p->Y = tempY;
		}
	}
	COORD pos = { qY, qX };
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle, pos);
	printf("  ");
	COORD pos2 = { 0, 0 };
	SetConsoleCursorPosition(handle, pos2);
	return list; 
}  //���ƶ� 

void TestKey(void)
{
	if (GetAsyncKeyState('W') && direction != south)
			direction = north;
	else if (GetAsyncKeyState('A') && direction != east)
			direction = west;
	else if (GetAsyncKeyState('S') && direction != north)
     		direction = south;
	else if (GetAsyncKeyState('D') && direction != west)
			direction = east;
}  //������뷽�� 

struct snake *SnakeGrow(struct snake *list)
{
	struct snake *p, *q;
	int tempX, tempY;
	for(p = list; p != NULL; p = p->next)
	{
		tempX = p->X;
		tempY = p->Y;
		q = p;
	}
	q->next = node();
	return list;
}  //������

struct snake *EatFood(struct snake *list)
{
	if(list->X == foodX && list->Y == foodY)
	{
		RandomFood(list);
		list = SnakeGrow(list);
		score++;
	}
	return list;
}

bool SnakeDie(struct snake *list)
{
	//ײǽ
	if (list->X == 4 || list->X == 21 || list->Y == 6 || list->Y == 50)
	{
		system("cls");
		puts("\n\n                 ��ײǽ����!");
		return true;
	}
	//ҧ���Լ�
	else
	{
     	struct snake *p;
		for (p = list->next; p != NULL; p = p->next)
		{
			if (list->X == p->X && list->Y == p->Y)
			{
				system("cls");
     			puts("\n\n                 ��ҧ���Լ�!");
				return true;
			}
		}
	}
	return false;
}  //�ж�������
