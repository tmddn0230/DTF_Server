#pragma once
#include "myInclude.h"
#include "myDefine.h"
#include "myEnum.h"

#include "framework.h"

class User
{
public:

	SOCKET mhSocket;

	int mThreadNum;
	int mIndex;
	int mUID;

	int mRecvWrite;
	char mRecvBuffer[MAX_RECV];

	int mSendSize;
	char mSendBuffer[MAX_SEND];

	unsigned char mName[32];

	enTamersDigimon mSelectedTDigimon;

	std::list<int> mydigimonCodes;

public:
	User(void);
	~User(void);
	void Clear();

	bool Init(int index, SOCKET sock, sockaddr_in ip);

	void LogOut();

	void EmptyRecvBuffer();

	int FlushSendBuffer();
	bool AddSendBuffer(char* buff, int size);

	void Send(char* buff, int size);
	void Recv();
	void Parse(int protocol, char* packet);

	bool IsValidDigicode(int uid, int digicode);


public: //RECV
	void RecvLoginReq(char* packet);
	void RecvEnterLobby(char* packet);
	void RecvGetUserInfo(char* packet);
	void RecvEnterGame(char* packet);
	void RecvLoadingFinish(char* packet);
	void RecvStart(char* packet);
	void RecvSelected(char* packet);
	void RecvTeleport_Tamer(char* packet);
	void RecvRClicked(char* packet);
	void RecvLClicked(char* packet);
	void RecvBought(char* packet);
	void RecvSold(char* packet);
	void RecvSpawn(char* packet);
	void RecvTransform(char* packet);
	void RecvSetMove(char* packet);
	void RecvSetAttack(char* packet);
	void RecvSetWin(char* packet);
	void RecvTarget(char* packet);
	void RecvSetHp(char* packet);
	void RecvSetMp(char* packet);
	void RecvDie(char* packet);
	void RecvAttached(char* packet);
	void RecvDetached(char* packet);
	void RecvCreepDie(char* packet);
	void RecvPicking(char* packet);
	void RecvPickingObj(char* packet);
	void RecvArgPicked(char* packet);
	void RecvEncountFin(char* packet);
	void RecvRoundFin(char* packet);
	void RecvFadeInFin(char* packet);
	void RecvBattleFin(char* packet);
	void RecvManageFin(char* packet);
	void RecvBattleReadyFin(char* packet);
};

