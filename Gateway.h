/*
 * Gateway.h
 *
 *  Created on: Aug 7, 2018
 *      Author: sysadmin-ingi
 */

#ifndef TESTCOLLAB_GATEWAY_H_
#define TESTCOLLAB_GATEWAY_H_
#include <omnetpp.h>
#include "inet/applications/base/ApplicationBase.h"
#include "WirelessNode.h"

namespace inet{
    class INET_API Gateway: public cSimpleModule{
        private:
           // state variables, event pointers
           bool channelBusy;
           cMessage *endRxEvent;
           cMessage *endReply;
           cModule *client;

           enum { IDLE = 0, TRANSMISSION = 1, COLLISION = 2 };

           simsignal_t channelStateSignal;
           simtime_t recvStartTime;
           simsignal_t receiveBeginSignal;
           simsignal_t receiveSignal;

           long receiveCounter;

        public:
            Gateway();
            virtual ~Gateway();
        protected:
            virtual void initialize() override;
            virtual void handleMessage(cMessage *msg) override;
            virtual void finish() override;
            virtual void refreshDisplay() const override;
    };
}



#endif /* TESTCOLLAB_GATEWAY_H_ */
