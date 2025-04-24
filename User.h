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

	int mRecvWrite;
	char mRecvBuffer[MAX_RECV];

	int mSendSize;
	char mSendBuffer[MAX_SEND];

	unsigned char mName[32];

	enTamersDigimon mSelectedTDigimon;

	std::list<int> mydigimonCodes;


	int mMyCombatCnt;	 // 전투 중 카운팅할 내 디지몬의 수
	int mMaxMyCombatCnt;	// 비교를 위한 최대값

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


// Combat
	// 전투 시작시 받을 패킷에서 설정
	void SetMaxCnt(int myMax);
	void ClearCombatCnt();



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

	// Game Info
	void RecvServerTime(char* packet);
	void RecvBought(char* packet);
	void RecvSold(char* packet);
	void RecvSpawn(char* packet);
	void RecvSpawnCreep(char* packet);
	void RecvTransform(char* packet);
	void RecvSetMove(char* packet);
	void RecvSetAttack(char* packet);
	void RecvSetSpecial(char* packet);
	void RecvSetWin(char* packet);

	void RecvSetHp(char* packet);
	void RecvSetMp(char* packet);
	void RecvDie(char* packet);
	void RecvAttached(char* packet);
	void RecvDetached(char* packet);
	// Creep
	void RecvCreepTR(char* packet);
	void RecvCreepHp(char* packet);
	void RecvCreepDie(char* packet);
	void RecvPicking(char* packet);
	void RecvPickingObj(char* packet);
	// Arguments
	void RecvArgPicked(char* packet);
	void RecvArgBranchingOutChoice(char* packet);
	void RecvArgTitan(char* packet);
	void RecvArgCalledShot(char* packet);
	void RecvArgOverEncumbered(char* packet);
	void RecvArgFiresale(char* packet);
	void RecvArgKingslayer(char* packet);

	// Flow 
	void RecvEncountStart(char* packet);
	void RecvEncountFin(char* packet);
	void RecvRoundStart(char* packet);
	void RecvRoundFin(char* packet);
	void RecvFadeInStart(char* packet);
	void RecvFadeInFin(char* packet);
	void RecvBattleReadyStart(char* packet);
	void RecvBattleReadyFin(char* packet);
	void RecvBattleStart(char* packet);
	void RecvBattleFin(char* packet);
	void RecvCombatEnd(char* packet);
	void RecvManageStart(char* packet);
	void RecvManageFin(char* packet);
};

