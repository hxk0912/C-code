#include<stdio.h> 
#include<stdlib.h> 
#include <iostream>
using namespace std;
#include<malloc.h>
#define OK 1
#define ERROR 0
typedef int Status;
typedef int ElemType;



typedef struct Node {
	int Num;
	struct Node* next;

}Node, * PNode, * HeadNode;


int ListInit(HeadNode* h)
{
	if (!h)
	{
		printf("初始化链表错误！\n");
		return 0;
	}
	(*h)->next = (*h);//循环单链表
	return 1;

}


int ListInsert(Node* h, int pos, int x)/*尾插法*/
{
	PNode p = h, q;
	int i = 1;
	if (pos == 1)
	{
		p->Num = x;
		p->next = p;
		return 1;
	}
	while (i < pos - 1)
	{
		p = p->next;
		i++;
	}
	q = (PNode)malloc(sizeof(Node));
	q->Num = x;
	q->next = p->next;
	p->next = q;
	return 1;
}

void ListTraverse(HeadNode h, int M)
{
	int i = 0;
	PNode p = h;
	printf("参与的猴子的编号为：\n");
	while (i < M)
	{
		printf("%d\t", p->Num);
		p = p->next;
		i++;
	}
	printf("\n");
}


int ListDelete(HeadNode h, int n, int m, int d)
{
	PNode p = h, q, z;
	for (int i = 1; i < m; i++)
	{
		p = p->next;
	}
	while (n > 1)
	{
		q = p;
		z = p;
		for (int i = 1;i < d;i++)
		{
			q = q->next;
		}
		for (int b = 1;b < d - 1;b++)
		{
			z = z->next;
		}
		p = q->next;
		z->next = p;
		printf("被淘汰的猴子序号为%d\n", q->Num);
		free(q);
		n--;
	}
	printf("大王为：%d", p->Num);
	return 1;
}

int main() {
	int i;//计数器
	int n=7;//猴子个数
	int m=2;//开始报数的猴子
	int d=4;//报多少的数就被淘汰
	printf("猴子总个数：7");
	cout << endl;
	printf("从第2个猴子开始报数");
	cout << endl;
	printf("报4的数淘汰");
	cout << endl;
	HeadNode h = ((HeadNode)malloc(sizeof(Node)));
	ListInit(&h);
	for (i = 1; i <= n; i++)
	{
		ListInsert(h, i, i);
	}
	ListTraverse(h, n);
	if (m > 1)
		ListDelete(h, n, m, d);
	else
	{
		for (i = 1; i < n; i++)
			printf("出局的猴子为：%d\n", i);
		printf("淘汰的猴子为：%d", n);
	}
	printf("\n");
	printf("\n");
	return 0;
}