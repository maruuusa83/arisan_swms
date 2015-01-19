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
#include "Job.h"
#include <stdlib.h>

#include "MessagePkt.h"

namespace marusa {
namespace swms {


Job::Job()
{
	
}

Job::~Job()
{

}

TASK_ID Job::addTask(Task &task)
{
	task.setTaskId(id_num);
	id_num++;

	(this->task_list).push_back(task);

	return (task.getTaskId());
}

int Job::delTask(const TASK_ID &task_id)
{
	//TODO: implement this
	return (0);
}

void Job::getTaskList(std::vector<Task> &task_list) const
{
	task_list = this->task_list;
}


/*** Job::Task ***/
Job::Task::Task()
{

}

Job::Task::Task(TASK_ID task_id,
				 BYTE *data,
				 const unsigned int &data_size)
{
	setTaskId(task_id);
	setData(data, data_size);
}

void Job::Task::setJobId(const JOB_ID &job_id)
{
	this->job_id = job_id;
}

void Job::Task::setTaskId(TASK_ID task_id)
{
	this->task_id = task_id;
}

void Job::Task::setData(BYTE *data,
						const unsigned int &data_size)
{
	this->data = (BYTE *)malloc(sizeof(BYTE) * data_size);
	
	int i = data_size;
	while (i--){
		(this->data)[i - 1] = data[i - 1];
	}
	this->data_size = data_size;
}

JOB_ID Job::Task::getJobId() const
{
	return (this->job_id);
}

TASK_ID Job::Task::getTaskId() const
{
	return (this->task_id);
}

int Job::Task::getData(BYTE **data,
					   unsigned int &dat_size)
{
	*data = this->data;
	dat_size = this->data_size;

	return (0);
}

/* deprecated */
void Job::Task::getAsByteArray(BYTE **result, unsigned int &size)
{
	BYTE *tmp = (BYTE *)malloc(sizeof(BYTE) * (sizeof(TASK_PKT_HEADER) + this->data_size));
	((TASK_PKT_HEADER *)tmp)->job_id = getJobId();
	((TASK_PKT_HEADER *)tmp)->task_id = getTaskId();
	((TASK_PKT_HEADER *)tmp)->div_id = 0;
	((TASK_PKT_HEADER *)tmp)->data_size = this->data_size;

	marusa::swms::bytecpy((BYTE *)&(tmp[sizeof(TASK_PKT_HEADER)]), this->data, this->data_size);
	*result = tmp;
	size = this->data_size + sizeof(TASK_PKT_HEADER);
}

int Job::Task::freeTaskAsByteArray(BYTE *task_byte)
{
	free(task_byte);
	return (0);
}


} /* namespace grad_res */
} /* namespace marusa */

