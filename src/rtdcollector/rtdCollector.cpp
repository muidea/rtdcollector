#include "rtdcollector/rtdCollector.h"
#include "eventLoop.h"
#include "util/thread.h"
#include "util/exception.h"
#include "dbuswrapper/endpoint.h"
#include "dbusmessage/rtdconfig.h"
#include "dbusmessage/rtddata.h"
#include "dbusmessage/rtdevent.h"
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
	virtual void onMessage(DBusWrapper::Message const& msg);
	
protected:
	void pushRegisterInternal();
	void pushUnregisterInternal();
	void pushConfigInfoInternal(ConfigInfo const& cfgInfo);
	void pushRtdDataInternal(RtdDataVectorPtr ptr);
	void pushRtdEventInternal(RtdEventVectorPtr ptr);

protected:
	RtdCollectorSink * m_pCollectorSink;

	std::string m_collectorName;

	Util::UInt64 m_currentSerialNo;

	DBusWrapper::EndPoint* m_endPoint;

	Util::Thread m_eventLoopThread;
	EventLoop m_eventLoop;
};

RtdCollectorImpl::RtdCollectorImpl()
	: m_pCollectorSink(nullptr)
	, m_currentSerialNo(0)
	, m_endPoint(nullptr)
{
}

RtdCollectorImpl::~RtdCollectorImpl()
{
}

void RtdCollectorImpl::initialize(RtdCollectorSink *pSink)
{
	m_pCollectorSink = pSink;

	m_endPoint = GetEndPoint("com.supos.shuttle.drivermanager", this);

	m_endPoint->registerEndPoint("com.supos.shuttle.drivermanager.endpoint");
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

    return true;
}

void RtdCollectorImpl::stop()
{
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

void RtdCollectorImpl::onMessage(DBusWrapper::Message const & msg)
{

}

void RtdCollectorImpl::pushRegisterInternal()
{
	std::stringstream oss;
	oss << "/com/supos/shuttle/drivermanager/" << m_collectorName;
	DBusMessage* msg = dbus_message_new_method_call("com.supos.shuttle.drivermanager", oss.str().c_str(), "com.supos.shuttle.drivermanager", "register");

	if (m_endPoint) {
		m_endPoint->sendMessage(msg);
	}

	dbus_message_unref(msg);
}

void RtdCollectorImpl::pushUnregisterInternal()
{
	std::stringstream oss;
	oss << "/com/supos/shuttle/drivermanager/" << m_collectorName;
	DBusMessage* msg = dbus_message_new_method_call("com.supos.shuttle.drivermanager", oss.str().c_str(), "com.supos.shuttle.drivermanager", "unregister");

	if (m_endPoint) {
		m_endPoint->sendMessage(msg);
	}

	dbus_message_unref(msg);
}

void RtdCollectorImpl::pushConfigInfoInternal(ConfigInfo const& cfgInfo)
{
	DBusMessage* msg = dbus_message_new_signal("/com/supos/shuttle/drivermanager", "com.supos.shuttle.drivermanager", "updateConfig");
	RtdDBus::encodeRtdConfig(cfgInfo, msg);

	if (m_endPoint) {
		m_endPoint->postMessage(msg);
	}

	dbus_message_unref(msg);
}
void RtdCollectorImpl::pushRtdDataInternal(RtdDataVectorPtr ptr)
{
	DBusMessage* msg = dbus_message_new_signal("/com/supos/shuttle/drivermanager", "com.supos.shuttle.drivermanager", "updateRtdData");
	RtdDBus::encodeRtdData(*ptr, msg);

	if (m_endPoint) {
		m_endPoint->postMessage(msg);
	}

	dbus_message_unref(msg);
}
void RtdCollectorImpl::pushRtdEventInternal(RtdEventVectorPtr ptr)
{
	DBusMessage* msg = dbus_message_new_signal("/com/supos/shuttle/drivermanager", "com.supos.shuttle.drivermanager", "updateRtdEvent");
	RtdDBus::encodeRtdEvent(*ptr, msg);

	if (m_endPoint) {
		m_endPoint->postMessage(msg);
	}

	dbus_message_unref(msg);
}
}

static Rtd::RtdCollectorImpl _impl;

Rtd::RtdCollector *GetCollector()
{
    return &_impl;
}
