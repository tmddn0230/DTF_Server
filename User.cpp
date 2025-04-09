#include "User.h"
#include "Core.h"
#include "myGlobal.h"

#include "protocol.h"
#include "packet.h"
#include "myEnum.h"

User::User(void)
{
	// Initialize var
	mhSocket = NULL;
	mRecvWrite = 0;

	mSendSize = 0;

	mIndex = INVALID_VALUE;


	mSelectedTDigimon = enTamersDigimon::T_None;

	memset(mName, 0x00, sizeof(mName));
	
	mMaxEnemyCombatCnt = 0;
	mMaxMyCombatCnt = 0;

	mEnemyCombatCnt = 0; // 전투중 계산되는 카운터
	mMyCombatCnt = 0;	 // 전투중 계산되는 카운터
}

User::~User(void)
{
	Clear();
}

void User::Clear()
{
	if (mhSocket != NULL)
	{
		shutdown(mhSocket, SD_SEND);
		shutdown(mhSocket, SD_RECEIVE);
	}
	SAFE_CLOSESOCKET(mhSocket);

	mRecvWrite = 0;
	memset(mRecvBuffer, 0x00, sizeof(mRecvBuffer));

	mSendSize = 0;
	memset(mSendBuffer, 0x00, sizeof(mSendBuffer));

	memset(mName, 0x00, sizeof(mName));

	mIndex = INVALID_VALUE;

	mThreadNum = INVALID_VALUE;

	mSelectedTDigimon = enTamersDigimon::T_None;
}

bool User::Init(int index, SOCKET sock, sockaddr_in ip)
{
	if (index < 0 || index >= MAX_USER)
		return false;

	Clear();

	mhSocket = sock;
	mIndex = index;

	mThreadNum = index / gUserper;

	mSelectedTDigimon = enTamersDigimon::T_None;
	//SendConnect();

	mydigimonCodes = std::list<int>();

	int t = mThreadNum;
	if (t < 0 || t > MAX_QUEUE)
		return false;

	return true;
}

void User::LogOut()
{
	if (mhSocket) {
		int t = mThreadNum;
		if (t < 0 || t > MAX_QUEUE)
			return;
	}
	Clear();
}

void User::EmptyRecvBuffer()
{
	memset(mRecvBuffer, 0x00, sizeof(mRecvBuffer));
	mRecvWrite = 0;
}

int User::FlushSendBuffer()
{
	int sendsize = 0;
	do
	{
		sendsize = send(mhSocket, mSendBuffer, mSendSize, 0);
		if (sendsize == SOCKET_ERROR)
		{
			uint32 error = WSAGetLastError();
			return error;
		}
		else
		{
			memmove(mSendBuffer, &mSendBuffer[sendsize], mSendSize - sendsize);
			mSendSize -= sendsize;
		}
	} while (mSendSize);

	return mSendSize;
}

bool User::AddSendBuffer(char* buff, int size)
{
	if (buff == NULL)
		return false;
	if (mSendSize + size >= MAX_SEND)
	{
		Clear();
		return false;
	}

	memcpy(&mSendBuffer[mSendSize], buff, size);
	mSendSize += size;
	return true;
}

void User::Send(char* buff, int size)
{
	if (mhSocket == NULL) {
		return;
	}
	if (buff == NULL)
		return;

	int sendsize, error = 0;
	if (mSendSize <= 0) {// Only once Case : Queue Empty

		do {
			sendsize = send(mhSocket, buff, size, 0);

			if (sendsize < 0) {
				AddSendBuffer(buff, size);
				break;
			}
			else
			{
				buff = buff + sendsize; // 버퍼의 위치를 send 한 만큼 뒤로 밈
				size -= sendsize;       // 패킷 사이즈를 보낸만큼 빼준다.
			}
		} while (size);                 // size가 0이 될 때까지 보낸다.

	}
	else {// 큐가 비어있지 않다면 보낼 데이터를 큐에 쌓고, 
		// 버퍼를 초과하지 않았다면 FlushBuffer();를 호출해서 처리한다.
		if (AddSendBuffer(buff, size)) {
			FlushSendBuffer();
		}
		else {
			FlushSendBuffer();
		}
	}
}

void User::Recv()
{
	if (mhSocket == NULL)
		return;
	if (mIndex < 0)
		return;

	int size = 0;
	if (mRecvWrite < MAX_RECV)
		size = recv(mhSocket, &mRecvBuffer[mRecvWrite], MAX_RECV - mRecvWrite, 0);
	//stTestPacket header;
	//memcpy(&header, mRecvBuffer, sizeof(stTestPacket));

	if (size > 0) {
		// ADD at Current RecvBuffer's Length
		mRecvWrite += size;

		if (mRecvWrite >= MAX_RECV) {
			puts("User Buffer is Full");
		}

		while (mRecvWrite >= HEADSIZE) {
			stHeader header;
			memcpy(&header, mRecvBuffer, HEADSIZE);
			// Why didn't use ?
			//if (header.nID >= PROTOCOL_END || header.nID <= PROTOCOL_START) {
			//	Clear();
			//	EmptyRecvBuffer();
			//	return;
			//}


			if (header.nSize <= 0) {
				EmptyRecvBuffer();
				return;
			}
			int iCheckSum = header.nType + header.nSize + header.nID;
			if (header.nCheckSum != iCheckSum) {
				EmptyRecvBuffer();
				return;
			}

			if (mRecvWrite >= header.nSize) {
				Parse(header.nID, mRecvBuffer);
				memmove(mRecvBuffer, &mRecvBuffer[header.nSize], mRecvWrite);
				mRecvWrite -= header.nSize;
			}
			else {
				break;
			}
		}
	}
}

void User::Parse(int protocol, char* packet)
{
	switch (protocol)
	{
	case prLoginReq:			 RecvLoginReq(packet);	break;
	case prEnterLobbyReq:		 RecvEnterLobby(packet);	break;
	case prGetUserInfo:			 RecvGetUserInfo(packet);	break;
	case prEnterGame:	    	 RecvEnterGame(packet);	break;
	case prLoadingFinishgReq:    RecvLoadingFinish(packet);   break;
	case prStartGame:			 RecvStart(packet);   break;
	case prSelectedReq:			 RecvSelected(packet);   break;
	case prTTelePortReq:		 RecvTeleport_Tamer(packet);   break;
	case prRClickedReq:          RecvRClicked(packet);   break;
	case prLClickedReq:		     RecvLClicked(packet);   break;
	case prBoughtReq:		     RecvBought(packet);   break;
	case prSoldReq:			     RecvSold(packet);   break;
	case prSpawnReq:			 RecvSpawn(packet);		 break;
	case prSpawnCreepReq:		 RecvSpawnCreep(packet); break;
	case prSyncTrReq:			 RecvTransform(packet); break;
	case prSetMoveReq:			 RecvSetMove(packet); break;
	case prSetAttackReq:		 RecvSetAttack(packet); break;
	case prSetWinReq:			 RecvSetWin(packet); break;
	case prSetTargetReq:		 RecvTarget(packet);	break;
	case prHpReq:				 RecvSetHp(packet); break;
	case prMpReq:				 RecvSetMp(packet); break;
	case prDieReq:			     RecvDie(packet);   break;
	case prAttachedReq:		     RecvAttached(packet);   break;
	case prDetachedReq:		     RecvDetached(packet);   break;
	case prCreepHpReq:			 RecvCreepHp(packet); break;
	case prCreepDieReq:			 RecvCreepDie(packet); break;
	case prPickingReq:			 RecvPicking(packet); break;
	case prPickingObjReq:		 RecvPickingObj(packet); break;
		// Arg					 
	case prArgPickedReq:         RecvArgPicked(packet);   break;
	case prArgBranchingOutChoice:RecvArgBranchingOutChoice(packet); break;
	case prArgTitan:			 RecvArgTitan(packet); break;
	case prArgCalledShot:		 RecvArgCalledShot(packet); break;
	case prArgOverEncumbered:	 RecvArgOverEncumbered(packet); break;
	case prArgFiresale:			 RecvArgFiresale(packet); break;
	case prArgKingslayer:		 RecvArgKingslayer(packet); break;
								 
		// Flow					 
	case prEncounterStart:       RecvEncountStart(packet); break;
	case prEncounterFin:		 RecvEncountFin(packet);	break; // 사실상 안쓰임
	case prFadeInStart:			 RecvFadeInStart(packet); break;
	case prFadeInFin:			 RecvFadeInFin(packet); break;
	case prBattleReadyStart:	 RecvBattleReadyStart(packet); break;
	case prBattleReadyFin:		 RecvBattleReadyFin(packet); break;
	case prBattleStart:			 RecvBattleStart(packet); break;
	case prBattleFin:			 RecvBattleFin(packet);	break;
	case prManageStart:			 RecvManageStart(packet); break;
	case prManageFin:			 RecvManageFin(packet); break;
								 
	case prRoundStart:			 RecvRoundStart(packet); break;
	case prRoundFin:			 RecvRoundFin(packet); break;
		//default:			SendDefault(packet);	break;
	}


}

bool User::IsValidDigicode(int uid, int digicode)
{
	auto it = std::find(g_User.mUser[uid].mydigimonCodes.begin(), g_User.mUser[uid].mydigimonCodes.end(), digicode);
		
	if (it != g_User.mUser[uid].mydigimonCodes.end()) // 찾았다.
		return true;

	return false;
}

void User::SetMaxCnt(int myMax, int enemyMax)
{
	mMaxMyCombatCnt = myMax;
	mMaxEnemyCombatCnt = enemyMax;
}

void User::ClearCombatCnt()
{
	mMyCombatCnt = 0;
	mEnemyCombatCnt = 0;
	mMaxMyCombatCnt = 0;
	mMaxEnemyCombatCnt = 0;
}

/*
Login 에서 UID 를 부여 할 것 본인만 주고 받음
각 클라에게 정보를 넘겨 주는 것은 EnterGame
*/
void User::RecvLoginReq(char* packet)
{
	stLoginReq req;
	memcpy(&req, packet, sizeof(stLoginReq));

	stLoginAck ack;

	ack.UID = g_User.GetUserCount() - 1;
	ack.Result = 1; // SUCCESS

	memcpy(ack.playerID, &req.playerID, sizeof(req.playerID));
	// mName 저장
	memcpy(g_User.mUser[ack.UID].mName, &req.playerID, sizeof(req.playerID));



	char buffer[128];
	memset(buffer, 0x00, sizeof(buffer));

	memcpy(buffer, &ack, sizeof(stLoginAck));
	//_User.SendAll(buffer, sizeof(stLoginAck));
	g_User.Send(ack.UID, buffer, sizeof(stLoginAck));

	Log("Login :[ %s ]" ,req.playerID);
}

void User::RecvEnterLobby(char* packet)
{
	stEnterLobbyReq req;
	memcpy(&req, packet, sizeof(stEnterLobbyReq));

	stEnterLobbyAck ack;

	ack.UID = req.UID;// test code
	ack.selectedTD = req.selectedTD;

	char buffer[64];	
	memset(buffer, 0x00, sizeof(buffer));
	memcpy(buffer, &ack, sizeof(stEnterLobbyAck));

	g_User.mUser[req.UID].mSelectedTDigimon = req.selectedTD;

	g_User.Send(req.UID, buffer, sizeof(stEnterLobbyAck));
	Log("Enter Lobby");

	// 현재 혼자라면 보내지 않음
	if (g_User.GetUserCount() == 1) return;

	// 자기자신의 정보를 다른 유저들에게 전달
	stMyInfo infoack;

	infoack.UID = req.UID;
	infoack.selectedTD = req.selectedTD;
	memcpy(infoack.playerID, &g_User.mUser[req.UID].mName, sizeof(g_User.mUser[req.UID].mName));

	char infobuffer[64];
	memset(infobuffer, 0x00, sizeof(infobuffer));
	memcpy(infobuffer, &infoack, sizeof(stMyInfo));

	g_User.SendOther(mIndex, infobuffer, sizeof(stMyInfo));
	Log("Send My Info");
}



void User::RecvGetUserInfo(char* packet)
{
	stGetUserInfo req;
	memcpy(&req, packet, sizeof(stGetUserInfo));

	for (int i = 0; i < g_User.GetUserCount(); i++)
	{
		if (i == req.UID) continue;

		stGetUserInfo ack;

		ack.UID = g_User.GetUser(i)->mIndex;
		ack.selectedTD = g_User.GetUser(i)->mSelectedTDigimon;
		memcpy(ack.playerID, &req.playerID, sizeof(req.playerID));

		char buffer[64];
		memcpy(buffer, &ack, sizeof(stGetUserInfo));
		
		g_User.Send(req.UID, buffer, sizeof(stGetUserInfo));

		Log("Send User Info [%d]", i);
	}
}

void User::RecvEnterGame(char* packet)
{
	stEnterGame req;
	req.Result = 1;


	char buffer[64];	
	memset(buffer, 0x00, sizeof(buffer));
	memcpy(buffer, &req, sizeof(stEnterGame));

	g_User.SendAll(buffer, sizeof(stEnterGame));

	//g_User.SendOther(req.UID, packet, sizeof(stEnterGameAck));
	Log("Enter Game");
}

void User::RecvLoadingFinish(char* packet)
{
	stLoadingFinishReq req;
	memcpy(&req, packet, sizeof(stLoadingFinishReq));

	stLoadingFinishAck ack;

	ack.UID = req.UID;

	char buffer[64];	
	memset(buffer, 0x00, sizeof(buffer));
	memcpy(buffer, &ack, sizeof(stLoadingFinishAck));

	g_User.SendAll(buffer, sizeof(stLoadingFinishAck));
	//g_User.SendOther(req.UID, buffer, sizeof(stLoadingFinishAck));
	Log("Loading Finish");
}

void User::RecvStart(char* packet)
{
	stStartGame req;
	memcpy(&req, packet, sizeof(stStartGame));
	
	Log("Start Game : [%d]", req.UID);

	// 답신 x : 클라에서 StartGame 패킷과 Encounter 패킷을 동시에 보낼 예정
	// 단순 Log 기록용
}

void User::RecvSelected(char* packet)
{
	stSelectedAck ack;
	memcpy(&ack, packet, sizeof(stSelectedAck));

	//g_User.SendOther(req.UID, packet, sizeof(stSelectedAck));
	char buffer[64];
	memset(buffer, 0x00, sizeof(buffer));

	memcpy(buffer, &ack, sizeof(stSelectedAck));

	g_User.SendAll(buffer, sizeof(stSelectedAck));
	Log("Recv Select Packet And Send Other");
}

void User::RecvTeleport_Tamer(char* packet)
{
	stTTeleportReq req;
	memcpy(&req, packet, sizeof(stTTeleportReq));

	stTTeleportAck ack;

	ack.startUID = req.startUID;
	ack.distUID = req.distUID;

	//g_User.SendOther(req.UID, packet, sizeof(stSelectedAck));
	char buffer[64];
	memset(buffer, 0x00, sizeof(buffer));
	memcpy(buffer, &ack, sizeof(stTTeleportAck));

	g_User.SendAll(buffer, sizeof(stTTeleportAck));
	Log("Teleport_Tamer[%d] to [%d]", req.startUID, req.distUID);
}



void User::RecvRClicked(char* packet)
{
	stRClickedReq req;
	memcpy(&req, packet, sizeof(stRClickedReq));

	stRClickedAck ack;
	ack.UID = req.UID;
	for (int i = 0; i < 3; i++)
	{
		ack.v[i] = req.v[i];
	}

    char buffer[64];
	memset(buffer, 0x00, sizeof(buffer));
	memcpy(buffer, &ack, sizeof(stRClickedAck));

	g_User.SendAll(buffer, sizeof(stRClickedAck));
	Log("Player : [%d] MoveTo ([%f], [%f], [%f]) ", req.UID, req.v[0], req.v[1], req.v[2]);
}

void User::RecvLClicked(char* packet)
{
	stLClickedAck req;
	memcpy(&req, packet, sizeof(stLClickedAck));

	g_User.SendOther(req.UID, packet, sizeof(stLClickedAck));
	puts("Recv And Send All Packet");
}

void User::RecvBought(char* packet)
{
	stBoughtAck req;
	memcpy(&req, packet, sizeof(stBoughtAck));

	g_User.SendOther(req.UID, packet, sizeof(stBoughtAck));
	puts("Recv And Send All Packet");
}

void User::RecvSold(char* packet)
{
	stSoldAck req;
	memcpy(&req, packet, sizeof(stSoldAck));

	g_User.SendOther(req.UID, packet, sizeof(stSoldAck));
	puts("Recv And Send All Packet");
}

void User::RecvDie(char* packet)
{
	stDieAck req;
	memcpy(&req, packet, sizeof(stDieAck));

	g_User.SendOther(req.UID, packet, sizeof(stDieAck));
	puts("Recv And Send All Packet");
}

void User::RecvAttached(char* packet)
{
	stAttachedAck req;
	memcpy(&req, packet, sizeof(stAttachedAck));

	g_User.SendOther(req.UID, packet, sizeof(stAttachedAck));
	puts("Recv And Send All Packet");
}

void User::RecvDetached(char* packet)
{
	stDetachedAck req;
	memcpy(&req, packet, sizeof(stDetachedAck));

	g_User.SendOther(req.UID, packet, sizeof(stDetachedAck));
	puts("Recv And Send All Packet");
}

void User::RecvCreepHp(char* packet)
{
	stCreepHpReq req;
	memcpy(&req, packet, sizeof(stCreepHpReq));

	stCreepHpAck ack;
	ack.UID = req.UID;
	ack.Creep = req.Creep;
	ack.value = req.value;

	char buffer[64];
	memset(buffer, 0x00, sizeof(buffer));
	memcpy(buffer, &ack, sizeof(stCreepHpAck));
	g_User.SendAll(buffer, sizeof(stCreepHpAck));
}

void User::RecvCreepDie(char* packet)
{
	stCreepDieReq req;
	memcpy(&req, packet, sizeof(stCreepDieReq));

	stCreepDieAck ack;
	ack.UID = req.UID;
	ack.Creep = req.Creep;

	char buffer[64];
	memset(buffer, 0x00, sizeof(buffer));
	memcpy(buffer, &ack, sizeof(stCreepDieAck));
	g_User.SendAll(buffer, sizeof(stCreepDieAck));
	

	// 여기야 여기 여기가ㅑ 문제
	Log("Creep Die : [%d] of [%d]", req.Creep, req.UID);
	g_User.mUser[req.UID].mEnemyCombatCnt++;
	if (g_User.mUser[req.UID].mEnemyCombatCnt == g_User.mUser[req.UID].mMaxEnemyCombatCnt)
	{
		// Combat Find 패킷 작성해서 보냄
		stCombatEnd ack;

		ack.uid = req.UID;

		char buffer[64];
		memset(buffer, 0x00, sizeof(buffer));
		memcpy(buffer, &ack, sizeof(stCombatEnd));
		g_User.SendAll(buffer, sizeof(stCombatEnd));

		Log("Combat Fin (Creep)");
	}
}

void User::RecvPicking(char* packet)
{
	stPickingReq req;
	memcpy(&req, packet, sizeof(stCreepDieReq));

	stPickingAck ack;
	ack.UID = req.UID;
	ack.getItem = req.getItem;

	char buffer[64];
	memset(buffer, 0x00, sizeof(buffer));
	memcpy(buffer, &ack, sizeof(stPickingAck));
	g_User.SendAll(buffer, sizeof(stPickingAck));

	Log("Picking Item");
}

void User::RecvPickingObj(char* packet)
{
	stPickingObjReq req;
	memcpy(&req, packet, sizeof(stPickingObjReq));

	stPickingObjAck ack;
	ack.UID = req.UID;
	ack.getItem = req.getItem;
	for (int i = 0; i < 3; i++)
	{
		ack.v[i] = req.v[i];
	}

	char buffer[64];
	memset(buffer, 0x00, sizeof(buffer));
	memcpy(buffer, &ack, sizeof(stPickingObjAck));
	g_User.SendAll(buffer, sizeof(stPickingObjAck));

	Log("Picking Item OBJ");
}


void User::RecvArgPicked(char* packet)
{
	stArgPickedReq req;
	memcpy(&req, packet, sizeof(stArgPickedReq));

	stArgPickedAck ack;

	ack.UID = req.UID;
	ack.pickedArg = req.pickedArg;

	char buffer[64];
	memset(buffer, 0x00, sizeof(buffer));
	memcpy(buffer, &ack, sizeof(stArgPickedAck));
	g_User.SendAll(buffer, sizeof(stArgPickedAck));

	Log("ArgPicked : [%d]", req.pickedArg);
}

void User::RecvArgBranchingOutChoice(char* packet)
{
	stArgBranchingOutChoice req;
	memcpy(&req, packet, sizeof(stArgBranchingOutChoice));

	stArgBranchingOutChoice ack;

	ack.UID = req.UID;
	ack.synergy = req.synergy;

	char buffer[64];
	memset(buffer, 0x00, sizeof(buffer));
	memcpy(buffer, &ack, sizeof(stArgBranchingOutChoice));
	g_User.SendAll(buffer, sizeof(stArgBranchingOutChoice));

	Log("ArgBranchingOutChoice");
}

void User::RecvArgTitan(char* packet)
{
	stArgTitan req;
	memcpy(&req, packet, sizeof(stArgTitan));

	stArgTitan ack;

	ack.UID = req.UID;
	char buffer[64];
	memset(buffer, 0x00, sizeof(buffer));
	memcpy(buffer, &ack, sizeof(stArgTitan));
	g_User.SendAll(buffer, sizeof(stArgTitan));

	Log("ArgTitan");
}

void User::RecvArgCalledShot(char* packet)
{
	stArgCalledShot req;
	memcpy(&req, packet, sizeof(stArgTitan));

	stArgCalledShot ack;

	ack.UID = req.UID;

	char buffer[64];
	memset(buffer, 0x00, sizeof(buffer));
	memcpy(buffer, &ack, sizeof(stArgCalledShot));
	g_User.SendAll(buffer, sizeof(stArgCalledShot));

	Log("ArgCalledShot");
}

void User::RecvArgOverEncumbered(char* packet)
{
	stArgOverEncumbered req;
	memcpy(&req, packet, sizeof(stArgOverEncumbered));

	stArgOverEncumbered ack;

	ack.UID = req.UID;
	ack.item1 = req.item1;
	ack.item2 = req.item2;
	ack.item3 = req.item3;

	char buffer[64];
	memset(buffer, 0x00, sizeof(buffer));
	memcpy(buffer, &ack, sizeof(stArgOverEncumbered));
	g_User.SendAll(buffer, sizeof(stArgOverEncumbered));

	Log("ArgOverEncumbered");
}

void User::RecvArgFiresale(char* packet)
{
	stArgFireslae req;
	memcpy(&req, packet, sizeof(stArgFireslae));

	stArgFireslae ack;

	ack.UID = req.UID;
	memcpy(ack.digimonName, &req.digimonName, sizeof(req.digimonName));
	ack.idx = req.idx;

	char buffer[64];
	memset(buffer, 0x00, sizeof(buffer));
	memcpy(buffer, &ack, sizeof(stArgFireslae));
	g_User.SendAll(buffer, sizeof(stArgFireslae));

	Log("ArgFireslae");
}

void User::RecvArgKingslayer(char* packet)
{
	stArgKngslayer req;
	memcpy(&req, packet, sizeof(stArgKngslayer));

	stArgKngslayer ack;

	ack.myUID = req.myUID;
	ack.enemyUID = req.enemyUID;

	char buffer[64];
	memset(buffer, 0x00, sizeof(buffer));
	memcpy(buffer, &ack, sizeof(stArgKngslayer));
	g_User.SendAll(buffer, sizeof(stArgKngslayer));

	Log("ArgKngslayer");
}



void User::RecvSpawn(char* packet)
{
	stSpawnReq req;
	memcpy(&req, packet, sizeof(stSpawnReq));

	stSpawnAck ack;

	ack.UID = req.UID;
	ack.spawnedSeatIndex = req.spawnedSeatIndex;
	// DIGICODE 부여
	ack.digicode = g_GameMgr.m_Digicode;
	g_GameMgr.m_Digicode++;
	// 서버에서 디지몬 관리
	g_User.mUser[ack.UID].mydigimonCodes.push_back(ack.digicode);

	memcpy(ack.spawnDigimonName, &req.spawnDigimonName, sizeof(req.spawnDigimonName));
	// mName 저장
	memcpy(g_User.mUser[ack.UID].mName, &req.spawnDigimonName, sizeof(req.spawnDigimonName));

	char buffer[64];
	memset(buffer, 0x00, sizeof(buffer));
	memcpy(buffer, &ack, sizeof(stSpawnAck));

	g_User.SendAll( buffer, sizeof(stSpawnAck));
	//g_User.SendOther(req.UID, buffer, sizeof(stLoadingFinishAck));
	Log("Spawn Digimon [%d]", g_GameMgr.m_Digicode);
}

void User::RecvSpawnCreep(char* packet)
{
	stSpawnCreepReq req;
	memcpy(&req, packet, sizeof(stSpawnCreepReq));

	stSpawnCreepAck ack;

	ack.UID = req.UID;
	ack.TileIndex = req.TileIndex;
	// CreepIdx 부여
	ack.CreepIdx = req.CreepIdx;

	memcpy(ack.spawnDigimonName, &req.spawnDigimonName, sizeof(req.spawnDigimonName));


	char buffer[64];
	memset(buffer, 0x00, sizeof(buffer));
	memcpy(buffer, &ack, sizeof(stSpawnCreepAck));

	g_User.SendAll(buffer, sizeof(stSpawnCreepAck));

	Log("Spawn Creep Digimon");
}


void User::RecvTransform(char* packet)
{
	stSyncTrReq req;
	memcpy(&req, packet, sizeof(stSyncTrReq));

	stSyncTrAck ack;

	ack.UID = req.UID;
	ack.Digicode = req.Digicode;

	if (g_User.mUser[req.UID].IsValidDigicode(req.UID, req.Digicode))
	{
		for (int i = 0; i < 3; i++)
		{
			ack.v[i] = req.v[i];
		}
		for (int j = 0; j < 4; j++)
		{
			ack.q[j] = req.q[j];
		}

		char buffer[64];
		memset(buffer, 0x00, sizeof(buffer));
		memcpy(buffer, &ack, sizeof(stSyncTrAck));

		g_User.SendOther(req.UID, buffer, sizeof(stSyncTrAck));
	}
	else
	{
		Log("InValid Digicode in User[%d]", req.UID);
	}
	
}

void User::RecvSetMove(char* packet)
{
	stSetMoveReq req;
	memcpy(&req, packet, sizeof(stSetMoveReq));

	stSetMoveAck ack;

	ack.UID = req.UID;
	ack.Digicode = req.Digicode;

	char buffer[64];
	memset(buffer, 0x00, sizeof(buffer));
	memcpy(buffer, &ack, sizeof(stSetMoveAck));

	g_User.SendAll(buffer, sizeof(stSetMoveAck));
}

void User::RecvSetAttack(char* packet)
{
	stSetAttackReq req;
	memcpy(&req, packet, sizeof(stSetAttackReq));

	stSetAttackAck ack;

	ack.UID = req.UID;
	ack.Digicode = req.Digicode;

	char buffer[64];
	memset(buffer, 0x00, sizeof(buffer));
	memcpy(buffer, &ack, sizeof(stSetAttackAck));

	g_User.SendAll(buffer, sizeof(stSetAttackAck));
}

void User::RecvSetWin(char* packet)
{
	stSetWinReq req;
	memcpy(&req, packet, sizeof(stSetWinReq));

	stSetWinAck ack;

	ack.UID = req.UID;
	ack.Digicode = req.Digicode;

	char buffer[64];
	memset(buffer, 0x00, sizeof(buffer));
	memcpy(buffer, &ack, sizeof(stSetWinAck));

	g_User.SendAll(buffer, sizeof(stSetWinAck));
}

void User::RecvTarget(char* packet)
{
	stSetTargetReq req;
	memcpy(&req, packet, sizeof(stSetTargetReq));

	stSetTargetAck ack;

	ack.UID = req.UID;
	ack.myDigicode = req.myDigicode;
	ack.tgDigicode = req.tgDigicode;

	char buffer[64];
	memset(buffer, 0x00, sizeof(buffer));
	memcpy(buffer, &ack, sizeof(stSetTargetAck));

	g_User.SendOther(req.UID, buffer, sizeof(stSetTargetAck));
}

void User::RecvSetHp(char* packet)
{
	stHpReq req;
	memcpy(&req, packet, sizeof(stHpReq));

	stHpAck ack;

	ack.UID = req.UID;
	ack.Digicode = req.Digicode;
	ack.Hp = req.Hp;

	char buffer[64];
	memset(buffer, 0x00, sizeof(buffer));
	memcpy(buffer, &ack, sizeof(stHpAck));

	g_User.SendAll(buffer, sizeof(stHpAck));
}

void User::RecvSetMp(char* packet)
{
	stMpReq req;
	memcpy(&req, packet, sizeof(stMpReq));

	stMpAck ack;

	ack.UID = req.UID;
	ack.Digicode = req.Digicode;
	ack.Mp = req.Mp;

	char buffer[64];
	memset(buffer, 0x00, sizeof(buffer));
	memcpy(buffer, &ack, sizeof(stMpAck));

	g_User.SendAll(buffer, sizeof(stMpAck));
}

void User::RecvEncountStart(char* packet)
{
	stEncounterStart req;
	memcpy(&req, packet, sizeof(stEncounterStart));

	g_User.mWaitingCnt++;
	if (g_User.mWaitingCnt == g_User.GetUserCount())
	{
		stEncounterStart ack;
		
		char buffer[64];
		memset(buffer, 0x00, sizeof(buffer));
		memcpy(buffer, &ack, sizeof(stEncounterStart));
		
		g_User.SendAll(buffer, sizeof(stEncounterStart));

		g_User.mWaitingCnt = 0;
	}
	Log("Encounter!! : [%d]", this->mIndex);
}

void User::RecvEncountFin(char* packet)
{
	stEncounterFin req;
	memcpy(&req, packet, sizeof(stEncounterFin));

	g_User.mTimerCnt++;
	if (g_User.mTimerCnt == g_User.GetUserCount())
	{
		stEncounterFin ack;

		char buffer[64];
		memset(buffer, 0x00, sizeof(buffer));

		memcpy(buffer, &ack, sizeof(stEncounterFin));
		g_User.SendAll(buffer, sizeof(stEncounterFin));

		Log("Encounter Fin");

		g_User.mTimerCnt = 0;
	}
}

void User::RecvFadeInStart(char* packet)
{
	stFadeInStart req;
	memcpy(&req, packet, sizeof(stFadeInStart));

	g_User.mTimerCnt++;
	if (g_User.mTimerCnt == g_User.GetUserCount())
	{
		// Fade-inout start
		stFadeInStart ack;
		ack.round = g_GameMgr.GetCurrentRoundType();
		ack.timer = enTimerType::TT_Fade_In;

		char buffer[64];
		memset(buffer, 0x00, sizeof(buffer));

		memcpy(buffer, &ack, sizeof(stFadeInStart));
		g_User.SendAll(buffer, sizeof(stFadeInStart));
		g_User.mTimerCnt = 0;

		Log("Fade In & Out Start");
	}
}


void User::RecvFadeInFin(char* packet)
{
	g_User.mTimerCnt++;
	if (g_User.mTimerCnt == g_User.GetUserCount())
	{
		// Fade-inout start
		stFadeInFin ack;
		char buffer[64];
		memset(buffer, 0x00, sizeof(buffer));

		memcpy(buffer, &ack, sizeof(stFadeInFin));
		g_User.SendAll(buffer, sizeof(stFadeInFin));
		g_User.mTimerCnt = 0;

		Log("Fade In & Out Finish");
	}
}

void User::RecvBattleReadyStart(char* packet)
{
	stBattleReadyStart req;
	memcpy(&req, packet, sizeof(stBattleReadyStart));

	g_User.mTimerCnt++;
	if (g_User.mTimerCnt == g_User.GetUserCount())
	{
		if (req.movingUID == 99)
		{
			char buffer[64];
			memset(buffer, 0x00, sizeof(buffer));

			memcpy(buffer, &req, sizeof(stBattleReadyStart));
			g_User.SendAll(buffer, sizeof(stBattleReadyStart));
			g_User.mTimerCnt = 0;
			Log("Battle Ready(Creep) Start");

			return;
		}

		int movingPlayerUid;
		// 이동해야할 uid 지정해서 보내기
		srand(static_cast<unsigned int>(time(0))); // 난수 초기화
		int min = 0; // 최소값
		int max = 1; // 최대값, 추후에 7까지 확장
		movingPlayerUid = rand() % (max - min + 1) + min; // min ~ max 범위의 난수 생성

		stBattleReadyStart ack;

		ack.movingUID = movingPlayerUid;

		char buffer[64];
		memset(buffer, 0x00, sizeof(buffer));

		memcpy(buffer, &ack, sizeof(stBattleReadyStart));
		g_User.SendAll(buffer, sizeof(stBattleReadyStart));
		g_User.mTimerCnt = 0;
		Log("Battle Ready Start");
	}
}

void User::RecvBattleReadyFin(char* packet)
{
	// max cnt set
	stBattleReadyFin req;
	memcpy(&req, packet, sizeof(stBattleReadyFin));

	g_User.mUser[req.uid].ClearCombatCnt();
	g_User.mUser[req.uid].SetMaxCnt(req.myMaxCnt, req.enemyMaxCnt);

	g_User.mTimerCnt++;
	if (g_User.mTimerCnt == g_User.GetUserCount())
	{
		stBattleReadyFin ack;

		char buffer[64];
		memset(buffer, 0x00, sizeof(buffer));

		memcpy(buffer, &ack, sizeof(stBattleReadyFin));
		g_User.SendAll(buffer, sizeof(stBattleReadyFin));
		g_User.mTimerCnt = 0;
		Log("Battle Ready Finish");
	}

}

void User::RecvBattleStart(char* packet)
{
	g_User.mTimerCnt++;

	if (g_User.mTimerCnt == g_User.GetUserCount())
	{
		// Fade-inout start
		stBattleStart ack;

		char buffer[64];
		memset(buffer, 0x00, sizeof(buffer));

		memcpy(buffer, &ack, sizeof(stBattleStart));
		g_User.SendAll(buffer, sizeof(stBattleStart));
		g_User.mTimerCnt = 0;

		// 배틀 시작 시점, 적이 나와 있는 시점 
		Log("Battle Start");
	}
}

void User::RecvBattleFin(char* packet)
{
	if (g_GameMgr.GetCurrentRoundType() != enRoundType::Type_Creep)
	{
		// 크립 제외한 라운드 -> 무빙 타이머, Fade IN
		g_User.mTimerCnt++;
		if (g_User.mTimerCnt == g_User.GetUserCount())
		{
			// Fade-inout start
			stFadeInStart ack;
			ack.round = g_GameMgr.GetCurrentRoundType();
			ack.timer = enTimerType::TT_Fade_In;

			char buffer[64];
			memset(buffer, 0x00, sizeof(buffer));

			memcpy(buffer, &ack, sizeof(stFadeInStart));
			g_User.SendAll(buffer, sizeof(stFadeInStart));
			g_User.mTimerCnt = 0;
		}
	}
	Log("Battle Finish");
}

void User::RecvManageStart(char* packet)
{

	Log("Manage Start");
}


void User::RecvManageFin(char* packet)
{
	g_User.mTimerCnt++;
	if (g_User.mTimerCnt == g_User.GetUserCount())
	{
		// Fade-inout start
		stBattleReadyStart ack;

		char buffer[64];
		memset(buffer, 0x00, sizeof(buffer));

		memcpy(buffer, &ack, sizeof(stBattleReadyStart));
		g_User.SendAll(buffer, sizeof(stBattleReadyStart));
		g_User.mTimerCnt = 0;

		Log("Manage Finish");
	}
}

void User::RecvRoundStart(char* packet)
{
	stRoundStart req;
	memcpy(&req, packet, sizeof(stRoundStart));

	g_User.mTimerCnt++;
	if (g_User.mTimerCnt == g_User.GetUserCount())
	{

		stRoundStart ack;
		ack.round = g_GameMgr.GetCurrentRoundType();
		ack.timer = g_GameMgr.GetNextTimerType();

		char buffer[64];
		memset(buffer, 0x00, sizeof(buffer));

		memcpy(buffer, &ack, sizeof(stRoundStart));
		g_User.SendAll(buffer, sizeof(stRoundStart));
		g_User.mTimerCnt = 0;

		Log("Round Start");
	}

}


void User::RecvRoundFin(char* packet)
{
	stRoundFin req;
	memcpy(&req, packet, sizeof(stRoundFin));

	g_User.mTimerCnt++;
	if (g_User.mTimerCnt == g_User.GetUserCount())
	{

		stRoundFin ack;

		ack.round = g_GameMgr.GetCurrentRoundType();
		ack.timer = g_GameMgr.GetNextTimerType();

		char buffer[64];
		memset(buffer, 0x00, sizeof(buffer));

		memcpy(buffer, &ack, sizeof(stRoundFin));
		g_User.SendAll(buffer, sizeof(stRoundFin));
		g_User.mTimerCnt = 0;

		g_GameMgr.NextRound(); // Round Count ++
		Log("Round Fin");
	}





	//g_User.mTimerCnt++;
	//if (g_User.mTimerCnt == g_User.GetUserCount())
	//{
	//	g_GameMgr.NextRound(); // Round Count ++
	//
	//	stRoundStart ack;
	//	ack.round = g_GameMgr.GetCurrentRoundType();
	//	ack.timer = g_GameMgr.GetNextTimerType();
	//
	//	char buffer[64];
	//	memset(buffer, 0x00, sizeof(buffer));
	//
	//	memcpy(buffer, &ack, sizeof(stRoundStart));
	//	g_User.SendAll(buffer, sizeof(stRoundStart));
	//	g_User.mTimerCnt = 0;
	//}

}

