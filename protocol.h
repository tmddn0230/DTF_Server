#pragma once
#pragma pack(1)

#include "Core.h"
#include "myDefine.h"
#include "myEnum.h"

enum enProtocol
{
    PROTOCOL_START = 0,
    // ���� �÷ο� ����
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
    prRClickedReq, prRClickedAck, // �̵� ��ȣ
    prLClickedReq, prLClickedAck,   // Drag Drop �� Drop ���� 
    // ���� ���� ����ȭ ����
    prBoughtReq, prBoughtAck,
    prSoldReq, prSoldAck,
    prSpawnReq, prSpawnAck,
    prSpawnCreepReq, prSpawnCreepAck,
    // ������ ���� ����ȭ ����
    prSyncTrReq, prSyncTrAck,
    prSetMoveReq, prSetMoveAck,
    prSetAttackReq, prSetAttackAck,
    prSetWinReq, prSetWinAck,
    prSetTargetReq, prSetTargetAck,
    // ������ ���� ����ȭ ����
    prHpReq, prHpAck,
    prMpReq, prMpAck,
    prDieReq, prDieAck,
    // ũ�� ����ȭ ����
    prCreepHpReq, prCreepHpAck,
    prCreepDieReq, prCreepDieAck,
    prPickingReq, prPickingAck,
    prPickingObjReq, prPickingObjAck,
    // ��� ����ȭ ����
    prAttachedReq, prAttachedAck,
    prDetachedReq, prDetachedAck,
    // ���� ����ȭ ����
    prArgPickedReq, prArgPickedAck,
    prArgBranchingOutChoice,
    prArgTitan,
    prArgCalledShot,
    prArgOverEncumbered,
    prArgFiresale,
    prArgKingslayer,
    // ���� �÷ο� Ÿ�̸� ����
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
