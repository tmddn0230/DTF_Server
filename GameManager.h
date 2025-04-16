#pragma once

#include "myInclude.h"
#include "myEnum.h";

class GameManager
{

public:
	int m_Digicode = 0;

	int movingUID = 0; // 현 2인 플레이 체제, 확장시 자료형 변경

private:
	/*
	0 : 시작 조우자 
	1 ,2 ,3 : 1라운드 크립
	4 ,		: 2라운드 증강
	5 ,6	: 2라운드 전투
	7		: 2라운드 초밥
	8 ,9	: 2라운드 전투
	10  	: 2라운드 보스
	11		: 3라운드 전투
	12		: 3라운드 증강
	13		: 3라운드 전투
	14		: 3라운드 초밥
	15, 16  : 3라운드 전투
	17		: 3라운드 보스
	*/
	int m_Round = 0;

	std::vector<std::pair<int, enRoundType>> roundList = 
	{
		{0,  enRoundType::Type_Encounter},   // 시작 캐러셀
		{1,  enRoundType::Type_Creep},       // 1라운드 PvE
		{2,  enRoundType::Type_ArgSelect},   // temp : 증강
		{3,  enRoundType::Type_Combat},      // temp : PVP
		//{2,  enRoundType::Type_Creep},     // 1라운드 PvE
		//{3,  enRoundType::Type_Creep},     // 1라운드 PvE
		{4,  enRoundType::Type_ArgSelect},   // 2라운드 증강
		{5,  enRoundType::Type_Combat},      // 2라운드 전투
		{6,  enRoundType::Type_Combat},      // 2라운드 전투
		{7,  enRoundType::Type_Rolling},     // 2라운드 초밥
		{8,  enRoundType::Type_Combat},      // 2라운드 전투
		{9,  enRoundType::Type_Combat},      // 2라운드 전투
		{10, enRoundType::Type_Boss},        // 2라운드 보스
		{11, enRoundType::Type_Combat},      // 3라운드 전투
		{12, enRoundType::Type_ArgSelect},   // 3라운드 증강
		{13, enRoundType::Type_Combat},      // 3라운드 전투
		{14, enRoundType::Type_Rolling},     // 3라운드 초밥
		{15, enRoundType::Type_Combat},      // 3라운드 전투
		{16, enRoundType::Type_Combat},      // 3라운드 전투
		{17, enRoundType::Type_Boss}         // 3라운드 보스
	};

public:
	// Get
	enRoundType GetCurrentRoundType() { return roundList[m_Round].second; }
	int			GetCurrentRound() { return m_Round; }

	enTimerType GetNextTimerType();
	void NextRound();

	

};

