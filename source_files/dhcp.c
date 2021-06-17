/*********************************FILE__HEADER*********************************\
* File:				dhcp.c
* Author:			Daniel Brodsky				 		  												  								
* Date:				15-06-2021
* Code Reviewer:	
* Pseudo Reviewers: Kobi, Rostik					   								
* Version:			1.0   								
* Description:		DHCP module implementation based on a trie.
\******************************************************************************/

/********************************* Inclusions *********************************/

#include <assert.h>			/*	assert					*/
#include <stddef.h>			/*	size_t, NULL			*/
#include <stdlib.h>			/*	malloc, calloc, free	*/

#include "dhcp.h"

/******************************* macros & enums *******************************/

enum
{
	SUCCESS = 0,
	NO_AVAILABLE_IPS = 1,
	MEMORY_ALLOCATION_ERR = 2
}

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
	trie_node_ty root;
	address_ty subnet;
	int num_variable_bits;
};

/**************************** Forward Declarations ****************************/

static size_t CountFullNodesIMP(trie_node_ty *node, int level);

static int AllocteIpIMP(trie_node_ty **node, address_ty *preferred_ip, 
														int num_variable_bits);
														
static void FreeIpIMP(trie_node_ty *node, address_ty *ip, int level);

static trie_node_ty *TrieCreateIMP(void);
													
/************************* Functions  Implementations *************************/
dhcp_ty *DhcpCreate(address_ty subnet, int num_variable_bits)
{
	dhcp_ty *new_dhcp = NULL;
	
	/* asserts */
	assert(subnet);
	assert(num_variable_bits);
	
	/*	allocate memory for dhcp struct and handle errors*/
	new_dhcp = (dhcp_ty *)malloc(sizeof(dhcp_ty));
	if (!new_dhcp)
	{
		return (NULL);
	}
	
	/*	define the subnet as the "root" of our dhcp */
	new_dhcp->root
	
	/*	assign parameters to dhcp struct memebrs*/
	new_dhcp->subnet = subnet;
	new_dhcp->num_variable_bits = num_variable_bits;
	
	/*	return pointer to dhcp*/
	return (new_dhcp);
}
/******************************************************************************/
void DhcpDestroy(dhcp_ty *dhcp)
{
	if (dhcp)
	{
		TrieDestoryIMP(dhcp->root);
		
		/*	nullify dhcp struct members*/
		memset(dhcp, 0, sizeof(dhcp_ty));
		
		/*	free dhcp*/
		free(dhcp);
	}
}
/******************************************************************************/
int DhcpAllocateIp(dhcp_ty *dhcp, address_ty preferred_ip)
{
	int ret = 0;
	/*	asserts*/
	assert(dhcp);
	
	ret = AllocteIpIMP(&dhcp->root, &preferred_ip, dhcp->num_variable_bits);
	/* if AllocteIpIMP has failed because of a mem error: */
	if (MEMORY_ALLOCATION_ERR == ret)
	{
		return (MEMORY_ALLOCATION_ERR);
	}
	
	/* if AllocteIpIMP has failed because no available ip: */
	if (NO_AVAILABLE_IPS == ret))
	{
		/* TODO Call AllocteIpIMP on the smallest group in the subnet */
		ret = AllocteIpIMP()
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
int AllocteIpIMP(trie_node_ty **node, address_ty *preferred_ip, 
														int num_variable_bits)
{
	trie_node_ty *new_node = NULL;
	
	/*	if node is null:*/
	if (!node)
	{
		/*		create node, handle memory errors */
		new_node = CreateNode(&node);
		if (!new_node)
		{
			return (MEMORY_ALLOCATION_ERR);
		}
		
		/* TODO		connect created node to the tree */
	}
	
	/*	if node is full:*/
	if (node->is_full)
	{
		/*	return  failure	 */
		return (NO_AVAILABLE_IPS);
	}
	
	/*	if num_variable_bits == 0:	*/
	if (!num_variable_bits)
	{
		/*	mark as full	*/
		node->is_full = 1;
		/*	return succeess	*/
		return (SUCCESS);
	}

	/*				// side depends on preferred_ip )*/
	/*	TODO recursively call AllocteIpIMP with needed side (by ip) of node */
	if (SUCCESS == AllocteIpIMP()
	{
		/*	if succeess:*/
		/*		update children of node as full*/
		node->children[0]->is_full = node->children[1]->is_full = 1;
	}
	
	/*	else (failure):	*/
	else
	{
		/* if side was left side, which means we failed to go on left child: TODO*/
		/*			nullify rest of the tree TODO */
		/*			call AllocteIpIMP on right subtree */
		if (SUCCESS == AllocteIpIMP(node->children[1], preferred_ip, num_variable_bits))
		{
			/* if this call was successful: */
			/* update ip to be with '1' at the current level */
			*preferred_ip = 1;
			/* return succeess */
			return (SUCCESS);
		}
	}
		
	/*	return failure */
	return (NO_AVAILABLE_IPS);
}
/******************************************************************************/
void DhcpFreeIp(dhcp_ty *dhcp, address_ty ip)
{
	/*	assert not a special ip address - broadcast and everything	*/
	/*  TODO */
}
/*----------------------------------------------------------------------------*/
void FreeIpIMP(trie_node_ty *node, address_ty *ip, int level)
{
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

	/*	recursively move to next node by level and ip	*/
	FreeIpIMP(node->children[*ip], level - 1);
}
/******************************************************************************/
size_t DhcpCountFree(dhcp_ty *dhcp)
{
	size_t total_number_of_nodes = Pow(2, num_variable_bits);
	/* asserts	*/
	assert(dhcp);
	
	/*	traverse the trie and count occupied nodes using CountFullNodes func */
	/*	substract number of full nodes of the total number of nodes  */
	return (total_number_of_nodes - 
								CountFullNodes(dhcp->root, num_variable_bits));
}
/*----------------------------------------------------------------------------*/
size_t CountFullNodesIMP(trie_node_ty *node, int level)
{
	/*	if node doesn't exist */
	if (!node)
	{
		/*	return (0) 	*/
		return (0);
	}
	
	/*	if node is full, return 2^curr_level				*/
	if (node->is_full)
	{
		return (Pow(2, level));
	}

	/*	scan left subtree and return its size								*/
	/*	scan right subtree and add its size									*/
	/*	return the sum of the sizes											*/
	return (CountFullNodes(node->children[LEFT]) + 
										CountFullNodes(node->children[RIGHT]));
}
/******************************************************************************/
trie_node_ty *TrieCreateIMP(void)
{
	/*	allocate memory and create trie_node struct handler*/
	trie_node_ty *new_trie = (trie_node_ty *)malloc(sizeof(trie_node_ty));
	if (!new_trie)
	{
		/*	handle errors if any*/
		return (NULL);
	}
	
	/*	nullify members*/
	memset (new_trie, 0, sizeof(trie_node_ty));
	
	/*	return trie */
	return (new_trie);
	
}
/******************************************************************************/
static void TrieDestory(trie_node_ty *root)
{
	
}
