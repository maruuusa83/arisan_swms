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

namespace marusa {
namespace swms {

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

int Stigmergy::sendTaskList(HOST_ID to)
{
	int num_task = this->mMapTasks.size();
	unsigned int size = sizeof(TASKLST_PKT_HEADER) + sizeof(TASKLST_PKT_BODY) * num_task;
	BYTE *data = (BYTE *)malloc(size);

	((TASKLST_PKT_HEADER *)data)->num_task = num_task;
	int pos = sizeof(TASKLST_PKT_HEADER);
	for (auto task : this->mMapTasks){
		std::pair<JOB_ID, TASK_ID> task_uid = task.first;
		TASK_INFO *task_info = task.second;

		((TASKLST_PKT_BODY *)data)->job_id   = task_uid.first;
		((TASKLST_PKT_BODY *)data)->task_id  = task_uid.second;
		((TASKLST_PKT_BODY *)data)->put_time = task_info->put_time;

		pos += sizeof(TASKLST_PKT_BODY);
	}

	MessagePkt pkt(to, MessagePkt::MSG_RET_TASKLIST, data, size);
	this->mCmc->sendMessagePkt(pkt);
	return (0);
}

int Stigmergy::addTask(std::pair<JOB_ID, TASK_ID> &task_uid,
					   const BYTE *data,
					   const unsigned int data_size)
{
	TASK_INFO *task_info = (TASK_INFO *)malloc(sizeof(TASK_INFO));

	task_info->job_id = task_uid.first;
	task_info->task_id = task_uid.second;
	task_info->put_time = time(NULL);
	task_info->task_data = (BYTE *)malloc(sizeof(BYTE) * data_size);
	bytecpy(task_info->task_data, data, data_size);

	this->mMapTasks[task_uid] = task_info;

	return (0);
}

void Stigmergy::SGYCallbackListener::onRecvTask(const SGYContext &context,
												const BYTE *task)
{
	// nothing to do
}


} /* swms */
} /* marusa */

