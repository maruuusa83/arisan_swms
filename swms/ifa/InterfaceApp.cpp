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
#include "InterfaceAppAPI.h"

#include "MessagePkt.h"

#include <iostream>

namespace marusa {
namespace swms {


/***** InterfaceAppAPI *****/
InterfaceAppAPI::InterfaceAppAPI(IFACallbackListener *listener,
							     CmcAdapter *cmc)
{
#ifdef ___DEBUG_TRANS_TASK_IFA2SGY___
	std::cout << "in TnterfaceAppAPI::InterfaceAppAPI" << std::endl;
#endif /* ___DEBUG_TRANS_TASK_IFA2SGY___ */

	this->mListener = listener;
	this->mCmc = cmc;

	//TODO: this line needs throw exception, i think
	(this->mCmc)->connToStigmergy();

#ifdef ___DEBUG_TRANS_TASK_IFA2SGY___
	std::cout << "out TnterfaceAppAPI::InterfaceAppAPI" << std::endl;
#endif /* ___DEBUG_TRANS_TASK_IFA2SGY___ */
}

JOB_ID InterfaceAppAPI::sendTasks(const Job &job)
{
	CmcAdapter *cmc = this->mCmc;

	std::vector<Job::Task> task_list;
	job.getTaskList(task_list);

	for (auto task : task_list){
		BYTE *byte_task_data;
		unsigned int size;
		task.getData(byte_task_data, size);

		MessagePkt pkt(stigmergy_id, MessagePkt::MSG_SEND_TASK, byte_task_data, size);
		cmc->sendMessagePkt(pkt);
	}

	return (0);
}

int InterfaceAppAPI::getTasksByJobId(const JOB_ID &job_id)
{
	//TODO:Implement this function.
	return (0);
}

int InterfaceAppAPI::getTaskByTaskId(const JOB_ID &job_id,
								  const TASK_ID &task_id)
{
	//TODO:Implement this function.
	return (0);
}

int InterfaceAppAPI::sendUsrMsg(const WORKER_ID &to,
							 BYTE *msg,
							 const unsigned int &msg_size)
{
	//TODO:Implement this function.
	return (0);
}

int InterfaceAppAPI::packetBuilder(BYTE *&pkt,
								   const Job &job)
{
	//TODO: implement this method
	return (0);
}


/***** InterfaceAppAPI::IFACallbackListener *****/
void InterfaceAppAPI::IFACallbackListener::onFinTask(const IFAContext &context,
											      const JOB_ID &job_id,
											      const TASK_ID &task_id)
{
	//nothing to do
}

void InterfaceAppAPI::IFACallbackListener::onRecvJobResult(const IFAContext &context,
					 const JOB_ID &job_id,
					 const TASK_ID &task_id)
{
	//nothing to do
}

void InterfaceAppAPI::IFACallbackListener::onRecvTaskResult(const IFAContext &context,
					  const JOB_ID &job_id,
					  const TASK_ID &task_id)
{
	//nothing to do
}

void InterfaceAppAPI::IFACallbackListener::onRecvJobId(const IFAContext &context,
						 									   const JOB_ID &job_id) const
{
	//nothing todo
}

void InterfaceAppAPI::IFACallbackListener::onNewWorker(const IFAContext &context,
				 			   						   const WORKER_ID &worker_id)
{
	//nothing to do
}

void InterfaceAppAPI::IFACallbackListener::onDelWorker(const IFAContext &context,
													const WORKER_ID &worker_id)
{
	//nothing to do
}

void InterfaceAppAPI::IFACallbackListener::onUsrMsg(const IFAContext &context,
											     const WORKER_ID &worker_id,
											     const BYTE *msg,
											     const unsigned int &size)
{
	//nothing to do
}


InterfaceAppAPI::IFAContext::IFAContext(InterfaceAppAPI &interfaceAppAPI)
{
	this->mInterfaceAppAPI = &interfaceAppAPI;
}


} /* swms */
} /* marusa */


