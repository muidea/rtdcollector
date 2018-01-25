#ifndef __RTDINFO_1028_H__
#define __RTDINFO_1028_H__

#include <deque>
#include <vector>
#include "tinyxml2/tinyxml2.h"
#include "util/util.h"
#include "rtd/value.h"

namespace Rtd
{
	struct RtdTag
	{
		std::string tagName;
		Util::UInt64 tagID;

		RtdTag()
			: tagID(-1)
		{
		}

		RtdTag(RtdTag const& right)
			: tagName(right.tagName)
			, tagID(right.tagID)
		{
		}

		RtdTag& operator=(RtdTag const& right)
		{
			if (this != &right) {
				this->tagName = right.tagName;
				this->tagID = right.tagID;
			}

			return *this;
		}

		bool operator==(RtdTag const& right) const
		{
			return this->tagID == right.tagID;
		}
	};

	struct RtdData
	{
		Util::UInt64 ownerID;
		Util::UInt64 timeStamp;
		Util::UInt64 quality;
		Value value;

		RtdData(Util::UInt64 ownerID, Util::UInt64 timeStamp, Util::UInt64 quality, Value value)
			: ownerID(ownerID)
			, timeStamp(timeStamp)
			, quality(quality)
			, value(value)
		{
		}

		RtdData(RtdData const& right)
			: ownerID(right.ownerID)
			, timeStamp(right.timeStamp)
			, quality(right.quality)
			, value(right.value)
		{
		}

		RtdData& operator=(RtdData const& right)
		{
			if (this != &right) {
				this->ownerID = right.ownerID;
				this->timeStamp = right.timeStamp;
				this->quality = right.quality;
				this->value = right.value;
			}

			return *this;
		}
	};

	struct RtdEvent
	{
		Util::UInt64 ownerID;
		Util::UInt64 timeStamp;
		Util::UInt64 eventID;

		RtdEvent(RtdEvent const& right)
			:ownerID(right.ownerID)
			, timeStamp(right.timeStamp)
			, eventID(right.eventID)
		{
		}

		RtdEvent& operator=(RtdEvent const& right) {
			if (this != &right) {
				this->ownerID = right.ownerID;
				this->timeStamp = right.timeStamp;
				this->eventID = right.eventID;
			}
			return *this;
		}
	};

	// RtdTag
	typedef std::deque<RtdTag> RtdTagDeque;
	typedef std::deque<Util::UInt64> RtdTagIDDeque;
	// RtdCollector配置数据
	typedef tinyxml2::XMLDocument* ConfigInfo;
	// RtdCollector实时数据
	typedef std::deque<RtdData> RtdDataDeque;
	typedef std::vector<RtdData> RtdDataVector;
	// RtdCollector实时事件
	typedef std::deque<RtdEvent> RtdEventDeque;
	typedef std::vector<RtdEvent> RtdEventVector;
}
#endif // __RTDINFO_1028_H__