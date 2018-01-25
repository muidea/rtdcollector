#include "eventLoop.h"
#include "util/exception.h"
#include "util/scopedLock.h"
#include <iostream>

namespace Rtd {
	const int WaitEventTimeOutValue = 5000;

	EventLoop::EventLoop()
		: m_eventSignal(false)
		, m_eventloopStatus(INVALID_STATUS)
	{
	}

	EventLoop::~EventLoop()
	{

	}

	void EventLoop::start() 
	{
		m_eventloopStatus = STARTING_STATUS;
	}

	void EventLoop::stop()
	{
		m_eventloopStatus = STOPING_STATUS;

		EventFunc eventFunc = std::bind(&EventLoop::stopInternal, this);

		call(eventFunc);

		m_eventloopStatus = INVALID_STATUS;
	}

	void EventLoop::invoke(EventFunc func)
	{
		EventAutoPtr ptr(new AsyncEvent<EventFunc>(func));

		{
			Util::ScopedLock<Util::FastMutex> guard(m_eventAutoPtrMutex);
			m_eventAutoPtrDeque.push_back(ptr);
		}

		m_eventSignal.set();
	}

	void EventLoop::call(EventFunc func)
	{
		Util::Event waitEvent(false);
		EventAutoPtr ptr(new SyncEvent<EventFunc>(func, waitEvent));

		{
			Util::ScopedLock<Util::FastMutex> guard(m_eventAutoPtrMutex);
			m_eventAutoPtrDeque.push_back(ptr);
		}

		m_eventSignal.set();
		waitEvent.wait();
	}

	void EventLoop::run()
	{
		m_eventloopStatus = RUNNING_STATUS;

		while (isRunning())
		{
			try
			{
				m_eventSignal.wait(WaitEventTimeOutValue);
			}
			catch (Util::TimeoutException e)
			{
				dispatchTimeout();

				continue;
			}
			catch (Util::Exception e)
			{
				break;
			}

			dispatchEvent();
		}

		dispatchEvent();

		m_eventSignal.reset();
	}

	void EventLoop::stopInternal()
	{
		m_eventloopStatus = STOPPED_STATUS;
	}

	void EventLoop::dispatchTimeout()
	{
	}

	void EventLoop::dispatchEvent()
	{
		EventAutoPtrDeque tempDeque;
		{
			Util::ScopedLock<Util::FastMutex> guard(m_eventAutoPtrMutex);
			tempDeque.swap(m_eventAutoPtrDeque);
		}

		std::for_each(tempDeque.begin(), tempDeque.end(), [](EventAutoPtr ptr) {
			ptr->OnEvent();
		});
	}
}

