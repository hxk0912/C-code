// 实验一.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define LIST_INIT_SISE 100     // 线性表存储空间的初始分配量
#define LIST_INCREASE_SISE 20  // 线性表存储空间的分配增量

#define OK        0
#define ERROR    -1
#define OVERFLOW -2 

typedef char elementType;
typedef struct
{
	elementType* List; // 线性表首地址，用于遍历线性表
	int leng;          // 当前长度
	int listsize;      // 当前分配的存储容量	
}SqList;


int AgainMalloc(SqList* sqlist)
{
	elementType* newbase;  // 分配一个临时基址

	// 重新分配空间
	newbase = (elementType*)realloc(sqlist->List, (sqlist->listsize + LIST_INCREASE_SISE) * sizeof(elementType) / sizeof(char));
	if (newbase == NULL)
	{
		return OVERFLOW;
	}

	sqlist->List = newbase;
	sqlist->listsize += LIST_INCREASE_SISE;

	return OK;

}


// 初始化一个空的线性表
int Init_List(SqList* sqlist)
{
	// 入口参数检查
	if (sqlist == NULL)
	{
		return ERROR;
	}

	// 给线性表分配初始容量
	sqlist->List = (elementType*)malloc(LIST_INIT_SISE * sizeof(elementType) / sizeof(char));
	if (sqlist->List == NULL)
	{
		return OVERFLOW;
	}

	sqlist->leng = 0; // 初始表为空表，里面没有元素
	sqlist->listsize = LIST_INIT_SISE;  // 初始表的存储容量，为 LIST_INIT_SISE 个 elementType 单位

	return OK;
}

// 向表头插入元素
int Insert_Head(SqList* sqlist, elementType newElement)
{
	// 入口参数检查
	if (sqlist == NULL)
	{
		return ERROR;
	}

	// 检测线性表是否已满，如果已满则进行扩充，再次分配空间
	if (sqlist->leng >= sqlist->listsize)
	{
		// 分配空间时检测空间是否分配成功
		if (AgainMalloc(sqlist) != OK)
		{
			return OVERFLOW;
		}
	}

	int i;
	for (i = sqlist->leng - 1; i >= 0; i--)
	{
		sqlist->List[i + 1] = sqlist->List[i];
	}

	// 新数据插入到线性表的尾部，线性表的当前长度加1
	sqlist->List[0] = newElement;
	sqlist->leng++;

	return OK;
}

// 向表尾插入元素
int Insert_Last(SqList* sqlist, elementType newElement)
{
	// 入口参数检查
	if (sqlist == NULL)
	{
		return ERROR;
	}

	// 检测线性表是否已满，如果已满则进行扩充，再次分配空间
	if (sqlist->leng >= sqlist->listsize)
	{
		// 分配空间时检测空间是否分配成功
		if (AgainMalloc(sqlist) != OK)
		{
			return OVERFLOW;
		}
	}

	// 新数据插入到线性表的尾部，线性表的当前长度加1
	sqlist->List[sqlist->leng] = newElement;
	sqlist->leng++;

	return OK;
}

// 在表中第pos个位置之前插入新元素
int Insert_Pos(SqList* sqlist, elementType newElement, int pos)
{
	// 入口参数检查
	if (sqlist == NULL || pos <= 0 || pos > sqlist->leng + 1)
	{
		return ERROR;
	}

	// 检测线性表是否已满，如果已满则进行扩充，再次分配空间
	if (sqlist->leng >= sqlist->listsize)
	{
		// 分配空间时检测空间是否分配成功
		if (AgainMalloc(sqlist) != OK)
		{
			return OVERFLOW;
		}
	}

	// 将从pos位置开始的数据往后移一位
	int i = 0;
	for (i = sqlist->leng - 1; i >= pos - 1; i--)
	{
		sqlist->List[i + 1] = sqlist->List[i];
	}

	// 将新数据插入打pos位置
	sqlist->List[pos - 1] = newElement;
	sqlist->leng++;

	return OK;
}


// 将pos位置的数据从表里删除
int Delete_Pos(SqList* sqlist, int pos)
{
	if (sqlist == NULL || pos < 1 || pos > sqlist->leng)
	{
		return ERROR;
	}

	int i;
	for (i = pos; i < sqlist->leng; i++)
	{
		sqlist->List[i - 1] = sqlist->List[i];
	}

	sqlist->leng--;

	return OK;
}

int Search_Element(SqList* sqlist, elementType element)
{
	if (sqlist == NULL)
	{
		return ERROR;
	}

	int i = 0;
	for (i = 0; i < sqlist->leng; i++)
	{
		if (sqlist->List[i] == element)
		{
			return i + 1;
		}
	}

	return OK;
}

int Inverse_List(SqList* sqlist)
{
	if (sqlist == NULL)
	{
		return ERROR;
	}

	int i;
	int low = 0;
	int high = sqlist->leng - 1;
	int temp;
	for (i = 0; i < (sqlist->leng / 2); i++)
	{
		temp = sqlist->List[low];
		sqlist->List[low++] = sqlist->List[high];
		sqlist->List[high--] = temp;
	}

	return OK;
}


// 线性表合并
int Merge_List(SqList* list1, SqList* list2, SqList* list3)
{
	if (list1 == NULL || list2 == NULL)
	{
		return ERROR;
	}

	list3->leng = list1->leng + list2->leng;
	list3->listsize = list3->leng;
	list3->List = (elementType*)malloc(list3->listsize * sizeof(elementType) / sizeof(char));

	int i = 0;
	int j = 0;
	int k = 0;
	while ((i < list1->leng) && (j < list2->leng))
	{
		if (list1->List[i] <= list2->List[j])
		{
			list3->List[k++] = list1->List[i++];
		}
		else
		{
			list3->List[k++] = list2->List[j++];
		}
	}

	while (i < list1->leng)
	{
		list3->List[k++] = list1->List[i++];
	}

	while (j < list2->leng)
	{
		list3->List[k++] = list2->List[j++];
	}

	return OK;
}

// 线性表输出
void Display_List(SqList* sqlist)
{
	if (sqlist == NULL)
	{
		return;
	}

	int i;
	for (i = 0; i < sqlist->leng; i++)
	{
		printf("%c", sqlist->List[i]);
	}

	printf("\n");
}
char getc(int n, SqList* sqlist)
{
	if (sqlist == NULL)
	{
		return ERROR;
	}

	return sqlist->List[n-1];
}

int main()
{
	SqList list;

	// 初始化线性表
	if (Init_List(&list) != OK)
	{
		return -1;
	}

	// 向线性表中插入数据，这里插入10个数据，分别是0--9
	int i;
	for (i = 0; i < 5; i++)
	{
		// 尾插法
		if (Insert_Last(&list,'a'+ i) != OK)
		{
			return -1;
		}
	}

	// 线性表数据展示
	printf("创建好的线性表：\n");
	Display_List(&list);

	// 在表中第5个位置之前插入10
	int pos = 2;
	if (Insert_Pos(&list, 'a', pos) != OK)
	{
		return -1;
	}

	printf("插入一个数据后的线性表：\n");
	Display_List(&list);

	// 从线性表中删除第6个位置的数据
	pos = 5;
	if (Delete_Pos(&list, pos) != OK)
	{
		return -1;
	}
	printf("删除一个数据后的线性表：\n");
	Display_List(&list);

	// 线性表查找元素，返回找到的元素位置
	int search_pos = Search_Element(&list, 'a');
	if (search_pos > 0)
	{
		printf("元素 a 的位置是 %d\n", search_pos);
	}
	char read;
	read = getc(4, &list);
		printf("第4个元素是 %c\n", read);
	SqList list_2;
	// 初始化线性表
	if (Init_List(&list_2) != OK)
	{
		return -1;
	}

	for (i = 5; i < 10; i++)
	{
		// 头插法
		if (Insert_Head(&list_2, 'a'+i) != OK)
		{
			return -1;
		}
	}
	// 线性表数据展示
	printf("创建好的线性表2：\n");
	Display_List(&list_2);

	// 线性表合并
	SqList list_3;
	if (Merge_List(&list, &list_2, &list_3) != OK)
	{
		return -1;
	}
	printf("合并的线性表3：\n");
	Display_List(&list_3);

	return 0;
}




// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
