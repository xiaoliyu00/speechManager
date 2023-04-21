#include <iostream>
#include <string>
#include <vector>
//#include <deque>
#include <map>
#include <algorithm>
//#include <ctime>
#include <functional>
#include "speechManager.h"
#include "Speaker.h"
#include <ctime>
using namespace std;

void test()
{
	//随机数种子
	srand((unsigned int)time(NULL));
	speechManager sm;
	//测试
	//for(map<int,Speaker>::iterator it = sm.m_Speaker.begin();it != sm.m_Speaker.end();it ++)
	//{
	//	cout<<"id:"<<it->first<<" name:"<<it->second.m_Name<<" score:"<<it->second.m_Score[0]<<endl;
	//}
	sm.Choice_Putton();
}
int main()
{
	test();
	return 0;
}