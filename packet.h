﻿#pragma once


#include "Core.h"
#include "protocol.h"

#pragma pack(1)
struct stConnectAck : public stHeader
{
	// Connect
	int32 Index;
	stConnectAck()
	{
		Index = 0;

		SetHeader(prConnectAck, sizeof(stConnectAck));
	};
};

struct stLoginReq : public stHeader
{
	int32 UID;
	int32 Result;
	char playerID[32];

	stLoginReq()
	{
		UID = 0;
		Result = 0;
		memset(playerID, 0x00, sizeof(playerID));
		SetHeader(prLoginReq, sizeof(stLoginReq));
	};
};

struct stLoginAck : public stHeader
{
	int32 UID;
	int32 Result;
	char playerID[32];

	stLoginAck()
	{
		UID = 0;
		Result = 0;
		memset(playerID, 0x00, sizeof(playerID));
		SetHeader(prLoginAck, sizeof(stLoginAck));
	};
};
// 	prEnterLobbyReq, prEnterLobbyAck,
// 로비 입장
struct stEnterLobbyReq : public stHeader
{
	int32 UID;
	enTamersDigimon selectedTD;

	stEnterLobbyReq()
	{
		UID = 0;
		selectedTD = enTamersDigimon::T_None;
		SetHeader(prEnterLobbyReq, sizeof(stEnterLobbyReq));
	};
};

struct stEnterLobbyAck : public stHeader
{
	int32 UID;
	enTamersDigimon selectedTD;

	stEnterLobbyAck()
	{
		UID = 0;
		selectedTD = enTamersDigimon::T_None;
		SetHeader(prEnterLobbyAck, sizeof(stEnterLobbyAck));
	};
};

// prMyInfo
struct stMyInfo : public stHeader
{
	int32 UID;
	enTamersDigimon selectedTD;
	char playerID[32];

	stMyInfo()
	{
		UID = 0;
		selectedTD = enTamersDigimon::T_None;
		memset(playerID, 0x00, sizeof(playerID));
		SetHeader(prGetUserInfo, sizeof(stMyInfo));
	};
};

// prGetUserInfo
struct stGetUserInfo : public stHeader
{
	int32 UID;
	enTamersDigimon selectedTD;
	char playerID[32];

	stGetUserInfo()
	{
		UID = 0;
		selectedTD = enTamersDigimon::T_None;
		memset(playerID, 0x00, sizeof(playerID));
		SetHeader(prGetUserInfo, sizeof(stGetUserInfo));
	};
};


// 	prEnterGameReq, prEnterGameAck,
// 게임 입장 , 오브젝트, 맵 등을 로드하기 시작한다.
struct stEnterGame : public stHeader
{
	int32 Result;
	stEnterGame()
	{
		Result = 0;
		SetHeader(prEnterGame, sizeof(stEnterGame));
	};
};


// 	prLoadingFinishgReq, prLoadingFinishAck,
// 클라->서버 : 필요한 에셋 로드가 끝났다고 알림
struct stLoadingFinishReq : public stHeader
{
	int32 UID;

	stLoadingFinishReq()
	{
		UID = 0;
		SetHeader(prLoadingFinishgReq, sizeof(stLoadingFinishReq));
	};
};

// 서버->클라 : 각 플레이어의 로딩 100% 체크라고 생각하면 됨
// 생략하고 시작해도 무관
struct stLoadingFinishAck : public stHeader
{
	int32 UID;

	stLoadingFinishAck()
	{
		UID = 0;
		SetHeader(prLoadingFinishAck, sizeof(stLoadingFinishAck));
	};
};

// 	prStarGame,
// 클라가 이 패킷을 전달 받으면 게임을 시작하면 됨 : 초밥 시작 trigger
struct stStartGame : public stHeader
{
	int32 UID;

	stStartGame()
	{
		UID = 0;
		SetHeader(prStartGame, sizeof(stStartGame));
	};
};

/*
==================================================================
================   테이머 동작 관련 패킷   =======================
==================================================================
*/

// 	prSelectedReq, prSelectedAck,
// 초밥에서 챔피언, 아이템을 고를 때 
struct stSelectedReq : public stHeader
{
	int32 UID;
	int32 SelectedDigimon;
	int32 SelectedItem;
	stSelectedReq()
	{
		UID = 0;
		SelectedDigimon = 0;
		SelectedItem = 0;
		SetHeader(prSelectedReq, sizeof(stSelectedReq));
	};
};

struct stSelectedAck : public stHeader
{
	int32 UID;
	enDigimon SelectedDigimon;
	enItem    SelectedItem;
	stSelectedAck()
	{
		UID = 0;
		SelectedDigimon = enDigimon::NoneDigimon;
		SelectedItem	= enItem::NoneItem;
		SetHeader(prSelectedAck, sizeof(stSelectedAck));
	};
};

struct stTTeleportReq : public stHeader
{
	int32 startUID;
	int32 distUID;

	stTTeleportReq()
	{
		startUID = 0;
		distUID = 0;
		SetHeader(prTTelePortReq, sizeof(stTTeleportReq));
	};
};

struct stTTeleportAck : public stHeader
{
	int32 startUID;
	int32 distUID;

	stTTeleportAck()
	{
		startUID = 0;
		distUID = 0;
		SetHeader(prTTelePortAck, sizeof(stTTeleportAck));
	};
};


// prRClickedReq, prRClickedAck,
// 테이머의 우클릭 패킷, 전설이가 이동할 위치값을 넘겨 동기화 (2D 평면 위 움직임 x, y)
struct stRClickedReq : public stHeader
{
	int32 UID;
	float v[3];

	stRClickedReq()
	{
		UID = 0;
		memset(v, 0, sizeof(v));

		SetHeader(prRClickedReq, sizeof(stRClickedReq));
	};
};

struct stRClickedAck : public stHeader
{
	int32 UID;
	float v[3];

	stRClickedAck()
	{
		UID = 0;
		memset(v, 0, sizeof(v));

		SetHeader(prRClickedAck, sizeof(stRClickedAck));
	};
};

/*
==================================================================
================   게임 플레이 관련 패킷   =======================
==================================================================
*/
// 서버 시간 동기화용
struct stServerTimeReq : public stHeader
{
	float requestSendTime = 0;

	stServerTimeReq()
	{
		SetHeader(prServerTimeReq, sizeof(stServerTimeReq));
	};
};

struct stServerTimeAck : public stHeader
{
	float requestSendTime = 0;
	float serverTime = 0;

	stServerTimeAck()
	{
		float serverTime = 0;

		SetHeader(prServerTimeAck, sizeof(stServerTimeAck));
	};
};


// 	prBoughtReq, prBoughtAck,
//  디지몬 구매시 호출 , 구매한 디지몬 명단만 모든 클라에 넘겨주고 각 클라의 매니저 클래스에서 동기화 하면서 기물 컨트롤, 골드 컨트롤 
struct stBoughtReq : public stHeader
{
	int32 UID;
	enDigimon boughtDigimon;
	stBoughtReq()
	{
		UID = 0;
		boughtDigimon = enDigimon::NoneDigimon;

		SetHeader(prBoughtReq, sizeof(stBoughtReq));
	};
};

struct stBoughtAck : public stHeader
{
	int32 UID;
	enDigimon boughtDigimon;
	stBoughtAck()
	{
		UID = 0;
		boughtDigimon = enDigimon::NoneDigimon;

		SetHeader(prBoughtAck, sizeof(stBoughtAck));
	};
};

// 	prSoldReq, prSoldAck,
// 구매와 동일
struct stSoldReq : public stHeader
{
	int32 UID;
	enDigimon soldDigimon;
	stSoldReq()
	{
		UID = 0;
		soldDigimon = enDigimon::NoneDigimon;

		SetHeader(prSoldReq, sizeof(stSoldReq));
	};
};

struct stSoldAck : public stHeader
{
	int32 UID;
	enDigimon soldDigimon;
	stSoldAck()
	{
		UID = 0;
		soldDigimon = enDigimon::NoneDigimon;

		SetHeader(prSoldAck, sizeof(stSoldAck));
	};
};

struct stSpawnReq : public stHeader
{
	int32 UID;
	int32 spawnedSeatIndex;
	int32 digicode;
	char  spawnDigimonName[32];

	stSpawnReq()
	{
		UID = 0;
		spawnedSeatIndex = 0;
		digicode = 0;
		memset(spawnDigimonName, 0x00, sizeof(spawnDigimonName));
		SetHeader(prSpawnReq, sizeof(stSpawnReq));
	};
};

struct stSpawnAck : public stHeader
{
	int32 UID;
	int32 spawnedSeatIndex;
	int32 digicode;
	char  spawnDigimonName[32];

	stSpawnAck()
	{
		UID = 0;
		spawnedSeatIndex = 0;
		digicode = 0;
		memset(spawnDigimonName, 0x00, sizeof(spawnDigimonName));
		SetHeader(prSpawnAck, sizeof(stSpawnAck));
	};
};

struct stSpawnCreepReq : public stHeader
{
	int32 UID;
	int32 TileIndex;
	int32 CreepIdx;
	char  spawnDigimonName[32];

	stSpawnCreepReq()
	{
		UID = 0;
		TileIndex = 0;
		CreepIdx = 0;
		memset(spawnDigimonName, 0x00, sizeof(spawnDigimonName));
		SetHeader(prSpawnCreepReq, sizeof(stSpawnCreepReq));
	};
};

struct stSpawnCreepAck : public stHeader
{
	int32 UID;
	int32 TileIndex;
	int32 CreepIdx;
	char  spawnDigimonName[32];

	stSpawnCreepAck()
	{
		UID = 0;
		TileIndex = 0;
		CreepIdx = 0;
		memset(spawnDigimonName, 0x00, sizeof(spawnDigimonName));
		SetHeader(prSpawnCreepAck, sizeof(stSpawnCreepAck));
	};
};

/*
==================================================================
================   디지몬 동작 관련 패킷   =======================
==================================================================
*/

//     prSyncTrReq, prSyncTrAck,
struct stSyncTrReq :public stHeader
{
	int32 UID;
	int32 Digicode;
	float v[3];
	float q[4];
	float serverTime;

	stSyncTrReq()
	{
		UID = 0;
		Digicode = 0;
		memset(v, 0, sizeof(v));
		memset(q, 0, sizeof(q));
		serverTime = 0;
		SetHeader(prSyncTrReq, sizeof(stSyncTrReq));
	};
};

struct stSyncTrAck :public stHeader
{
	int32 UID;
	int32 Digicode;
	float v[3];
	float q[4];
	float serverTime;

	stSyncTrAck()
	{
		UID = 0;
		Digicode = 0;
		memset(v, 0, sizeof(v));
		memset(q, 0, sizeof(q));
		serverTime = 0;
		SetHeader(prSyncTrAck, sizeof(stSyncTrAck));
	};
};

// prSetMoveReq, prSetMoveAck
struct stSetMoveReq : public stHeader
{
	int32 UID;
	int32 Digicode;
	float ChangeStateTime;
	float ClientSyncServerTime;
	stSetMoveReq()
	{
		UID = 0;
		Digicode = 0;
		ChangeStateTime = 0;
		ClientSyncServerTime = 0;
		SetHeader(prSetMoveReq, sizeof(stSetMoveReq));
	};
};

struct stSetMoveAck : public stHeader
{
	int32 UID;
	int32 Digicode;
	float ChangeStateTime;
	float serverTime;

	stSetMoveAck()
	{
		UID = 0;
		Digicode = 0;
		ChangeStateTime = 0;
		serverTime = 0;
		SetHeader(prSetMoveAck, sizeof(stSetMoveAck));
	};
};

// prAttachedReq, prAttachedAck
struct stSetAttackReq : public stHeader
{
	int32 UID;
	int32 Digicode;
	float ChangeStateTime;
	float ClientSyncServerTime;

	stSetAttackReq()
	{
		UID = 0;
		Digicode = 0;
		ChangeStateTime = 0;
		ClientSyncServerTime = 0;
		SetHeader(prSetAttackReq, sizeof(stSetMoveReq));
	};
};

struct stSetAttackAck : public stHeader
{
	int32 UID;
	int32 Digicode;
	float ChangeStateTime;
	float serverTime;

	stSetAttackAck()
	{
		UID = 0;
		Digicode = 0;
		ChangeStateTime = 0;
		serverTime = 0;
		SetHeader(prSetAttackAck, sizeof(stSetAttackAck));
	};
};

// prSetSpecialReq, prSetSpecialAck,
struct stSetSpecialReq : public stHeader
{
	int32 UID;
	int32 Digicode;
	float ChangeStateTime;
	float ClientSyncServerTime;
	stSetSpecialReq()
	{
		UID = 0;
		Digicode = 0;
		ChangeStateTime = 0;
		ClientSyncServerTime = 0;
		SetHeader(prSetSpecialReq, sizeof(stSetSpecialReq));
	};
};

struct stSetSpecialAck : public stHeader
{
	int32 UID;
	int32 Digicode;
	float ChangeStateTime;
	float serverTime;

	stSetSpecialAck()
	{
		UID = 0;
		Digicode = 0;
		ChangeStateTime = 0;
		serverTime = 0;
		SetHeader(prSetSpecialAck, sizeof(stSetSpecialAck));
	};
};

// prSetWinReq, prSetWinAck
struct stSetWinReq : public stHeader
{
	int32 UID;
	int32 Digicode;
	float ChangeStateTime;
	float ClientSyncServerTime;
	stSetWinReq()
	{
		UID = 0;
		Digicode = 0;
		ChangeStateTime = 0;
		ClientSyncServerTime = 0;
		SetHeader(prSetWinReq, sizeof(stSetWinReq));
	};
};

struct stSetWinAck : public stHeader
{
	int32 UID;
	int32 Digicode;
	float serverTime;
	float ChangeStateTime;
	stSetWinAck()
	{
		UID = 0;
		Digicode = 0;
		ChangeStateTime = 0;
		serverTime = 0;
		SetHeader(prSetWinAck, sizeof(stSetWinAck));
	};
};

// HP
struct stHpReq : public stHeader
{
	int32 UID;
	int32 Digicode;
	float Hp;

	stHpReq()
	{
		UID = 0;
		Digicode = 0;
		Hp = 0;
		SetHeader(prHpReq, sizeof(stHpReq));
	};
};

struct stHpAck : public stHeader
{
	int32 UID;
	int32 Digicode;
	float Hp;
	float serverTime;

	stHpAck()
	{
		UID = 0;
		Digicode = 0;
		Hp = 0;
		serverTime = 0;
		SetHeader(prHpAck, sizeof(stHpAck));
	};
};

// MP
struct stMpReq : public stHeader
{
	int32 UID;
	int32 Digicode;
	float Mp;

	stMpReq()
	{
		UID = 0;
		Digicode = 0;
		Mp = 0;
		SetHeader(prMpReq, sizeof(stMpReq));
	};
};

struct stMpAck : public stHeader
{
	int32 UID;
	int32 Digicode;
	float Mp;
	float serverTime;

	stMpAck()
	{
		UID = 0;
		Digicode = 0;
		Mp = 0;
		serverTime = 0;
		SetHeader(prMpAck, sizeof(stMpAck));
	};
};

// 	prDieReq, prDieAck,
// 오브젝트 off
struct stDieReq : public stHeader
{
	int32 UID;
	int32 Digicode;
	float serverTime;
	float ChangeStateTime;

	stDieReq()
	{
		UID = 0;
		Digicode = 0;
		ChangeStateTime = 0;
		serverTime = 0;
		SetHeader(prDieReq, sizeof(stDieReq));
	};
};

struct stDieAck : public stHeader
{
	int32 UID;
	int32 Digicode;
	float serverTime;
	float ChangeStateTime;

	stDieAck()
	{
		UID = 0;
		Digicode = 0;
		ChangeStateTime = 0;
		serverTime = 0;
		SetHeader(prDieAck, sizeof(stDieAck));
	};
};
/*
==================================================================
================   크립 동기화 관련 패킷   =======================
==================================================================
*/
// prCreepTrReq, prCreepTrAck,
struct stCreepTrReq : public stHeader
{
	int32 UID;
	int32 Creep;
	float v[3];
	float q[4];

	stCreepTrReq()
	{
		UID = 0;
		Creep = 0;
		memset(v, 0, sizeof(v));
		memset(q, 0, sizeof(q));
		SetHeader(prCreepTrReq, sizeof(stCreepTrReq));
	};
};

struct stCreepTrAck : public stHeader
{
	int32 UID;
	int32 Creep;
	float v[3];
	float q[4];

	stCreepTrAck()
	{
		UID = 0;
		Creep = 0;
		memset(v, 0, sizeof(v));
		memset(q, 0, sizeof(q));
		SetHeader(prCreepTrAck, sizeof(stCreepTrAck));
	};
};


// prCreepHpReq, prCreepHpAck,
struct stCreepHpReq : public stHeader
{
	int32 UID;
	int32 Creep;
	float value;

	stCreepHpReq()
	{
		UID = 0;
		Creep = 0;
		value = 0;
		SetHeader(prCreepHpReq, sizeof(stCreepHpReq));
	};
};

struct stCreepHpAck : public stHeader
{
	int32 UID;
	int32 Creep;
	float value;

	stCreepHpAck()
	{
		UID = 0;
		Creep = 0;
		value = 0;
		SetHeader(prCreepHpAck, sizeof(stCreepHpAck));
	};
};


// prCreepDieReq, prCreepDieAck,
struct stCreepDieReq : public stHeader
{
	int32 UID;
	int32 Creep;

	stCreepDieReq()
	{
		UID = 0;
		Creep = 0;
		SetHeader(prCreepDieReq, sizeof(stCreepDieReq));
	};
};

struct stCreepDieAck : public stHeader
{
	int32 UID;
	int32 Creep;

	stCreepDieAck()
	{
		UID = 0;
		Creep = 0;
		SetHeader(prCreepDieAck, sizeof(stCreepDieAck));
	};
};

// prPickingReq, prPickingAck
struct stPickingReq : public stHeader
{
	int32 UID;
	enItem getItem;

	stPickingReq()
	{
		UID = 0;
		getItem = enItem::NoneItem;
		SetHeader(prPickingReq, sizeof(stPickingReq));
	};
};

struct stPickingAck : public stHeader
{
	int32 UID;
	enItem getItem;

	stPickingAck()
	{
		UID = 0;
		getItem = enItem::NoneItem;
		SetHeader(prPickingAck, sizeof(stPickingAck));
	};
};

// prPickingReq, prPickingAck
struct stPickingObjReq : public stHeader
{
	int32 UID;
	enItem getItem;
	float v[3];

	stPickingObjReq()
	{
		UID = 0;
		getItem = enItem::NoneItem;
		memset(v, 0, sizeof(v));
		SetHeader(prPickingObjReq, sizeof(stPickingObjReq));
	};
};

struct stPickingObjAck : public stHeader
{
	int32 UID;
	enItem getItem;
	float v[3];

	stPickingObjAck()
	{
		UID = 0;
		getItem = enItem::NoneItem;
		memset(v, 0, sizeof(v));
		SetHeader(prPickingObjAck, sizeof(stPickingObjAck));
	};
};

/*
==================================================================
================   장비 동기화 관련 패킷   =======================
==================================================================
*/
// 	prAttachedReq, prAttachedAck,
// 장비 착용시 attachedDigimon : 장착하는 디지몬 , attachedItem : 장비
struct stAttachedReq : public stHeader
{
	int32 UID;
	enDigimon attachedDigimon;
	enItem    attachedItem;
	stAttachedReq()
	{
		UID = 0;
		attachedDigimon = enDigimon::NoneDigimon;
		attachedItem = enItem::NoneItem;
		SetHeader(prAttachedReq, sizeof(stAttachedReq));
	};
};

struct stAttachedAck : public stHeader
{
	int32 UID;
	enDigimon attachedDigimon;
	enItem    attachedItem;
	stAttachedAck()
	{
		UID = 0;
		attachedDigimon = enDigimon::NoneDigimon;
		attachedItem = enItem::NoneItem;
		SetHeader(prAttachedAck, sizeof(stAttachedAck));
	};
};

// 	prDetachedReq, prDetachedAck,
// attach 와 동일
struct stDetachedReq : public stHeader
{
	int32 UID;
	enDigimon detachedDigimon;
	enItem    detachedItem;
	stDetachedReq()
	{
		UID = 0;
		detachedDigimon = enDigimon::NoneDigimon;
		detachedItem = enItem::NoneItem;
		SetHeader(prDetachedReq, sizeof(stDetachedReq));
	};
};

struct stDetachedAck : public stHeader
{
	int32 UID;
	enDigimon detachedDigimon;
	enItem    detachedItem;
	stDetachedAck()
	{
		UID = 0;
		detachedDigimon = enDigimon::NoneDigimon;
		detachedItem = enItem::NoneItem;
		SetHeader(prDetachedAck, sizeof(stDetachedAck));
	};
};

/*
==================================================================
================   증강 동기화 관련 패킷   =======================
==================================================================
*/

// 	prArgPickedReq, prArgPicKedAck,

struct stArgPickedReq : public stHeader
{
	int32 UID;
	enArgument pickedArg;
	stArgPickedReq()
	{
		UID = 0;
		pickedArg = enArgument::None;
		SetHeader(prArgPickedReq, sizeof(stArgPickedReq));
	};
};

struct stArgPickedAck : public stHeader
{
	int32 UID;
	enArgument pickedArg;
	stArgPickedAck()
	{
		UID = 0;
		pickedArg = enArgument::None;
		SetHeader(prArgPickedAck, sizeof(stArgPickedAck));
	};
};

struct stArgBranchingOutChoice : public stHeader
{
	int32 UID;
	Synergyes synergy;

	stArgBranchingOutChoice()
	{
		UID = 0;
		synergy = Synergyes::S_None;
		SetHeader(prArgBranchingOutChoice, sizeof(stArgBranchingOutChoice));
	};
};

struct stArgTitan : public stHeader
{
	int32 UID;


	stArgTitan()
	{
		UID = 0;
		SetHeader(prArgTitan, sizeof(stArgTitan));
	};
};

struct stArgCalledShot : public stHeader
{
	int32 UID;

	stArgCalledShot()
	{
		UID = 0;

		SetHeader(prArgCalledShot, sizeof(stArgCalledShot));
	};
};

struct stArgOverEncumbered : public stHeader
{
	int32 UID;
	int32 item1;
	int32 item2;
	int32 item3;

	stArgOverEncumbered()
	{
		UID = 0;
		item1 = 0;
		item2 = 0;
		item3 = 0;
		SetHeader(prArgOverEncumbered, sizeof(stArgOverEncumbered));
	};
};

struct stArgFireslae : public stHeader
{
	int32 UID;
	char digimonName[32];
	int32 idx;

	stArgFireslae()
	{
		UID = 0;
		memset(digimonName, 0x00, sizeof(digimonName));
		idx = 0;
		SetHeader(prArgFiresale, sizeof(stArgFireslae));
	};
};

struct stArgKngslayer : public stHeader
{
	int32 myUID;
	int32 enemyUID;

	stArgKngslayer()
	{
		myUID	 = 0;
		enemyUID = 0;

		SetHeader(prArgKingslayer, sizeof(stArgKngslayer));
	};
};

/*
==================================================================
================   게임 플로우 관련 패킷   =======================
==================================================================
*/

struct stEncounterStart : public stHeader
{
	int32 UID;
	stEncounterStart()
	{
		UID = 0;
		SetHeader(prEncounterStart, sizeof(stEncounterStart));
	};
};

struct stEncounterFin : public stHeader
{
	int32 UID;
	stEncounterFin()
	{
		UID = 0;
		SetHeader(prEncounterFin, sizeof(stEncounterFin));
	};
};


struct stFadeInStart : public stHeader
{
	int32 UID;
	enRoundType round;
	enTimerType	timer;

	stFadeInStart()
	{
		UID = 0;
		round = enRoundType::Type_None;
		timer = enTimerType::TT_Fade_In;
		SetHeader(prFadeInStart, sizeof(stFadeInStart));
	};
};

struct stFadeInFin : public stHeader
{
	int32 UID;

	stFadeInFin()
	{
		UID = 0;
		SetHeader(prFadeInFin, sizeof(stFadeInFin));
	};
};

struct stBattleReadyStart : public stHeader
{
	int32 UID;
	int32 movingUID;

	stBattleReadyStart()
	{
		UID = 0;
		movingUID = 0;
		SetHeader(prBattleReadyStart, sizeof(stBattleReadyStart));
	};
};

struct stBattleReadyFin : public stHeader
{
	int32 uid;
	int32 myMaxCnt;

	stBattleReadyFin()
	{
		uid = 0;
		myMaxCnt = 0;
		SetHeader(prBattleReadyFin, sizeof(stBattleReadyFin));
	};
};


struct stBattleStart : public stHeader
{
	int32 UID;
	stBattleStart()
	{
		UID = 0;
		SetHeader(prBattleStart, sizeof(stBattleStart));
	};
};

struct stBattleFin : public stHeader
{
	int32 UID;
	stBattleFin()
	{
		UID = 0;
		SetHeader(prBattleFin, sizeof(stBattleFin));
	};
};

struct stCombatEnd : public stHeader
{
	int32 winnerUID;
	float serverTime;

	stCombatEnd()
	{
		winnerUID = 0;
		serverTime = 0;
		SetHeader(prCombatEnd, sizeof(stCombatEnd));
	};
};


struct stManageStart : public stHeader
{
	int32 UID;
	stManageStart()
	{
		UID = 0;
		SetHeader(prManageStart, sizeof(stManageStart));
	};
};

struct stManageFin : public stHeader
{
	int32 UID;
	stManageFin()
	{
		UID = 0;
		SetHeader(prManageFin, sizeof(stManageFin));
	};
};


struct stRoundStart : public stHeader
{
	int32 UID;
	enRoundType round;
	enTimerType timer;

	stRoundStart()
	{
		UID = 0;
		round = enRoundType::Type_None;
		timer = enTimerType::TT_None;
		SetHeader(prRoundStart, sizeof(stRoundStart));
	};
};

struct stRoundFin : public stHeader
{
	int32 UID;
	enRoundType round;
	enTimerType timer;
	stRoundFin()
	{
		UID = 0;
		round = enRoundType::Type_None;
		timer = enTimerType::TT_None;
		SetHeader(prRoundFin, sizeof(stRoundFin));
	};
};
