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
	prEnterGame,
	prLoadingFinishgReq, prLoadingFinishAck,
	prStartGame,
	// ���̸� ���� ����ȭ ����
	prSelectedReq, prSelectedAck,   // �ʹ� ����
	prTTelePortReq, prTTelePortAck, // �ڷ���Ʈ
	prRClickedReq, prRClickedAck,	// �̵� ��ȣ
	prLClickedReq, prLClickedAck,   // Drag Drop �� Drop ���� 
	// ���� ���� ����ȭ ����
	prBoughtReq, prBoughtAck,
	prSoldReq, prSoldAck,
	prSpawnReq, prSpawnAck,
	// ������ ���� ����ȭ ����
	prSyncTrReq, prSyncTrAck,
	prAttackReq, prAttackAck,
	prSkillReq, prSkillAck,
	prMoveReq, prMoveAck,
	prDieReq, prDieAck,
	// ��� ����ȭ ����
	prAttachedReq, prAttachedAck,
	prDetachedReq, prDetachedAck,
	// ���� ����ȭ ����
	prArgPickedReq, prArgPicKedAck,
	// ���� �÷ο� ����
	prEncounterStart, prEncounterFin,
	prFadeInStart, prFadeInFin,
	prBattleReadyStart, prBattleReadyFin,
	prBattleStart, prBattleFin,
	prManageStart, prManageFin,

	prRoundStart,	prRoundFin,

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
