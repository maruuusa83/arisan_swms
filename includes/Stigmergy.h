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

private:
	CmcAdapter *mCmc;
};

class Stigmergy::SGYCallbackListener
{
public:
	virtual void onRecvTask(const SGYContext &context,
							const BYTE *task) const;
};

class Stigmergy::SGYContext
{
public:
	SGYContext(const Stigmergy &stigmergy);

	Stigmergy *mSGY = nullptr;
};


} /* swms */
} /* marusa */

#endif /* ___STIGMERGY_H___ */


