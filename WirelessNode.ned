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

package testCollab;

import inet.node.inet.WirelessHost;
//
// TODO auto-generated module
//
module WirelessNode
{
    parameters:
        //int numApps = default(5);
    	@class(inet::WirelessNode);
    	@display("i=device/wifilaptop");
    	@signal[state](type="long");
        @statistic[radioState](source="state";title="Radio state";enum="IDLE=0,TRANSMIT=1";record=vector);
        
       
    	double x @unit(m);                 // the x coordinate of the host
        double y @unit(m);               // the y coordinate of the host
        double txRate @unit(bps);          // transmission rate
        volatile int pkLenBits @unit(b);   // packet length in bits
        volatile double iaTime @unit(s);   // packet interarrival time
        volatile int numServers @int;
        
        double idleAnimationSpeed;         // used when there is no packet being transmitted
        double transmissionEdgeAnimationSpeed; // used when the propagation of a first or last bit is visible
        double midTransmissionAnimationSpeed; // used during transmission
        bool controlAnimationSpeed = default(true);
    gates:
        input in @directIn;
        //output out @directOut;
    connections allowunconnected:
	    
}
