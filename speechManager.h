#pragma once//��ֹͷ�ļ��ظ�����
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
*����:
*���û��Ĺ�ͨ�˵�����
*
*
*/

class speechManager
{
public:
	//�޲������캯��
	speechManager();

	//�˵�չʾ����
	void Show_Menu();

	//ѡ��
	void Choice_Putton();

	//�˳�ϵͳ
	void Exit_System();

	//��ʼ������������
	void initSpeechManager();

	//����ѡ��
	void createSpeaker();

	//��ʼ����   
	void startSpeech();

	//��ǩ
	void speechDraw();

	//����
	void speechContest();

	//��ʾ�÷�
	void showScore();

	//�������
	void  saveRecord();

	//��ȡ��¼
	void loadRecord();

	//��ʾ�����¼
	void showRecord();

	//������м�¼
	void clearRecord();

	//�ж������ļ��Ƿ�Ϊ��
	bool fileIsEmpty;

	//��������¼������
	map<int,vector<string>>m_Record;

	//��������
	~speechManager();

public:
	//��Ա����
	//��һ�ֱ���ѡ�ֱ������
	vector<int>v1;

	//�ڶ��ֽ���ѡ�ֱ������
	vector<int>v2;

	//ǰ����ѡ�ֱ������
	vector<int>vVictory;

	//��ű���Լ�����ѡ������
	map<int,Speaker>m_Speaker;

	//��������
	int  m_Index;
};


#endif
