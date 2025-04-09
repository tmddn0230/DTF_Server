#pragma once
#pragma pack(1)

#include "Core.h"
#include "myDefine.h"
#include "myEnum.h"

enum enProtocol
{
    PROTOCOL_START = 0,
    // 게임 플로우 관련
    prConnectAck,
    prLoginReq, prLoginAck,
    prEnterLobbyReq, prEnterLobbyAck,
    prMyInfo,
    prGetUserInfo,
    prEnterGame,
    prLoadingFinishgReq, prLoadingFinishAck,
    prStartGame,
    // 테이머 동작 동기화 관련
    prSelectedReq, prSelectedAck,   // 초밥 선택
    prTTelePortReq, prTTelePortAck, // 텔레포트
    prRClickedReq, prRClickedAck, // 이동 신호
    prLClickedReq, prLClickedAck,   // Drag Drop 시 Drop 에서 
    // 게임 정보 동기화 관련
    prBoughtReq, prBoughtAck,
    prSoldReq, prSoldAck,
    prSpawnReq, prSpawnAck,
    prSpawnCreepReq, prSpawnCreepAck,
    // 디지몬 동작 동기화 관련
    prSyncTrReq, prSyncTrAck,
    prSetMoveReq, prSetMoveAck,
    prSetAttackReq, prSetAttackAck,
    prSetWinReq, prSetWinAck,
    prSetTargetReq, prSetTargetAck,
    // 디지몬 스텟 동기화 관련
    prHpReq, prHpAck,
    prMpReq, prMpAck,
    prDieReq, prDieAck,
    // 크립 동기화 관련
    prCreepHpReq, prCreepHpAck,
    prCreepDieReq, prCreepDieAck,
    prPickingReq, prPickingAck,
    prPickingObjReq, prPickingObjAck,
    // 장비 동기화 관련
    prAttachedReq, prAttachedAck,
    prDetachedReq, prDetachedAck,
    // 증강 동기화 관련
    prArgPickedReq, prArgPickedAck,
    prArgBranchingOutChoice,
    prArgTitan,
    prArgCalledShot,
    prArgOverEncumbered,
    prArgFiresale,
    prArgKingslayer,
    // 게임 플로우 타이머 관련
    prEncounterStart, prEncounterFin,
    prFadeInStart, prFadeInFin,
    prBattleReadyStart, prBattleReadyFin,
    prBattleStart, prBattleFin, prCombatEnd,
    prManageStart, prManageFin,

    prRoundStart, prRoundFin,

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
