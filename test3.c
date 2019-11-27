#include <cstdio>
#include <cstdlib>
#include <malloc.h>
typedef int ElemType;

struct SNode
{
	ElemType data;
	SNode* next;
};

SNode* Create()
{
	SNode* l;
	l = (SNode*)malloc(sizeof(SNode));
	if (l)
	{
		l->data = 0;
		l->next = l;
		return l;
	}
}

ElemType GetElem_SN(SNode* l, int i)
{
	for (int j = 0; j < i; j++)
	{
		l = l->next;
	}
	return l->data;
}

int LocateElem_SN(SNode* l, ElemType e)
{
	int i = 0;
	while (e != l->data)
	{
		++i;
		l = l->next;
	}
	return i;
}

void InsertElem_SN(SNode* l, int i, ElemType e)
{
	SNode* lh=l;
	for (int j = 0; j < i; j++)
	{
		l = l->next;
	}
	SNode* p;
	p = (SNode*)malloc(sizeof(SNode));
	if (p)
	{
		if (l->next == lh)
		{
			l->next = p;
			p->data = e;
			p->next = lh;
		}
		else
		{
			p->next = l->next;
			p->data = e;
			l->next = p;
		}
	}
}

void DeleteElem_SN(SNode* l, int i)
{
	SNode* lh = l;
	for (int j = 0; j < i - 1; j++)
	{
		l = l->next;
	}
	SNode* p;
	p = (SNode*)malloc(sizeof(SNode));
	if (p)
	{
		if (l->next->next == lh)
		{
			l->next = lh;
		}
		else
		{
			p->next = l->next->next;
			l->next = p->next;
		}
	}
}

void display(SNode* l)
{
	SNode* lh = l;
	l = l->next;
	for (int i = 0; l != lh; i++)
	{
		printf("%d", l->data);
		l = l->next;
	}
}
int a[10] = { 1,2,3,4,5,6,7,8,9,10 };

int main()
{
	SNode* S1;
	S1 = Create();
	for (int i = 0; i < 10; i++)
	{
		InsertElem_SN(S1, i, a[i]);
	}
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			S1 = S1->next;
			DeleteElem_SN(S1, 0);
		}
	}
	display(S1);
}