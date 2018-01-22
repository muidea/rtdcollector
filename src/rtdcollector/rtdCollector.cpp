#include "rtdcollector/rtdCollector.h"

namespace Rtd
{

class RtdCollectorImpl : public RtdCollector
{
  public:
	RtdCollectorImpl();

    virtual ~RtdCollectorImpl();

    void initialize(RtdCollectorSink *pSink);

    void uninitialize();

    bool start();

    void stop();

    void pushConfigInfo(ConfigInfo const &cfgInfo);

    void pushRtdData(RtdDataVector const &rtdData);

    void pushRtdEvent(RtdEventVector const &rtdEvent);
};

RtdCollectorImpl::RtdCollectorImpl()
{
}

RtdCollectorImpl::~RtdCollectorImpl()
{
}

void RtdCollectorImpl::initialize(RtdCollectorSink *pSink)
{
}

void RtdCollectorImpl::uninitialize()
{
}

bool RtdCollectorImpl::start()
{
    return true;
}

void RtdCollectorImpl::stop()
{
}

void RtdCollectorImpl::pushConfigInfo(ConfigInfo const &cfgInfo)
{
}

void RtdCollectorImpl::pushRtdData(RtdDataVector const &rtdData)
{
}

void RtdCollectorImpl::pushRtdEvent(RtdEventVector const &rtdEvent)
{
}
}

static Rtd::RtdCollectorImpl _impl;

Rtd::RtdCollector *GetCollector()
{
    return &_impl;
}
