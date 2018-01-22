#ifndef __RTDINFO_1028_H__
#define __RTDINFO_1028_H__

#include <vector>
#include "tinyxml2/tinyxml2.h"
#include "util/util.h"
#include "rtd/value.h"

namespace Rtd
{

struct RtdData
{
    Util::UInt64 ownerID;
    Util::UInt64 timeStamp;
    Util::UInt64 quality;
    Value value;
};

struct RtdEvent
{
    Util::UInt64 timeStamp;
    Util::UInt64 eventID;
};

// RtdCollector
typedef tinyxml2::XMLDocument ConfigInfo;
// RtdCollector实时数据
typedef std::vector<RtdData> RtdDataVector;
// RtdCollector实时事件
typedef std::vector<RtdEvent> RtdEventVector;
}
#endif // __RTDINFO_1028_H__