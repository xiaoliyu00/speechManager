#pragma once//防止头文件重复包含
#ifndef _SPEECHMANAGER_H
#define _SPEECHMANAGER_H
#include <iostream>
#include <fstream>
#include <ostream>
#include <vector>
#include <map>
#include <deque>
#include <algorithm>
#include <functional>
#include <numeric>
#include "Speaker.h"
using namespace std;

/*
*功能:
*与用户的沟通菜单界面
*
*
*/

class speechManager
{
public:
	//无参数构造函数
	speechManager();

	//菜单展示函数
	void Show_Menu();

	//选项
	void Choice_Putton();

	//退出系统
	void Exit_System();

	//初始化容器和属性
	void initSpeechManager();

	//创建选手
	void createSpeaker();

	//开始比赛   
	void startSpeech();

	//抽签
	void speechDraw();

	//比赛
	void speechContest();

	//显示得分
	void showScore();

	//保存分数
	void  saveRecord();

	//读取记录
	void loadRecord();

	//显示往届记录
	void showRecord();

	//清空现有记录
	void clearRecord();

	//判断现有文件是否为空
	bool fileIsEmpty;

	//存放往届记录的容器
	map<int,vector<string>>m_Record;

	//析构函数
	~speechManager();

public:
	//成员属性
	//第一轮比赛选手编号容器
	vector<int>v1;

	//第二轮晋级选手编号容器
	vector<int>v2;

	//前三名选手编号容器
	vector<int>vVictory;

	//存放编号以及具体选手容器
	map<int,Speaker>m_Speaker;

	//比赛轮数
	int  m_Index;
};


#endif
