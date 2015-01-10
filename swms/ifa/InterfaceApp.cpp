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

namespace marusa {
namespace swms {


/***** InterfaceAppAPI *****/
InterfaceAppAPI::InterfaceAppAPI(const IFACallbackListener &listener,
							     const CmcAdapter &cmc)
{
	//TODO:Implement this function.
}

JOB_ID InterfaceAppAPI::sendTasks(const Job &job)
{
	//TODO:Implement this function.
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


} /* swms */
} /* marusa */


