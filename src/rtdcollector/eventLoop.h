#ifndef __EVENTLOOP_H_1637__
#define __EVENTLOOP_H_1637__
#include "util/runnable.h"
#include "util/event.h"
#include "util/mutex.h"
#include "event.h"
#include <functional>

namespace Rtd {
	typedef std::function<void()> EventFunc;

	class EventLoop : public Util::Runnable {

	public:
		EventLoop();

		~EventLoop();

		void start();

		void stop();

		void invoke(EventFunc func);

		void call(EventFunc func);

		virtual void run();

	protected:
		void stopInternal();

		void dispatchTimeout();

		void dispatchEvent();

		bool isRunning() { return RUNNING_STATUS == m_eventloopStatus; }


	protected:
		enum EventLoopStatus
		{
			INVALID_STATUS = 0,
			STARTING_STATUS,
			RUNNING_STATUS,
			STOPING_STATUS,
			STOPPED_STATUS
		};

		Util::Event m_eventSignal;
		volatile int m_eventloopStatus;

		EventAutoPtrDeque m_eventAutoPtrDeque;
		Util::FastMutex m_eventAutoPtrMutex;
	};

}

#endif // __EVENTLOOP_H_1637__
