#ifndef __PROTOCOL_H_1104__
#define __PROTOCOL_H_1104__
#include "muprotocol/muprotocolhelper.h"
#include "protocol/message.h"
#include "protocol/rtdconfig.h"
#include "protocol/rtdvalue.h"
#include "protocol/rtdevent.h"
#include "value.h"

namespace Rtd
{
    enum Version
    {
        Version_Base = 0x1000,
        Current_Verion = Version_Base
    };
    
    enum CommandCode
    {
        RTD_CONFIG_BASE = 0x10000000,
        RTD_CONFIG_NOTIFY,

        RTD_DATA_BASE = 0x10001000,
        RTD_DATA_NOTIFY,

        RTD_EVENT_BASE = 0x10002000,
        RTD_EVENT_NOTIFY,
    };

	void RtdValue2RtdProtocolValue(Rtd::Value const& val, RtdPrococol::RtdValue& v)
	{
		v.setVt(val.vt);

		switch (val.vt)
		{
		case ValueType_Bool:
			v.setVal(val.boolVal ? 1.0 : 0.0);
			break;
		case ValueType_I1:
			v.setVal((DOUBLE)val.i1Val);
			break;
		case ValueType_I2:
			v.setVal((DOUBLE)val.i2Val);
			break;
		case ValueType_I4:
			v.setVal((DOUBLE)val.i4Val);
			break;
		case ValueType_I8:
			v.setVal((DOUBLE)val.i8Val);
			break;
		case ValueType_UI1:
			v.setVal((DOUBLE)val.ui1Val);
			break;
		case ValueType_UI2:
			v.setVal((DOUBLE)val.ui2Val);
			break;
		case ValueType_UI4:
			v.setVal((DOUBLE)val.ui4Val);
			break;
		case ValueType_UI8:
			v.setVal((DOUBLE)val.ui8Val);
			break;
		case ValueType_Float:
			v.setVal((DOUBLE)val.fltVal);
			break;
		case ValueType_Double:
			v.setVal(val.dblVal);
			break;
		default:
			break;
		}
	}

	void RtdProtocolValue2RtdValue(RtdPrococol::RtdValue const& val, Rtd::Value& v)
	{
		v.vt = val.getVt();

		DOUBLE dblVal = val.getVal();
		switch (v.vt)
		{
		case ValueType_Bool:
			v.boolVal = dblVal != 0 ? true : false;
			break;
		case ValueType_I1:
			v.i1Val = (Util::Int8)dblVal;
			break;
		case ValueType_I2:
			v.i2Val = (Util::Int16)dblVal;
			break;
		case ValueType_I4:
			v.i4Val = (Util::Int32)dblVal;
			break;
		case ValueType_I8:
			v.i8Val = (Util::Int64)dblVal;
			break;
		case ValueType_UI1:
			v.ui1Val = (Util::UInt8)dblVal;
			break;
		case ValueType_UI2:
			v.ui2Val = (Util::UInt16)dblVal;
			break;
		case ValueType_UI4:
			v.ui4Val = (Util::UInt32)dblVal;
			break;
		case ValueType_UI8:
			v.ui8Val = (Util::UInt64)dblVal;
			break;
		case ValueType_Float:
			v.fltVal = (FLOAT)dblVal;
			break;
		case ValueType_Double:
			v.dblVal = dblVal;
			break;
		default:
			break;
		}
	}

    // 配置信息通知
    typedef typename MUPProtocol::PackHelper<RtdPrococol::Head, RtdPrococol::RtdConfigInfo> RtdConfigNotify;
    // 实时数据通知
	typedef typename MUPProtocol::PackHelper<RtdPrococol::Head, RtdPrococol::RtdDataInfo> RtdDataNotify;
    // 实时事件通知
	typedef typename MUPProtocol::PackHelper<RtdPrococol::Head, RtdPrococol::RtdEventInfo> RtdEventNotify;
}


#endif //  __PROTOCOL_H_1104__

