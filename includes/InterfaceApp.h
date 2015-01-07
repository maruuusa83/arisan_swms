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
#ifndef ___INTERFACEAPP_H___
#define ___INTERFACEAPP_H___

#include "./common.h"
#include "./Task.h"

#include <vector>

namespace marusa {
namespace swms {


class InterfaceApp
{
public:
	class IFACallbackListener;

	InterfaceApp(const IFACallbackListener &listener,
			     const CmcAdapter &cmc);

	JOB_ID sendTasks(const std::vector<Task> &tasks);
	int getTasksByJobId(const JOB_ID &job_id,
						std::vector<Task> &tasks);
	int getTaskByTaskId(const JOB_ID &job_id,
			            const TASK_ID &task_id,
						Task *&task);

	int sendUsrMsg(const WORKER_ID &to,
			       BYTE *msg,
				   const unsigned int &msg_size);
};

class InterfaceApp::IFACallbackListener
{
public:
	virtual void onTask(const WorkerContext &context,
			            const Task &task);

	virtual void onRecvMsg(const WorkerContext &context,
			               const BYTE *msg,
						   const unsigned int &msg_size);
};


} /* swms */
} /* marusa */

#endif /* ___INTERFACEAPP_H___ */
