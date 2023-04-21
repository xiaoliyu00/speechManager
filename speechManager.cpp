#include "speechManager.h"
#include "Speaker.h"

speechManager::speechManager()
{
	//初始化
	this->initSpeechManager();
	
	//创建选手
	this->createSpeaker();

	//加载
	this->loadRecord();
}

void speechManager::Show_Menu()
{
	cout<<"*******************************"<<endl;
	cout<<"****** 欢迎参加演讲比赛 ******"<<endl;
	cout<<"****** 1.开始演讲比赛 ******"<<endl;
	cout<<"****** 2.查看往届比赛记录 ******"<<endl;
	cout<<"****** 3.清空比赛记录 ******"<<endl;
	cout<<"****** 0.退出比赛程序 ******"<<endl;
	cout<<"*******************************"<<endl;
	cout<<endl;
}

//选项
void speechManager::Choice_Putton()
{
	int choice = 0;//存储用户选项
	//speechManager sm;

	while(true)
	{
		this->Show_Menu();
		cout<<"请输入您的选择！！！"<<endl;
		cin >> choice;//接受选项
		//m_choice = choice;
		switch(choice)
		{
		case 0:
			this->Exit_System();
			break;
		case 1://开始
			this->startSpeech();
			break;
		case 2:
			this->showRecord();
			break;
		case 3:
			this->clearRecord();
			break;
		default:
			system("cls");
			break;
		}
	}
}

void speechManager::Exit_System()
{
	cout<<"欢迎下次使用！！！"<<endl;
	system("pause");
	exit(0);
}

void speechManager::initSpeechManager()
{
	//容器置空
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();

	//初始化比赛轮数
	this->m_Index = 1;

	//清空容器
	this->m_Record.clear();
}

void speechManager::createSpeaker()
{
	string nameSeed = "ABCDEFGHJKLM";
	 for (int i = 0;i < nameSeed.size();i ++)
	 {
		   //名字
			string name = "player";
			name += nameSeed[i];

			Speaker sp;
			sp.m_Name = name;
			//成绩
			for (int j = 0;j < 2;j++)
			{
				sp.m_Score[j] = 0;
			}
			//选手编号
			this->v1.push_back(i+10001);

			//选手编号以及对应的选手信息存放到map容器中
			this->m_Speaker.insert(make_pair(i+10001,sp));
	 }
}

void speechManager::startSpeech()
{
	///////第一轮开始比赛

	//1.抽签
	this->speechDraw();

	//2.比赛
	this->speechContest();

	//3.显示晋级结果
	this->showScore();
	
	///////第二轮开始比赛

	this->m_Index++;
	//1.抽签
	this->speechDraw();

	//2.比赛
	this->speechContest();

	//3.显示晋级结果
	this->showScore();

	//4.保存分数到文件中
	this->saveRecord();

	cout<<"本届比赛完毕"<<endl;

	//重置比赛记录
	//初始化
	this->initSpeechManager();

	//创建选手
	this->createSpeaker();

	//加载
	this->loadRecord();

	system("pause");
	system("cls");
}

void speechManager::speechDraw()
{
	cout<<"第<<"<<this->m_Index<<">> 轮比赛选手正在抽签"<<endl;
	cout<<"------------------------"<<endl;
	cout<<"抽签后演讲顺序如下"<<endl;

	if(this->m_Index == 1)
	{
		//第一轮比赛
		random_shuffle(v1.begin(),v1.end());
		for(vector<int>::iterator it = v1.begin();it != v1.end(); it++)
		{
			cout<<*it<<" "<<endl;
		}
	}
	else
	{
		//第二轮比赛
		random_shuffle(v2.begin(),v2.end());
		for(vector<int>::iterator it = v2.begin();it != v2.end(); it++)
		{
			cout<<*it<<" "<<endl;
		}
		cout<<endl;
	}
	cout<<"-----------------------"<<endl;
	system("pause");
	cout<<endl;
}

void speechManager::speechContest()
{
	cout<<"<<"<<this->m_Index<<">>轮正式比赛开始：-----------"<<endl;

	multimap<double,int,greater<double>>groupScore; //临时容器，保存key分数 value 选手编号

	int num = 0; //记录人员数，6个人为1组

	vector<int>v_Src; // 比赛的人员容器
	if(this->m_Index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}

	//遍历所有参赛选手
	for(vector<int>::iterator it = v_Src.begin(); it != v_Src.end();it++)
	{
		num++;
		//cout<<"num:"<<num<<endl;
		//评委打分
		deque<double>d;
		for(int i = 0;i < 10; i++)
		{
			double score = (rand() % 401 +600) / 10.f;//600-1000
			d.push_back(score);
		}
	
		sort(d.begin(),d.end(),greater<double>()); //排序
		d.pop_front(); //去掉最高分
		d.pop_back(); //去掉最低分

		double sum = accumulate(d.begin(),d.end(),0.0f);//获取总分
		double avg = sum/(double)d.size();//获取平均分

		//打印平均分
		//cout<<"编号："<<*it<<"姓名："<<this->m_Speaker[*it].m_Name<<" 获取平均分"<<avg<<endl;

		//将平均分放入到map容器中
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;

		//将打分数据 放入到临时小组容器中
		groupScore.insert(make_pair(avg,*it));
		//每6人取出前三名
		if(num % 6 == 0)
		{
			cout<<"第"<<num / 6 <<"小组比赛名次"<<endl;
			for (multimap<double,int,greater<double>>::iterator it = groupScore.begin();it != groupScore.end();it++)
			{
				cout<<"选手编号："<<it->second<<" 姓名："<<this->m_Speaker[it->second].m_Name<<" 成绩："<<this->m_Speaker[it->second].m_Score[this->m_Index - 1]<<endl;
			}
			
			//取走前三名
			int  count = 0;
			for (multimap<double,int,greater<double>>::iterator it = groupScore.begin();it != groupScore.end() && count < 3;it++,count ++)
			{

				if(this->m_Index == 1)
				{
					v2.push_back((*it).second);
				}
				else
				{
					vVictory.push_back((*it).second);
				}
			}
			groupScore.clear();//小组容器清空
		}
	}
	cout<<"-------------第"<<this->m_Index<<"轮比赛完毕------------"<<endl;
	system("pause");
}

//展示分数
void speechManager::showScore()
{
		cout<<"------------第"<<this->m_Index<<"轮晋级选手信息如下：------------"<<endl;
 
		vector<int>v;
		if (this->m_Index == 1)
		{
			//第二轮
			v = v2;
		}else{
			//胜利组
			v =vVictory;
		}

		for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
		{
			cout<<"选手编号："<<*it<<" 姓名："<<this->m_Speaker[*it].m_Name<<" 成绩："<<
				this->m_Speaker[*it].m_Score[this->m_Index - 1]<<endl;
		}
		cout<<endl;

		system("pause");
		system("cls");
		this->Show_Menu();
}

void speechManager::saveRecord()
{
	ofstream ofs;//输出流
	ofs.open("speech.csv" , ios::out | ios::app);//用输出的方式打开文件 --写文件
	
	//将每个人数据写入到文件中
	for(vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it<<","<<this->m_Speaker[*it].m_Score[1]<<",";
	} 
	ofs << endl;

	//数据记录保存，修改状态
	cout<<"记录已经保存"<<endl;
	this->fileIsEmpty = false;
}

void speechManager::loadRecord()
{
	ifstream ifs;//输入流
	ifs.open("speech.csv" , ios::in);//读文件
	
	//情况1:文件不存在
	if(!ifs.is_open())
	{
		this->fileIsEmpty = true;
		cout<<"文件不存在"<<endl;
		ifs.close();
		return;
	}
	//情况2：文件存在，内容为空
	char ch;
	ifs >> ch;
	if(ifs.eof())
	{
		cout<<"文件为空"<<endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}
	//情况3:文件存在，内容存在，读取内容
	int index  = 0;
	this->fileIsEmpty = false;
	
	ifs.putback(ch);//将上面读取的单个字符，放回来
	string data;
	while(ifs >> data)
	{
		vector<string>v;//存放六个

		//cout << data << endl;
		//1002,12,22,33
		int start, pos;
		pos = -1;
		start  = 0;
		while (true)
		{
			pos = data.find(",",start);
			if (pos == -1)
			{
				break;
			}
			string temp = data.substr(start,pos - start);
			//cout<<temp<<endl;
			start  = pos + 1;
			v.push_back(temp);
		}
		
		this->m_Record.insert(make_pair(index,v));
		index++;
	}
	ifs.close();
}		

void speechManager::showRecord()
{
	if(this->fileIsEmpty)
	{
		cout<<"文件不存在，或记录为空"<<endl;
	}
	else
	{
		//cout<<this->m_Record[0].size()<<endl;
		for (int i = 0; i < this->m_Record.size();i ++)
		{
			cout<<"------------第"<<i+1<<"届比赛记录------------"<<endl;
			cout<<"冠军编号:"<<this->m_Record[i][0]<<" 得分:"<<this->m_Record[i][1]<<" ||"
				<<"亚军编号:"<<this->m_Record[i][2]<<" 得分:"<<this->m_Record[i][3]<<" ||"
				<<"季军编号:"<<this->m_Record[i][4]<<" 得分:"<<this->m_Record[i][5]<<endl;
		}
	}
	system("pause");
	system("cls");
}

void speechManager::clearRecord()
{
		
		cout<<"是否确认清空文件?"<<endl;
		cout<<"1、是"<<endl; 
		cout<<"2、否"<<endl;
		int select = 0;
		cin>>select;
		if(select == 1)
		{
			//确认清空
			ofstream ofs("speech.csv" , ios::trunc);//读文件
			ofs.close();
			
			//初始化
			this->initSpeechManager();

			//创建选手
			this->createSpeaker();

			//加载
			this->loadRecord();
			cout<<"清空成功"<<endl;
		}

		system("pause");
		system("cls");
}

speechManager::~speechManager()
{	
	//释放内存11
	//if (this->m_EmpArray != NULL)
	//{
	//	delete [] this->m_EmpArray;|	//	this->m_EmpArray = NULL;
	//}
}