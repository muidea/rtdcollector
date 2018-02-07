#include "dbusmessage/rtdconfig.h"
#include "dbusmessage/rtddata.h"
#include "dbusmessage/rtdevent.h"
#include "tinyxml2/tinyxml2.h"
#include <dbus/dbus.h>
#include <iostream>

void testRtdConfig()
{
    tinyxml2::XMLDocument doc;
    doc.LoadFile("configInfo.xml");

    DBusMessage* msg = dbus_message_new_signal("/com/supos/shuttle/drivermanager", "com.supos.shuttle.drivermanager", "Test");
    RtdDBus::encodeRtdConfig(&doc, msg);

    tinyxml2::XMLDocument newDoc;
    tinyxml2::XMLDocument* pPtr = &newDoc;
    RtdDBus::decodeRtdConfig(msg, pPtr);

    newDoc.SaveFile("configInfo_new.xml");
}

void testRtdData()
{
    DBusMessage* msg = dbus_message_new_signal("/com/supos/shuttle/drivermanager", "com.supos.shuttle.drivermanager", "Test");

    Rtd::RtdDataVector rtdData;
    Rtd::RtdData rt1;
    rt1.ownerID = 1;
    rt1.timeStamp = 123456;
    rt1.quality = 0;
    rt1.value.vt = Rtd::ValueType_Double;
    rt1.value.dblVal = 32.123;
    rtdData.push_back(rt1);

    Rtd::RtdData rt2;
    rt2.ownerID = 2;
    rt2.timeStamp = 7890;
    rt2.quality = 0;
    rt2.value.vt = Rtd::ValueType_UI8;
    rt2.value.ui8Val = 64;
    rtdData.push_back(rt2);

    RtdDBus::encodeRtdData(rtdData, msg);

    Rtd::RtdDataVector newRtdData;
    RtdDBus::decodeRtdData(msg, newRtdData);
    if (newRtdData.size() != 2) {
        std::cout << "encodeRtdData failed" << std::endl;
    }

    Rtd::RtdData const& front = newRtdData.front();
    if (!(front == rt1)) {
        std::cout << "front != rt1" << std::endl;
    }
    Rtd::RtdData const& back = newRtdData.back();
    if (!(back == rt2)) {
        std::cout << "back != rt2" << std::endl;
    }

    std::cout << "front.value, type:" << (int)front.value.vt << ", value:" << front.value.dblVal << std::endl;

    dbus_message_unref(msg);
}

void testRtdEvent()
{    
    DBusMessage* msg = dbus_message_new_signal("/com/supos/shuttle/drivermanager", "com.supos.shuttle.drivermanager", "Test");

    Rtd::RtdEventVector rtdEvent;
    Rtd::RtdEvent rt1;
    rt1.ownerID = 1;
    rt1.timeStamp = 123456;
    rt1.eventID = 10;
    rtdEvent.push_back(rt1);

    Rtd::RtdEvent rt2;
    rt2.ownerID = 2;
    rt2.timeStamp = 7890;
    rt2.eventID = 20;
    rtdEvent.push_back(rt2);

    RtdDBus::encodeRtdEvent(rtdEvent, msg);

    Rtd::RtdEventVector newRtdEvent;
    RtdDBus::decodeRtdEvent(msg, newRtdEvent);
    if (newRtdEvent.size() != 2) {
        std::cout << "decodeRtdEvent failed" << std::endl;
    }

    Rtd::RtdEvent const& front = newRtdEvent.front();
    if (!(front == rt1)) {
        std::cout << "front != rt1" << std::endl;
    }
    Rtd::RtdEvent const& back = newRtdEvent.back();
    if (!(back == rt2)) {
        std::cout << "back != rt2" << std::endl;
    }

    dbus_message_unref(msg);
}

int main(int argc, char* argv[])
{
    testRtdConfig();

    testRtdData();

    testRtdEvent();

    return 0;
}

