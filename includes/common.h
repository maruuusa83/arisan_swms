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
#ifndef ___COMMON_H___
#define ___COMMON_H___

#define ___DEBUG_TRANS_TASK_IFA2SGY___

namespace marusa {
namespace swms {


/*** COMMON ***/
typedef unsigned char BYTE;

/*** Stigmagy Layer ***/
typedef unsigned int JOB_ID;
typedef unsigned int TASK_ID;
typedef unsigned int WORKER_ID;

static const unsigned int TASK_ID_NO_TASK = 0;

/*** Messaging Layer ***/
typedef unsigned int HOST_ID;

typedef struct _task_pkt {
	JOB_ID job_id;
	TASK_ID task_id;
	unsigned int div_id;
	unsigned int data_size;
} TASK_PKT_HEADER;

} /* swms */
} /* marusa */

#endif /* ___COMMON_H___ */
