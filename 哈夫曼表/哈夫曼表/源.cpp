#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<queue>
#include<malloc.h>
#include <iostream>
#include <fstream>

using namespace std;

typedef struct node {
	char ch;                          //存储该节点表示的字符，只有叶子节点用的到
	int val;                          //记录该节点的权值
	struct node *self, *left, *right;   //三个指针，分别用于记录自己的地址，左孩子的地址和右孩子的地址
	friend bool operator <(const node &a, const node &b) //运算符重载，定义优先队列的比较结构
	{
		return a.val > b.val;           //这里是权值小的优先出队列
	}
}node;

priority_queue<node> p;                //定义优先队列
char res[30];                          //用于记录哈夫曼编码
void dfs(node *root, int level)         //打印字符和对应的哈夫曼编码
{
	if (root->left == root->right)        //叶子节点的左孩子地址一定等于右孩子地址，且一定都为NULL;叶子节点记录有字符
	{
		if (level == 0)                   //“AAAAA”这种只有一字符的情况
		{
			res[0] = '0';
			level++;
		}
		res[level] = '\0';               //字符数组以'\0'结束
		printf("%c=>%s\n", root->ch, res);
	}
	else
	{
		res[level] = '0';                //左分支为0
		dfs(root->left, level + 1);
		res[level] = '1';                //右分支为1
		dfs(root->right, level + 1);
	}
}
void huffman(int *hash)                //构建哈夫曼树
{
	node *root, fir, sec;
	for (int i = 0; i < 100; i++)              
	{
		if (!hash[i])                   //对应字母在text中未出现
			continue;
		root = (node *)malloc(sizeof(node));          //开辟节点
		root->self = root;                            //记录自己的地址，方便父节点连接自己
		root->left = root->right = NULL;                //该节点是叶子节点，左右孩子地址均为NULL
		root->ch = 32 + i;                             //记录该节点表示的字符
		root->val = hash[i];                          //记录该字符的权值
		p.push(*root);                              //将该节点压入优先队列
	}
	//下面循环模拟建树过程，每次取出两个最小的节点合并后重新压入队列
	//当队列中剩余节点数量为1时，哈夫曼树构建完成
	while (p.size() > 1)
	{
		fir = p.top(); p.pop();      //取出最小的节点
		sec = p.top(); p.pop();      //取出次小的节点
		root = (node *)malloc(sizeof(node));          //构建新节点，将其作为fir，sec的父节点
		root->self = root;                            //记录自己的地址，方便该节点的父节点连接
		root->left = fir.self;      //记录左孩子节点地址
		root->right = sec.self;     //记录右孩子节点地址
		root->val = fir.val + sec.val;//该节点权值为两孩子权值之和
		p.push(*root);            //将新节点压入队列
	}
	fir = p.top(); p.pop();          //弹出哈夫曼树的根节点
	dfs(fir.self, 0);              //输出叶子节点记录的字符和对应的哈夫曼编码
}
int main()
{
	ifstream in("C:\\Users\\user\\Desktop\\读入.txt");
	char text[100];
	char a[32];
	int hash[100];
	memset(hash, 0, sizeof(hash));  //哈希数组初始化全为0
	
	for (int i = 0; i < 50; i++)
		in>>text[i];
	
	for (int i = 0; i < 50; i++)//通过哈希求每个字符的出现次数
	{
		hash[text[i] -32]++;      //程序运行的字符
	}
	huffman(hash);
		in.close();
	cin.get();
	system("pause");
	return 0;
}

//#include <fstream>
//#include <iostream>
//using namespace std;
//int main()
//{
//	int a[10];
//	ifstream in("C:\\Users\\user\\Desktop\\读入.txt");
//	for(int i=0;i<10;i++)
//		in>>a[i];
//	for(int i=0;i<10;i++)
//		cout<<a[i]<<endl;
//	in.close();
//	cin.get();
//}