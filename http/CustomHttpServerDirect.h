/*
 * CustomHttpServerDirect.h
 *
 *  Created on: Aug 1, 2018
 *      Author: sysadmin-ingi
 */

#ifndef TESTCOLLAB_HTTP_CUSTOMHTTPSERVERDIRECT_H_
#define TESTCOLLAB_HTTP_CUSTOMHTTPSERVERDIRECT_H_

#include <omnetpp.h>
#include "inet/applications/httptools/server/HttpServerDirect.h"

namespace inet {

class INET_API CustomHttpServerDirect : public inet::httptools::HttpServerDirect{
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

}


#endif /* TESTCOLLAB_HTTP_CUSTOMHTTPSERVERDIRECT_H_ */
