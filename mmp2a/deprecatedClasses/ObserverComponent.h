#pragma region include

#pragma once
#include "stdafx.h"

using namespace std;
#pragma endregion

class ObserverComponent
{
public:
	virtual ~ObserverComponent() = default;

	virtual void onNotification(string & event) = 0;

private:
};