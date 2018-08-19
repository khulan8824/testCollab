/*
 * CustomPingApp.h
 *
 *  Created on: Aug 1, 2018
 *      Author: sysadmin-ingi
 */

#ifndef TESTCOLLAB_HTTP_CUSTOMPINGAPP_H_
#define TESTCOLLAB_HTTP_CUSTOMPINGAPP_H_

#include<omnetpp.h>

#include "inet/applications/pingapp/PingApp.h"

namespace inet{
    class INET_API CustomPingApp: public inet::PingApp{
    protected:
        virtual void initialize(int stage) override;
        virtual void handleMessage(cMessage *msg) override;
    };
}

#endif /* TESTCOLLAB_HTTP_CUSTOMPINGAPP_H_ */
