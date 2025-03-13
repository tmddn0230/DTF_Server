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
// ���� ���� , ������Ʈ, �� ���� �ε��ϱ� �����Ѵ�.
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
// Ŭ��->���� : �ʿ��� ���� �ε尡 �����ٰ� �˸�
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

// ����->Ŭ�� : �� �÷��̾��� �ε� 100% üũ��� �����ϸ� ��
// �����ϰ� �����ص� ����
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
// Ŭ�� �� ��Ŷ�� ���� ������ ������ �����ϸ� �� : �ʹ� ���� trigger
struct stStartGame : public stHeader
{
	stStartGame()
	{
		SetHeader(prStartGame, sizeof(prStartGame));
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
// ���̸��� ��Ŭ�� ��Ŷ, �����̰� �̵��� ��ġ���� �Ѱ� ����ȭ (2D ��� �� ������ x, y)
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
// Drag and drop �� ����� Ÿ���� ��ġ
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
// ���ſ� ����
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
// �� ���� ���� �� ��� Ŭ�󿡰� ȣ��
struct stMatchStart : public stHeader
{
	stMatchStart()
	{

		SetHeader(prMatchStart, sizeof(prMatchStart));
	};
};

// 	prMatchEnd,
// �� ���� ���� �� ��� Ŭ�󿡰� ȣ��
struct stMatchEnd : public stHeader
{
	stMatchEnd()
	{

		SetHeader(prMatchEnd, sizeof(prMatchEnd));
	};
};


/*
==================================================================
================   ������ ���� ���� ��Ŷ   =======================
==================================================================
*/
// 	prMoveReq, prMoveAck,
// �̵� ���� ��Ŷ, ��� ���Ⱑ ����ȭ�� �� �Ǿ�� �� Ž��, ��ų ��� �� ����ȭ�� ������ ������
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
// �ش� �������� ���� sign
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
// ������Ʈ off
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
// attach �� ����
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
