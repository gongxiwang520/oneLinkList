/*----------------------------------------------------------------------------------------
	
	Program Explain：单链表的基本操作
    Create Date：2018.2.13 by lzn
----------------------------------------------------------------------------------------*/
 
#include <stdio.h>
#include <stdlib.h>
 
#define ERROR 1
#define OK 	  0
 
/* 单链表结点定义 */
typedef struct LNode
{
	int data;			//data中存放结点数据域（默认是int型）
	struct LNode *next; //指向后继结点的指针
}LNode;
 
//操作函数的声明
LNode *HeadCreateList(int len);							//头插法建立单链表
LNode *TailCreateList(int len);							//尾插法建立单链表
int Serch(LNode *L, int elem);							//在表中寻找元素的位置
LNode *Replace(LNode *L, int pos, int elem); 	   		//替换第pos个位置的元素成elem
LNode *Insert(LNode *L, int pos, int elem);				//在表中插入新结点
LNode *Delete(LNode *L, int pos, int *elem);			//删除表中的结点
void PrintfList(LNode *L);								//打印链表
int MenuSelect(void);									//菜单
//测试函数的声明
void Test1(LNode *L);	//测试"Serch"函数
void Test2(LNode *L);	//测试"Replace"函数
void Test3(LNode *L);	//测试"Insert"函数
void Test4(LNode *L);	//测试"Delete"函数
LNode *Test5(void);		//测试"TailCreateList"函数
LNode *Test6(void);		//测试"HeadCreateList"函数
 
/*********************************************************************************
* Function Name    ： main主函数
* Parameter		   ： NULL
* Return Value     ： 0 
* Function Explain ： 
* Create Date      ： 2018.2.13 by lzn
**********************************************************************************/
int main(void)
{
	int len = 0;
	int cmd;
	LNode *L;		
	
	/* 初始默认为尾插法建立单链表 */
	printf("Please input list length:");
	scanf("%d",&len);
	L = TailCreateList(len);
	PrintfList(L);
	while(1)
	{
		cmd = MenuSelect();
		switch(cmd)
		{
			case 1: Test1(L);		break; //测试"Serch"函数
			case 2: Test2(L);		break; //测试"Replace"函数
			case 3: Test3(L);		break; //测试"Insert"函数
			case 4: Test4(L);		break; //测试"Delete"函数
			case 5: L=Test5();		break; //测试"TailCreateList"函数
			case 6: L=Test6();		break; //测试"HeadCreateList"函数
			case 7: system("cls");	break; //清屏
			case 8: exit(0);		break; //退出
		}
	}
	return 0;
}
 
/*********************************************************************************
* Function Name    ： HeadCreateList, 头插法建立单链表（逆序）
* Parameter		   ： len：链表长度
* Return Value     ： 创建好的链表
* Function Explain ： 从一个空表开始，不断读入数据，生成新结点，将读入数据存放到新
					  结点的数据域中，然后将新结点插入到当前链表的表头结点之后。
* Create Date      ： 2018.2.13 by lzn
**********************************************************************************/
LNode *HeadCreateList(int len)
{
	LNode *L = (LNode*)malloc(sizeof(LNode)); //创建一个头结点
	LNode *temp = L;//声明一个中间变量，指向头结点，用于遍历链表（曾因没有这个中间变量而出错）
	temp->next = NULL;	//该链表此刻只带头结点
	
	for(int i=1;i<=len;i++) //循环申请len个结点来接收scanf得到的元素
	{
		LNode *p = (LNode*)malloc(sizeof(LNode)); //生成新结点
		scanf("%d",&p->data);  //用新申请的结点来接收scanf得到的元素
		/* 以下两条语句是头插法的关键步骤，与本工程"Insert"函数原理一样 */
		p->next = temp->next;  //新结点的next指针指向开始结点
		temp->next = p;		   //头结点的next指针指向新结点
	}
	
	return (LNode*)L;
}
 
/*********************************************************************************
* Function Name    ： TailCreateList, 尾插法建立单链表（顺序）
* Parameter		   ： len：链表长度
* Return Value     ： 创建好的链表
* Function Explain ： 从一个空表开始，不断读入数据，生成新结点，将读入数据存放到新
					  结点的数据域中，然后将新结点插入到当前链表的表尾结点之后。
* Create Date      ： 2018.2.13 by lzn
**********************************************************************************/
LNode *TailCreateList(int len)
{
	LNode *L = (LNode*)malloc(sizeof(LNode)); //创建一个头结点
	LNode *temp = L;//声明一个中间变量，指向头结点，用于遍历链表（曾因没有这个中间变量而出错）
	temp->next = NULL;//该链表此刻只带头结点
	
	for(int i=1;i<=len;i++) //循环申请len个结点来接收scanf得到的元素
	{
		LNode *p = (LNode*)malloc(sizeof(LNode)); //生成新结点
		scanf("%d",&p->data);  //用新申请的结点来接收scanf得到的元素
		/* 以下两条语句是尾插法的关键步骤 */
		temp->next = p;   //用来接纳新结点
		temp = p;		  //指向终端结点，以便于接纳下一个到来的结点，此语句也可以改为"L = L->next"
	}
	temp->next = NULL;	  //此刻所有元素已经全装入链表L中，L的终端结点的指针域置为NULL
	
	return (LNode*)L;
}
 
/*********************************************************************************
* Function Name    ： Serch, 查找结点
* Parameter		   ： L：链表	elem：所查找的结点的数据域
* Return Value     ： pos：搜索到的元素的位置  ERROR：elem不在顺序表L中
* Function Explain ： 
* Create Date      ： 2018.2.13 by lzn
**********************************************************************************/
int Serch(LNode *L, int elem)
{
	LNode *temp = L;
	int pos = 0;
	int i = 1;
	
	while(temp->next)
	{
		temp = temp->next;
		if(elem==temp->data)
		{
			pos = i;
			printf("The %d position in the list is %d\n",elem,pos);
			return pos;	//返回elem元素在顺序表中的位置
		}
		i++;
	}
	printf("Serch error!\n");
	
	return ERROR;	//查找失败
}
 
/*********************************************************************************
* Function Name    ： Replace, 替换第pos个位置的元素成elem
* Parameter		   ： L：链表  pos：要替换的位置  elem：要替换的元素
* Return Value     ： 替换某结点之后生成的新链表
* Function Explain ： 
* Create Date      ： 2018.2.13 by lzn
**********************************************************************************/
LNode *Replace(LNode *L, int pos, int elem)
{
	LNode *temp = L;	//引入一个中间变量，用于循环变量链表
	temp = temp->next;  //在遍历之前，temp指向开始结点
	for(int i=1;i<pos;i++)
	{
		temp = temp->next;
	}
	temp->data = elem;  //找到要替换的结点并替换其数据域的值为elem
	
	return (LNode*)L;   //注意！！不能写为 "return (LNode*)temp;"
}
 
/*********************************************************************************
* Function Name    ： Insert, 向链表中插入结点
* Parameter		   ： L：链表  pos：要插入的位置  elem：要插入的结点的数据域
* Return Value     ： 插入新结点之后生成的新链表
* Function Explain ： 
* Create Date      ： 2018.2.13 by lzn
**********************************************************************************/
LNode *Insert(LNode *L, int pos, int elem)
{
	LNode *temp = L;	//引入一个中间变量，用于循环变量链表
	int i = 0;
	/* 首先找到插入结点的上一结点，即第pos-1个结点 */
	while( (temp!=NULL)&&(i<pos-1) )
	{
		temp = temp->next;
		++i;
	}
	/* 错误处理：链表为空或插入位置不存在 */
	if( (temp==NULL)||(i>pos-1) )		
	{
		printf("%s:Insert false!\n",__FUNCTION__);
		return (LNode*)temp;
	}
	LNode *new = (LNode*)malloc(sizeof(LNode));	//创建新结点new
	new->data = elem;		//插入的新结点的数据域
	new->next = temp->next; //新结点的next指针指向插入位置后的结点
	temp->next = new;		//插入位置前的结点的next指针指向新结点
	
	return (LNode*)L;		//注意！！不能写为 "return (LNode*)temp;"
}
 
/*********************************************************************************
* Function Name    ： Delete, 删除链表中的结点
* Parameter		   ： L：链表  pos：要删除的位置  elem：被删除的结点的数据域
* Return Value     ： 删除结点之后生成的新链表
* Function Explain ： 
* Create Date      ： 2018.2.13 by lzn
**********************************************************************************/
LNode *Delete(LNode *L, int pos, int *elem)
{
	LNode *temp = L;	//引入一个中间变量，用于循环变量链表
	int i = 0;
	/* 首先找到删除结点的上一结点，即第pos-1个结点 */
	while( (temp!=NULL)&&(i<pos-1) )
	{
		temp = temp->next;
		++i;
	}
	/* 错误处理：链表为空或删除位置不存在 */
	if( (temp==NULL)||(i>pos-1) )
	{
		printf("%s:Delete false!\n",__FUNCTION__);
		return (LNode*)temp;
	}
	LNode *del = temp->next;	//定义一个del指针指向被删除结点
	*elem = del->data;			//保存被删除的结点的数据域
	temp->next = del->next;		/*删除结点的上一个结点的指针域指向删除结点的下一个结点，
								  也可写为“temp->next = temp->next->next”*/
	free(del);					//手动释放该结点，防止内存泄露
	del = NULL;					//防止出现野指针
	
	return (LNode*)L;			//注意！！不能写为 "return (LNode*)temp;"
}
 
/*********************************************************************************
* Function Name    ： PrintfList，打印链表
* Parameter		   ： L：要打印的链表
* Return Value     ： NULL
* Function Explain ： 
* Create Date      ： 2018.2.13 by lzn
**********************************************************************************/
void PrintfList(LNode *L)
{
	LNode *temp = L;
	int count = 0;		//计数器
	printf("List:\n");
	while(temp->next)
	{
		temp = temp->next;
		printf("%d\t",temp->data);
		count++;
		if(count%5==0)		//每5个元素作为一行
		{
			printf("\n");
		}
	}
	printf("\n");
}
 
/*********************************************************************************
* Function Name    ： MenuSelect,菜单
* Parameter		   ： void
* Return Value     ： cmd
* Function Explain ： 
* Create Date      ： 2018.2.13 by lzn
**********************************************************************************/
int MenuSelect(void)
{
	int cmd;
	
	printf("1.Serch test\n");
	printf("2.Replace test\n");
	printf("3.Insert test\n");
	printf("4.Delete test\n");
	printf("5.TailCreateList test\n");
	printf("6.HeadCreateList test\n");
	printf("7.Clear\n");
	printf("8.Exit\n");
	do
	{
		printf("Enter your choice: ");
		scanf("%d",&cmd);
	}while(cmd<0||cmd>8);
	
	return cmd;
}
/* ====================================以下是测试函数============================== */
/*********************************************************************************
* Function Name    ： Test1, 测试"Serch"函数
* Parameter		   ： L：链表
* Return Value     ： void
* Function Explain ： 
* Create Date      ： 2018.2.13 by lzn
**********************************************************************************/
void Test1(LNode *L)	
{
	int serchElem = 0;				//存储要搜索的元素
	
	printf("--------------------%s start!--------------------\n",__FUNCTION__);
	PrintfList(L);
	printf("Please input the element you want to serch:");
	scanf("%d",&serchElem);
	Serch(L,serchElem);
	printf("--------------------%s end!--------------------\n",__FUNCTION__);
	printf("\n");
}
 
/*********************************************************************************
* Function Name    ： Test2, 测试"Replace"函数
* Parameter		   ： L：链表
* Return Value     ： void
* Function Explain ： 
* Create Date      ： 2018.2.13 by lzn
**********************************************************************************/
void Test2(LNode *L)	
{
	int replacePos = 0, replaceElem = 0; //存储替换的位置，替换的元素
	
	printf("--------------------%s start!--------------------\n",__FUNCTION__);
	PrintfList(L);
	printf("Please input the position and the element you want replace(example:10,33):");
	scanf("%d,%d",&replacePos,&replaceElem);
	L = Replace(L,replacePos,replaceElem);
	printf("After replace by position,list is:\n");
	PrintfList(L);
	printf("--------------------%s end!--------------------\n",__FUNCTION__);
	printf("\n");
}
 
/*********************************************************************************
* Function Name    ： Test3, 测试"Insert"函数
* Parameter		   ： L：链表
* Return Value     ： void
* Function Explain ： 
* Create Date      ： 2018.2.13 by lzn
**********************************************************************************/
void Test3(LNode *L)	
{
	int insertPos = 0, insertElem = 0;	//存储插入的位置，插入的元素
	
	printf("--------------------%s start!--------------------\n",__FUNCTION__);
	PrintfList(L);
	printf("Please input the position and the element you want insert(example:10,33):");
	scanf("%d,%d",&insertPos,&insertElem);
	L = Insert(L,insertPos,insertElem);
	printf("After insert,list is:\n");
	PrintfList(L);
	printf("--------------------%s end!--------------------\n",__FUNCTION__);
	printf("\n");
}
 
/*********************************************************************************
* Function Name    ： Test4, 测试"Delete"函数
* Parameter		   ： L：链表
* Return Value     ： void
* Function Explain ： 
* Create Date      ： 2018.2.13 by lzn
**********************************************************************************/
void Test4(LNode *L)	
{
	int deletePos = 0;				//存储要删除的位置
	int elem = 0;
	
	printf("--------------------%s start!--------------------\n",__FUNCTION__);
	PrintfList(L);
	printf("Please input the position of the element you want to delete(example:10):");
	scanf("%d",&deletePos);
	L = Delete(L,deletePos,&elem);
	printf("Delete node data is:%d\n",elem);
	printf("After delete,list is:\n");
	PrintfList(L);
	printf("--------------------%s end!--------------------\n",__FUNCTION__);
	printf("\n");
}
 
/*********************************************************************************
* Function Name    ： Test5, 测试"TailCreateList"函数
* Parameter		   ： void
* Return Value     ： 初始化成功的链表
* Function Explain ： 
* Create Date      ： 2018.2.13 by lzn
**********************************************************************************/
LNode *Test5(void)	
{
	LNode *L;
	int len = 0;
	
	printf("--------------------%s start!--------------------\n",__FUNCTION__);
	printf("Please input list length:");
	scanf("%d",&len);
	L = TailCreateList(len);
	PrintfList(L);
	printf("--------------------%s end!--------------------\n",__FUNCTION__);
	printf("\n");
	
	return (LNode*)L;
}
 
/*********************************************************************************
* Function Name    ： Test6, 测试"HeadCreateList"函数
* Parameter		   ： void
* Return Value     ： 初始化成功的链表
* Function Explain ： 
* Create Date      ： 2018.2.13 by lzn
**********************************************************************************/
LNode *Test6(void)	
{
	LNode *L;
	int len = 0;
	
	printf("--------------------%s start!--------------------\n",__FUNCTION__);
	printf("Please input list length:");
	scanf("%d",&len);
	L = HeadCreateList(len);
	PrintfList(L);
	printf("--------------------%s end!--------------------\n",__FUNCTION__);
	printf("\n");
	
	return (LNode*)L;
}