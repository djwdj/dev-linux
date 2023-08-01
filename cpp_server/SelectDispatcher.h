#pragma once
#include "Channel.h"
#include "Dispatcher.h"
#include <string>
#include <sys/select.h>

using namespace std;
//Dispatcher 结构体
class SelectDispatcher : public Dispatcher  //继承父类Dispatcher
{
public:
	SelectDispatcher(struct EventLoop* evLoop);
	~SelectDispatcher();  //也虚函数，在多态时
	// override修饰前面的函数，表示此函数是从父类继承过来的函数，子类将重写父类虚函数
	// override会自动对前面的名字进行检查,
	int add() override;   //等于 =纯虚函数，就不用定义 
	//删除 将某一个节点从epoll树上删除
	int remove() override;
	//修改
	int modify() override;
	//事件检测， 用于检测待检测三者之一模型epoll_wait等的一系列事件上是否有事件被激活，读/写事件
	int dispatch(int timeout = 2) override;//单位 S 超时时长
	// 不改变的不写，直接继承父类
private:
	void setFdSet();
	void clearFdset();
private:
	fd_set m_readSet;
	fd_set m_writeSet;
	const int m_maxSize = 1024;
};