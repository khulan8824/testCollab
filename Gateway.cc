/*
 * Gateway.cc
 *
 *  Created on: Aug 7, 2018
 *      Author: sysadmin-ingi
 */



#include "Gateway.h"

namespace inet{

    Define_Module(Gateway);
    Gateway::Gateway(){
        endRxEvent = nullptr;
    }

    Gateway::~Gateway(){
        cancelAndDelete(endRxEvent);
    }

    void Gateway::initialize() {

        channelStateSignal = registerSignal("channelState");
        endRxEvent = new cMessage("end-reception");
        channelBusy = false;
        emit(channelStateSignal, IDLE);

        gate("in")->setDeliverOnReceptionStart(true);

        getDisplayString().setTagArg("p", 0, par("x").doubleValue());
        getDisplayString().setTagArg("p", 1, par("y").doubleValue());


    }

    void Gateway::handleMessage(cMessage* msg) {
        cPacket *pkt, *resendPkt;
        if (msg == endRxEvent) {
                channelBusy = false;
                emit(channelStateSignal, IDLE);
                //send(endRxEvent,  gate("out$o",0));
                // update statistics
                simtime_t dt = simTime() - recvStartTime;
                resendPkt =  new cPacket("endReception");
                resendPkt->setBitLength(952);

                EV << "reception finished:"<<(resendPkt==nullptr)<<":"<<dt<<"\n";
                receiveCounter = 0;

                sendDirect(resendPkt, client->gate("in"));
                //emit(receiveBeginSignal, receiveCounte);
            }
            else {
                pkt = check_and_cast<cPacket *>(msg);
                resendPkt = pkt->dup();

                ASSERT(pkt->isReceptionStart());
                simtime_t endReceptionTime = simTime() + pkt->getDuration();

                //emit(receiveBeginSignal, ++receiveCounter);

                if (!channelBusy) {
                    EV << "started receiving\n";
                    recvStartTime = simTime();
                    channelBusy = true;
                    emit(channelStateSignal, TRANSMISSION);
                    scheduleAt(endReceptionTime, endRxEvent);
                }
                else {
                    EV << "another frame arrived while receiving -- collision!\n";
                    emit(channelStateSignal, COLLISION);

                    //if (currentCollisionNumFrames == 0)
                    //    currentCollisionNumFrames = 2;
                    //else
                    //    currentCollisionNumFrames++;

                    //if (endReceptionTime > endRxEvent->getArrivalTime()) {
                    //     cancelEvent(endRxEvent);
                    //     scheduleAt(endReceptionTime, endRxEvent);
                    //}

                    // update network graphics
                    //if (hasGUI()) {
                    //    char buf[32];
                    //    sprintf(buf, "Collision! (%ld frames)", currentCollisionNumFrames);
                    //    bubble(buf);
                        //getParentModule()->getCanvas()->holdSimulationFor(par("animationHoldTimeOnCollision"));
                    ///}
                }
                channelBusy = true;
                client = getModuleByPath(pkt->getSenderModule()->getFullName());
                //int size = this->gateSize("out");
                /*char* gatename ="";
                sprintf(gatename, "out[%d]",size);
                this->addGate(gatename, cGate::OUTPUT, true);
                cGate* out = gate("out", size);*/


                //cMessage* msg = new cMessage("end-reception");

                //int id =pkt->getSenderModule()->getIndex();

                //this->deleteGate("out");

                //send(msg,"out",id);

            }
    }

    void Gateway::finish() {
        //delete pkt;
        EV << "duration: " << simTime() << endl;
        recordScalar("duration", simTime());
    }

    void Gateway::refreshDisplay() const {
        if (!channelBusy) {
                getDisplayString().setTagArg("i2", 0, "status/off");
                getDisplayString().setTagArg("t", 0, "");
            }
    }

}
