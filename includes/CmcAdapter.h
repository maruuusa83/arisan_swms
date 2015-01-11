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
#ifndef ___CMCADAPTER_H___
#define ___CMCADAPTER_H___

#include "./common.h"

namespace marusa {
namespace swms {


class CmcAdapter
{
public:
	class CmcCallbackListener;
		
	/***    Common    ***/
	CmcAdapter();
	CmcAdapter(CmcCallbackListener *listener);
	virtual ~CmcAdapter();
		
	virtual int sendMessage(const HOST_ID &host_id,
							const BYTE *msg);
			
			
	/***  For Worker  ***/
	virtual HOST_ID connToStigma();
				
	/*** For Stigmagy ***/
	virtual int startListen();

	
	/*** Special host ID ***/
	static const HOST_ID HOST_ID_STIGMAGY  = 0x00000000;
	static const HOST_ID HOST_ID_BROADCAST = 0xFFFFFFFF;

private:
	CmcCallbackListener *listener;
};

class CmcAdapter::CmcCallbackListener
{
public:
	class CmcContext;

	void onMessage(const HOST_ID &hostid,
				   const BYTE *msg);

	void onNewWorker(const HOST_ID &host_id);

	void onDisconnWorker(const HOST_ID &host_id);
};


} /* swms */
} /* marusa */

#endif /* ___CMCADAPTER_H___ */


