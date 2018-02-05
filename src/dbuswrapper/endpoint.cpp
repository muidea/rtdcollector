#include "dbuswrapper/endpoint.h"
#include "dbuswrapper.h"
#include "util/runnable.h"
#include "util/thread.h"
#include "util/event.h"
#include <iostream>

namespace DBusWrapper
{
	const int WaitEventTimeOutValue = 100;

	class EndPointImpl 
		: public EndPoint
		, public Util::Runnable
		, protected DBusWrapperSink
	{
	public:
		EndPointImpl(std::string const& interface, EndPointCallBack* pCallBack);

		virtual ~EndPointImpl();

		virtual void registerEndPoint(std::string const& endPointName);

		virtual void unregisterEndPoint();

		virtual void postMessage(DBusMessage* dbusMsg);

		virtual void sendMessage(DBusMessage* dbusMsg);

		virtual void run();
		
		virtual void release();

	protected:
		bool isRunning() { return RUNNING_STATUS == m_eventloopStatus; }

		virtual void onRecvMessage(DBusMessage* dbusMsg);

	protected:
		DBusWrapper m_dbusWrapper;
		Util::Thread m_thread;

		enum EventLoopStatus
		{
			INVALID_STATUS = 0,
			STARTING_STATUS,
			RUNNING_STATUS,
			STOPING_STATUS,
			STOPPED_STATUS
		};

		volatile int m_eventloopStatus;
		Util::Event m_eventSignal;

		EndPointCallBack * m_pCallBack;
	};


	EndPointImpl::EndPointImpl(std::string const& interface, EndPointCallBack* pCallBack)
		: m_dbusWrapper(interface, this)
		, m_pCallBack(pCallBack)
		, m_eventloopStatus(INVALID_STATUS)
	{
	}

	EndPointImpl::~EndPointImpl()
	{
	}

	void EndPointImpl::registerEndPoint(std::string const& endPointName)
	{
		std::cout << "registerEndPoint" << std::endl;

		m_dbusWrapper.initialize(endPointName);

		if (m_pCallBack) {
			m_eventloopStatus = STARTING_STATUS;
			m_thread.start(*this);
		}
	}

	void EndPointImpl::unregisterEndPoint()
	{
		std::cout << "unregisterEndPoint" << std::endl;

		m_dbusWrapper.uninitialize();

		if (m_pCallBack) {
			m_eventloopStatus = STOPING_STATUS;
			m_thread.join();
			m_eventloopStatus = INVALID_STATUS;
		}
	}

	void EndPointImpl::sendMessage(DBusMessage* dbusMsg)
	{
		m_dbusWrapper.sendMessage(dbusMsg);
	}

	void EndPointImpl::postMessage(DBusMessage* dbusMsg)
	{
		m_dbusWrapper.postMessage(dbusMsg);
	}

	void EndPointImpl::run()
	{
		m_eventloopStatus = RUNNING_STATUS;
		while (isRunning())
		{
			if (!m_dbusWrapper.isAvailable()) {
				std::cout << "dbus isn\'t available" << std::endl;
				break;
			}

			if (!m_dbusWrapper.recvMessage()) {
				try {
					m_eventSignal.wait(WaitEventTimeOutValue);
				} catch (Util::TimeoutException e)
				{
				}
			}
		}
	}

	void EndPointImpl::onRecvMessage(DBusMessage* dbusMsg)
	{
		if (m_pCallBack) {
			m_pCallBack->onMessage(dbusMsg);
		}
	}

	void EndPointImpl::release()
	{
		delete this;
	}
}

DBusWrapper::EndPoint* GetEndPoint(std::string const& interface, DBusWrapper::EndPointCallBack* pCallBack)
{
	DBusWrapper::EndPoint* pPtr = new DBusWrapper::EndPointImpl(interface, pCallBack);

	return pPtr;
}
