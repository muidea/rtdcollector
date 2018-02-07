#ifndef __RTDCOLLECTOR_H_0947__
#define __RTDCOLLECTOR_H_0947__
#include "def.h"
#include "rtd/rtdInfo.h"

namespace Rtd
{

class RtdCollectorSink
{
public:
  virtual ~RtdCollectorSink(){};

  virtual void onSubscribe(RtdTagDeque const& tags) = 0;

  virtual void OnUnsubscribe(RtdTagIDDeque const& tags) = 0;

  virtual void onReload() = 0;
};

class RtdCollector
{
public:
  RtdCollector(){};
  virtual ~RtdCollector(){};

  virtual bool initialize(RtdCollectorSink *pSink) = 0;

  virtual void uninitialize() = 0;

  virtual bool start() = 0;

  virtual void stop() = 0;

  virtual void pushConfigInfo(ConfigInfo const &cfgInfo) = 0;

  virtual void pushRtdData(RtdDataDeque const &rtdData) = 0;

  virtual void pushRtdEvent(RtdEventDeque const &rtdEvent) = 0;
};
}

RtdCollector_API Rtd::RtdCollector* GetCollector();

#endif // __RTDCOLLECTOR_H_0947__