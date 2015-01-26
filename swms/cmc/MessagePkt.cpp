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
#include "MessagePkt.h"
#include <stdlib.h>

#ifdef ___DEBUG_TRANS_TASK_IFA2SGY___
#include <stdio.h>
#include <iostream>
#endif /* ___DEBUG_TRANS_TASK_IFA2SGY___ */

namespace marusa {
namespace swms {


void bytecpy(BYTE *to,
			 const BYTE *from,
			 const unsigned int &len)
{
	for (unsigned int i = 0; i < len; i++){
		to[i] = from[i];
	}
}


/*** MessagePkt class ***/
/* constractor */
MessagePkt::MessagePkt() {  }

MessagePkt::MessagePkt(const int &to)
{
	set_to(to);
}

MessagePkt::MessagePkt(const int &from, const BYTE *msg)
{
	set_to(from);
	set_data(*(unsigned char *)msg, &msg[SIZE_MSG_TYPE + SIZE_DATA_SIZE], *(unsigned int *)&msg[SIZE_MSG_TYPE]);

#ifdef ___DEBUG_TRANS_TASK_IFA2SGY___
	printf("MessagePkt::MessagePkt - gen from bin data\n");
	printf("\ttype : %d\n", *(unsigned char *)msg);
	printf("\tsize : %d\n", *(unsigned int *)&msg[SIZE_MSG_TYPE]);
#endif /* ___DEBUG_TRANS_TASK_IFA2SGY___ */
}

MessagePkt::MessagePkt(const int &to, const unsigned char &msg_type, const BYTE *data, const unsigned int &size_data)
{
	set_to(to);
	set_data(msg_type, data, size_data);
}

MessagePkt::~MessagePkt()
{
	free(this->data);
}


/* methods */
int MessagePkt::set_to(const int &to)
{
	this->to = to;

	return (0);
}

int MessagePkt::set_data(const unsigned char &msg_type,
						 const BYTE *data,
						 const unsigned int &size_data)
{
	this->msg_type = msg_type;

	this->data = (BYTE *)malloc(sizeof(BYTE) * size_data);
	bytecpy(this->data, data, size_data);
	this->size_data = size_data;

	return (0);
}

int MessagePkt::get_to() const
{
	return (this->to);
}

int MessagePkt::get_data(BYTE **data, unsigned int &size_data) const
{
	*data = (BYTE *)malloc(sizeof(BYTE) * this->size_data);
	bytecpy(*data, this->data, this->size_data);
	size_data = this->size_data;

	return (0);
}

/**
 * Generate message as byte
 * This method generate message data as byte.
 * BYTE ** : To save message data
 * unsigned int & : To save length of message
 */
void MessagePkt::get_msg(BYTE **data, unsigned int &size_msg) const
{
	/* save data size */
	size_msg = this->size_data + MessagePkt::SIZE_MSG_TYPE + MessagePkt::SIZE_DATA_SIZE;

	/* save data */
	*data = (BYTE *)malloc(size_msg * sizeof(BYTE));

	*((unsigned char *)*data) = (unsigned char)this->msg_type;
	*((unsigned int *)(*data + MessagePkt::SIZE_MSG_TYPE)) = (unsigned int)this->size_data;
	bytecpy(*data + MessagePkt::SIZE_MSG_TYPE + MessagePkt::SIZE_DATA_SIZE, this->data, this->size_data);
}

unsigned char MessagePkt::get_msg_type() const
{
	return (this->msg_type);
}

void MessagePkt::free_msg(BYTE *data)
{
	free(data);
}

}
}

