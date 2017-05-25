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
#ifndef ___MESSAGEPKT_H___
#define ___MESSAGEPKT_H___

#include "./common.h"

namespace marusa {
namespace swms {


void bytecpy(BYTE *to, const BYTE *from, const unsigned int &len);

class MessagePkt
{
public:
	MessagePkt();
	MessagePkt(const int &to);
	MessagePkt(const int &from, const BYTE *msg);
	MessagePkt(const unsigned char &msg_type, const BYTE *data, const unsigned int &size_data);
	MessagePkt(const int &to, const unsigned char &msg_type, const BYTE *data, const unsigned int &size_data);

	virtual ~MessagePkt();

	int set_to(const int &to);
	int set_data(const unsigned char &msg_type, const BYTE *data, const unsigned int &size_data);

	int get_to() const;
	int get_data(BYTE **data, unsigned int &size_data) const;
	void get_msg(BYTE **data, unsigned int &size_msg) const;
	unsigned char get_msg_type() const;

	static void free_msg(BYTE *data);

	/* Constants */
	static const int SIZE_MSG_TYPE	= 1;
	static const int SIZE_DATA_SIZE	= 4;
	static const int MAX_DATA_SIZE = 100000;


	/* Message types */
	static const int MSG_SEND_TASK		= 0;
	static const int MSG_REQ_TASKRES	= 1;
	static const int MSG_REQ_RESULTLIST = 2;
	static const int MSG_REP_RESULTLIST = 3;

	static const int MSG_RET_JOBID		= 4;
	static const int MSG_NOTE_TASKFIN	= 5;
	static const int MSG_RET_TASKRES	= 6;

	static const int MSG_RET_TASKLIST	= 7;
	static const int MSG_RET_TASK		= 8;
	static const int MSG_NOTE_TASKRES	= 9;

	static const int MSG_REQ_TASKLIST	= 10;
	static const int MSG_REQ_TASK		= 11;

	static const int MSG_NOTE_TASKFIN_IF = 6;

	static const int MSG_TYPE_PLUS_ONE	= 13;

private:
	HOST_ID to = 0;
	unsigned char msg_type = MSG_TYPE_PLUS_ONE;
	unsigned int size_data = 0;
	BYTE *data = nullptr;
};


} /* namespace swms */
} /* namespace marusa */

#endif /* ___MSGPAKCET_H___ */

