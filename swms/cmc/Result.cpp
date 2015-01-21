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
#include "Result.h"
#include <stdlib.h>

#include "MessagePkt.h"

namespace marusa {
namespace swms {

Result::Result()
{

}

Result::Result(const JOB_ID &job_id,
			   const TASK_ID &task_id,
			   const BYTE *data,
			   const unsigned int &data_size)
{
	setJobId(job_id);
	setTaskId(task_id);
	setData(data, data_size);
}

void Result::setJobId(const JOB_ID &job_id)
{
	this->job_id = job_id;
}

void Result::setTaskId(const TASK_ID &task_id)
{
	this->task_id = task_id;
}

void Result::setData(const BYTE *data,
					 const unsigned int &data_size)
{
	this->data = (BYTE *)malloc(sizeof(BYTE) * data_size);
	bytecpy(this->data, data, data_size);
	this->data_size = data_size;
}

void Result::getAsByteArray(BYTE **result, unsigned int &size)
{
	*result = (BYTE *)malloc(sizeof(RESULT_PKT_HEADER) + sizeof(BYTE) * this->data_size);
	((RESULT_PKT_HEADER *)result)->job_id = this->job_id;
	((RESULT_PKT_HEADER *)result)->task_id = this->task_id;
	((RESULT_PKT_HEADER *)result)->div_id = 0;
	((RESULT_PKT_HEADER *)result)->data_size = this->data_size;

	bytecpy((BYTE *)&(result[sizeof(RESULT_PKT_HEADER)]), this->data, this->data_size);
	
	size = sizeof(RESULT_PKT_HEADER) + this->data_size;
}

int Result::freeResultAsByteArray(BYTE *result_byte)
{
	free (result_byte);

	return (0);
}


} /* namespace swms */
} /* namespace marusa */


