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
#include "./Result.h"

#include <vector>

namespace marusa {
namespace swms {


class InterfaceAppAPI
{
public:
	class IFACallbackListener;
	class IFAContext;

	InterfaceAppAPI(IFACallbackListener *listener,
			        CmcAdapter *cmc);

	JOB_ID sendTasks(const Job &job);
	int getTasksByJobId(const JOB_ID &job_id);
	int getTaskByTaskId(const JOB_ID &job_id,
			            const TASK_ID &task_id);

	int sendReqResultList();
	int sendUsrMsg(const WORKER_ID &to,
			       BYTE *msg,
				   const unsigned int &msg_size);

private:
	IFACallbackListener *mListener;
	CmcAdapter *mCmc;

	HOST_ID stigmergy_id = 0;

	int packetBuilder(BYTE *&pkt,
					  const Job &job);
};

class InterfaceAppAPI::IFACallbackListener
{
public:
	virtual void onFinTask(const IFAContext &context,
						   const JOB_ID &job_id,
						   const TASK_ID &task_id);

	virtual void onRecvResultList(const InterfaceAppAPI::IFAContext &context,
								  const std::vector<std::pair<JOB_ID, TASK_ID>> &results_info);

    virtual void onRecvTaskFin(const IFAContext &context,
                               const Result &result);

	virtual void onRecvJobResult(const IFAContext &context,
								 const JOB_ID &job_id,
								 const TASK_ID &task_id);
	virtual void onRecvTaskResult(const IFAContext &context,
								 const JOB_ID &job_id,
								 const TASK_ID &task_id);

	virtual void onRecvJobId(const IFAContext &context,
							 const JOB_ID &job_id) const;

	virtual void onNewWorker(const IFAContext &context,
							 const WORKER_ID &worker_id);
	virtual void onDelWorker(const IFAContext &context,
							 const WORKER_ID &worker_id);

	virtual void onUsrMsg(const IFAContext &context,
						  const WORKER_ID &worker_id,
						  const BYTE *msg,
						  const unsigned int &size);
};

class InterfaceAppAPI::IFAContext
{
public:
	IFAContext(InterfaceAppAPI &interfaceAppAPI);

	InterfaceAppAPI *mInterfaceAppAPI = nullptr;
};


} /* swms */
} /* marusa */

#endif /* ___INTERFACEAPP_H___ */
