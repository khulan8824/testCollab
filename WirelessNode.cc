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



namespace inet {
    Define_Module(WirelessNode);

    WirelessNode::WirelessNode(){

        client = getModuleByPath("client2");
        std::cout<<client<<endl;

    }

    void WirelessNode::processStart() {
    }

    void WirelessNode::initialize(int stage) {
        x = par("x").doubleValue();
        y = par("y").doubleValue();
        getDisplayString().setTagArg("p", 0, x);
        getDisplayString().setTagArg("p", 1, y);
        senseCloseNeighbors();
    }

    void WirelessNode::handleMessage(cMessage* msg) {
        std::cout<<getIndex()<<endl;
        if(msg->isSelfMessage()){
            // Message arrived.
            EV << "Message " << msg << " arrived after \n";
            bubble("ARRIVED, starting new one!");
            delete msg;

            cMessage *newmsg = new cMessage("new message");
            int n = gateSize("gate");
            int k = intuniform(0, n-1);
        }
        else{
            std::cout<<"Coming this side"<<endl;
        }

    }

    void WirelessNode::handleMessageWhenUp(cMessage* msg) {

        std::cout<<"Node is UP and working"<<endl;
    }

    void WirelessNode::senseCloseNeighbors() {

    }

}
