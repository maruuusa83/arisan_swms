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
	if (mCmc->connToStigmergy() == 0){
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
		JOB_ID job_id;
		TASK_ID task_id;
		checkDoTask(job_id, task_id);
		if (job_id != JOB_ID_NO_TASK){
			Job::Task task;

			getTask(task, job_id, task_id);
			doTask(task);
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
	return (0);
}

int TaskProcessorAPI::checkDoTask(JOB_ID &job_id,
								  TASK_ID &task_id)
{
	// First, send request.
	sendReqTasklist();

	// Second, check old data
	
	job_id = JOB_ID_NO_TASK;
	return (0);
}

int TaskProcessorAPI::getTask(Job::Task &task,
							  const JOB_ID &job_id,
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



