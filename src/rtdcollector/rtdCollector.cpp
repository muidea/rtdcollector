#include "rtdcollector/rtdCollector.h"
#include "eventLoop.h"
#include "util/thread.h"
#include "util/exception.h"
#include "dbuswrapper/endpoint.h"
#include "rtd/protocol/message.h"
#include "rtd/protocol/rtdconfig.h"
#include "rtd/protocol/rtdvalue.h"
#include "rtd/protocol/rtdevent.h"
#include "rtd/protocol.h"
#include "tinyxml2/tinyxml2.h"
#include <memory>
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
	void pushConfigInfoInternal(ConfigInfo const& cfgInfo);
	void pushRtdDataInternal(RtdDataVectorPtr ptr);
	void pushRtdEventInternal(RtdEventVectorPtr ptr);

protected:
	RtdCollectorSink * m_pCollectorSink;

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

void RtdCollectorImpl::pushConfigInfoInternal(ConfigInfo const& cfgInfo)
{
	RtdPrococol::Head head;
	head.setVersion(Rtd::Current_Verion);
	head.setCommandCode(Rtd::RTD_CONFIG_NOTIFY);
	head.setSerialNo(++m_currentSerialNo);

	RtdPrococol::RtdConfigInfo configInfo;
	tinyxml2::XMLPrinter printer;
	cfgInfo->Print(&printer);
	configInfo.setConfigInfo(printer.CStr());

	Rtd::RtdConfigNotify rtdConfigNotify(head, configInfo);

	Util::UInt32 totalSize = rtdConfigNotify.calcSize();
	Util::UInt32 remainSize = totalSize;
	char* pBuffPtr = new char[totalSize];
	rtdConfigNotify.encode(pBuffPtr, totalSize, remainSize);
	std::string data(pBuffPtr, totalSize);

	if (m_endPoint) {
		m_endPoint->sendMessage(data);
	}

	delete []pBuffPtr;
}
void RtdCollectorImpl::pushRtdDataInternal(RtdDataVectorPtr ptr)
{
	RtdPrococol::Head head;
	head.setVersion(Rtd::Current_Verion);
	head.setCommandCode(Rtd::RTD_DATA_NOTIFY);
	head.setSerialNo(++m_currentSerialNo);

	RtdPrococol::RtdDataInfo rtdData;
	RtdPrococol::RtdDataVector& dataVector = rtdData.peerDataVector();
	dataVector.reserve(ptr->size());
	for (auto iter = ptr->begin(); iter != ptr->end(); ++iter) {
		RtdPrococol::RtdData rt;
		rt.setOwnerID(iter->ownerID);
		rt.setTimeStamp(iter->timeStamp);
		rt.setQuality(iter->quality);

		RtdPrococol::RtdValue v;
		RtdValue2RtdProtocolValue(iter->value, v);
		rt.setValue(v);
		dataVector.push_back(rt);
	}

	Rtd::RtdDataNotify rtdDataNotify(head, rtdData);

	Util::UInt32 totalSize = rtdDataNotify.calcSize();
	Util::UInt32 remainSize = totalSize;
	char* pBuffPtr = new char[totalSize];
	rtdDataNotify.encode(pBuffPtr, totalSize, remainSize);
	std::string data(pBuffPtr, totalSize);

	if (m_endPoint) {
		m_endPoint->sendMessage(data);
	}

	delete[]pBuffPtr;
}
void RtdCollectorImpl::pushRtdEventInternal(RtdEventVectorPtr ptr)
{
	RtdPrococol::Head head;
	head.setVersion(Rtd::Current_Verion);
	head.setCommandCode(Rtd::RTD_EVENT_NOTIFY);
	head.setSerialNo(++m_currentSerialNo);

	RtdPrococol::RtdEventInfo rtdEvent;
	RtdPrococol::RtdEventVector& eventVector = rtdEvent.peerEventVector();
	eventVector.reserve(ptr->size());
	for (auto iter = ptr->begin(); iter != ptr->end(); ++iter) {
		RtdPrococol::RtdEvent rt;
		rt.setOwnerID(iter->ownerID);
		rt.setTimeStamp(iter->timeStamp);
		rt.setEventID(iter->eventID);

		eventVector.push_back(rt);
	}

	Rtd::RtdEventNotify rtdEventNotify(head, rtdEvent);

	Util::UInt32 totalSize = rtdEventNotify.calcSize();
	Util::UInt32 remainSize = totalSize;
	char* pBuffPtr = new char[totalSize];
	rtdEventNotify.encode(pBuffPtr, totalSize, remainSize);
	std::string data(pBuffPtr, totalSize);

	if (m_endPoint) {
		m_endPoint->sendMessage(data);
	}

	delete[]pBuffPtr;
}
}

static Rtd::RtdCollectorImpl _impl;

Rtd::RtdCollector *GetCollector()
{
    return &_impl;
}
