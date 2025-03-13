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
	stLoginReq()
	{
		UID = 0;
		Result = 0;
		SetHeader(prLoginReq, sizeof(stLoginReq));
	};
};

struct stLoginAck : public stHeader
{
	int32 UID;
	int32 Result;
	stLoginAck()
	{
		UID = 0;
		Result = 0;
		SetHeader(prLoginAck, sizeof(stLoginAck));
	};
};

// 	prEnterGameReq, prEnterGameAck,
// 게임 입장 , 오브젝트, 맵 등을 로드하기 시작한다.
struct stEnterGameReq : public stHeader
{
	int32 UID;
	int32 Result;
	stEnterGameReq()
	{
		UID = 0;
		Result = 0;
		SetHeader(prEnterGameReq, sizeof(prEnterGameReq));
	};
};

struct stEnterGameAck : public stHeader
{
	int32 UID;
	int32 Result;
	stEnterGameAck()
	{
		UID = 0;
		Result = 0;
		SetHeader(prEnterGameAck, sizeof(prEnterGameAck));
	};
};

// 	prLoadingFinishgReq, prLoadingFinishAck,
// 클라->서버 : 필요한 에셋 로드가 끝났다고 알림
struct stLoadingFinishReq : public stHeader
{
	int32 UID;
	int32 Result;
	stLoadingFinishReq()
	{
		UID = 0;
		Result = 0;
		SetHeader(prLoadingFinishgReq, sizeof(prLoadingFinishgReq));
	};
};

// 서버->클라 : 각 플레이어의 로딩 100% 체크라고 생각하면 됨
// 생략하고 시작해도 무관
struct stLoadingFinishAck : public stHeader
{
	int32 UID;
	int32 Result;
	stLoadingFinishAck()
	{
		UID = 0;
		Result = 0;
		SetHeader(prLoadingFinishAck, sizeof(prLoadingFinishAck));
	};
};

// 	prStarGame,
// 클라가 이 패킷을 전달 받으면 게임을 시작하면 됨 : 초밥 시작 trigger
struct stStartGame : public stHeader
{
	stStartGame()
	{
		SetHeader(prStartGame, sizeof(prStartGame));
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
	int32 Result;
	stSelectedReq()
	{
		UID = 0;
		Result = 0;
		SetHeader(prSelectedReq, sizeof(prSelectedReq));
	};
};

struct stSelectedAck : public stHeader
{
	int32 UID;
	int32 Result;
	stSelectedAck()
	{
		UID = 0;
		Result = 0;
		SetHeader(prSelectedAck, sizeof(prSelectedAck));
	};
};

// prRClickedReq, prRClickedAck,
// 테이머의 우클릭 패킷, 전설이가 이동할 위치값을 넘겨 동기화 (2D 평면 위 움직임 x, y)
struct stRClickedReq : public stHeader
{
	int32 UID;
	float v[3];
	float q[4];
	stRClickedReq()
	{
		UID = 0;
		memset(v, 0, sizeof(v));
		memset(q, 0, sizeof(q));
		SetHeader(prRClickedReq, sizeof(prRClickedReq));
	};
};

struct stRClickedAck : public stHeader
{
	int32 UID;
	float v[3];
	float q[4];
	stRClickedAck()
	{
		UID = 0;
		memset(v, 0, sizeof(v));
		memset(q, 0, sizeof(q));
		SetHeader(prRClickedAck, sizeof(prRClickedAck));
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

		SetHeader(prLClickedReq, sizeof(prLClickedReq));
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

		SetHeader(prLClickedAck, sizeof(prLClickedAck));
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
		boughtDigimon = enDigimon::None;

		SetHeader(prBoughtReq, sizeof(prBoughtReq));
	};
};

struct stBoughtAck : public stHeader
{
	int32 UID;
	enDigimon boughtDigimon;
	stBoughtAck()
	{
		UID = 0;
		boughtDigimon = enDigimon::None;

		SetHeader(prBoughtAck, sizeof(prBoughtAck));
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
		soldDigimon = enDigimon::None;

		SetHeader(prSoldReq, sizeof(prSoldReq));
	};
};

struct stSoldAck : public stHeader
{
	int32 UID;
	enDigimon soldDigimon;
	stSoldAck()
	{
		UID = 0;
		soldDigimon = enDigimon::None;

		SetHeader(prSoldAck, sizeof(prSoldAck));
	};
};

// 	prMatchStart,
// 매 전투 시작 시 모든 클라에게 호출
struct stMatchStart : public stHeader
{
	stMatchStart()
	{

		SetHeader(prMatchStart, sizeof(prMatchStart));
	};
};

// 	prMatchEnd,
// 매 전투 종료 시 모든 클라에게 호출
struct stMatchEnd : public stHeader
{
	stMatchEnd()
	{

		SetHeader(prMatchEnd, sizeof(prMatchEnd));
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
		movingDigimon = enDigimon::None;
		memset(v, 0, sizeof(v));
		memset(q, 0, sizeof(q));
		SetHeader(prMoveReq, sizeof(prMoveReq));
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
		movingDigimon = enDigimon::None;
		memset(v, 0, sizeof(v));
		memset(q, 0, sizeof(q));

		SetHeader(prMoveAck, sizeof(prMoveAck));
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
		attackDigimon = enDigimon::None;

		SetHeader(prAttackReq, sizeof(prAttackReq));
	};
};

struct stAttackAck : public stHeader
{
	int32 UID;
	enDigimon attackDigimon;
	stAttackAck()
	{
		UID = 0;
		attackDigimon = enDigimon::None;

		SetHeader(prAttackAck, sizeof(prAttackAck));
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
		diedDigimon = enDigimon::None;

		SetHeader(prDieReq, sizeof(prDieReq));
	};
};

struct stDieAck : public stHeader
{
	int32 UID;
	enDigimon diedDigimon;
	stDieAck()
	{
		UID = 0;
		diedDigimon = enDigimon::None;

		SetHeader(prDieAck, sizeof(prDieAck));
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
		attachedDigimon = enDigimon::None;
		attachedItem = enItem::None;
		SetHeader(prAttachedReq, sizeof(prAttachedReq));
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
		attachedDigimon = enDigimon::None;
		attachedItem = enItem::None;
		SetHeader(prAttachedAck, sizeof(prAttachedAck));
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
		detachedDigimon = enDigimon::None;
		detachedItem = enItem::None;
		SetHeader(prDetachedReq, sizeof(prDetachedReq));
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
		detachedDigimon = enDigimon::None;
		detachedItem = enItem::None;
		SetHeader(prDetachedAck, sizeof(prDetachedAck));
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
		SetHeader(prArgPickedReq, sizeof(prArgPickedReq));
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
		SetHeader(prArgPicKedAck, sizeof(prArgPicKedAck));
	};
};
