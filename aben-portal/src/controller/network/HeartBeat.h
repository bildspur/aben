//
// Created by Florian Bruggisser on 26.11.18.
//

#ifndef THREE_SCAN_HEARTBEAT_H
#define THREE_SCAN_HEARTBEAT_H


#include <util/Timer.h>
#include <controller/BaseController.h>
#include <functional>

class HeartBeat : public BaseController {
    Timer *beatTimer;

    typedef std::function<void()> HeartbeatHandler;
    HeartbeatHandler onHeartbeatCallback;


public:
    explicit HeartBeat(unsigned long beatTime);

    void setup() override;

    void loop() override;

    void onHeartbeat(HeartbeatHandler onHeartbeatCallback);
};


#endif //THREE_SCAN_HEARTBEAT_H
