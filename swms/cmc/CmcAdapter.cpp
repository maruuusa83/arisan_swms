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
#include "CmcContext.h"

#include "Stigmergy.h"

namespace marusa {
namespace swms {


CmcAdapter::CmcAdapter(CmcCallbackListener *listener)
{
	this->mListener = listener;
}

int CmcAdapter::sendMessagePkt(const MessagePkt &pkt)
{
	int result;

	BYTE *data;
	unsigned int size;
	pkt.get_msg(&data, size);

	HOST_ID to = pkt.get_to();
	result = sendMessage(to, data, size);

	return (result);
}

int CmcAdapter::setCmcContext(CmcContext *context)
{
	this->mContext = context;
	return (0);
}
		
HOST_ID CmcAdapter::connToStigmergy()
{
	//TODO: implement this function
	return (0);
}
			
int CmcAdapter::startListen()
{
	//TODO: implement this function
	return (0);
}


/*** Private methods ***/
int CmcAdapter::sendMessage(const HOST_ID &host_id,
							const BYTE *msg,
							const unsigned int &size_msg)
{
	//nothing to do.
	return (0);
}


/*** CmcCallbackListener ***/
void CmcAdapter::CmcCallbackListener::onMessage(const CmcContext &context,
												const HOST_ID &hostid,
											    const MessagePkt &msg)
{
	BYTE *data;
	unsigned int size_data;

	msg.get_msg(&data, size_data);

	switch (msg.get_msg_type()){
	  case MessagePkt::MSG_SEND_TASK:
	  {
		const Stigmergy::SGYCallbackListener &sgyCL = context.getSGYCallbackListener();
		const Stigmergy::SGYContext &sgyCTXT = context.getSGYContext();

		sgyCL.onRecvTask(sgyCTXT, data);
	  }

	  case MessagePkt::MSG_RET_JOBID:
	  {
		const InterfaceAppAPI::IFACallbackListener &ifaCL = context.getIFACallbackListener();
		const InterfaceAppAPI::IFAContext &ifaCTXT = context.getIFAContext();

		ifaCL.onRecvJobId(ifaCTXT, *((JOB_ID *)data));
	  }

	  default:
	    break;
	}
}

void CmcAdapter::CmcCallbackListener::onNewWorker(const CmcContext &context,
												  const HOST_ID &host_id)
{
	//TODO: implement this method
}


void CmcAdapter::CmcCallbackListener::onDisconnWorker(const CmcContext &context,
													  const HOST_ID &host_id)
{
	//TODO: implement this method
}


} /* swms */
} /* marusa */

