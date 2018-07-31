//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "WirelessNode.h"
#include "inet/networklayer/configurator/ipv4/Ipv4FlatNetworkConfigurator.h"



namespace inet {
    Define_Module(WirelessNode);
    cMessage *event;

    WirelessNode::WirelessNode(){
        event = nullptr;

    }

    void WirelessNode::initialize(int stage) {
        cMessage *msg = new cMessage("event");
        x = par("x").doubleValue();
        y = par("y").doubleValue();
        getDisplayString().setTagArg("p", 0, x);
        getDisplayString().setTagArg("p", 1, y);
        msg->setKind(1);
        scheduleAt(0, msg);
    }

    void WirelessNode::handleMessage(cMessage* msg) {
           if(msg->isSelfMessage()){
                   if(msg->getKind() == 1){
                    EV << "Message " << msg << " arrived after \n";
                    cMessage *newmsg = new cMessage("new message");
                    for(int i=0; i<3; i++){
                        cModule *c6 = getParentModule()->getSubmodule("client", i);
                        sendDirect(newmsg->dup(), c6->gate("radioIn", 0));
                    }
                    delete newmsg;
               }
            }
            else{
                EV <<"COMING at this side";
                delete msg;
            }
    }

    void WirelessNode::handleMessageWhenUp(cMessage* msg) {
        std::cout<<"Node is UP and working"<<endl;
    }

    void WirelessNode::senseCloseNeighbors() {


    }

}
