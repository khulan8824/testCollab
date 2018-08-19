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

#ifndef BROADCAST_H_
#define BROADCAST_H_

//#include <inet/applications/base/ApplicationBase.h>
#include <inet/applications/udpapp/UDPBasicApp.h>

class Broadcast : public inet::UDPBasicApp {

protected:
    virtual int numInitStages() const override {
        return inet::NUM_INIT_STAGES;
    }

    void processStart() override;
    void sendPacket() override;

public:
    Broadcast(){}
    ~Broadcast(){
        cancelAndDelete(selfMsg);
    };
};


#endif /* BROADCAST_H_ */
