/************************
*File: dhcp.h			*
*Date: 15/04/2021		*
*Version: 1.2			*
*Description: DHCP API	*
*************************/

#ifndef __DHCP_H__
#define __DHCP_H__

#include <stddef.h>	/*	size_t	*/

typedef struct dhcp dhcp_ty;

typedef unsigned int address_ty;

/*in case of complilation error replace unsigned int with a 4 byte integral type */
typedef int static_assert_check[2/(sizeof(address_ty)==4)];

/*Creates a new dhcp handler struct*/
/*preallocates network, broadcast and server address*/
/*Returns NULL on failure*/
/*Complexity: O(1)*/
dhcp_ty *DhcpCreate(address_ty subnet, int num_variable_bits);


/*Complexity: O(k) - k is the amount of allocated ips*/
void DhcpDestroy(dhcp_ty *dhcp);

/*RETURNS 0 on successful ip allocation*/
/*RETURNS: 1 if no ips are available*/
/*RETURNS: 2 if memory allocation failure*/
/*Pass 0 as preferred_ip if you don't care*/
/*Complexity: O(log(n)) - n is the max number of available ips*/
int DhcpAllocateIp(dhcp_ty *dhcp, address_ty *preferred_ip);

/*Complexity: O(log(n)) - n is the max number of available ips*/
void DhcpFreeIp(dhcp_ty *dhcp, address_ty ip);

/*Complexity: O(n) - n is the max number of available ips*/
size_t DhcpCountFree(dhcp_ty *dhcp);

#endif /*__DHCP_H__*/
