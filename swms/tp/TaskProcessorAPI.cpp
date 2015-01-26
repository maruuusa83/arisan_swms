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
#include <sys/time.h>

namespace marusa {
namespace swms {

TaskProcessorAPI::TaskProcessorAPI(TPCallbackListener *listener,
								   CmcAdapter *cmc)
{
	this->mListener = listener;
	this->mCmc = cmc;

	
	// get theta (in 0.0 through 2.0)
	std::random_device r_seed;
	std::mt19937 mt(r_seed());
	std::normal_distribution<> dist(1.0, 0.4);

	double theta_tmp;
	do {
		theta_tmp = dist(mt);
	} while (theta_tmp < 0.0 || 2.0 < theta_tmp);

	this->mTheta = theta_tmp;
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
		if (job_id != JOB_ID_NO_TASK && forbidInteruptFlag == false){
			getTask(job_id, task_id);
		}

		sleep(TP_SPAN_POLLING);
	}

	return (0);
}

int TaskProcessorAPI::sendTaskFin(const Result &result)
{
	BYTE *result_data;
	unsigned int result_data_size;
	result.getData(&result_data, result_data_size);

	unsigned int pkt_data_size = sizeof(RESULT_PKT_HEADER) + result_data_size * sizeof(BYTE);
	BYTE *pkt_data = (BYTE *)malloc(pkt_data_size);

	((RESULT_PKT_HEADER *)pkt_data)->job_id  = result.getJobId();
	((RESULT_PKT_HEADER *)pkt_data)->task_id = result.getTaskId();
	((RESULT_PKT_HEADER *)pkt_data)->div_id  = 0;
	((RESULT_PKT_HEADER *)pkt_data)->data_size = result_data_size;
	bytecpy(&(pkt_data[sizeof(RESULT_PKT_HEADER)]), result_data, result_data_size);

	MessagePkt pkt(stigmergy_id, MessagePkt::MSG_NOTE_TASKFIN, pkt_data, pkt_data_size);
	this->mCmc->sendMessagePkt(pkt);

	free(pkt_data);

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

	job_id = JOB_ID_NO_TASK;

	for (auto task : mMapTasks){
		// calculate reaction probablity of each task
		TASK_INFO *info = task.second;

		if (info->job_id == 0){
			continue;
		}

		struct timeval tv;
		gettimeofday(&tv, NULL);

		struct timeval tv_age;
		tv_age.tv_sec  = tv.tv_sec - info->put_time;
		if (tv.tv_usec >= info->tv_put_time.tv_usec){
			tv_age.tv_usec = tv.tv_usec - info->tv_put_time.tv_usec;
		}
		else {
			tv_age.tv_sec--;
			tv_age.tv_usec = info->tv_put_time.tv_usec - tv.tv_usec;
		}
		tv_age.tv_usec = 0;

		CONS_PROB cons_prob = calcTaskConsumeProb(tv_age);

		// decide execute or reject task
		double random = std::generate_canonical<double, std::numeric_limits<double>::digits>(mt);
		std::cout << "\t" << info->job_id << "-" << info->task_id;
		std::cout << " rand:" << random << ", prob:" << cons_prob << ", age:" << (tv_age.tv_sec * 1000.) + (tv_age.tv_usec / 1000.) << ", th:" << this->mTheta << std::endl;
		if (random < cons_prob){
			job_id  = info->job_id;
			task_id = info->task_id;
			break;
		}
	}

	return (0);
}

void TaskProcessorAPI::forbidInterupt()
{
	this->forbidInteruptFlag = true;
}

void TaskProcessorAPI::permitInterupt()
{
	this->forbidInteruptFlag = false;
}

bool TaskProcessorAPI::getForbidInteruptFlag()
{
	return (this->forbidInteruptFlag);
}

CONS_PROB TaskProcessorAPI::calcTaskConsumeProb(time_t age)
{
	double ageage = age * age;
	CONS_PROB cons_prob = ageage / (ageage + this->mTheta);

	return (cons_prob);
}

CONS_PROB TaskProcessorAPI::calcTaskConsumeProb(const timeval &tv_age)
{
	double age = (tv_age.tv_sec * 1000.) + (tv_age.tv_usec / 1000.);

	// ( Th ( t - t0 ) ) ^2
	double ageage = age * this->mTheta;
	ageage *= ageage;

	CONS_PROB cons_prob = ageage / (ageage + HALF_CONSPROB_DOUBLE_MSEC);

	return (cons_prob);
}

int TaskProcessorAPI::getTask(const JOB_ID &job_id,
							  const TASK_ID &task_id)
{
	//TODO: implement this function
	std::cout << "TaskProcessorAPI::getTask - get task" << std::endl;

	TASKREQ_PKT_BODY req;
	req.job_id = job_id;
	req.task_id = task_id;

	MessagePkt pkt(this->stigmergy_id, MessagePkt::MSG_REQ_TASK, (BYTE *)&req, sizeof(TASKREQ_PKT_BODY));
	(this->mCmc)->sendMessagePkt(pkt);


	return (0);
}

int TaskProcessorAPI::doTask(const Job::Task &task)
{
	//TODO: implement this function
	return (0);
}

int TaskProcessorAPI::renewTaskList(const std::map<std::pair<JOB_ID, TASK_ID>, TASK_INFO *> &task_list)
{
	// delete old taskinfos
	for (auto old_info : this->mMapTasks){
		TASK_INFO *task_info = old_info.second;
		free(task_info);
	}

	// append new taskinfos
	this->mMapTasks = task_list;

	return (0);
}

void TaskProcessorAPI::TPCallbackListener::onTask(const TPContext &context,
												  const Job::Task &task)
{
	//TODO: implement this function
}

void TaskProcessorAPI::TPCallbackListener::onTaskList(const TPContext &context,
													  const std::vector<TASKLST_PKT_BODY *> &tasklist)
{
	//nothing
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



