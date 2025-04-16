#pragma once

#include "myInclude.h"
#include "myEnum.h";

class GameManager
{

public:
	int m_Digicode = 0;

	int movingUID = 0; // �� 2�� �÷��� ü��, Ȯ��� �ڷ��� ����

private:
	/*
	0 : ���� ������ 
	1 ,2 ,3 : 1���� ũ��
	4 ,		: 2���� ����
	5 ,6	: 2���� ����
	7		: 2���� �ʹ�
	8 ,9	: 2���� ����
	10  	: 2���� ����
	11		: 3���� ����
	12		: 3���� ����
	13		: 3���� ����
	14		: 3���� �ʹ�
	15, 16  : 3���� ����
	17		: 3���� ����
	*/
	int m_Round = 0;

	std::vector<std::pair<int, enRoundType>> roundList = 
	{
		{0,  enRoundType::Type_Encounter},   // ���� ĳ����
		{1,  enRoundType::Type_Creep},       // 1���� PvE
		{2,  enRoundType::Type_ArgSelect},   // temp : ����
		{3,  enRoundType::Type_Combat},      // temp : PVP
		//{2,  enRoundType::Type_Creep},     // 1���� PvE
		//{3,  enRoundType::Type_Creep},     // 1���� PvE
		{4,  enRoundType::Type_ArgSelect},   // 2���� ����
		{5,  enRoundType::Type_Combat},      // 2���� ����
		{6,  enRoundType::Type_Combat},      // 2���� ����
		{7,  enRoundType::Type_Rolling},     // 2���� �ʹ�
		{8,  enRoundType::Type_Combat},      // 2���� ����
		{9,  enRoundType::Type_Combat},      // 2���� ����
		{10, enRoundType::Type_Boss},        // 2���� ����
		{11, enRoundType::Type_Combat},      // 3���� ����
		{12, enRoundType::Type_ArgSelect},   // 3���� ����
		{13, enRoundType::Type_Combat},      // 3���� ����
		{14, enRoundType::Type_Rolling},     // 3���� �ʹ�
		{15, enRoundType::Type_Combat},      // 3���� ����
		{16, enRoundType::Type_Combat},      // 3���� ����
		{17, enRoundType::Type_Boss}         // 3���� ����
	};

public:
	// Get
	enRoundType GetCurrentRoundType() { return roundList[m_Round].second; }
	int			GetCurrentRound() { return m_Round; }

	enTimerType GetNextTimerType();
	void NextRound();

	

};

