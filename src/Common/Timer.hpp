/*********************************************************************
 *	@file		Timer.hpp
 *	@brief		简易的计时器，包含计时，暂停，停止，恢复等操作。
 *
 *	Date        Name        Description
 *	23/11/14	MYLS		Creation.
 *
 *********************************************************************/

#pragma once

namespace cm {
	class Timer;
}

/**
 *	\brief	A timer, just for timing;
 */
class cm::Timer {

public:

	/**
	 *	\brief Constructor
	 */
	Timer();

	/**
	 *	\brief	Destructor
	 */
	~Timer();

public:

	/**
	 *	\brief	Clear and start Timer
	 */
	void start(void);

	/**
	 *	\brief	pause Timer
	 *			While running
	 */
	void pause(void);

	/**
	 *	\brief	resume Timer
	 *			while paused
	 */
	void resume(void);

	/**
	 *	\brief	Reset the timer
	 */
	void stop(void);

	/**
	 *	\brief	Get Elapsed Time...
	 *
	 *	\return	逝去的时间，单位为毫秒
	 */
	unsigned int getElapsedTime(void) const;

private:

	/**
	 *	\brief	a enum representative timer status
	 */
	enum TimerStatus : unsigned char {
		TIMER_STOP,											/**< status stop */
		TIMER_RUNNINNG,										/**< status running */
		TIMER_PAUSED										/**< status paused */
	};

	TimerStatus _Status;									/**< timer's Status */
	unsigned int _TimePaused;								/**< time when pause timer */
	unsigned int _TimeInitial;								/**< time when start timer */
};


