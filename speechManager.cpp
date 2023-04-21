#include "speechManager.h"
#include "Speaker.h"

speechManager::speechManager()
{
	//��ʼ��
	this->initSpeechManager();
	
	//����ѡ��
	this->createSpeaker();

	//����
	this->loadRecord();
}

void speechManager::Show_Menu()
{
	cout<<"*******************************"<<endl;
	cout<<"****** ��ӭ�μ��ݽ����� ******"<<endl;
	cout<<"****** 1.��ʼ�ݽ����� ******"<<endl;
	cout<<"****** 2.�鿴���������¼ ******"<<endl;
	cout<<"****** 3.��ձ�����¼ ******"<<endl;
	cout<<"****** 0.�˳��������� ******"<<endl;
	cout<<"*******************************"<<endl;
	cout<<endl;
}

//ѡ��
void speechManager::Choice_Putton()
{
	int choice = 0;//�洢�û�ѡ��
	//speechManager sm;

	while(true)
	{
		this->Show_Menu();
		cout<<"����������ѡ�񣡣���"<<endl;
		cin >> choice;//����ѡ��
		//m_choice = choice;
		switch(choice)
		{
		case 0:
			this->Exit_System();
			break;
		case 1://��ʼ
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
	cout<<"��ӭ�´�ʹ�ã�����"<<endl;
	system("pause");
	exit(0);
}

void speechManager::initSpeechManager()
{
	//�����ÿ�
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();

	//��ʼ����������
	this->m_Index = 1;

	//�������
	this->m_Record.clear();
}

void speechManager::createSpeaker()
{
	string nameSeed = "ABCDEFGHJKLM";
	 for (int i = 0;i < nameSeed.size();i ++)
	 {
		   //����
			string name = "player";
			name += nameSeed[i];

			Speaker sp;
			sp.m_Name = name;
			//�ɼ�
			for (int j = 0;j < 2;j++)
			{
				sp.m_Score[j] = 0;
			}
			//ѡ�ֱ��
			this->v1.push_back(i+10001);

			//ѡ�ֱ���Լ���Ӧ��ѡ����Ϣ��ŵ�map������
			this->m_Speaker.insert(make_pair(i+10001,sp));
	 }
}

void speechManager::startSpeech()
{
	///////��һ�ֿ�ʼ����

	//1.��ǩ
	this->speechDraw();

	//2.����
	this->speechContest();

	//3.��ʾ�������
	this->showScore();
	
	///////�ڶ��ֿ�ʼ����

	this->m_Index++;
	//1.��ǩ
	this->speechDraw();

	//2.����
	this->speechContest();

	//3.��ʾ�������
	this->showScore();

	//4.����������ļ���
	this->saveRecord();

	cout<<"����������"<<endl;

	//���ñ�����¼
	//��ʼ��
	this->initSpeechManager();

	//����ѡ��
	this->createSpeaker();

	//����
	this->loadRecord();

	system("pause");
	system("cls");
}

void speechManager::speechDraw()
{
	cout<<"��<<"<<this->m_Index<<">> �ֱ���ѡ�����ڳ�ǩ"<<endl;
	cout<<"------------------------"<<endl;
	cout<<"��ǩ���ݽ�˳������"<<endl;

	if(this->m_Index == 1)
	{
		//��һ�ֱ���
		random_shuffle(v1.begin(),v1.end());
		for(vector<int>::iterator it = v1.begin();it != v1.end(); it++)
		{
			cout<<*it<<" "<<endl;
		}
	}
	else
	{
		//�ڶ��ֱ���
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
	cout<<"<<"<<this->m_Index<<">>����ʽ������ʼ��-----------"<<endl;

	multimap<double,int,greater<double>>groupScore; //��ʱ����������key���� value ѡ�ֱ��

	int num = 0; //��¼��Ա����6����Ϊ1��

	vector<int>v_Src; // ��������Ա����
	if(this->m_Index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}

	//�������в���ѡ��
	for(vector<int>::iterator it = v_Src.begin(); it != v_Src.end();it++)
	{
		num++;
		//cout<<"num:"<<num<<endl;
		//��ί���
		deque<double>d;
		for(int i = 0;i < 10; i++)
		{
			double score = (rand() % 401 +600) / 10.f;//600-1000
			d.push_back(score);
		}
	
		sort(d.begin(),d.end(),greater<double>()); //����
		d.pop_front(); //ȥ����߷�
		d.pop_back(); //ȥ����ͷ�

		double sum = accumulate(d.begin(),d.end(),0.0f);//��ȡ�ܷ�
		double avg = sum/(double)d.size();//��ȡƽ����

		//��ӡƽ����
		//cout<<"��ţ�"<<*it<<"������"<<this->m_Speaker[*it].m_Name<<" ��ȡƽ����"<<avg<<endl;

		//��ƽ���ַ��뵽map������
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;

		//��������� ���뵽��ʱС��������
		groupScore.insert(make_pair(avg,*it));
		//ÿ6��ȡ��ǰ����
		if(num % 6 == 0)
		{
			cout<<"��"<<num / 6 <<"С���������"<<endl;
			for (multimap<double,int,greater<double>>::iterator it = groupScore.begin();it != groupScore.end();it++)
			{
				cout<<"ѡ�ֱ�ţ�"<<it->second<<" ������"<<this->m_Speaker[it->second].m_Name<<" �ɼ���"<<this->m_Speaker[it->second].m_Score[this->m_Index - 1]<<endl;
			}
			
			//ȡ��ǰ����
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
			groupScore.clear();//С���������
		}
	}
	cout<<"-------------��"<<this->m_Index<<"�ֱ������------------"<<endl;
	system("pause");
}

//չʾ����
void speechManager::showScore()
{
		cout<<"------------��"<<this->m_Index<<"�ֽ���ѡ����Ϣ���£�------------"<<endl;
 
		vector<int>v;
		if (this->m_Index == 1)
		{
			//�ڶ���
			v = v2;
		}else{
			//ʤ����
			v =vVictory;
		}

		for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
		{
			cout<<"ѡ�ֱ�ţ�"<<*it<<" ������"<<this->m_Speaker[*it].m_Name<<" �ɼ���"<<
				this->m_Speaker[*it].m_Score[this->m_Index - 1]<<endl;
		}
		cout<<endl;

		system("pause");
		system("cls");
		this->Show_Menu();
}

void speechManager::saveRecord()
{
	ofstream ofs;//�����
	ofs.open("speech.csv" , ios::out | ios::app);//������ķ�ʽ���ļ� --д�ļ�
	
	//��ÿ��������д�뵽�ļ���
	for(vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it<<","<<this->m_Speaker[*it].m_Score[1]<<",";
	} 
	ofs << endl;

	//���ݼ�¼���棬�޸�״̬
	cout<<"��¼�Ѿ�����"<<endl;
	this->fileIsEmpty = false;
}

void speechManager::loadRecord()
{
	ifstream ifs;//������
	ifs.open("speech.csv" , ios::in);//���ļ�
	
	//���1:�ļ�������
	if(!ifs.is_open())
	{
		this->fileIsEmpty = true;
		cout<<"�ļ�������"<<endl;
		ifs.close();
		return;
	}
	//���2���ļ����ڣ�����Ϊ��
	char ch;
	ifs >> ch;
	if(ifs.eof())
	{
		cout<<"�ļ�Ϊ��"<<endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}
	//���3:�ļ����ڣ����ݴ��ڣ���ȡ����
	int index  = 0;
	this->fileIsEmpty = false;
	
	ifs.putback(ch);//�������ȡ�ĵ����ַ����Ż���
	string data;
	while(ifs >> data)
	{
		vector<string>v;//�������

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
		cout<<"�ļ������ڣ����¼Ϊ��"<<endl;
	}
	else
	{
		//cout<<this->m_Record[0].size()<<endl;
		for (int i = 0; i < this->m_Record.size();i ++)
		{
			cout<<"------------��"<<i+1<<"�������¼------------"<<endl;
			cout<<"�ھ����:"<<this->m_Record[i][0]<<" �÷�:"<<this->m_Record[i][1]<<" ||"
				<<"�Ǿ����:"<<this->m_Record[i][2]<<" �÷�:"<<this->m_Record[i][3]<<" ||"
				<<"�������:"<<this->m_Record[i][4]<<" �÷�:"<<this->m_Record[i][5]<<endl;
		}
	}
	system("pause");
	system("cls");
}

void speechManager::clearRecord()
{
		
		cout<<"�Ƿ�ȷ������ļ�?"<<endl;
		cout<<"1����"<<endl; 
		cout<<"2����"<<endl;
		int select = 0;
		cin>>select;
		if(select == 1)
		{
			//ȷ�����
			ofstream ofs("speech.csv" , ios::trunc);//���ļ�
			ofs.close();
			
			//��ʼ��
			this->initSpeechManager();

			//����ѡ��
			this->createSpeaker();

			//����
			this->loadRecord();
			cout<<"��ճɹ�"<<endl;
		}

		system("pause");
		system("cls");
}

speechManager::~speechManager()
{	
	//�ͷ��ڴ�11
	//if (this->m_EmpArray != NULL)
	//{
	//	delete [] this->m_EmpArray;|	//	this->m_EmpArray = NULL;
	//}
}