#include "Generate.h"
#include <QElapsedTimer>  //记录流程所需时间
#include <QDebug>
#include <QThread>

Generate::Generate(QObject *parent) : QObject(parent)
{

}

void Generate::working(int num)
{
    qDebug() << "生成随机数的线程地址:" << QThread::currentThread();//指向当前线程对象地址
    QVector<int> list;
    QElapsedTimer time; //创建time对象
    time.start(); //time对象调用start方法
    for(int i = 1; i < num; ++i)
    {
        list.push_back(qrand() % 100000);
    }
    int milsec = time.elapsed(); //执行后返回一个值并赋值
    qDebug() << "生成" << num << "个随机数总共用时：" << milsec << "毫秒";
    emit sendArray(list); // 把得到的数据发送给主线程
}

BubbleSort::BubbleSort(QObject *parent) : QObject(parent)
{

}

void BubbleSort::working(QVector<int> list)
{
    qDebug() << "冒泡排序的线程的线程地址:" << QThread::currentThread();//指向当前线程对象地址
    QElapsedTimer time; //创建time对象
    time.start(); //time对象调用start方法
    int temp;
    for(int i=0; i<list.size(); ++i)
    {
        for(int j = 0; j<list.size()-i-1; ++j)
        {
            if(list[j] > list[j+1])
            {
                temp = list[j];
                list[j] = list[j+1];
                list[j+1] = temp;
            }
        }
    }
    int milsec = time.elapsed(); //执行后返回一个值并赋值
    qDebug() << "冒泡排序用时" << milsec << "毫秒";
    emit finish(list); // 把得到的数据发送给主线程

}


QuickSort::QuickSort(QObject *parent) : QObject(parent)
{

}

void QuickSort::working(QVector<int> list)
{
    qDebug() << "快速排序的线程的线程地址:" << QThread::currentThread();//指向当前线程对象地址
    QElapsedTimer time; //创建time对象
    time.start(); //time对象调用start方法

    quickSort(list, 0, list.size()-1);

    int milsec = time.elapsed(); //执行后返回一个值并赋值
    qDebug() << "快速排序用时" << milsec << "毫秒";
    emit finish(list); // 把得到的数据发送给主线程

}

void QuickSort::quickSort(QVector<int> &s, int l, int r)
{
    if (l < r)
    {
        int i = l, j = r;
        //拿出第一个元素，保存到x中，第一个位置成为一个坑
        int x = s[l];
        while (i < j)
        {
            //从右向左找小于x的数
            while (i < j && s[j] >= x)
            {
                //左移，直到遇到小于等于x的数
                j--;
            }
            if (i < j)
            {
                //将右侧找到的小于x的元素放入左侧坑中，右侧出现一个坑
                //左侧元素索引后移
                s[i++] = s[j];
            }

            //从左向右找大于等于x的数
            while (i < j && s[i] < x)
            {
                //右移，知道遇到大于x的数
                i++;
            }
            if (i < j)
            {
                //将左侧找到的元素放入右侧坑中，左侧出现一个坑
                //右侧元素索引向前移动
                s[j--] = s[i];
            }
        }
        //此时 i=j,将保存在x中的数填入坑中
        s[i] = x;
        quickSort(s, l, i - 1);//递归调用
        quickSort(s, i + 1, r);
    }
}


