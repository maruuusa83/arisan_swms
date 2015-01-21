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
#include "TaskProcessorAPI.h"

#ifdef ___DEBUG_TRANS_TASK_IFA2SGY___
#include <stdio.h>
#include <iostream>
#endif /* ___DEBUG_TRANS_TASK_IFA2SGY___ */

namespace marusa {
namespace swms {


CmcAdapter::CmcAdapter()
{
	// nothing to do
}

CmcAdapter::CmcAdapter(CmcCallbackListener *listener)
{
	this->mListener = listener;
}

CmcAdapter::~CmcAdapter()
{
	// nothing to do
}

int CmcAdapter::sendMessagePkt(const MessagePkt &pkt)
{
	int result;

	BYTE *data;
	unsigned int size;
	pkt.get_msg(&data, size);

	HOST_ID to = pkt.get_to();
	result = sendMessage(to, data, size);

	pkt.free_msg(data);
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

	msg.get_data(&data, size_data);

#ifdef ___DEBUG_TRANS_TASK_IFA2SGY___
	std::cout << "CmcAdapter::CmcCallbackListener::onMessage - recv msg : TYPE-" << (int)msg.get_msg_type() << std::endl;
#endif /* ___DEBUG_TRANS_TASK_IFA2SGY___ */

	switch (msg.get_msg_type()){
	  case MessagePkt::MSG_SEND_TASK:
	  {
		Stigmergy::SGYCallbackListener *sgyCL = context.getSGYCallbackListener();
		Stigmergy::SGYContext *sgyCTXT = context.getSGYContext();

		sgyCL->onRecvTask(*sgyCTXT, data);

#ifdef ___DEBUG_TRANS_TASK_IFA2SGY___
		std::cout << "CmcAdapter::CmcCallbackListener::onMessage - MSG_SEND_TASK" << std::endl;
#endif /* ___DEBUG_TRANS_TASK_IFA2SGY___ */
		break;
	  }

	  case MessagePkt::MSG_REQ_TASKLIST:
	  {
#ifdef ___DEBUG_TRANS_TASK_IFA2SGY___
		std::cout << "CmcAdapter::CmcCallbackListener::onMessage - MSG_REQ_TASKLIST" << std::endl;
#endif /* ___DEBUG_TRANS_TASK_IFA2SGY___ */
		Stigmergy::SGYCallbackListener *sgyCL = context.getSGYCallbackListener();
		Stigmergy::SGYContext *sgyCTXT = context.getSGYContext();

		sgyCL->onRecvReqTaskList(*sgyCTXT, hostid);

		break;
	  }

	  case MessagePkt::MSG_RET_TASKLIST:
	  {
#ifdef ___DEBUG_TRANS_TASK_IFA2SGY___
		std::cout << "CmcAdapter::CmcCallbackListener::onMessage - MSG_RET_TASKLIST" << std::endl;
#endif /* ___DEBUG_TRANS_TASK_IFA2SGY___ */
		TaskProcessorAPI::TPCallbackListener *tpCL = context.getTPCallbackListener();
		TaskProcessorAPI::TPContext *tpCTXT = context.getTPContext();

		Job::Task task;
		tpCL->onTask(*tpCTXT, task);

		break;
	  }

	  case MessagePkt::MSG_NOTE_TASKFIN:
	  {
#ifdef ___DEBUG_TRANS_TASK_IFA2SGY___
		std::cout << "CmcAdapter::CmcCallbackListener::onMessage - MSG_NOTE_TASKFIN" << std::endl;
#endif /* ___DEBUG_TRANS_TASK_IFA2SGY___ */

		Stigmergy::SGYCallbackListener *sgyCL = context.getSGYCallbackListener();
		Stigmergy::SGYContext *sgyCTXT = context.getSGYContext();

		RESULT_PKT_HEADER *header = (RESULT_PKT_HEADER *)data;
		Result result(header->job_id,
					  header->task_id,
					  (BYTE *)&data[sizeof(RESULT_PKT_HEADER)],
					  header->data_size);
		sgyCL->onRecvTaskFin(*sgyCTXT, result, hostid);

		break;
	  }


	  case MessagePkt::MSG_RET_JOBID:
	  {
		InterfaceAppAPI::IFACallbackListener *ifaCL = context.getIFACallbackListener();
		InterfaceAppAPI::IFAContext *ifaCTXT = context.getIFAContext();

		ifaCL->onRecvJobId(*ifaCTXT, *((JOB_ID *)data));

		break;
	  }

	  default:
	    break;
	}

	msg.free_msg(data);
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

