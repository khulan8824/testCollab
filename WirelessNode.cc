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
#include <algorithm>
#include <iostream>
#include <stdlib.h>


namespace inet {
    Define_Module(WirelessNode);
    cMessage *event;

    WirelessNode::WirelessNode(){
        event = nullptr;
        endTxEvent = nullptr;
    }

    WirelessNode::~WirelessNode(){
        delete lastPacket;
        cancelAndDelete(endTxEvent);
    }
    void WirelessNode::initialize(int stage) {
        x = par("x").doubleValue();
        y = par("y").doubleValue();

        EV<<"COMING"<<endl;
        numServers = par("numServers").intValue();

        getDisplayString().setTagArg("p", 0, x);
        getDisplayString().setTagArg("p", 1, y);

        stateSignal = registerSignal("state");
        state = IDLE;
        emit(stateSignal, state);
        pkCounter = 0;

        txRate = par("txRate");
        iaTime = &par("iaTime");
        pkLenBits = &par("pkLenBits");

        idleAnimationSpeed = par("idleAnimationSpeed");
        transmissionEdgeAnimationSpeed = par("transmissionEdgeAnimationSpeed");
        midtransmissionAnimationSpeed = par("midTransmissionAnimationSpeed");

        getDisplayString().setTagArg("p", 0, x);
        getDisplayString().setTagArg("p", 1, y);

        endTxEvent = new cMessage("send/endTx");

        if(endTxEvent->isScheduled()){
            cancelEvent(endTxEvent);
        }
        scheduleAt(getNextTransmissionTime(), endTxEvent);
    }

    bool WirelessNode::generateRandom(int range){
        choice1 = rand() % range;
        choice2 = rand()%range;
        if (choice1 == choice2) generateRandom(range);
        return true;
    }

    void WirelessNode::handleMessage(cMessage* msg) {
        ASSERT(msg == endTxEvent);
        if(msg->isSelfMessage()){
        getParentModule()->getCanvas()->setAnimationSpeed(transmissionEdgeAnimationSpeed, this);
        if (state == IDLE) {

            if(msg == endTxEvent){
            char pkname[40];
            sprintf(pkname, "pk-%d-#%d", getId(), pkCounter++);
            EV << "generating packet " << pkname <<endl;
            state = TRANSMIT;
            emit(stateSignal, state);

            cPacket *pk = new cPacket(pkname);
            pk->setBitLength(pkLenBits->intValue());

            simtime_t duration = pk->getBitLength() / txRate;

            generateRandom(numServers);
            EV<<"RANDOM:"<<choice1<<":"<<choice2<<endl;

            //rand() % len

            cModule *server1 = getParentModule()->getSubmodule("server", choice1);
            double serverX = server1->par("x").doubleValue();
            double serverY = server1->par("y").doubleValue();

            double dist = std::sqrt((x-serverX) * (x-serverX) + (y-serverY) * (y-serverY));
            radioDelay = dist/propagationSpeed;

            sendDirect(pk, radioDelay, duration, server1->gate("in"));


            cModule *server2 = getParentModule()->getSubmodule("server", choice2);
            serverX = server2->par("x").doubleValue();
            serverY = server2->par("y").doubleValue();

            dist = std::sqrt((x-serverX) * (x-serverX) + (y-serverY) * (y-serverY));
            radioDelay = dist/propagationSpeed;

            sendDirect(pk->dup(), radioDelay, duration, server2->gate("in"));

            if(endTxEvent->isScheduled()){
                cancelEvent(endTxEvent);
            }
            scheduleAt(simTime()+duration, endTxEvent);

            // let visualization code know about the new packet
            //if (transmissionRing != nullptr) {
            delete lastPacket;
            lastPacket = pk->dup();
            //}
            }
        }
        else if (state == TRANSMIT) {
               // endTxEvent indicates end of transmission
               state = IDLE;
               emit(stateSignal, state);
               if(endTxEvent->isScheduled()){
                               cancelEvent(endTxEvent);
               }
               scheduleAt(getNextTransmissionTime(), endTxEvent);
               // schedule next sending
               //scheduleAt(getNextTransmissionTime(), msg);
        }
        }
        else{
            cPacket *pkt = check_and_cast<cPacket *>(msg);
            EV << "Packet received:"<< pkt->getName()<<endl;
            delete pkt;
            //cancelEvent(endTxEvent);

            state = IDLE;
            emit(stateSignal, state);
        }

    }

    void WirelessNode::handleMessageWhenUp(cMessage* msg) {
        std::cout<<"Node is UP and working"<<endl;
    }

void WirelessNode::processStart() {
}

void WirelessNode::senseCloseNeighbors() {

}

void WirelessNode::sendCloseNeighbors(cPacket* packet) {

}

simtime_t WirelessNode::getNextTransmissionTime()
{
    simtime_t t = simTime() + iaTime->doubleValue()+30;
    return t;

}



    void WirelessNode::refreshDisplay() const
    {
        cCanvas *canvas = getParentModule()->getCanvas();
        const int numCircles = 20;
        const double circleLineWidth = 10;

        // create figures on our first invocation
        if (!transmissionRing) {
            auto color = cFigure::GOOD_DARK_COLORS[getId() % cFigure::NUM_GOOD_DARK_COLORS];

            transmissionRing = new cRingFigure(("Host" + std::to_string(getIndex()) + "Ring").c_str());
            transmissionRing->setOutlined(false);
            transmissionRing->setFillColor(color);
            transmissionRing->setFillOpacity(0.25);
            transmissionRing->setFilled(true);
            transmissionRing->setVisible(false);
            transmissionRing->setZIndex(-1);
            canvas->addFigure(transmissionRing);

            for (int i = 0; i < numCircles; ++i) {
                auto circle = new cOvalFigure(("Host" + std::to_string(getIndex()) + "Circle" + std::to_string(i)).c_str());
                circle->setFilled(false);
                circle->setLineColor(color);
                circle->setLineOpacity(0.75);
                circle->setLineWidth(circleLineWidth);
                circle->setZoomLineWidth(true);
                circle->setVisible(false);
                circle->setZIndex(-0.5);
                transmissionCircles.push_back(circle);
                canvas->addFigure(circle);
            }
        }

        if (lastPacket) {
            // update transmission ring and circles
            if (transmissionRing->getAssociatedObject() != lastPacket) {
                transmissionRing->setAssociatedObject(lastPacket);
                for (auto c : transmissionCircles)
                    c->setAssociatedObject(lastPacket);
            }

            simtime_t now = simTime();
            simtime_t frontTravelTime = now - lastPacket->getSendingTime();
            simtime_t backTravelTime = now - (lastPacket->getSendingTime() + lastPacket->getDuration());

            // conversion from time to distance in m using speed
            double frontRadius = std::min(ringMaxRadius, frontTravelTime.dbl() * propagationSpeed);
            double backRadius = backTravelTime.dbl() * propagationSpeed;
            double circleRadiusIncrement = circlesMaxRadius / numCircles;

            // update transmission ring geometry and visibility/opacity
            double opacity = 1.0;
            if (backRadius > ringMaxRadius) {
                transmissionRing->setVisible(false);
                transmissionRing->setAssociatedObject(nullptr);
            }
            else {
                transmissionRing->setVisible(true);
                transmissionRing->setBounds(cFigure::Rectangle(x - frontRadius, y - frontRadius, 2*frontRadius, 2*frontRadius));
                transmissionRing->setInnerRadius(std::max(0.0, std::min(ringMaxRadius, backRadius)));
                if (backRadius > 0)
                    opacity = std::max(0.0, 1.0 - backRadius / circlesMaxRadius);
            }

            transmissionRing->setLineOpacity(opacity);
            transmissionRing->setFillOpacity(opacity/5);

            // update transmission circles geometry and visibility/opacity
            double radius0 = std::fmod(frontTravelTime.dbl() * propagationSpeed, circleRadiusIncrement);
            for (int i = 0; i < (int)transmissionCircles.size(); ++i) {
                double circleRadius = std::min(ringMaxRadius, radius0 + i * circleRadiusIncrement);
                if (circleRadius < frontRadius - circleRadiusIncrement/2 && circleRadius > backRadius + circleLineWidth/2) {
                    transmissionCircles[i]->setVisible(true);
                    transmissionCircles[i]->setBounds(cFigure::Rectangle(x - circleRadius, y - circleRadius, 2*circleRadius, 2*circleRadius));
                    transmissionCircles[i]->setLineOpacity(std::max(0.0, 0.2 - 0.2 * (circleRadius / circlesMaxRadius)));
                }
                else
                    transmissionCircles[i]->setVisible(false);
            }

            // compute animation speed
            double animSpeed = idleAnimationSpeed;
            if ((frontRadius >= 0 && frontRadius < circlesMaxRadius) || (backRadius >= 0 && backRadius < circlesMaxRadius))
                animSpeed = transmissionEdgeAnimationSpeed;
            if (frontRadius > circlesMaxRadius && backRadius < 0)
                animSpeed = midtransmissionAnimationSpeed;
            canvas->setAnimationSpeed(animSpeed, this);
        }
        else {
            // hide transmission rings, update animation speed
            if (transmissionRing->getAssociatedObject() != nullptr) {
                transmissionRing->setVisible(false);
                transmissionRing->setAssociatedObject(nullptr);

                for (auto c : transmissionCircles) {
                    c->setVisible(false);
                    c->setAssociatedObject(nullptr);
                }
                canvas->setAnimationSpeed(idleAnimationSpeed, this);
            }
        }

        // update host appearance (color and text)
        getDisplayString().setTagArg("t", 2, "#808000");
        if (state == IDLE) {
            getDisplayString().setTagArg("i", 1, "");
            getDisplayString().setTagArg("t", 0, "");
        }
        else if (state == TRANSMIT) {
            getDisplayString().setTagArg("i", 1, "yellow");
            getDisplayString().setTagArg("t", 0, "TRANSMIT");
        }
    }

}
