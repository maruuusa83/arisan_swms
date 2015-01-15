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

namespace marusa {
namespace swms {

Job::Job()
{
	
}

Job::~Job()
{

}

TASK_ID Job::addTask(const Task &task)
{
	return (0);
}

int Job::delTask(const TASK_ID &task_id)
{
	return (0);
}

void Job::getTaskList(std::vector<Task> &task_list) const
{

}


/*** Job::Task ***/
Job::Task::Task()
{

}

Job::Task::Task(const TASK_ID &task_id,
				 const BYTE *data,
				 const unsigned int &data_size)
{

}

void Job::Task::setJobId(const JOB_ID &job_id)
{

}

void Job::Task::setTaskId(const TASK_ID &task_id)
{

}

void Job::Task::setData(const BYTE *data,
						const unsigned int &data_size)
{

}

JOB_ID Job::Task::getJobId()
{
	return (0);
}

TASK_ID Job::Task::getTaskId()
{
	return (0);
}

int Job::Task::getData(BYTE *&data,
					   unsigned int &dat_size)
{
	return (0);
}

BYTE *Job::Task::getAsByteArray()
{
	return (nullptr);
}


} /* namespace grad_res */
} /* namespace marusa */

