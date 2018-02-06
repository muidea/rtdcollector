#include "rtdcollector/rtdCollector.h"
#include "eventLoop.h"
#include "util/thread.h"
#include "util/exception.h"
#include "dbuswrapper/endpoint.h"
#include "dbusmessage/rtdconfig.h"
#include "dbusmessage/rtddata.h"
#include "dbusmessage/rtdevent.h"
#include "dbusmessage/rtdmessage.h"
#include "rtd/protocol/message.h"
#include "rtd/protocol/rtdconfig.h"
#include "rtd/protocol/rtdvalue.h"
#include "rtd/protocol/rtdevent.h"
#include "rtd/protocol.h"
#include "tinyxml2/tinyxml2.h"
#include <memory>
#include <sstream>
#include <iostream>

namespace Rtd
{
	typedef std::shared_ptr<RtdDataVector> RtdDataVectorPtr;
	typedef std::shared_ptr<RtdEventVector> RtdEventVectorPtr;

	class RtdCollectorImpl : public RtdCollector, public DBusWrapper::EndPointCallBack
	{
	public:
		RtdCollectorImpl();

		virtual ~RtdCollectorImpl();

		void initialize(RtdCollectorSink *pSink);

		void uninitialize();

		bool start();

		void stop();

		void pushConfigInfo(ConfigInfo const &cfgInfo);

		void pushRtdData(RtdDataDeque const &rtdData);

		void pushRtdEvent(RtdEventDeque const &rtdEvent);

		// DBusWrapper::EndPointCallBack
		virtual void onMessage(DBusMessage* dbusMsg);

	protected:
		void pushRegisterInternal();
		void pushUnregisterInternal();
		void pushConfigInfoInternal(ConfigInfo const& cfgInfo);
		void pushRtdDataInternal(RtdDataVectorPtr ptr);
		void pushRtdEventInternal(RtdEventVectorPtr ptr);

	protected:
		RtdCollectorSink * m_pCollectorSink;

		std::string m_dbusName;
		std::string m_dbusInterface;
		std::string m_dbusPath;
		std::string m_collectorName;
		std::string m_endPointName;

		Util::UInt64 m_currentSerialNo;

		DBusWrapper::EndPoint* m_endPoint;

		Util::Thread m_eventLoopThread;
		EventLoop m_eventLoop;
	};

	RtdCollectorImpl::RtdCollectorImpl()
		: m_pCollectorSink(nullptr)
		, m_dbusName("com.supos.shuttle.drivermanager")
		, m_dbusInterface("com.supos.shuttle.driver")
		, m_collectorName("endpoint")
		, m_currentSerialNo(0)
		, m_endPoint(nullptr)
	{
		std::stringstream pathOss;
		pathOss << "/drivermanager/" << m_collectorName;
		m_dbusPath = pathOss.str();

		std::stringstream endPointOss;
		endPointOss << m_dbusName << "." << m_collectorName;
		m_endPointName = endPointOss.str();

	}

	RtdCollectorImpl::~RtdCollectorImpl()
	{
	}

	void RtdCollectorImpl::initialize(RtdCollectorSink *pSink)
	{
		m_pCollectorSink = pSink;

		m_endPoint = GetEndPoint(m_dbusInterface, this);

		m_endPoint->registerEndPoint(m_endPointName);
	}

	void RtdCollectorImpl::uninitialize()
	{
		m_endPoint->unregisterEndPoint();
		m_endPoint->release();
		m_endPoint = nullptr;

		m_pCollectorSink = nullptr;
	}

	bool RtdCollectorImpl::start()
	{
		m_eventLoop.start();

		m_eventLoopThread.start(m_eventLoop);

		auto eventFunc = std::bind(&RtdCollectorImpl::pushRegisterInternal, this);

		m_eventLoop.invoke(eventFunc);

		return true;
	}

	void RtdCollectorImpl::stop()
	{
		auto eventFunc = std::bind(&RtdCollectorImpl::pushUnregisterInternal, this);

		m_eventLoop.call(eventFunc);

		m_eventLoop.stop();

		try
		{
			m_eventLoopThread.join();
		}
		catch (Util::SyntaxException e)
		{
		}
	}

	void RtdCollectorImpl::pushConfigInfo(ConfigInfo const &cfgInfo)
	{
		auto eventFunc = std::bind(&RtdCollectorImpl::pushConfigInfoInternal, this, cfgInfo);

		m_eventLoop.invoke(eventFunc);
	}

	void RtdCollectorImpl::pushRtdData(RtdDataDeque const &rtdData)
	{
		RtdDataVectorPtr ptr(new RtdDataVector());
		ptr->reserve(rtdData.size());
		std::for_each(rtdData.begin(), rtdData.end(), [&](RtdData const& val) {
			ptr->push_back(val);
		});

		auto eventFunc = std::bind(&RtdCollectorImpl::pushRtdDataInternal, this, ptr);

		m_eventLoop.invoke(eventFunc);
	}

	void RtdCollectorImpl::pushRtdEvent(RtdEventDeque const &rtdEvent)
	{
		RtdEventVectorPtr ptr(new RtdEventVector());
		ptr->reserve(rtdEvent.size());
		std::for_each(rtdEvent.begin(), rtdEvent.end(), [&](RtdEvent const& val) {
			ptr->push_back(val);
		});

		auto eventFunc = std::bind(&RtdCollectorImpl::pushRtdEventInternal, this, ptr);

		m_eventLoop.invoke(eventFunc);
	}

	void RtdCollectorImpl::onMessage(DBusMessage* dbusMsg)
	{
		if (dbus_message_is_method_call(dbusMsg, m_dbusInterface.c_str(), "subscribe")) {
			Rtd::RtdTagDeque tagDeque;
			RtdDBus::decodeSubscribe(dbusMsg, tagDeque);
			if (m_pCollectorSink) {
				m_pCollectorSink->onSubscribe(tagDeque);
			}
		}
		else if (dbus_message_is_signal(dbusMsg, m_dbusInterface.c_str(), "unsubscribe")) {
			Rtd::RtdTagIDDeque idDeque;
			RtdDBus::decodeUnsubscribe(dbusMsg, idDeque);
			if (m_pCollectorSink) {
				//m_pCollectorSink->OnUnsubscribe(idDeque);
			}
		}
		else if (dbus_message_is_signal(dbusMsg, m_dbusInterface.c_str(), "reload")) {
			if (m_pCollectorSink) {
				m_pCollectorSink->onReload();
			}
		}
		else {
			if (dbusMsg != nullptr) {
				std::cout << "message path:" << dbus_message_get_path(dbusMsg) << std::endl;
				std::cout << "message type:" << dbus_message_get_type(dbusMsg) << std::endl;
				std::cout << "message sender:" << dbus_message_get_sender(dbusMsg) << std::endl;
				std::cout << "message signature:" << dbus_message_get_signature(dbusMsg) << std::endl;
			}
		}
	}

	void RtdCollectorImpl::pushRegisterInternal()
	{
		DBusMessage* msg = dbus_message_new_method_call(m_dbusName.c_str(), m_dbusPath.c_str(), m_dbusInterface.c_str(), "login");
		dbus_message_set_destination(msg, m_dbusName.c_str());

		if (m_endPoint) {
			m_endPoint->sendMessage(msg);
		}
	}

	void RtdCollectorImpl::pushUnregisterInternal()
	{
		DBusMessage* msg = dbus_message_new_method_call(m_dbusName.c_str(), m_dbusPath.c_str(), m_dbusInterface.c_str(), "logout");
		dbus_message_set_destination(msg, m_dbusName.c_str());

		if (m_endPoint) {
			m_endPoint->sendMessage(msg);
		}
	}

	void RtdCollectorImpl::pushConfigInfoInternal(ConfigInfo const& cfgInfo)
	{
		DBusMessage* msg = dbus_message_new_method_call(m_dbusName.c_str(), m_dbusPath.c_str(), m_dbusInterface.c_str(), "refreshtags");
		dbus_message_set_destination(msg, m_dbusName.c_str());

		RtdDBus::encodeRtdConfig(cfgInfo, msg);

		if (m_endPoint) {
			m_endPoint->sendMessage(msg);
		}
	}
	void RtdCollectorImpl::pushRtdDataInternal(RtdDataVectorPtr ptr)
	{
		DBusMessage* msg = dbus_message_new_signal(m_dbusPath.c_str(), m_dbusInterface.c_str(), "updatetagvalue");
		dbus_message_set_destination(msg, m_dbusName.c_str());

		RtdDBus::encodeRtdData(*ptr, msg);

		if (m_endPoint) {
			m_endPoint->postMessage(msg);
		}
	}
	void RtdCollectorImpl::pushRtdEventInternal(RtdEventVectorPtr ptr)
	{
		DBusMessage* msg = dbus_message_new_signal(m_dbusPath.c_str(), m_dbusInterface.c_str(), "updateevent");
		dbus_message_set_destination(msg, m_dbusName.c_str());

		RtdDBus::encodeRtdEvent(*ptr, msg);

		if (m_endPoint) {
			m_endPoint->postMessage(msg);
		}
	}
}

static Rtd::RtdCollectorImpl _impl;

Rtd::RtdCollector *GetCollector()
{
	return &_impl;
}
