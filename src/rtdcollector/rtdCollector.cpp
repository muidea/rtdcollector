#include "rtdcollector/rtdCollector.h"
#include "eventLoop.h"
#include "util/thread.h"
#include "util/exception.h"
#include "dbuswrapper/endpoint.h"
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

	Util::Thread m_eventLoopThread;
	EventLoop m_eventLoop;
};

RtdCollectorImpl::RtdCollectorImpl()
	: m_pCollectorSink(nullptr)
{
}

RtdCollectorImpl::~RtdCollectorImpl()
{
}

void RtdCollectorImpl::initialize(RtdCollectorSink *pSink)
{
	m_pCollectorSink = pSink;
}

void RtdCollectorImpl::uninitialize()
{
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
	std::cout << "pushConfigInfoInternal" << std::endl;
}
void RtdCollectorImpl::pushRtdDataInternal(RtdDataVectorPtr ptr)
{
	std::cout << "pushRtdDataInternal" << std::endl;
}
void RtdCollectorImpl::pushRtdEventInternal(RtdEventVectorPtr ptr)
{
	std::cout << "pushRtdEventInternal" << std::endl;
}
}

static Rtd::RtdCollectorImpl _impl;

Rtd::RtdCollector *GetCollector()
{
    return &_impl;
}
