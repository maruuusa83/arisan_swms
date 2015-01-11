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
#ifndef ___INTERFACEAPPAPI_H___
#define ___INTERFACEAPPAPI_H___

#include "./common.h"
#include "./Job.h"
#include "./CmcAdapter.h"

#include <vector>

namespace marusa {
namespace swms {


class InterfaceAppAPI
{
public:
	class IFACallbackListener;
	class IFAContext;

	InterfaceAppAPI(const IFACallbackListener &listener,
			        const CmcAdapter &cmc);

	JOB_ID sendTasks(const Job &job);
	int getTasksByJobId(const JOB_ID &job_id);
	int getTaskByTaskId(const JOB_ID &job_id,
			            const TASK_ID &task_id);

	int sendUsrMsg(const WORKER_ID &to,
			       BYTE *msg,
				   const unsigned int &msg_size);

private:
	IFACallbackListener mListener;
	CmcAdapter mCmc;

	HOST_ID stigmergy_id = 0;
};

class InterfaceAppAPI::IFACallbackListener
{
public:
	virtual void onFinTask(const IFAContext &context,
						   const JOB_ID &job_id,
						   const TASK_ID &task_id);

	virtual void onRecvJobResult(const IFAContext &context,
								 const JOB_ID &job_id,
								 const TASK_ID &task_id);
	virtual void onRecvTaskResult(const IFAContext &context,
								 const JOB_ID &job_id,
								 const TASK_ID &task_id);

	virtual void onNewWorker(const IFAContext &context,
							 const WORKER_ID &worker_id);
	virtual void onDelWorker(const IFAContext &context,
							 const WORKER_ID &worker_id);

	virtual void onUsrMsg(const IFAContext &context,
						  const WORKER_ID &worker_id,
						  const BYTE *msg,
						  const unsigned int &size);
};



} /* swms */
} /* marusa */

#endif /* ___INTERFACEAPP_H___ */
