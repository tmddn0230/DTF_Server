#pragma once
#include "User.h"

class UserManager
{
public:

	User mUser[MAX_USER];
	int mPreIndex;
	int mChatIndex;

	int mRoundCnt = 0;
	int mTimerCnt = 0;
	int mWaitingCnt = 0;
	int mCombatCnt = 0;

	bool mbStart;

public:
	UserManager(void);
	~UserManager(void);

	bool AddUser(SOCKET sock, sockaddr_in ip);
	void DelUser(int index);
	User* GetUser(int uid);

	void Send(int index, char* buff, int size);
	void SendOther(int index, char* buff, int size);
	void SendAll(char* buff, int size);

	void SendMsg(char* buff, int size, int FID);

	int GetUserCount();
};

