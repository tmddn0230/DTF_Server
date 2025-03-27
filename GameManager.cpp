#include "GameManager.h"


enTimerType GameManager::GetNextTimerType()
{
	enTimerType _timer;

	switch (roundList[m_Round].second)
	{
	case enRoundType::Type_Creep : 
		if (m_Round == 1)
		{
			_timer = enTimerType::TT_Battle_ready;
		}
		else
		{
			_timer = enTimerType::TT_Manage;
		}
		break;

	case enRoundType::Type_ArgSelect:
		_timer = enTimerType::TT_Manage;
		break;

	case enRoundType::Type_Rolling:
		_timer = enTimerType::TT_Select;
		break;

	default: // combat, 
		_timer = enTimerType::TT_Manage;
		break;
	}

	return _timer;
}

void GameManager::NextRound()
{
	m_Round++;
}
