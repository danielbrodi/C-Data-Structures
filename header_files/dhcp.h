/*********************************FILE__HEADER*********************************\
* File:				dhcp.h						 		  								
* Author:			Daniel Brodsky					  								
* Date:				15-06-2021							   												   								
* Description:		DHCP module API.		 
\******************************************************************************/

#ifndef __DHCP_H__
#define __DHCP_H__

#include <stddef.h>		/*	size_t	*/

dhcp_ty *CreateDhcp(void *subnet_id);

void *Allocatelp(dhcp_ty *dhcp);

void Freelp(dhcp_ty *dhcp);

size_t CountFree(dhcp_ty *dhcp);


#endif	/* __DHCP_H__	*/
