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
#include "TaskProcessorAPI.h"

#include <random>
#include <iostream>

namespace marusa {
namespace swms {

TaskProcessorAPI::TaskProcessorAPI(TPCallbackListener *listener,
								   CmcAdapter *cmc)
{
	this->mListener = listener;
	this->mCmc = cmc;
}

TaskProcessorAPI::~TaskProcessorAPI()
{
	delete this->mListener;
	delete this->mCmc;
}

int TaskProcessorAPI::startWorker()
{
	this->stigmergy_id = (this->mCmc)->connToStigmergy();
	if (this->stigmergy_id == 0){
		//TODO: it needs the error code.
		//if success, connToStigma will return HOST_ID (not zero)
		return (-1);
	}


	while (1){
		/* sending tasklist request to stigmergy */
		if (sendReqTasklist() != 0){
			//TODO: error process
			//TODO: it needs the error code.
			return (-1);
		}

		/* Reaction threshold */
		JOB_ID job_id = JOB_ID_NO_TASK;
		TASK_ID task_id;

		checkDoTask(job_id, task_id);
		if (job_id != JOB_ID_NO_TASK){
			getTask(job_id, task_id);
		}

		sleep(TP_SPAN_POLLING);
	}

	return (0);
}

int TaskProcessorAPI::sendTaskFin(const Result &resut)
{
	//TODO: implement this function
	return (0);
}

int TaskProcessorAPI::sendUsrMsg(const WORKER_ID &to,
								 BYTE *msg,
								 const unsigned int &msg_size)
{
	//TODO: implement this function
	return (0);
}

int TaskProcessorAPI::sendReqTasklist()
{
	MessagePkt pkt(stigmergy_id, MessagePkt::MSG_REQ_TASKLIST, nullptr, 0);
	this->mCmc->sendMessagePkt(pkt);

	return (0);
}

int TaskProcessorAPI::checkDoTask(JOB_ID &job_id,
								  TASK_ID &task_id)
{
	std::random_device r_seed;
	std::mt19937 mt(r_seed());

	for (auto task : mMapTasks){
		// calculate needs of each task
		TASK_INFO *info = task.second;
		time_t task_age = difftime(time(NULL), info->put_time);
		CONS_PROB cons_prob = calcTaskConsumeProb(task_age);

		// decide consume or reject task
		std::cout << mt() << std::endl;
	}
	
	job_id = JOB_ID_NO_TASK;
	return (0);
}

CONS_PROB TaskProcessorAPI::calcTaskConsumeProb(time_t age)
{
	//TODO: calc probability
	return (1.0);
}

int TaskProcessorAPI::getTask(const JOB_ID &job_id,
							  const TASK_ID &task_id)
{
	//TODO: implement this function
	return (0);
}

int TaskProcessorAPI::doTask(const Job::Task &task)
{
	//TODO: implement this function
	return (0);
}


void TaskProcessorAPI::TPCallbackListener::onTask(const TPContext &context,
												  const Job::Task &task)
{
	//TODO: implement this function
}

void TaskProcessorAPI::TPCallbackListener::onUsrMsg(const TPContext &context,
												    const BYTE *msg,
												    const unsigned int &size)
{
	//TODO: implement this function
}

TaskProcessorAPI::TPCallbackListener::~TPCallbackListener()
{

}

TaskProcessorAPI::TPContext::TPContext(TaskProcessorAPI *taskProcessorAPI)
{
	this->taskProcessorAPI = taskProcessorAPI;
}


} /* swms */
} /* marusa */



