/*
 * CustomHttpServerDirect.cc
 *
 *  Created on: Aug 1, 2018
 *      Author: sysadmin-ingi
 */

#include <omnetpp.h>
#include "CustomHttpServerDirect.h"

namespace inet{

Define_Module(CustomHttpServerDirect);

void CustomHttpServerDirect::initialize()
{

}

void CustomHttpServerDirect::handleMessage(cMessage *msg)
{
    EV_INFO<<"COMING AT LAST"<<endl;
    inet::httptools::HttpServerDirect::handleMessage(msg);
}

}
