// *****************************************************************
// This file is part of the CYBERMED Libraries
//
// Copyright (C) 2007 LabTEVE (http://www.de.ufpb.br/~labteve),
// Federal University of Paraiba and University of São Paulo.
// All rights reserved.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public
// License along with this program; if not, write to the Free
// Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
// Boston, MA 02110-1301, USA.
// *****************************************************************

#include "cybMulticastPeer.h"

CybMulticastPeer::CybMulticastPeer(const short multiPort, const char* group) : CybUDPServer(multiPort) {

	// Address for sending multicast data
	this->multiSock = new CybDatagramSock(); 
	this->multiAddr = new CybNodeAddress(multiPort, group, AF_INET);

	// Structure for joining into a multicast group
	this->multiReq.imr_interface.s_addr = htonl(INADDR_ANY);	
	this->multiReq.imr_multiaddr.s_addr = inet_addr(group);
}

void CybMulticastPeer::joinGroup() throw (CybMulticastException) {
	cout << "joining group..." << endl;
	setsockopt(this->multiSock->getSock(), IPPROTO_IP, IP_ADD_MEMBERSHIP, (void*) &multiReq, sizeof(multiReq));
}

void CybMulticastPeer::sendMulticastData(void* data, int size) throw (CybMulticastException)
{
    //cout << "sending data on server multicast..." << endl;	
    int result = 0;
    result = sendto(this->multiSock->getSock(), data, size, 0, (struct sockaddr *) this->multiAddr->getAddr(), this->multiAddr->getAddrSizeValue());
    if(result < 0) throw CybMulticastException(2);
}

void CybMulticastPeer::setLoopbackOption(int flag) {
	if (setsockopt(this->multiSock->getSock(), IPPROTO_IP, IP_MULTICAST_LOOP, &flag, sizeof(flag)) < 0) 
	   perror("Failed at setting multicast loopback interface!\n");		
}

void CybMulticastPeer::setTTL(int ttl) {
	if (setsockopt(this->multiSock->getSock(), IPPROTO_IP, IP_MULTICAST_TTL, (void*) &ttl, sizeof(ttl)) < 0) 
	   perror("Failed at setting ttl");
}

