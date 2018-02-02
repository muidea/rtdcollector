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
#ifndef __MESSAGE_H_1517541490__
#define __MESSAGE_H_1517541490__
#include "muprotocol/muprotocol.h"
#include "muprotocol/muserialize.h"


namespace RtdPrococol {

struct Head
{
    UINT32 version;
    UINT64 messageCode;
    UINT64 serialNo;
};

inline UINT32 getSize(Head const& value)
{
    UINT32 uRet = sizeof(UINT32);

    uRet += MUPProtocol::getSize(value.version);
    uRet += MUPProtocol::getSize(value.messageCode);
    uRet += MUPProtocol::getSize(value.serialNo);
    return uRet;
};

inline bool encode(Head const& value, void* pBuffPtr, UINT32 uBuffSize, UINT32& uRemainSize)
{
    bool bRet = false;
    UINT32 uPacketSize = getSize(value);
    if (uBuffSize < uPacketSize) {
        return false;
    }
    uRemainSize = uBuffSize;
    bRet = MUPProtocol::encode(uPacketSize, (char*)pBuffPtr + uBuffSize - uRemainSize, uRemainSize, uRemainSize);
    if (!bRet) {
        return bRet;
    }

    bRet = MUPProtocol::encode(value.version, (char*)pBuffPtr + uBuffSize - uRemainSize, uRemainSize, uRemainSize);
    if (!bRet) {
        return bRet;
    }

    bRet = MUPProtocol::encode(value.messageCode, (char*)pBuffPtr + uBuffSize - uRemainSize, uRemainSize, uRemainSize);
    if (!bRet) {
        return bRet;
    }

    bRet = MUPProtocol::encode(value.serialNo, (char*)pBuffPtr + uBuffSize - uRemainSize, uRemainSize, uRemainSize);
    if (!bRet) {
        return bRet;
    }

    return bRet;
};

inline bool decode(const void* pDataPtr, UINT32 uDataSize, Head& value, UINT32& uRemainSize)
{
    bool bRet = false;
    UINT32 uPacketSize = 0;
    uRemainSize = uDataSize;
    bRet = MUPProtocol::decode((char*)pDataPtr + uDataSize - uRemainSize, uRemainSize, uPacketSize, uRemainSize);
    if (!bRet || (uPacketSize > uDataSize)) {
        return bRet;
    }

    bRet = MUPProtocol::decode((char*)pDataPtr + uDataSize - uRemainSize, uRemainSize, value.version, uRemainSize);
    if (!bRet) {
        return bRet;
    }

    bRet = MUPProtocol::decode((char*)pDataPtr + uDataSize - uRemainSize, uRemainSize, value.messageCode, uRemainSize);
    if (!bRet) {
        return bRet;
    }

    bRet = MUPProtocol::decode((char*)pDataPtr + uDataSize - uRemainSize, uRemainSize, value.serialNo, uRemainSize);
    if (!bRet) {
        return bRet;
    }

    uRemainSize = uDataSize - uPacketSize;
    return bRet;
};


}

#endif
