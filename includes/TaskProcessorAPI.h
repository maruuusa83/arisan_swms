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
#ifndef ___TASKPROCESSOR_H___
#define ___TASKPROCESSOR_H___

#include <unistd.h>

#include "./common.h"
#include "./Task.h"
#include "./Result.h"
#include "./CmcAdapter.h"

namespace marusa {
namespace swms {


class TaskProcessorAPI
{
public:
	class TPCallbackListener;
	class TPContext;

	TaskProcessorAPI(const TPCallbackListener &listener,
					 const CmcAdapter &cmc);
	virtual ~TaskProcessorAPI();

	int startWorker();

	int sendTaskFin(const Result &resut);

	int sendUsrMsg(const WORKER_ID &to,
			       BYTE *msg,
				   const unsigned int &msg_size);

	static const unsigned int TP_SPAN_POLLING = 1;

private:
	TPCallbackListener *mListener;
	CmcAdapter *mCmc;

	int sendReqTasklist();
	int checkDoTask(JOB_ID &job_id,
			        TASK_ID &task_id);
	int getTask(Task &task,
			    const JOB_ID &job_id,
				const TASK_ID &task_id);
	int doTask(const Task &task);
};

class TaskProcessorAPI::TPCallbackListener
{
public:
	virtual void onTask(const TPContext &context,
						const Task &task);

	virtual void onUsrMsg(const TPContext &context,
						  const BYTE *msg,
						  const unsigned int &size);

	virtual ~TPCallbackListener();
};

class TaskProcessorAPI::TPContext
{
public:
	TPContext(const TaskProcessorAPI &taskProcessorAPI);

	TaskProcessorAPI *taskProcessorAPI = nullptr;
};


} /* swms */
} /* marusa */

#endif /* ___TASKPROCESSOR_H___ */

