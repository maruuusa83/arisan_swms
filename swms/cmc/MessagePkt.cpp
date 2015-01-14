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

namespace marusa {
namespace swms {


void bytecpy(BYTE *to, const BYTE *from, unsigned int len)
{
	while (len--){
		*to++ = *from++;
	}
}

/*** MessagePkt class ***/
/* constractor */
MessagePkt::MessagePkt() {  }

MessagePkt::MessagePkt(const int &to)
{
	set_to(to);
}

MessagePkt::MessagePkt(const unsigned char &msg_type, const BYTE *data, const unsigned int &size_data)
{
	set_data(msg_type, data, size_data);
}

MessagePkt::MessagePkt(const int &to, const unsigned char &msg_type, const BYTE *data, const unsigned int &size_data)
{
	set_to(to);
	set_data(msg_type, data, size_data);
}

/* methods */
int MessagePkt::set_to(const int &to)
{
	this->to = to;

	return (0);
}

int MessagePkt::set_data(const unsigned char &msg_type, const BYTE *data, const unsigned int &size_data)
{
	this->msg_type = msg_type;

	bytecpy(this->data, data, size_data);
	this->size_data = size_data;

	return (0);
}

int MessagePkt::get_to() const
{
	return (this->to);
}

/**
 * Generate message as byte
 * This metod generate message data as byte.
 * BYTE ** : To save massage data
 * unsigned int * : To save length of message
 */
void MessagePkt::get_msg(BYTE **data, unsigned int &size_data) const
{
	/* save data size */
	size_data = this->size_data;

	/* save data */
	*data = (BYTE *)malloc(MessagePkt::SIZE_MSG_TYPE + MessagePkt::SIZE_DATA_SIZE + sizeof(BYTE) * this->size_data);

	*((unsigned char *)*data) = (unsigned char)this->msg_type;
	*((unsigned int *)(*data + MessagePkt::SIZE_MSG_TYPE)) = (unsigned int)this->size_data;
	bytecpy(*data + MessagePkt::SIZE_MSG_TYPE + MessagePkt::SIZE_DATA_SIZE, this->data, this->size_data);
}

void MessagePkt::free_msg(BYTE *data)
{
	free(data);
}


} /* namespace grad_res */
} /* namespace marusa */

