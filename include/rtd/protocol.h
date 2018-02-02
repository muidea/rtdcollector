#ifndef __PROTOCOL_H_1104__
#define __PROTOCOL_H_1104__
#include "muprotocol/muprotocolhelper.h"
#include "protocol/message.h"
#include "protocol/rtdconfig.h"
#include "protocol/rtdvalue.h"
#include "protocol/rtdevent.h"

namespace Rtd
{
    // 配置信息通知
    typedef MUPProtocol::PackHelper<RtdPrococol::Head, RtdPrococol::ConfigInfoEvent> RtdConfigNotify;
    // 实时数据通知
    typedef MUPProtocol::PackHelper<RtdPrococol::Head, RtdPrococol::RtdDataVector> RtdDataNotify;
    // 实时事件通知
    typedef MUPProtocol::PackHelper<RtdPrococol::Head, RtdPrococol::RtdEventVector> RtdEventNotify;
}


#endif //  __PROTOCOL_H_1104__

