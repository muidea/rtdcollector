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

		_VALUE()
			: vt(ValueType_Null)
		{
		}

		_VALUE(_VALUE const& right)
			: vt(right.vt) 
		{
			switch (right.vt)
			{
			case ValueType_Bool:
				this->boolVal = right.boolVal;
				break;
			case ValueType_I1:
				this->i1Val = right.i1Val;
				break;
			case ValueType_I2:
				this->i2Val = right.i2Val;
				break;
			case ValueType_I4:
				this->i4Val = right.i4Val;
				break;
			case ValueType_UI1:
				this->ui1Val = right.ui1Val;
				break;
			case ValueType_UI2:
				this->ui2Val = right.ui2Val;
				break;
			case ValueType_UI4:
				this->ui4Val = right.ui4Val;
			case ValueType_UI8:
				this->ui8Val = right.ui8Val;
				break;
			case ValueType_Float:
				this->fltVal = right.fltVal;
				break;
			case ValueType_Double:
				this->dblVal = right.dblVal;
			default:
				break;
			}
		}

		_VALUE& operator=(_VALUE const& right) {
			if (&right != this) {
				switch (right.vt)
				{
				case ValueType_Bool:
					this->boolVal = right.boolVal;
					break;
				case ValueType_I1:
					this->i1Val = right.i1Val;
					break;
				case ValueType_I2:
					this->i2Val = right.i2Val;
					break;
				case ValueType_I4:
					this->i4Val = right.i4Val;
					break;
				case ValueType_UI1:
					this->ui1Val = right.ui1Val;
					break;
				case ValueType_UI2:
					this->ui2Val = right.ui2Val;
					break;
				case ValueType_UI4:
					this->ui4Val = right.ui4Val;
				case ValueType_UI8:
					this->ui8Val = right.ui8Val;
					break;
				case ValueType_Float:
					this->fltVal = right.fltVal;
					break;
				case ValueType_Double:
					this->dblVal = right.dblVal;
				default:
					break;
				}

				this->vt = right.vt;
			}

			return *this;
		}
	} Value;
}

#endif //  __VALUE_H_1534__
