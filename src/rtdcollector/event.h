#ifndef __EVENT_H_0907__
#define __EVENT_H_0907__
#include "util/refCountedObject.h"
#include "util/autoPtr.h"
#include "util/event.h"
#include <deque>
#include <functional>

namespace Rtd {

	class Event : public Util::RefCountedObject {
	public:
		Event() {}

		virtual void OnEvent() = 0;

	protected:
		virtual ~Event() {}
	};

	template <typename EventCall>
	class SyncEvent : public Event {
	public:
		SyncEvent(EventCall eventCall, Util::Event& event)
			: m_eventCall(eventCall)
			, m_syncEvent(event)
		{
		}

		virtual void OnEvent()
		{
			m_eventCall();
			m_syncEvent.set();
		}

	protected:
		EventCall m_eventCall;
		Util::Event& m_syncEvent;

	private:
		SyncEvent() {};
		~SyncEvent() {};
	};

	template <typename EventCall>
	class AsyncEvent : public Event {
	public:
		AsyncEvent(EventCall func)
			: m_eventCall(func)
		{
		}

		virtual void OnEvent()
		{
			m_eventCall();
		}

	protected:
		EventCall m_eventCall;
	};

	typedef Util::AutoPtr<Event> EventAutoPtr;
	typedef std::deque<EventAutoPtr> EventAutoPtrDeque;

}

#endif // __EVENT_H_0907__
