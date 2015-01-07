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

TaskProcessorAPI::TaskProcessorAPI(const TPCallbackListener &listener,
								   const CmcAdapter &cmc)
{
	//TODO: implement this function
}

int TaskProcessorAPI::startWorker()
{
	//TODO: implement this function
}

int TaskProcessorAPI::sendTaskFin(const Result &resut)
{
	//TODO: implement this function
}

int TaskProcessorAPI::sendUsrMsg(const WORKER_ID &to,
								 BYTE *msg,
								 const unsigned int &msg_size)
{
	//TODO: implement this function
}

void TaskProcessorAPI::TPCallbackListeneronTask(const TPContext &context,
												const Task &task)
{
	//TODO: implement this function
}

void TaskProcessorAPI::TPCallbackListeneronUsrMsg(const IFAContext &context,
												  const BYTE *msg,
												  const unsigned int &size)
{
	//TODO: implement this function
}

TaskProcessorAPI::TPContext(const TaskProcessorAPI &taskProcessorAPI)
{
	//TODO: implement this function
}


} /* swms */
} /* marusa */



