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
#ifndef ___TASK_H___
#define ___TASK_H___

#include <vector>

#include "./common.h"

namespace marusa {
namespace swms {

class Job
{
public:
	class Task;
	
	Job(JOB_ID job_id);
	virtual ~Job();

	TASK_ID addTask(Task &task);
	int delTask(const TASK_ID &task_id);

	void getTaskList (std::vector<Task> &task_list) const;

private:
	std::vector<Task> task_list;
	TASK_ID id_num = 0;
	JOB_ID job_id = 0;
};

class Job::Task
{
public:
	Task();
	Task(TASK_ID task_id,
		 BYTE *data,
		 const unsigned int &data_size);

	void setJobId(const JOB_ID &job_id);
	void setTaskId(TASK_ID task_id);
	void setData(BYTE *data,
				 const unsigned int &data_size);

	JOB_ID getJobId() const;
	TASK_ID getTaskId() const;
	int getData(BYTE **data,
			    unsigned int &dat_size) const;

	void getAsByteArray(BYTE **result, unsigned int &size);
	int freeTaskAsByteArray(BYTE *task_byte);

private:
	JOB_ID  job_id  = 0;
	TASK_ID task_id = 0;

	BYTE *data = nullptr;
	unsigned int data_size = 0;

	static const int SIZE_JOB_ID = 4;
	static const int SIZE_TASK_ID = 4;
	static const int SIZE_DIV_ID = 4;
	static const int SIZE_DATA_SIZE = 4;
};


} /* swms */
} /* marusa */

#endif /* ___TASK_H___ */

