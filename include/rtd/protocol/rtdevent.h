//
//
//    This software is provided 'as-is', without any express or implied
//    warranty. In no event will the authors be held liable for any
//    damages arising from the use of this software.
//
//    Generated by mupcompiler.
//
//    Author: muidea@gmail.com
//
//
#ifndef __RTDEVENT_H_1517557968__
#define __RTDEVENT_H_1517557968__
#include "muprotocol/muprotocol.h"
#include "muprotocol/muserialize.h"
#include <vector>


namespace RtdPrococol {

class RtdEvent : public IMUProtocol
{
public:
    RtdEvent();

    virtual ~RtdEvent();

    virtual bool encode(void* pBuffPtr, UINT32 uBuffSize, UINT32& uRemainSize) const;

    virtual bool decode(const void* pDataPtr, UINT32 uDataSize, UINT32& uRemainSize);

    virtual UINT32 calcSize() const;

    inline void setOwnerID(UINT64 const& value)
    {
        _ownerID = value;
    };

    inline UINT64 const& getOwnerID() const
    {
        return _ownerID;
    };

    inline UINT64& peerOwnerID()
    {
        return _ownerID;
    };

    inline void setTimeStamp(UINT64 const& value)
    {
        _timeStamp = value;
    };

    inline UINT64 const& getTimeStamp() const
    {
        return _timeStamp;
    };

    inline UINT64& peerTimeStamp()
    {
        return _timeStamp;
    };

    inline void setEventID(UINT64 const& value)
    {
        _eventID = value;
    };

    inline UINT64 const& getEventID() const
    {
        return _eventID;
    };

    inline UINT64& peerEventID()
    {
        return _eventID;
    };

protected:
    bool operator==(RtdEvent const& right);

    UINT64 _ownerID;
    UINT64 _timeStamp;
    UINT64 _eventID;
};

typedef std::vector<RtdEvent> RtdEventVector;

class RtdEventInfo : public IMUProtocol
{
public:
    RtdEventInfo();

    virtual ~RtdEventInfo();

    virtual bool encode(void* pBuffPtr, UINT32 uBuffSize, UINT32& uRemainSize) const;

    virtual bool decode(const void* pDataPtr, UINT32 uDataSize, UINT32& uRemainSize);

    virtual UINT32 calcSize() const;

    inline void setEventVector(RtdEventVector const& value)
    {
        _eventVector = value;
    };

    inline RtdEventVector const& getEventVector() const
    {
        return _eventVector;
    };

    inline RtdEventVector& peerEventVector()
    {
        return _eventVector;
    };

protected:
    bool operator==(RtdEventInfo const& right);

    RtdEventVector _eventVector;
};


}

#endif
