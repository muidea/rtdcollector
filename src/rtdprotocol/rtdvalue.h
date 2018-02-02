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
#ifndef __RTDVALUE_H_1517557968__
#define __RTDVALUE_H_1517557968__
#include "muprotocol/muprotocol.h"
#include "muprotocol/muserialize.h"
#include <string>
#include <vector>


namespace RtdPrococol {

class RtdTag : public IMUProtocol
{
public:
    RtdTag();

    virtual ~RtdTag();

    virtual bool encode(void* pBuffPtr, UINT32 uBuffSize, UINT32& uRemainSize) const;

    virtual bool decode(const void* pDataPtr, UINT32 uDataSize, UINT32& uRemainSize);

    virtual UINT32 calcSize() const;

    inline void setTagName(std::string const& value)
    {
        _tagName = value;
    };

    inline std::string const& getTagName() const
    {
        return _tagName;
    };

    inline std::string& peerTagName()
    {
        return _tagName;
    };

    inline void setTagID(UINT64 const& value)
    {
        _tagID = value;
    };

    inline UINT64 const& getTagID() const
    {
        return _tagID;
    };

    inline UINT64& peerTagID()
    {
        return _tagID;
    };

protected:
    bool operator==(RtdTag const& right);

    std::string _tagName;
    UINT64 _tagID;
};

class RtdValue : public IMUProtocol
{
public:
    RtdValue();

    virtual ~RtdValue();

    virtual bool encode(void* pBuffPtr, UINT32 uBuffSize, UINT32& uRemainSize) const;

    virtual bool decode(const void* pDataPtr, UINT32 uDataSize, UINT32& uRemainSize);

    virtual UINT32 calcSize() const;

    inline void setVt(UINT8 const& value)
    {
        _vt = value;
    };

    inline UINT8 const& getVt() const
    {
        return _vt;
    };

    inline UINT8& peerVt()
    {
        return _vt;
    };

    inline void setVal(DOUBLE const& value)
    {
        _val = value;
    };

    inline DOUBLE const& getVal() const
    {
        return _val;
    };

    inline DOUBLE& peerVal()
    {
        return _val;
    };

protected:
    bool operator==(RtdValue const& right);

    UINT8 _vt;
    DOUBLE _val;
};

class RtdData : public IMUProtocol
{
public:
    RtdData();

    virtual ~RtdData();

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

    inline void setQuality(UINT64 const& value)
    {
        _quality = value;
    };

    inline UINT64 const& getQuality() const
    {
        return _quality;
    };

    inline UINT64& peerQuality()
    {
        return _quality;
    };

    inline void setValue(RtdValue const& value)
    {
        _value = value;
    };

    inline RtdValue const& getValue() const
    {
        return _value;
    };

    inline RtdValue& peerValue()
    {
        return _value;
    };

protected:
    bool operator==(RtdData const& right);

    UINT64 _ownerID;
    UINT64 _timeStamp;
    UINT64 _quality;
    RtdValue _value;
};

typedef std::vector<RtdData> RtdDataVector;

class RtdDataInfo : public IMUProtocol
{
public:
    RtdDataInfo();

    virtual ~RtdDataInfo();

    virtual bool encode(void* pBuffPtr, UINT32 uBuffSize, UINT32& uRemainSize) const;

    virtual bool decode(const void* pDataPtr, UINT32 uDataSize, UINT32& uRemainSize);

    virtual UINT32 calcSize() const;

    inline void setDataVector(RtdDataVector const& value)
    {
        _dataVector = value;
    };

    inline RtdDataVector const& getDataVector() const
    {
        return _dataVector;
    };

    inline RtdDataVector& peerDataVector()
    {
        return _dataVector;
    };

protected:
    bool operator==(RtdDataInfo const& right);

    RtdDataVector _dataVector;
};


}

#endif
