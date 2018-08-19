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

#ifndef __INET4_WIRELESSNODE_H_
#define __INET4_WIRELESSNODE_H_

#include <omnetpp.h>
#include "inet/applications/base/ApplicationBase.h"
//#include "inet/networklayer/contract/ipv4/Ipv4Address.h"



namespace inet {
class INET_API WirelessNode: public ApplicationBase{
    public:
        WirelessNode();
        ~WirelessNode();
        void processStart();
    private:
        std::set<cModule*> neighbours;
        cModule *client;
        double x, y; //position of the node
        int choice1, choice2;
        enum { IDLE = 0, TRANSMIT = 1, MEASURE=2 } state;
        simsignal_t stateSignal;
        simtime_t radioDelay;
        const double propagationSpeed = 299792458.0;

        int pkCounter;
        double txRate;
        cPar *iaTime;
        cPar *pkLenBits;

        int numServers;

        cMessage *endTxEvent;

        // animation parameters
        const double ringMaxRadius = 2000; // in m
        const double circlesMaxRadius = 1000; // in m
        double idleAnimationSpeed;
        double transmissionEdgeAnimationSpeed;
        double midtransmissionAnimationSpeed;

        // figures and animation state
        cPacket *lastPacket = nullptr; // a copy of the last sent message, needed for animation
        mutable cRingFigure *transmissionRing = nullptr; // shows the last packet
        mutable std::vector<cOvalFigure *> transmissionCircles; // ripples inside the packet ring


    protected:
        virtual void initialize(int stage) override;
        virtual void handleMessage(cMessage *msg) override;

        virtual void refreshDisplay() const override;
        virtual void handleMessageWhenUp(cMessage *msg) override;
        void senseCloseNeighbors();
        void sendCloseNeighbors(cPacket *packet);

        bool generateRandom(int range);

        simtime_t getNextTransmissionTime();

    };

}
#endif
