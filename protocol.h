#pragma once
#pragma pack(1)

#include "Core.h"
#include "myDefine.h"
#include "myEnum.h"

enum enProtocol
{
	PROTOCOL_START = 0,
	prConnectAck,
	prLoginReq, prLoginAck,
	prEnterLobbyReq, prEnterLobbyAck,
	prMyInfo,
	prGetUserInfo,
	prEnterGameReq, prEnterGameAck,
	prLoadingFinishgReq, prLoadingFinishAck,
	prStartGame,
	// 테이머 동작 동기화 관련
	prSelectedReq, prSelectedAck,   // 초밥 선택
	prRClickedReq, prRClickedAck,	// 이동 신호
	prLClickedReq, prLClickedAck,   // Drag Drop 시 Drop 에서 
	// 게임 정보 동기화 관련
	prBoughtReq, prBoughtAck,
	prSoldReq, prSoldAck,
	prMatchStart,
	prMatchEnd,
	// 디지몬 동작 동기화 관련
	prAttackReq, prAttackAck,
	prSkillReq, prSkillAck,
	prMoveReq, prMoveAck,
	prDieReq, prDieAck,
	// 장비 동기화 관련
	prAttachedReq, prAttachedAck,
	prDetachedReq, prDetachedAck,
	// 증강 동기화 관련
	prArgPickedReq, prArgPicKedAck,
	// 게임 시스템 관련
	prSpawnReq,	prSpawnAck,

	PROTOCOL_END
};



struct stHeader
{
	uint16 nID;
	uint16 nSize;
	uint16 nType;
	uint16 nCheckSum;

	stHeader()
	{
		nID = nSize = nType = nCheckSum = 0;
	};
	void SetHeader(int id, int len)
	{
		nID = id;
		nSize = len;
		nType = DTF;
		nCheckSum = nType + nID + nSize;
	};
};

#define HEADSIZE sizeof( stHeader )

#pragma pack()
