#include<stdio.h>
#include<stdlib.h> 
#include<malloc.h>
#define MaxSize 100
#define M 8
#define N 8
typedef struct
{
	int i, j;    //�������Թ��е�����λ��(i,j)         
	int pre;    //��·������һ�����ڶ����е��±�   
} SqQueue;
SqQueue Qu[MaxSize];  //����˳���ѭ������
int front = 0, rear = 0;
int mg[M + 2][N + 2] =
{
	{1,1,1,1,1,1,1,1,1,1},
	{1,0,0,1,0,0,0,1,0,1},
	{1,0,0,1,0,0,0,1,0,1},
	{1,0,0,0,0,1,1,0,0,1},
	{1,0,1,1,1,0,0,0,0,1},
	{1,0,0,0,1,0,0,0,0,1},
	{1,0,1,0,0,0,1,0,0,1},
	{1,0,1,1,1,0,1,1,0,1},
	{1,1,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1}
};
void print(SqQueue Qu[], int front)
{
	int k = 0;
	for (int i = front; i > 0; i = Qu[i].pre)
	{
		printf("(%d,%d) ", Qu[i].i, Qu[i].j);
		k++;
		if (k % 5 == 0)   //ÿ���ÿ5�������һ��
			printf("\n");
	}
}
bool mgpath1(int xi, int yi, int xe, int ye)	//����·��Ϊ:(xi,yi)->(xe,ye)
{
	int i, j, di, i1, j1;
	rear++;
	Qu[rear].i = xi; Qu[rear].j = yi; Qu[rear].pre = 1; //(xi,yi)����
	mg[xi][yi] = -1;		        //���丳ֵ-1,�Ա���ع����ظ�����
	while (front != rear)		    //�Ӳ���ѭ��
	{
		front++;
		i = Qu[front].i; j = Qu[front].j; //����
		if (i == xe && j == ye)	    //�ҵ��˳���,���·��
		{
			print(Qu, front);	//����print�������·��
			return true;		//�ҵ�һ��·��ʱ������
		}
		for (di = 0; di < 8; di++)    //ѭ��ɨ��ÿ����λ
		{
			switch (di)
			{
			case 0:i1 = i - 1;   j1 = j; break;
			case 1:i1 = i;  j1 = j + 1; break;
			case 2:i1 = i + 1;  j1 = j; break;
			case 3:i1 = i;   j1 = j - 1; break;
			case 4:i1 = i - 1;   j1 = j-1; break;
			case 5:i1 = i-1;  j1 = j +1; break;
			case 6:i1 = i + 1;  j1 = j-1; break;
			case 7:i1 = i +1;   j1 = j + 1; break;
			}
			if (mg[i1][j1] == 0)
			{
				rear++;
				Qu[rear].i = i1; Qu[rear].j = j1;
				Qu[rear].pre = front;	//(i1��j1)�������
				mg[i1][j1] = -1;	//���丳ֵ-1
			}
		}//for
	}//while
	return false;
}//mgpath1

int main()
{
	if (!mgpath1(1, 1, M, N))
		printf("���Թ�����û�н�!");
	system("pause");
	return 1;
}