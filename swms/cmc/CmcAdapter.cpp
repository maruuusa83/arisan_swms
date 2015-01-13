/********************************************************************************
 * Copyright (C) 2014 Daichi Teruya (@maruuusa83)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License.
 *
 * This program is destributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *******************************************************************************/
#include "CmcAdapter.h"

namespace marusa {
namespace swms {


CmcAdapter::CmcAdapter(CmcCallbackListener *listener)
{
	//nothing to do.
	this->mListener = listener;
}

int CmcAdapter::sendMessagePkt(const MessagePkt &pkt)
{
	//TODO: implement this method
	return (0);
}
		
HOST_ID CmcAdapter::connToStigma()
{
	//TODO: implement this function
	return (0);
}
			
int CmcAdapter::startListen()
{
	//TODO: implement this function
	return (0);
}

void CmcAdapter::CmcCallbackListener::onMessage(const HOST_ID &hostid,
											    const BYTE *msg)
{
	//nothing to do.
}

void CmcAdapter::CmcCallbackListener::onNewWorker(const HOST_ID &host_id)
{
	//nothing to do.
}


void CmcAdapter::CmcCallbackListener::onDisconnWorker(const HOST_ID &host_id)
{
	//nothing to do.
}

int CmcAdapter::sendMessage(const HOST_ID &host_id,
							const BYTE *msg)
{
	//TODO: implement this function
	return (0);
}



} /* swms */
} /* marusa */

