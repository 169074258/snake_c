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
};   //方向常量

int direction = west;  //设置初始方向

int speed = 300;       //设置初始速度

int score = 0;         //分数

int foodX, foodY;      //食物坐标

struct snake
{
	int X;
	int Y;
	struct snake *next;
};   //蛇结构体

struct snake *node(void);                          //产生蛇节点 
void Welcome(void);                                //欢迎界面 
void DrawBackground(void);                         //画出背景 
struct snake *CreatSnake(void);                    //产生初始的小蛇 
void DrawSnake(struct snake *list);                //画蛇 
void RandomFood(struct snake* list);               //随机食物 
struct snake *SnakeMove(struct snake *list);       //蛇移动 
void TestKey(void);                                //检测输入方向按键 
struct snake *SnakeGrow(struct snake *list);       //蛇增长 
struct snake *EatFood(struct snake *list);         //判断是否吃到食物 
bool SnakeDie(struct snake *list);                 //判断蛇死亡 

int main(void)
{
	Welcome();
	srand((unsigned)time(NULL));  	//蛇结构体指针
	struct snake *head;             
	head = CreatSnake();            //初始化蛇和方向
	direction = west;              
	DrawBackground();	            //画背景
	RandomFood(head);            	//随机食物
	while (true) 
	{
		TestKey();                  //检测按键
		head = SnakeMove(head);    	//蛇移动
		DrawSnake(head); 	    	//画蛇
		head = EatFood(head);		//判断食物有没有被吃
		if(SnakeDie(head))
		break;
		Sleep(speed);            	//游戏速度
	}
    printf("\n                   分数:%d\n\n\n", score);

	return 0;
} 

struct snake *node(void)
{
	struct snake *n = (struct snake *) malloc(sizeof(struct snake));
	n->next = NULL;
	return n;
}    //增加蛇节点

void Welcome(void)
{
	printf("\n\n\n");
	printf("\t\t                      贪吃蛇");
	printf("\n\n");
	printf("\t\t              用 W A S D 控制蛇的方向");
	printf("\n\n");
	printf("\t\t                 按空格键开始游戏");
	printf("\n\n");
	printf("\t\t    按y可以设置速度,现在的速度是%d,1000等于1秒.\n\n\t\t\t\t  ", speed);
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
			printf("	\n\t\t\t      输入整数后回车：  ");
			scanf("%d", &speed);
			system("cls");
			break;
		}
	}
}

void DrawBackground(void)
{
    printf("\n\n\n\n      ■■■■■■■■■■■■■■■■■■■■■■■\n"
		   "      ■                                          ■\n"
		   "      ■                                          ■\n"
		   "      ■                                          ■\n"
		   "      ■                                          ■\n"
		   "      ■                                          ■\n"
		   "      ■                                          ■\n"
		   "      ■                                          ■\n"
		   "      ■                                          ■\n"
		   "      ■                                          ■\n"
		   "      ■                                          ■\n"
		   "      ■                                          ■\n"
           "      ■                                          ■\n"
		   "      ■                                          ■\n"
		   "      ■                                          ■\n"
		   "      ■                                          ■\n"
		   "      ■                                          ■\n"
		   "      ■■■■■■■■■■■■■■■■■■■■■■■");

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
}  //产生初始蛇

void DrawSnake(struct snake *list)
{
	struct snake *p;
	for(p = list; p != NULL; p = p->next)
	{
		COORD pos = { p->Y, p->X };
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(handle, pos);
		printf("●");
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
	printf("★");
}  //产生食物位置 

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
}  //蛇移动 

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
}  //检测输入方向 

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
}  //蛇增长

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
	//撞墙
	if (list->X == 4 || list->X == 21 || list->Y == 6 || list->Y == 50)
	{
		system("cls");
		puts("\n\n                 蛇撞墙死亡!");
		return true;
	}
	//咬到自己
	else
	{
     	struct snake *p;
		for (p = list->next; p != NULL; p = p->next)
		{
			if (list->X == p->X && list->Y == p->Y)
			{
				system("cls");
     			puts("\n\n                 蛇咬到自己!");
				return true;
			}
		}
	}
	return false;
}  //判断蛇死亡
