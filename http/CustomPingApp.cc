/*
 * CustomPingApp.cc
 *
 *  Created on: Aug 1, 2018
 *      Author: sysadmin-ingi
 */

#include <omnetpp.h>
#include "CustomPingApp.h"
#include "inet/applications/pingapp/PingApp.h"

namespace inet{

Define_Module(CustomPingApp);

void CustomPingApp::initialize(int stage) {
    inet::PingApp::initialize(stage);

}

void CustomPingApp::handleMessage(cMessage* msg) {
    inet::PingApp::handleMessage(msg);
}

}
