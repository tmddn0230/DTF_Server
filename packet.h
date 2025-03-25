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

//	prLClickedReq, prLClickedAck,
// Drag and drop 시 변경된 타일의 위치
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
================   게임 플레이 관련 패킷   =======================
==================================================================
*/
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

// 	prMatchStart,
// 매 전투 시작 시 모든 클라에게 호출
struct stMatchStart : public stHeader
{
	int32 UID;
	stMatchStart()
	{
		UID = 0;
		SetHeader(prMatchStart, sizeof(stMatchStart));
	};
};

// 	prMatchEnd,
// 매 전투 종료 시 모든 클라에게 호출
struct stMatchEnd : public stHeader
{
	int32 UID;
	stMatchEnd()
	{
		UID = 0;
		SetHeader(prMatchEnd, sizeof(stMatchEnd));
	};
};


/*
==================================================================
================   디지몬 동작 관련 패킷   =======================
==================================================================
*/
// 	prMoveReq, prMoveAck,
// 이동 관련 패킷, 사실 여기가 동기화가 잘 되어야 적 탐색, 스킬 사용 등 동기화에 문제가 없어짐
struct stMoveReq : public stHeader
{
	int32 UID;
	enDigimon movingDigimon;
	float v[3];
	float q[4];

	stMoveReq()
	{
		UID = 0;
		movingDigimon = enDigimon::NoneDigimon;
		memset(v, 0, sizeof(v));
		memset(q, 0, sizeof(q));
		SetHeader(prMoveReq, sizeof(stMoveReq));
	};
};

struct stMoveAck : public stHeader
{
	int32 UID;
	enDigimon movingDigimon;
	float v[3];
	float q[4];

	stMoveAck()
	{
		UID = 0;
		movingDigimon = enDigimon::NoneDigimon;
		memset(v, 0, sizeof(v));
		memset(q, 0, sizeof(q));

		SetHeader(prMoveAck, sizeof(stMoveAck));
	};
};


// 	prAttackReq, prAttackAck,
// 해당 디지몬의 공격 sign
struct stAttackReq : public stHeader
{
	int32 UID;
	enDigimon attackDigimon;
	stAttackReq()
	{
		UID = 0;
		attackDigimon = enDigimon::NoneDigimon;

		SetHeader(prAttackReq, sizeof(stAttackReq));
	};
};

struct stAttackAck : public stHeader
{
	int32 UID;
	enDigimon attackDigimon;
	stAttackAck()
	{
		UID = 0;
		attackDigimon = enDigimon::NoneDigimon;

		SetHeader(prAttackAck, sizeof(stAttackAck));
	};
};

// 스킬
struct stSkillReq : public stHeader
{
	int32 UID;
	enDigimon skilledDigimon;
	stSkillReq()
	{
		UID = 0;
		skilledDigimon = enDigimon::NoneDigimon;

		SetHeader(prSkillReq, sizeof(stSkillReq));
	};
};

struct stSkillAck : public stHeader
{
	int32 UID;
	enDigimon skilledDigimon;
	stSkillAck()
	{
		UID = 0;
		skilledDigimon = enDigimon::NoneDigimon;

		SetHeader(prSkillAck, sizeof(stSkillAck));
	};
};

// 	prDieReq, prDieAck,
// 오브젝트 off
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
