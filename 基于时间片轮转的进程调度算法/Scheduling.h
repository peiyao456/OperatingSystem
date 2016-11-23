#pragma once
#include<iostream>
using namespace std;
#include<vector>
#include<queue>

int roundTime = 1;//����ʱ��ƬΪ1
//������Ϣ�ڵ�
typedef struct NodeInfo
{
	char m_name;//��������
	int m_arriveTime;//���̵ĵ���ʱ��
	int m_totalTime;//����ִ�������Ҫ����ʱ��
	int m_doneTime;//�����Ѿ�ִ�е�ʱ��
	int m_restTime;//���̻���Ҫ��ִ�е�ʱ��
	friend istream& operator>>(istream& is,NodeInfo& x)//������Ϣ������
	{
		is>>x.m_name>>x.m_arriveTime>>x.m_totalTime>>x.m_doneTime>>x.m_restTime;
		return is;
	}
	friend ostream& operator<<(ostream& os,NodeInfo& x)//������Ϣ�����
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
	//�µĽ��̽����������
	void PushNewProcess(const NodeInfo& x)
	{
		_ready.push(x);
	}
	//����ʱ��Ƭ��ת����ִ��
	void ServerProcess()
	{
		if(_ready.empty())
			return;
		NodeInfo top = _ready.front();//�ҵ����׽���
		while(!_ready.empty())
		{
			top = _ready.front();//�ҵ����׽���
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
	//��ӡ�����̵������Ϣ
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
		//���������еĽ�����Ϣ���Ѿ���ӡ��ɣ���tmp�����Ϣת����������
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
		//��ɶ����еĽ�����Ϣ���Ѿ���ӡ��ɣ���tmp�����Ϣת����ɶ���
		while(!tmp.empty())
		{
			top = tmp.front();
			_finish.push(top);
			tmp.pop();
		}
	}
private:
	queue<NodeInfo> _ready;//��������
	queue<NodeInfo> _finish;//��ɽ��̵Ķ���
};
void menu()
{
	cout<<"------����ʱ��Ƭ��ת�Ľ��̵����㷨------"<<endl;
	cout<<"------0.�˳�ϵͳ------"<<endl;
	cout<<"------1.�����µ���ҵ�����������--------"<<endl;
	cout<<"------2.������ҵ------"<<endl;
	cout<<"��ѡ��>:";
}
void Test()
{
	menu();
	//��������
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
				cout<<"��������̵����ƣ�����ʱ�䣬�ܹ�����ʱ�䣬�ѷ���ʱ�䣬�������ʱ��"<<endl;
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
		cout<<"��ѡ��>:";
	}while(choose > 0);
}