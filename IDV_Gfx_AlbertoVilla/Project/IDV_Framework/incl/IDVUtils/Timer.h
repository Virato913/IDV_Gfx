/*********************************************************
* Copyright (C) 2017 Daniel Enriquez (camus_mm@hotmail.com)
* All Rights Reserved
*
* You may use, distribute and modify this code under the
* following terms:
* ** Do not claim that you wrote this software
* ** A mention would be appreciated but not needed
* ** I do not and will not provide support, this software is "as is"
* ** Enjoy, learn and share.
*********************************************************/

#ifndef T800_TIMER_H
#define T800_TIMER_H
#include <windows.h>


//#include <sys/time.h>

class Timer {
public:
	void Init();
	void Update();

	float	GetDTSecs();


	LARGE_INTEGER	StartTime;

	//timeval	        StartTime;

	double			Frequency;
	double			Dt;
	double			DtSecs;
};

#endif
#pragma once
