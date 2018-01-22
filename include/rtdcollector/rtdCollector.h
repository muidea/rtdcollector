#ifndef __RTDCOLLECTOR_H_0947__
#define __RTDCOLLECTOR_H_0947__
#include "rtdInfo.h"

namespace Rtd
{

class RtdCollectorSink
{
public:
  virtual ~RtdCollectorSink(){};

  virtual void onReload();
};

class RtdCollector
{
public:
  RtdCollector(){};
  virtual ~RtdCollector(){};

  void initialize(RtdCollectorSink* pSink);

  void uninitialize();

  bool start();

  void stop();

  void pushConfigInfo(ConfigInfo const& cfgInfo);

  void pushRtdData(RtdDataVector const& rtdData);

  void pushRtdEvent(RtdEventVector const& rtdEvent);
};

}

Rtd::RtdCollector *GetCollector();

#endif // __RTDCOLLECTOR_H_0947__