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
#ifndef ___STIGMERGY_H___
#define ___STIGMERGY_H___

#include "./common.h"
#include "./CmcAdapter.h"
#include "./Result.h"

#include <map>

namespace marusa {
namespace swms {


class Stigmergy
{
public:
	class SGYCallbackListener;
	class SGYContext;

	Stigmergy(CmcAdapter *cmc);
	virtual ~Stigmergy();

	int startStigmergy();

	int sendTaskList(HOST_ID to);
	int sendResultList(HOST_ID to);
	int addTask(std::pair<JOB_ID, TASK_ID> &task_uid,
				const BYTE *data,
				const unsigned int data_size);
	int delTask(const std::pair<JOB_ID, TASK_ID> &task_uid);

	int addResult(const Result &result);

	int sendTaskFin(HOST_ID to);

private:
	CmcAdapter *mCmc;

	std::map<std::pair<JOB_ID, TASK_ID>, TASK_INFO *> mMapTasks;
	std::map<std::pair<JOB_ID, TASK_ID>, Result *> mMapResults;
};

class Stigmergy::SGYCallbackListener
{
public:
	virtual void onRecvTask(const SGYContext &context,
							const BYTE *task);
	virtual void onRecvReqTaskList(const Stigmergy::SGYContext &context,
								   const HOST_ID &from);
	virtual void onRecvTaskFin(const SGYContext &context,
							   const Result &result,
							   const HOST_ID &from);
	virtual void onRecvReqResultList(const Stigmergy::SGYContext &context,
								   const HOST_ID &from);
};

class Stigmergy::SGYContext
{
public:
	SGYContext(Stigmergy *stigmergy);

	Stigmergy *mSGY = nullptr;
};


} /* swms */
} /* marusa */

#endif /* ___STIGMERGY_H___ */


