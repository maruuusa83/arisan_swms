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

	this->mTaskList[task_uid] = task_info;

	return (0);
}

void Stigmergy::SGYCallbackListener::onRecvTask(const SGYContext &context,
												const BYTE *task)
{
	// nothing to do
}


} /* swms */
} /* marusa */

