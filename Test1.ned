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
import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.node.inet.INetworkNode;
import inet.physicallayer.contract.packetlevel.IRadioMedium;
import inet.physicallayer.ieee80211.packetlevel.Ieee80211ScalarRadioMedium;
import inet.visualizer.contract.IIntegratedVisualizer;
import inet.node.wireless.AccessPoint;
import inet.node.inet.WirelessHost;

network Testing
{
    parameters:
    	double txRate @unit(bps);  // transmission rate
    	double slotTime @unit(ms);  // zero means no slots (pure Aloha)    
    	int numHosts @int;
    	int numServers @int;
        @display("bgb=2000,2000;bgg=100,1,grey95");
        @figure[title](type=label; pos=0,-1; anchor=sw; color=darkblue);
    submodules:
        visualizer: <default("IntegratedCanvasVisualizer")> like IIntegratedVisualizer if hasVisualizer() {
            @display("p=925.688,226.90399");
        }
        configurator: Ipv4NetworkConfigurator {
            parameters:
                @display("p=100,250");
        }
        radioMedium: Ieee80211ScalarRadioMedium {
            parameters:
                @display("p=100,350");
        }
        client[numHosts]: WirelessNode {
            @display("p=345,90");
            txRate = txRate;
        }
        server[numServers]: Gateway{
            @display("p=205,69");
        }
      // connections:
        //   for i=0..numHosts-1{
          //     server.out[i] --> client[i].in;
           //}         
}


