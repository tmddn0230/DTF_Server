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

	mUID = 0;
	mIndex = INVALID_VALUE;

	mSelectedTDigimon = enTamersDigimon::T_None;

	memset(mName, 0x00, sizeof(mName));
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

	mUID = 0;
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
	case prLoginReq:			RecvLoginReq(packet);	break;
	case prEnterLobbyReq:		RecvEnterLobby(packet);	break;
	case prGetUserInfo:			RecvGetUserInfo(packet);	break;
	case prEnterGame:	    	RecvEnterGame(packet);	break;
	case prLoadingFinishgReq:   RecvLoadingFinish(packet);   break;
	case prStartGame:			RecvStart(packet);   break;
	case prSelectedReq:			RecvSelected(packet);   break;
	case prTTelePortReq:		RecvTeleport_Tamer(packet);   break;
	case prRClickedReq:         RecvRClicked(packet);   break;
	case prLClickedReq:		    RecvLClicked(packet);   break;
	case prBoughtReq:		    RecvBought(packet);   break;
	case prSoldReq:			    RecvSold(packet);   break;
	case prSpawnReq:			RecvSpawn(packet);		 break;
	case prAttackReq:		    RecvAttack(packet);   break;
	case prSkillReq:		    RecvSkill(packet);   break;
	case prMoveReq:			    RecvMove(packet);   break;
	case prDieReq:			    RecvDie(packet);   break;
	case prSyncTrReq:			RecvTransform(packet); break;
	case prAttachedReq:		    RecvAttached(packet);   break;
	case prDetachedReq:		    RecvDetached(packet);   break;
	case prArgPickedReq:        RecvArgPicked(packet);   break;
	case prEncounterFin:		RecvEncountFin(packet);	break; // 사실상 안쓰임
	case prFadeInFin:			RecvFadeInFin(packet); break;
	case prBattleReadyFin:		RecvBattleReadyFin(packet); break;
	case prBattleFin:			RecvBattleFin(packet);	break;
	case prManageFin:			RecvManageFin(packet); break;
	case prRoundFin:			RecvRoundFin(packet); break;
		//default:			SendDefault(packet);	break;
	}


}

bool User::IsValidDigicode(int digicode)
{
	for (int k = 0; k < mydigimonCodes.size(); k++)
	{
		if (mydigimonCodes[k] == digicode)
			return true;
	}


	return false;
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

		ack.UID = g_User.GetUser(i)->mUID;
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
	
	g_User.mWaitingCnt++;
	if (g_User.mWaitingCnt == g_User.GetUserCount())
	{
		stEncounterStart ack;

		char buffer[64];
		memset(buffer, 0x00, sizeof(buffer));
		memcpy(buffer, &ack, sizeof(stEncounterStart));

		g_User.SendAll(buffer, sizeof(stEncounterStart));
		puts("Recv And Send All Packet");
		g_User.mWaitingCnt = 0;
	}
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


void User::RecvAttack(char* packet)
{
	stAttackAck req;
	memcpy(&req, packet, sizeof(stAttackAck));

	g_User.SendOther(req.UID, packet, sizeof(stAttackAck));
	puts("Recv And Send All Packet");
}

void User::RecvSkill(char* packet)
{
	stSkillAck req;
	memcpy(&req, packet, sizeof(stSkillAck));

	g_User.SendOther(req.UID, packet, sizeof(stSkillAck));
	puts("Recv And Send All Packet");
}

void User::RecvMove(char* packet)
{
	stMoveAck req;
	memcpy(&req, packet, sizeof(stMoveAck));

	g_User.SendOther(req.UID, packet, sizeof(stMoveAck));
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

void User::RecvArgPicked(char* packet)
{
	stArgPicKedAck req;
	memcpy(&req, packet, sizeof(stArgPicKedAck));

	g_User.SendOther(req.UID, packet, sizeof(stArgPicKedAck));
	puts("Recv And Send All Packet");
}



void User::RecvSpawn(char* packet)
{
	stSpawnReq req;
	memcpy(&req, packet, sizeof(stSpawnReq));

	stSpawnAck ack;

	ack.UID = req.UID;
	ack.spawnedSeatIndex = req.spawnedSeatIndex;
	// DIGICODE 부여
	ack.digicode = g_GameMgr.m_Digicode + DTF;
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
	Log("Spawn Digimon");
}

void User::RecvTransform(char* packet)
{
	stSyncTrReq req;
	memcpy(&req, packet, sizeof(stSyncTrReq));

	stSyncTrAck ack;

	ack.UID = req.UID;
	ack.Digicode = req.Digicode;

	if (IsValidDigicode(req.Digicode))
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

void User::RecvEncountFin(char* packet)
{
	stEncounterFin req;
	memcpy(&req, packet, sizeof(stEncounterFin));

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


void User::RecvFadeInFin(char* packet)
{
	Log("Fade In & Out Finish");
}

void User::RecvBattleReadyFin(char* packet)
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
	}

	Log("Battle Ready Finish");
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
	}

	Log("Manage Finish");
}

void User::RecvRoundFin(char* packet)
{
	stRoundFin req;
	memcpy(&req, packet, sizeof(stRoundFin));

	g_User.mTimerCnt++;
	if (g_User.mTimerCnt == g_User.GetUserCount())
	{
		g_GameMgr.NextRound(); // Round Count ++

		stRoundStart ack;
		ack.round = g_GameMgr.GetCurrentRoundType();
		ack.timer = g_GameMgr.GetNextTimerType();

		char buffer[64];
		memset(buffer, 0x00, sizeof(buffer));

		memcpy(buffer, &ack, sizeof(stRoundStart));
		g_User.SendAll(buffer, sizeof(stRoundStart));
		g_User.mTimerCnt = 0;
	}
}