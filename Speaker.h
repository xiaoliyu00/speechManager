#pragma once//防止头文件重复包含
#ifndef _SPEAKER_H
#define _SPEAKER_H
#include <iostream>
#include <fstream>
#include <ostream>
#include <vector>
#include <map>
#include <string>
using namespace std;
//演讲比赛参赛选手
class Speaker
{
public:
	string m_Name;//姓名
	double  m_Score[2];//两轮分数
};

#endif