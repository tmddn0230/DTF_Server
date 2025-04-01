#pragma once


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
// �κ� ����
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
// ���� ���� , ������Ʈ, �� ���� �ε��ϱ� �����Ѵ�.
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
// Ŭ��->���� : �ʿ��� ���� �ε尡 �����ٰ� �˸�
struct stLoadingFinishReq : public stHeader
{
	int32 UID;

	stLoadingFinishReq()
	{
		UID = 0;
		SetHeader(prLoadingFinishgReq, sizeof(stLoadingFinishReq));
	};
};

// ����->Ŭ�� : �� �÷��̾��� �ε� 100% üũ��� �����ϸ� ��
// �����ϰ� �����ص� ����
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
// Ŭ�� �� ��Ŷ�� ���� ������ ������ �����ϸ� �� : �ʹ� ���� trigger
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
================   ���̸� ���� ���� ��Ŷ   =======================
==================================================================
*/

// 	prSelectedReq, prSelectedAck,
// �ʹ信�� è�Ǿ�, �������� �� �� 
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
// ���̸��� ��Ŭ�� ��Ŷ, �����̰� �̵��� ��ġ���� �Ѱ� ����ȭ (2D ��� �� ������ x, y)
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

//	prLClickedReq, prLClickedAck,
// Drag and drop �� ����� Ÿ���� ��ġ
struct stLClickedReq : public stHeader
{
	int32 UID;
	int32 TileIndex;
	stLClickedReq()
	{
		UID = 0;
		TileIndex = 0;

		SetHeader(prLClickedReq, sizeof(stLClickedReq));
	};
};

struct stLClickedAck : public stHeader
{
	int32 UID;
	int32 TileIndex;
	stLClickedAck()
	{
		UID = 0;
		TileIndex = 0;

		SetHeader(prLClickedAck, sizeof(stLClickedAck));
	};
};

/*
==================================================================
================   ���� �÷��� ���� ��Ŷ   =======================
==================================================================
*/
// 	prBoughtReq, prBoughtAck,
//  ������ ���Ž� ȣ�� , ������ ������ ��ܸ� ��� Ŭ�� �Ѱ��ְ� �� Ŭ���� �Ŵ��� Ŭ�������� ����ȭ �ϸ鼭 �⹰ ��Ʈ��, ��� ��Ʈ�� 
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
// ���ſ� ����
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

/*
==================================================================
================   ������ ���� ���� ��Ŷ   =======================
==================================================================
*/

//     prSyncTrReq, prSyncTrAck,
struct stSyncTrReq :public stHeader
{
	int32 UID;
	int32 Digicode;
	float v[3];
	float q[4];

	stSyncTrReq()
	{
		UID = 0;
		Digicode = 0;
		memset(v, 0, sizeof(v));
		memset(q, 0, sizeof(q));
		SetHeader(prSyncTrReq, sizeof(stSyncTrReq));
	};
};

struct stSyncTrAck :public stHeader
{
	int32 UID;
	int32 Digicode;
	float v[3];
	float q[4];

	stSyncTrAck()
	{
		UID = 0;
		Digicode = 0;
		memset(v, 0, sizeof(v));
		memset(q, 0, sizeof(q));
		SetHeader(prSyncTrAck, sizeof(stSyncTrAck));
	};
};

// prSetMoveReq, prSetMoveAck
struct stSetMoveReq : public stHeader
{
	int32 UID;
	int32 Digicode;

	stSetMoveReq()
	{
		UID = 0;
		Digicode = 0;
		SetHeader(prSetMoveReq, sizeof(stSetMoveReq));
	};
};

struct stSetMoveAck : public stHeader
{
	int32 UID;
	int32 Digicode;

	stSetMoveAck()
	{
		UID = 0;
		Digicode = 0;
		SetHeader(prSetMoveAck, sizeof(stSetMoveAck));
	};
};

// prSetTargetReq, prSetTargetAck
// Ÿ�� ����
struct stSetTargetReq : public stHeader
{
	int32 UID;
	int32 myDigicode;
	int32 tgDigicode;

	stSetTargetReq()
	{
		UID = 0;
		myDigicode = 0;
		tgDigicode = 0;
		SetHeader(prSetTargetReq, sizeof(stSetTargetReq));
	};
};

struct stSetTargetAck : public stHeader
{
	int32 UID;
	int32 myDigicode;
	int32 tgDigicode;

	stSetTargetAck()
	{
		UID = 0;
		myDigicode = 0;
		tgDigicode = 0;
		SetHeader(prSetTargetAck, sizeof(stSetTargetAck));
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

	stHpAck()
	{
		UID = 0;
		Digicode = 0;
		Hp = 0;
		SetHeader(prHpAck, sizeof(stHpAck));
	};
};

// 	prDieReq, prDieAck,
// ������Ʈ off
struct stDieReq : public stHeader
{
	int32 UID;
	enDigimon diedDigimon;
	stDieReq()
	{
		UID = 0;
		diedDigimon = enDigimon::NoneDigimon;

		SetHeader(prDieReq, sizeof(stDieReq));
	};
};

struct stDieAck : public stHeader
{
	int32 UID;
	enDigimon diedDigimon;
	stDieAck()
	{
		UID = 0;
		diedDigimon = enDigimon::NoneDigimon;

		SetHeader(prDieAck, sizeof(stDieAck));
	};
};

/*
==================================================================
================   ��� ����ȭ ���� ��Ŷ   =======================
==================================================================
*/
// 	prAttachedReq, prAttachedAck,
// ��� ����� attachedDigimon : �����ϴ� ������ , attachedItem : ���
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
// attach �� ����
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
================   ���� ����ȭ ���� ��Ŷ   =======================
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

struct stArgPicKedAck : public stHeader
{
	int32 UID;
	enArgument pickedArg;
	stArgPicKedAck()
	{
		UID = 0;
		pickedArg = enArgument::None;
		SetHeader(prArgPicKedAck, sizeof(stArgPicKedAck));
	};
};


/*
==================================================================
================   ���� �ý��� ���� ��Ŷ   =======================
==================================================================
*/

struct stEncounterStart : public stHeader
{
	stEncounterStart()
	{
		SetHeader(prEncounterStart, sizeof(stEncounterStart));
	};
};

struct stEncounterFin : public stHeader
{
	stEncounterFin()
	{
		SetHeader(prEncounterFin, sizeof(stEncounterFin));
	};
};


struct stFadeInStart : public stHeader
{
	enRoundType round;
	enTimerType	timer;

	stFadeInStart()
	{
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
	stBattleReadyStart()
	{

		SetHeader(prBattleReadyStart, sizeof(stBattleReadyStart));
	};
};

struct stBattleReadyFin : public stHeader
{

	stBattleReadyFin()
	{
		SetHeader(prBattleReadyFin, sizeof(stBattleReadyFin));
	};
};


struct stBattleStart : public stHeader
{
	stBattleStart()
	{

		SetHeader(prBattleStart, sizeof(stBattleStart));
	};
};

struct stBattleFin : public stHeader
{

	stBattleFin()
	{
		SetHeader(prBattleFin, sizeof(stBattleFin));
	};
};

struct stManageStart : public stHeader
{
	stManageStart()
	{

		SetHeader(prManageStart, sizeof(stManageStart));
	};
};

struct stManageFin : public stHeader
{
	stManageFin()
	{
		SetHeader(prManageFin, sizeof(stManageFin));
	};
};


struct stRoundStart : public stHeader
{
	enRoundType round;
	enTimerType timer;

	stRoundStart()
	{
		round = enRoundType::Type_None;
		timer = enTimerType::TT_None;
		SetHeader(prRoundStart, sizeof(stRoundStart));
	};
};

struct stRoundFin : public stHeader
{
	stRoundFin()
	{
		SetHeader(prRoundFin, sizeof(stRoundFin));
	};
};
