#ifndef __VALUE_H_1534__
#define __VALUE_H_1534__
#include "util/util.h"

namespace Rtd
{

enum ValueType
{
    ValueType_Empty = 0,
    ValueType_Null,
    ValueType_Bool,
    ValueType_I1,
    ValueType_I2,
    ValueType_I4,
    ValueType_I8,
    ValueType_UI1,
    ValueType_UI2,
    ValueType_UI4,
    ValueType_UI8,
    ValueType_Float,
    ValueType_Double,
    ValueType_Bstr,
    ValueType_Blob,
    ValueType_DateTime,
    ValueType_SafeArray,
    ValueType_Object,
};

typedef struct _VALUE
{
    Util::UInt8 vt;
    union {
        bool boolVal;
        Util::Int8 i1Val;
        Util::Int16 i2Val;
        Util::Int32 i4Val;
        Util::Int64 i8Val;
        Util::UInt8 ui1Val;
        Util::UInt16 ui2Val;
        Util::UInt32 ui4Val;
        Util::UInt64 ui8Val;
        float fltVal;
        double dblVal;
    };
} Value;
}

#endif //  __VALUE_H_1534__
