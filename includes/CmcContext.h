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
#ifndef ___CMCCONTEXT_H___
#define ___CMCCONTEXT_H___

#include "./common.h"

#include "./TaskProcessorAPI.h"
#include "./InterfaceAppAPI.h"
#include "./Stigmergy.h"

#include "./CmcAdapter.h"

namespace marusa {
namespace swms {


class CmcAdapter::CmcContext
{
public:
	int setIFACallbackListener(const InterfaceAppAPI::IFACallbackListener &ifaCallbackListener);
	int setTPCallbackListener(const TaskProcessorAPI::TPCallbackListener &tpCallbackListener);
	int setSGYCallbackListener(const Stigmergy::SGYCallbackListener &sgyCallbackListner);

	const InterfaceAppAPI::IFACallbackListener &getIFACallbackListener() const;
	const TaskProcessorAPI::TPCallbackListener &getTPCallbackListener() const;
	const Stigmergy::SGYCallbackListener &getSGYCallbackListener() const;


	int setIFAContext(const InterfaceAppAPI::IFAContext &ifaContext);
	int setTPContext(const TaskProcessorAPI::TPContext &tpContext);
	int setSGYContext(const Stigmergy::SGYContext &sgyCallbackListner);

	const InterfaceAppAPI::IFAContext &getIFAContext() const;
	const TaskProcessorAPI::TPContext &getTPContext() const;
	const Stigmergy::SGYContext &getSGYContext() const;

private:
	InterfaceAppAPI::IFACallbackListener mIFACallbackListener;
	InterfaceAppAPI::IFAContext mIFAContext;

	TaskProcessorAPI::TPCallbackListener mTPCallbackListener;
	TaskProcessorAPI::TPContext mTPContext;

	Stigmergy::SGYCallbackListener mSGYCallbackListener;
	Stigmergy::SGYContext mSGYContext;
};


} /* swms */
} /* marusa */

#endif /* ___CMCCONTEXT_H___ */



