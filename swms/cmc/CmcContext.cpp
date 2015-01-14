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
#include "CmcContext.h"

namespace marusa {
namespace swms {


int CmcAdapter::CmcContext::setIFACallbackListener(const InterfaceAppAPI::IFACallbackListener &ifaCallbackListener)
{
	this->mIFACallbackListener = ifaCallbackListener;
	return (0);
}

int CmcAdapter::CmcContext::setTPCallbackListener(const TaskProcessorAPI::TPCallbackListener &tpCallbackListener)
{
	this->mTPCallbackListener = tpCallbackListener;
	return (0);
}
int CmcAdapter::CmcContext::setSGYCallbackListener(const Stigmergy::SGYCallbackListener &sgyCallbackListener)
{
	this->mSGYCallbackListener = sgyCallbackListener;
	return (0);
}

InterfaceAppAPI::IFACallbackListener CmcAdapter::CmcContext::getIFACallbackListener() const
{
	return (this->mIFACallbackListener);
}

TaskProcessorAPI::TPCallbackListener CmcAdapter::CmcContext::getTPCallbackListener() const
{
	return (this->mTPCallbackListener);
}

Stigmergy::SGYCallbackListener CmcAdapter::CmcContext::getSGYCallbackListener() const
{
	return (this->mSGYCallbackListener);
}


} /* swms */
} /* marusa */


