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
#include "Stigmergy.h"

#include <time.h>
#include <sys/time.h>

#include <iostream>

namespace marusa {
namespace swms {

bool forbidIntruptFlg = false;
bool resultAccessFlg = false;
bool taskAccessFlg = false;

Stigmergy::Stigmergy(CmcAdapter *cmc)
{
	(this->mCmc) = cmc;
}

Stigmergy::~Stigmergy()
{
	//tohitng to do
}

int Stigmergy::startStigmergy()
{
	(this->mCmc)->startListen();

	return (0);
}

int Stigmergy::sendTask(const HOST_ID &to, const JOB_ID &job_id, const TASK_ID &task_id)
{
	std::pair<JOB_ID, TASK_ID> task_uid(job_id, task_id);
	if (mMapTasks[task_uid] == nullptr){
		return (0);
	}
	BYTE *task_pkt = (BYTE *)malloc(sizeof(TASK_PKT_HEADER) + mMapTasks[task_uid]->task_data_size);
	((TASK_PKT_HEADER *)task_pkt)->job_id = job_id;
	((TASK_PKT_HEADER *)task_pkt)->task_id = task_id;
	((TASK_PKT_HEADER *)task_pkt)->div_id = 0;
	((TASK_PKT_HEADER *)task_pkt)->data_size = mMapTasks[task_uid]->task_data_size;

	bytecpy((BYTE *)&(task_pkt[sizeof(TASK_PKT_HEADER)]), mMapTasks[task_uid]->task_data, mMapTasks[task_uid]->task_data_size);

	MessagePkt pkt(to, MessagePkt::MSG_RET_TASK, task_pkt, sizeof(TASK_PKT_HEADER) + mMapTasks[task_uid]->task_data_size);
	(this->mCmc)->sendMessagePkt(pkt);

	return (0);
}

int Stigmergy::sendTaskList(HOST_ID to)
{
	taskAccessFlg = true;
	int num_task = this->mMapTasks.size();
	unsigned int size = sizeof(TASKLST_PKT_HEADER) + sizeof(TASKLST_PKT_BODY) * num_task;
	BYTE *data = (BYTE *)malloc(size);

	((TASKLST_PKT_HEADER *)data)->num_task = num_task;
	int pos = sizeof(TASKLST_PKT_HEADER);
	for (auto task : this->mMapTasks){
		std::pair<JOB_ID, TASK_ID> task_uid = task.first;
		// std::cout << "\t" << task_uid.first << "-" << task_uid.second << std::endl;
		TASK_INFO *task_info = task.second;

		if (0 >= task_uid.first && task_uid.first >= 10){
			((TASKLST_PKT_BODY *)&data[pos])->job_id   = 0;
            mMapTasks.erase(task.first);
			continue;
		}

		if (task_info == nullptr){
			((TASKLST_PKT_BODY *)&data[pos])->job_id   = 0;
			continue;
		}

		if (task_info->flag == true){
			((TASKLST_PKT_BODY *)&data[pos])->job_id   = task_uid.first;
		}
		else {
			((TASKLST_PKT_BODY *)&data[pos])->job_id   = 0;
		}

		((TASKLST_PKT_BODY *)&data[pos])->task_id  = task_uid.second;
		((TASKLST_PKT_BODY *)&data[pos])->put_time = task_info->put_time;

		pos += sizeof(TASKLST_PKT_BODY);
	}

	MessagePkt pkt(to, MessagePkt::MSG_RET_TASKLIST, data, size);
	(this->mCmc)->sendMessagePkt(pkt);

	free(data);
	taskAccessFlg = false;

	return (0);
}

int Stigmergy::sendResultList(HOST_ID to)
{
	int num_result = this->mMapResults.size();
	unsigned int size = sizeof(RESULTLST_PKT_HEADER) + sizeof(RESULTLST_PKT_BODY) * num_result;
	BYTE *data = (BYTE *)malloc(size);

	((RESULTLST_PKT_HEADER *)data)->num_result = num_result;
	int pos = sizeof(RESULTLST_PKT_HEADER);
	std::cout << "******* building result list *******" << std::endl;
	for (auto result : this->mMapResults){
		std::pair<JOB_ID, TASK_ID> task_uid = result.first;
		std::cout << "\t" << task_uid.first << "-" << task_uid.second << std::endl;

		((RESULTLST_PKT_BODY *)&data[pos])->job_id = task_uid.first;
		((RESULTLST_PKT_BODY *)&data[pos])->task_id = task_uid.second;

		pos += sizeof(RESULTLST_PKT_BODY);
	}
	std::cout << "******* builded result list *******" << std::endl;

	MessagePkt pkt(to, MessagePkt::MSG_REP_RESULTLIST, data, size);
	(this->mCmc)->sendMessagePkt(pkt);

	return (0);
}

int Stigmergy::addTask(std::pair<JOB_ID, TASK_ID> &task_uid,
					   const BYTE *data,
					   const unsigned int data_size)
{
	if (forbidIntruptFlg == true){
		return (0);
	}
	TASK_INFO *task_info = (TASK_INFO *)malloc(sizeof(TASK_INFO));

	std::cout << "***ADD TASK***" << std::endl;
	task_info->job_id = task_uid.first;
	task_info->task_id = task_uid.second;
	task_info->put_time = time(NULL) + (80 - task_info->task_id);
	gettimeofday(&task_info->tv_put_time, NULL);
	(task_info->tv_put_time).tv_sec += (80 - task_info->task_id);
	task_info->task_data_size = data_size;
	task_info->task_data = (BYTE *)malloc(sizeof(BYTE) * data_size);
	bytecpy(task_info->task_data, data, data_size);
	task_info->flag = true;

	this->mMapTasks[task_uid] = task_info;

	std::cout << "Stigmergy::addTask - task was added. now : " << this->mMapTasks.size() << std::endl;

	return (0);
}

int Stigmergy::delTask(const std::pair<JOB_ID, TASK_ID> &task_uid)
{
	/*
	if (taskAccessFlg == true){
		return (0);
	}
	free(this->mMapTasks[task_uid]);
	(this->mMapTasks).erase(task_uid);
	*/
	(this->mMapTasks[task_uid])->flag = false;

	return (0);
}

int Stigmergy::addResult(const Result &result)
{
	if (forbidIntruptFlg == true){
		return (0);
	}
	std::pair<JOB_ID, TASK_ID> task_uid(result.getJobId(), result.getTaskId());

	Result *tmp = new Result(result);
	this->mMapResults[task_uid] = tmp;

	return (0);
}

int Stigmergy::sendTaskFinToIF(const Stigmergy::SGYContext &context,
                                const Result &result)
{
    BYTE *data;
    unsigned int data_size;
    

    result.getData(&data, data_size);
	unsigned int pkt_data_size = sizeof(RESULT_PKT_HEADER) + data_size * sizeof(BYTE);

	BYTE *pkt_data = (BYTE *)malloc(pkt_data_size);
	((RESULT_PKT_HEADER *)pkt_data)->job_id  = result.getJobId();
	((RESULT_PKT_HEADER *)pkt_data)->task_id = result.getTaskId();
	((RESULT_PKT_HEADER *)pkt_data)->div_id  = 0;
	((RESULT_PKT_HEADER *)pkt_data)->data_size = data_size;
	bytecpy(&(pkt_data[sizeof(RESULT_PKT_HEADER)]), data, data_size);

    MessagePkt pkt(ifa, MessagePkt::MSG_NOTE_TASKFIN_IF, pkt_data, pkt_data_size);
	(this->mCmc)->sendMessagePkt(pkt);
    result.freeData(data);

    return (0);
}

void Stigmergy::setIFAID(const HOST_ID hostid){
    ifa = hostid;
}

void Stigmergy::SGYCallbackListener::onRecvTask(const SGYContext &context,
												const BYTE *task,
                                                const HOST_ID hostid)
{
	// nothing to do
}

void Stigmergy::SGYCallbackListener::onRecvReqTask(const SGYContext &context,
												   const JOB_ID &job_id,
												   const TASK_ID &task_id,
												   const HOST_ID &from)
{
	// nothing to do
}

void Stigmergy::SGYCallbackListener::onRecvReqTaskList(const SGYContext &context,
													   const HOST_ID &from)
{
	// nothing to do
}

void Stigmergy::SGYCallbackListener::onRecvTaskFin(const SGYContext &context,
												   const Result &result,
												   const HOST_ID &from)
{
	// nothing to do
}

void Stigmergy::SGYCallbackListener::onRecvReqResultList(const SGYContext &context,
														 const HOST_ID &from)
{
	// nothing to do
}


Stigmergy::SGYContext::SGYContext(Stigmergy *stigmergy)
{
	this->mSGY = stigmergy;
}


} /* swms */
} /* marusa */

