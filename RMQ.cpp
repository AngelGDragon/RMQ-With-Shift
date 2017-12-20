//
//  main.cpp
//  RMQ
//
//  Created by Dragon on 2017/11/1.
//  Copyright © 2017年 Dragon. All rights reserved.
//

#include <iostream>
#define MAXNUM 10000
const int INFINITE = INT_MAX;
using namespace std;

int min(int a,int b)        //比较a与b中的最小值
{
    return a>=b?b:a;
}

struct SegTreeNode
{
    int val;
}segTree[MAXNUM];//定义线段树

void build(int root, int arr[], int istart, int iend)       //构造线段树
{
    if(istart == iend)//叶子节点
        segTree[root].val = arr[istart];
    else
    {
        int mid = (istart + iend) / 2;  //计算中间位置
        build(root*2+1, arr, istart, mid);//递归构造左子树
        build(root*2+2, arr, mid+1, iend);//递归构造右子树
        //根据左右子树根节点的值，更新当前根节点的值
        segTree[root].val = min(segTree[root*2+1].val, segTree[root*2+2].val);
    }
}

int query(int root, int nstart, int nend, int qstart, int qend)     //区间最小值查询
{

    //查询区间和当前节点区间没有交集
    if(qstart > nend || qend < nstart)
        return INFINITE;
    //当前节点区间包含在查询区间内
    if(qstart <= nstart && qend >= nend)
        return segTree[root].val;
    //分别从左右子树查询，返回两者查询结果的较小值
    int mid = (nstart + nend) / 2;
    return min(query(root*2+1, nstart, mid, qstart, qend),
               query(root*2+2, mid + 1, nend, qstart, qend));

}


void updateOne(int root, int nstart, int nend, int index, int Newindex, int *array)
{
    if(nstart == nend)
    {
        if(index == nstart)//找到了相应的节点，更新之
            segTree[root].val = array[Newindex];
        return ;
    }
    int mid = (nstart + nend) / 2;
    if(index <= mid)//在左子树中更新
        updateOne(root*2+1, nstart, mid, index, Newindex, array);
    else updateOne(root*2+2, mid+1, nend, index, Newindex, array);//在右子树中更新
    //根据左右子树的值回溯更新当前节点的值
    segTree[root].val = min(segTree[root*2+1].val, segTree[root*2+2].val);
}

int ChangeStr(char *string, int i)
{
    char ReString[30] = {0};
    int j;
    for (j = 0; string[i] != ',' && string[i] != ')'; j++,i++) {
        ReString[j] = string[i];
    }
    return (atoi(ReString)-1);      //减1是为了和线段树中的下标对齐
}


void Shift(int *array,char *string,int i,int N)//shift语句更新线段树 i为括号或者逗号的下标
{
    int j;
    j = i+1;    //将逗号后面那个数的开头位置下标赋值给j
    do {
        i++;
    } while (string[i] != ','  && string[i] != ')'); //找到","或者")"的时候停止i自加1
    
    if (string[i] == ',') { //当找到","时
        updateOne(0, 0, N, ChangeStr(string, j), ChangeStr(string, i+1), array);  //将序号为i+1对应的数放到j对应的线段树上
        Shift(array, string, i, N);
    }
    else    //当找到")“时
    {
        updateOne(0, 0, N, ChangeStr(string, j),ChangeStr(string, 6), array);   //将第一个对应数组的数放到最后一个数对应的线段树上
    }
}

int Query(int N,char *string)//读取字符串中query操作中的两个数并执行query函数 N为数组的最后一位数的下标
{
    int min = 0;
    int j = 0;
    int i = 5;  //query(*,*) i代表左括号的下标
    j = i+1;    //j代表第一个操作数的下标
    do {
        i++;
    } while (string[i] != ',');
    
   min = query(0, 0, N, ChangeStr(string, j), ChangeStr(string, i+1));
    return (min);
}


void Input(int q,int n)
{
    int N = n-1;
    int array[n];   //存储要输入的数组
    int Num[q];     //存储某个区间内的最小值
    int i = 0;
    char ch;
    array[0] = {0};
    Num[0] = {0};
    
    
    do {
        cin>>array[i];//储存输入的数组元素
        i++;
    } while (i != n);
    
    build(0, array, 0, N);

    ch = getchar();     //吸收输入缓冲区中的回车
    
    int j = 0;
    
    for (int i = 0; i < q; i++) {
        char string[31];
        fgets(string, sizeof(string)/sizeof(string[0]), stdin);//储存输入的操作
        if (string[0] == 's'){               //如果发现输入的第一个字母为"s"
            Shift(array, string, 5, N);        //执行Shift函数
        }
        
        if (string[0] == 'q'){               //如果发现输入的第一个字母为"q"
            Num[j] = Query(N, string);   //执行Query函数并将区间的最小值存到Num数组中
            j++;
        }
        
    }

    for (int k = 0; k<j ; k++)
        cout<<Num[k]<<endl; //输出最小值

}


int main()
{
    char ch;

    int n = 0;
    int q = 0;
    cin>>n>>q;  //输入n与q的值
    ch = getchar();         //吸收输入缓冲区中的回车
    Input(q, n);
    
    return 0;
}









