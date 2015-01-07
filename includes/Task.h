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

#include "./common.h"

namespace marusa {
namespace swms {


class Task
{
public:
	Task();
	Task(const TASK_ID &task_id,
		 const BYTE *data,
		 const unsigned int &data_size);

	void setJobId(const JOB_ID &job_id);
	void setTaskId(const TASK_ID &task_id);
	void setData(const BYTE *data,
				 const unsigned int &data_size);

	BYTE *getAsByteArray();

private:
	JOB_ID  job_id  = 0;
	TASK_ID task_id = 0;

	BYTE *data = nullptr;
	unsigned int data_size = 0;
};


} /* swms */
} /* marusa */

#endif /* ___TASK_H___ */

