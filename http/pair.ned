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

package testCollab.http;

import inet.applications.httptools.configurator.HttpController;
import inet.node.httptools.DirectHost;


//
// Simple scenario with a pair of nodes. Direct message passing used.
//
network HttpDirectPair
{
    parameters:
    submodules:
        httpController: HttpController {
            parameters:
                @display("is=s;p=100,100;i=block/cogwheel");
        }
        srv1: WNode {
            parameters:
                @display("p=234,194;i=device/server");
        }

        srv2: WNode {
            parameters:
                @display("p=255,80;i=device/server");

        }
        cli1: WNode {
            parameters:
                @display("p=369,100;i=device/laptop");
        }

        cli2: WNode {
            parameters:
                @display("p=369,236;i=device/laptop");
        }
        cli3: WNode {
            parameters:
                @display("p=432,31;i=device/laptop");
        }
        cli4: WNode {
            parameters:
                @display("p=448,151;i=device/laptop");
        }
    connections allowunconnected:
}

