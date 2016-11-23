#pragma once
#include<iostream>
using namespace std;
#include<vector>
#include<queue>

int roundTime = 1;//定义时间片为1
//进程信息节点
typedef struct NodeInfo
{
	char m_name;//进程名称
	int m_arriveTime;//进程的到达时间
	int m_totalTime;//进程执行完成需要的总时间
	int m_doneTime;//进程已经执行的时间
	int m_restTime;//进程还需要的执行的时间
	friend istream& operator>>(istream& is,NodeInfo& x)//进程信息的输入
	{
		is>>x.m_name>>x.m_arriveTime>>x.m_totalTime>>x.m_doneTime>>x.m_restTime;
		return is;
	}
	friend ostream& operator<<(ostream& os,NodeInfo& x)//进程信息的输出
	{
		cout<<x.m_name<<"	   " <<x.m_arriveTime<<"	     "<<x.m_totalTime<<"      "<<
				x.m_doneTime<<"	   "<<x.m_restTime<<endl;
		return os;
	}
} NodeInfo;
class Scheduling
{
public:
	Scheduling()
	{}
	//新的进程进入就绪队列
	void PushNewProcess(const NodeInfo& x)
	{
		_ready.push(x);
	}
	//按照时间片轮转进行执行
	void ServerProcess()
	{
		if(_ready.empty())
			return;
		NodeInfo top = _ready.front();//找到队首进程
		while(!_ready.empty())
		{
			top = _ready.front();//找到队首进程
			top.m_restTime -= roundTime;
			top.m_doneTime += roundTime;
			if(top.m_restTime != 0)
			{
				_ready.pop();
				_ready.push(top);
			}
			else
			{
				_ready.pop();
				_finish.push(top);
			}
			Print();
		}
	}
	//打印出进程的相关信息
	void Print()
	{
		queue<NodeInfo> tmp;
		NodeInfo top;
		cout<<"name"<<" "<<"arriveTime"<<" "<<"totalTime"<<" "<<"doneTime"<<" "<<"restTime"<<endl;
		while(!_ready.empty())
		{
			top = _ready.front();
			cout<<top;
			tmp.push(top);
			_ready.pop();
		}
		//就绪队列中的进程信息，已经打印完成，将tmp里的信息转至就绪队列
		while(!tmp.empty())
		{
			top = tmp.front();
			_ready.push(top);
			tmp.pop();
		}

		while(!_finish.empty())
		{
			top = _finish.front();
			cout<<top;
			tmp.push(top);
			_finish.pop();
		}
		//完成队列中的进程信息，已经打印完成，将tmp里的信息转至完成队列
		while(!tmp.empty())
		{
			top = tmp.front();
			_finish.push(top);
			tmp.pop();
		}
	}
private:
	queue<NodeInfo> _ready;//就绪队列
	queue<NodeInfo> _finish;//完成进程的队列
};
void menu()
{
	cout<<"------基于时间片轮转的进程调度算法------"<<endl;
	cout<<"------0.退出系统------"<<endl;
	cout<<"------1.输入新的作业进入就绪队列--------"<<endl;
	cout<<"------2.服务作业------"<<endl;
	cout<<"请选择>:";
}
void Test()
{
	menu();
	//用作测试
	/*NodeInfo p[] = {{'A',0,4,0,4},
		{'B',1,2,1,1},
		{'C',2,5,0,5}};
	*/
	int choose = 0;
	Scheduling s;
	NodeInfo newPro;
	do
	{
		cin>>choose;
		switch(choose)
		{
			case 1:
			{
				cout<<"请输入进程的名称，到达时间，总共服务时间，已服务时间，还需服务时间"<<endl;
				cin>>newPro;
				s.PushNewProcess(newPro);
				break;
			}
			case 2:
			{
				s.ServerProcess();
				break;
			}
			case 0:
				return;
			default:
				break;
		}
		cout<<"请选择>:";
	}while(choose > 0);
}