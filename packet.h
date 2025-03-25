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

// 	prMatchStart,
// �� ���� ���� �� ��� Ŭ�󿡰� ȣ��
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
// �� ���� ���� �� ��� Ŭ�󿡰� ȣ��
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
// �ش� �������� ���� sign
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

// ��ų
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
