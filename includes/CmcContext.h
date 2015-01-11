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
#include "./InterfaceAppAPI.h"
#include "./CmcAdapter.h"

namespace marusa {
namespace swms {


class CmcAdapter::CmcCallbackListener::CMCContext
{
public:
	int setIFACallbackListener(const InterfaceAppAPI::IFACallbackListener &ifaCallbackListener);
};


} /* swms */
} /* marusa */

#endif /* ___CMCCONTEXT_H___ */



