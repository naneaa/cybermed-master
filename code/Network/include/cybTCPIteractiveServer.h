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

#ifndef _CYBTCPITERACTIVESERVER_H
#define	_CYBTCPITERACTIVESERVER_H

#include "cybTCPServer.h"

class CybTCPIteractiveServer: public CybTCPServer
{
public:
    /** Constructor */
	CybTCPIteractiveServer(const short server_port);
    
public:
	/**
	 *
	 */
    void communicate(int i);
};
#endif	/* _CYBTCPITERACTIVESERVER_H */

