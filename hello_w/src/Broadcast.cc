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

#include <Broadcast.h>

#include "inet/networklayer/common/L3AddressResolver.h"
//#include "inet/common/ModuleAccess.h"
#include "inet/transportlayer/contract/udp/UDPControlInfo_m.h"

Define_Module(Broadcast);

void Broadcast::processStart() {
    EV_INFO << "my.processStart()" << endl;
    socket.setOutputGate(gate("udpOut"));
    const char *localAddress = par("localAddress");
    socket.bind(
            *localAddress ?
                    inet::L3AddressResolver().resolve(localAddress) :
                    inet::L3Address(), localPort);

    UDPBasicApp::setSocketOptions();

    const char *destAddrs = par("destAddresses");
    inet::L3Address result;
    inet::L3AddressResolver().tryResolve(destAddrs, result);

    if (result.isUnspecified())
        EV_ERROR << "cannot resolve destination address: " << endl;
    else
        destAddresses.push_back(result);

    if (!destAddresses.empty()) {
        selfMsg->setKind(SEND);
        UDPBasicApp::processSend();
    } else {
        if (stopTime >= SIMTIME_ZERO) {
            selfMsg->setKind(STOP);
            scheduleAt(stopTime, selfMsg);
        }
    }
}

void Broadcast::sendPacket() {
    EV_INFO << "my.sendPacket()" << endl;
    std::ostringstream str;
    str << packetName << "-" << numSent;
    cPacket *payload = new cPacket(str.str().c_str());
    payload->setByteLength(par("messageLength").longValue());

    inet::L3Address destAddr = destAddresses[destAddresses.size() - 1];

    emit(sentPkSignal, payload);
    socket.sendTo(payload, destAddr, destPort);
    numSent++;
}
