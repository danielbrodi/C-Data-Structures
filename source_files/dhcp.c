/*********************************FILE__HEADER*********************************\
* File:				dhcp.c
* Author:			Daniel Brodsky				 		  												  								
* Date:				15-06-2021
* Code Reviewer:	Ariel
* Pseudo Reviewers: Kobi, Rostik					   								
* Version:			1.0   								
* Description:		DHCP module implementation based on a trie.
\******************************************************************************/

/********************************* Inclusions *********************************/

#include <assert.h>			/*	assert					*/
#include <math.h>			/*	pow						*/
#include <stddef.h>			/*	size_t, NULL			*/
#include <stdlib.h>			/*	malloc, calloc, free	*/
#include <string.h>			/*	memset					*/

#include "dhcp.h"

/******************************* macros & enums *******************************/

/*	status indication of a finished ip allocation operation					*/
enum
{
	SUCCESS = 0,
	NO_AVAILABLE_IPS = 1,
	MEMORY_ALLOCATION_ERR = 2
};

/*	from which direction the child node connected to its parent node		*/
enum
{
	LEFT = 0,
	RIGHT = 1
};
/**************************** Structs  Definitions ****************************/

/* trie's nodes strucure */
typedef struct trie_node
{
	int is_full;
	struct trie_node *children[2];
}trie_node_ty;

/* DHCP manager */
struct dhcp
{
	int num_variable_bits;
	address_ty subnet;
	trie_node_ty root;
};

/**************************** Forward Declarations ****************************/

/*	returns the number of the full (allocated) ips in the dhcp */
static size_t CountUsedIpsIMP(trie_node_ty *node, int level);

/*	allocates an ip based on a request	*/
/*	RETURNS  0 on successful ip allocation			*/
/*	RETURNS: 1 if no ips are available				*/
/*	RETURNS: 2 if memory allocation failure			*/
static int AllocateIpIMP(trie_node_ty **node, address_ty *preferred_ip, 
														int num_variable_bits);
/* frees up an previously allocaed ip */											
static void FreeIpIMP(trie_node_ty *node, address_ty *ip, int level);

/*	allocates memory and creates a new clean new trie node */
static trie_node_ty *TrieCreateNodeIMP(void);

/*	recursively traverses through trie, in a post order way,
 *	and frees every node.													*/
void TrieDestroyIMP(trie_node_ty *node);

/*	returns whether a given node is full or not				*/			
static int IsNodeFull(trie_node_ty *node);

/*	returns side to advance based on ip and level	*/
static int GetSideToGo(address_ty ip, int level);	
/************************* Functions  Implementations *************************/
dhcp_ty *DhcpCreate(address_ty subnet, int num_variable_bits)
{
	dhcp_ty *new_dhcp = NULL;
	
	address_ty network_address = 0;
	address_ty server_address = 0;
	address_ty broadcast_address = 0;
	
	/* asserts */
	assert(subnet);
	assert(num_variable_bits);
	
	/*	allocate memory for dhcp struct and handle errors*/
	new_dhcp = (dhcp_ty *)calloc(1,sizeof(dhcp_ty));
	if (!new_dhcp)
	{
		return (NULL);
	}
	
	/*	define the subnet as the "root" of our dhcp */
	
	/*	assign parameters to dhcp struct memebrs*/
	new_dhcp->subnet = subnet;
	new_dhcp->num_variable_bits = num_variable_bits;
	
	/*	define the addresses that are allocated impliclity	*/
	network_address = subnet;
	broadcast_address = subnet | (((address_ty)1 << new_dhcp->num_variable_bits) - 1);
	server_address = broadcast_address - 1;
	
	/*	allocate reserved ip addresses	*/
	DhcpAllocateIp(new_dhcp, &network_address);
	DhcpAllocateIp(new_dhcp, &server_address);
	DhcpAllocateIp(new_dhcp, &broadcast_address);
	
	
	/*	return pointer to dhcp*/
	return (new_dhcp);
}
/******************************************************************************/
void DhcpDestroy(dhcp_ty *dhcp)
{
	if (dhcp)
	{
		TrieDestroyIMP(dhcp->root.children[LEFT]);
		TrieDestroyIMP(dhcp->root.children[RIGHT]);
		
		/*	nullify dhcp struct members*/
		memset(dhcp, 0, sizeof(dhcp_ty));
		
		/*	free dhcp*/
		free(dhcp);
	}
}
/******************************************************************************/
int DhcpAllocateIp(dhcp_ty *dhcp, address_ty *preferred_ip)
{
	int ret = 0;
	trie_node_ty *root_ptr = NULL;
	
	/*	asserts*/
	assert(dhcp);
	
	root_ptr = &dhcp->root;
	
	ret = AllocateIpIMP(&root_ptr, preferred_ip, dhcp->num_variable_bits);
	/* if AllocateIpIMP has failed because of a mem error: */
	if (MEMORY_ALLOCATION_ERR == ret)
	{
		return (MEMORY_ALLOCATION_ERR);
	}
	
	/* if AllocateIpIMP has failed because no available ip: */
	if (NO_AVAILABLE_IPS == ret)
	{
		/* Call AllocateIpIMP on the smallest ip in the subnet */
		ret = AllocateIpIMP(&root_ptr, &dhcp->subnet, dhcp->num_variable_bits);
		/* If also this failed: */
		if (NO_AVAILABLE_IPS == ret)
		{
			/* return failured */
			return (NO_AVAILABLE_IPS);
		}
	}
		
	/*	return success*/
	return (SUCCESS);
}
/*----------------------------------------------------------------------------*/
int AllocateIpIMP(trie_node_ty **node, address_ty *preferred_ip, 
														int num_variable_bits)
{
	int level = num_variable_bits;
	
	trie_node_ty **next_node = NULL;
	trie_node_ty *curr_node = NULL;
	int child_side = LEFT;
		
	/*	if node is null:*/
	if (!(*node))
	{
		/*		create node, handle memory errors */
		trie_node_ty *new_node = TrieCreateNodeIMP();
		if (!new_node)
		{
			return (MEMORY_ALLOCATION_ERR);
		}
		
		/* connect created node to the tree */
		*node = new_node;
	}
	
	/*	if node is full:*/
	if (((*node)->is_full))
	{
		/*	return  failure	 */
		return (NO_AVAILABLE_IPS);
	}
	
	/*	if num_variable_bits == 0 (the level is 0): 	*/
	if (!num_variable_bits)
	{
		/*	mark node as full	*/
		(*node)->is_full = 1;
		
		/*	return succeess	*/
		return (SUCCESS);
	}

	/*				// side depends on preferred_ip )*/
	/*	recursively call AllocateIpIMP with correct side (by ip) of node */
	curr_node = *node;
	
	/* determine from which side the node is connected to its parent */
	child_side = GetSideToGo(*preferred_ip, level - 1);
	
	/*next_node = child of node at correct side*/
	next_node = &(curr_node->children[child_side]);
	
	if (SUCCESS == AllocateIpIMP(next_node, preferred_ip, level - 1))
	{
		/*	if succeess:*/
		/*		update fulness based on child nodes fulness status 	*/
		curr_node->is_full = (IsNodeFull(curr_node->children[LEFT]) & 
										IsNodeFull(curr_node->children[RIGHT]));
		/*return success*/
		return (SUCCESS);
	}
	
	/*	else (failure):	*/
	else
	{
		/*	if side was left side, which means we failed to go on left child */
		if (curr_node->children[LEFT] == *next_node)
		{
			/*	nullify rest of the subtree */
			*preferred_ip =  (*preferred_ip & (~(((address_ty)1 << level) - 1)));
			
			/*	call AllocateIpIMP on right subtree */
			if (SUCCESS == AllocateIpIMP(&curr_node->children[RIGHT], 
													preferred_ip, level - 1))
			{
				/* if this call was successful: */
				/* update ip to be with '1' at current level + 1 */
				*preferred_ip |= ((address_ty)1 << (level - 1));
				
				/*	update fulness based on child nodes fulness status 	*/
				curr_node->is_full = (IsNodeFull(curr_node->children[LEFT]) & 
										IsNodeFull(curr_node->children[RIGHT]));
				
				/* return succeess */
				return (SUCCESS);
			}
		}
	}
		
	/*	return failure */
	return (NO_AVAILABLE_IPS);
}
/*----------------------------------------------------------------------------*/
int IsNodeFull(trie_node_ty *node)
{
	return (!!(node && node->is_full));
}
/*----------------------------------------------------------------------------*/
int GetSideToGo(address_ty ip, int level)
{
	return (!!(ip & ((address_ty)1 << level)));
}
/******************************************************************************/
void DhcpFreeIp(dhcp_ty *dhcp, address_ty ip)
{
	/*	assert not a special ip address - broadcast, subnet or server address */
	assert(dhcp);
	assert(dhcp->subnet);
	
	/*	free ip from dhcp's trie using FreeIpIMP	*/
	FreeIpIMP(&dhcp->root, &ip, dhcp->num_variable_bits);
}
/*----------------------------------------------------------------------------*/
void FreeIpIMP(trie_node_ty *node, address_ty *ip, int level)
{
	trie_node_ty *next_node = NULL;
	
	/*	if node does not exist:*/
	if (!node)
	{
		/*	return	*/
		return;
	}
	
	/*	mark as not full*/
	node->is_full = 0;
	
	/*	if level is 0:*/
	if (!level)
	{
		/*	return */
		return;
	}

	/*	next_node = get next child by ip_to_free		*/
	next_node = node->children[GetSideToGo(*ip, level - 1)];
	
	/*	recursively move to next node by level and ip	*/
	FreeIpIMP(next_node, ip, level - 1);
}
/******************************************************************************/
size_t DhcpCountFree(dhcp_ty *dhcp)
{
	size_t num_of_ips = 0, num_of_allocated_ips = 0;
	
	/* asserts	*/
	assert(dhcp);
	
	num_of_ips = pow(2, dhcp->num_variable_bits);
	
	/*	traverse the trie and count occupied nodes using CountFullNodes func */
	num_of_allocated_ips = CountUsedIpsIMP(&dhcp->root, dhcp->num_variable_bits);
	
	/*	substract number of full nodes of the total number of nodes  */
	return (num_of_ips - num_of_allocated_ips);
}
/*----------------------------------------------------------------------------*/
size_t CountUsedIpsIMP(trie_node_ty *node, int level)
{
	/*	if node doesn't exist */
	if (!node)
	{
		/*	return (0) 	*/
		return (0);
	}
	
	/*if at lowest level*/
	if (!level)
	{
		/*return if full or not*/
		return (node->is_full);
	}
	
	/*	if node is full, return 2^curr_level				*/
	if (node->is_full)
	{
		return (pow(2, level));
	}

	/*	scan left subtree and return its size								*/
	/*	scan right subtree and add its size									*/
	/*	return the sum of the sizes											*/
	return (CountUsedIpsIMP(node->children[LEFT], level - 1) + 
						CountUsedIpsIMP(node->children[RIGHT], level - 1));
}
/******************************************************************************/
trie_node_ty *TrieCreateNodeIMP(void)
{
	/*	allocate memory and create trie_node struct handler*/
	trie_node_ty *new_node = (trie_node_ty *)calloc(1, sizeof(trie_node_ty));
	
	/*	return trie */
	return (new_node);
}
/******************************************************************************/
void TrieDestroyIMP(trie_node_ty *node)
{
	/*	if node does not exist do nothing					*/
	if (!node)
	{
		return;
	}
	
	/*	recursivly scan the left subtree and destroy it						*/
	TrieDestroyIMP(node->children[LEFT]);
	/*	recursivly scan the right subtree and destroy it					*/
	TrieDestroyIMP(node->children[RIGHT]);
	
	/*	nullify node's children nodes fields */
	memset(node, 0, sizeof(trie_node_ty));
	
	/*	free reached node because it has no child nodes					*/
	free(node);
}
/******************************************************************************/
