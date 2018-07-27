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
#include "inet/networklayer/contract/ipv4/Ipv4Address.h"
#include "inet/node/inet/WirelessHost.h"


namespace inet {
typedef std::vector<std::set<inet::Ipv4Address>> IPSetList;
class INET_API WirelessNode: public ApplicationBase , WirelessHost{
    public:
        WirelessNode();
        void processStart();
        std::set<inet::Ipv4Address> getNeighbors(inet::Ipv4Address addr);
        std::set<inet::Ipv4Address> getNeighbors(inet::Ipv4Address, unsigned);
    protected:
        virtual void initialize(int stage) override;
        virtual void handleMessage(cMessage *msg) override;
        virtual void handleMessageWhenUp(cMessage *msg) override;

    };
}
#endif
