/*********************************FILE__HEADER*********************************\
* File:				dhcp.c
* Author:			Daniel Brodsky				 		  												  								
* Date:				15-06-2021
* Code Reviewer:	
* Pseudo Reviewers: Kobi, Rostik					   								
* Version:			1.0   								
* Description:		DHCP module implementation pseudocode.
\******************************************************************************/

/* trie's nodes strucure */
typedef struct trie_node
{
	int is_full;
	struct trie_node *children[2];
}trie_node_ty;

/* DHCP manager */
struct dhcp
{
	trie_node_ty rooti;
	address_ty subnet;
	int num_variable_bits;
};
/*****************************Pseudo-Code*************************************/
/******************************************************************************/
dhcp_ty *DhcpCreate(address_ty subnet, int num_variable_bits)
{
	/*	allocate memory for dhcp struct and handle errors*/

	/*	allocate memory and create trie, handle errors*/
	/*	assign it to dhcp*/
	
	/*	assign parameters to dhcp struct memebrs*/
	
	/*	return pointer to dhcp*/
}
/******************************************************************************/
void DhcpDestroy(dhcp_ty *dhcp)
{
	/*	destroy trie*/
	/*	nullify dhcp struct members*/
	/*	free dhcp*/
}
/******************************************************************************/
int DhcpAllocateIp(dhcp_ty *dhcp, address_ty preferred_ip)
{
	/*	asserts*/
	
	/* if AllocteIpIMP has failed: */
		/* Call AllocteIpIMP on the smallest group in the subnet */
		/* If also this failed: */
			/* return failured */
		
	/*	return success*/
}
/*----------------------------------------------------------------------------*/
static int AllocteIpIMP(trie_node_ty **node, address_ty *preferred_ip, int num_variable_bits)
{
	
	/*	if node is null:*/
	/*		create node, handle memory errors */
	/*		connect created node to the tree */
	
	/*	if node is full:*/
	/*		return  failure */

	/*	if num_variable_bits == 0:*/
	/*		mark as full*/
	/*		return succeess*/


	/*				// side depends on preferred_ip )*/
	/*	recursively call AllocteIpIMP with needed side (by ip) of node 
	/*	if succeess:*/
	/*		update children of node as full*/

	/*	else (failure):	*/
		/* if side was left side, which means we failed to go on left child:*/
		/*			nullify rest of the tree*/
		/*			call AllocteIpIMP on right subtree
					if this call was successful:
						update ip to be with '1' at the current level
						return succeess

		/*	return failure */
}
/******************************************************************************/
void DhcpFreeIp(dhcp_ty *dhcp, address_ty ip)
{
	/*	assert not a special ip address - broadcast and everything	*/
	/*  */
}
/*----------------------------------------------------------------------------*/
FreeIpIMP(trie_node_ty *node, address_ty *ip, int level)
{
	/*	if node does not exist:*/
	/*		return*/

	/*	mark as not full*/

	/*	if level is 0:*/
	/*		return */

	/*	recursively move to next node by level and ip	*/
}
/******************************************************************************/
size_t DhcpCountFree(dhcp_ty *dhcp)
{
	/*	traverse the trie and count occupied nodes using CountFullNodes func */
	/*	substract number of full nodes of the total number of nodes (2 ^ num_variable_bits) */
}
/*----------------------------------------------------------------------------*/
size_t CountFullNodesIMP(trie_node_ty *node, int level)
{
	/*	if node doesn't exist */
	/*	return (0) 	*/
	
	/*	if node is full, return 2^curr_level				*/

	/*	scan left subtree and return its size								*/
	/*	scan right subtree and add its size									*/
	/*	return the sum of the sizes											*/
/*	return (CountFullNodes(node->children[LEFT]) + */
/*				CountFullNodes(node->children[RIGHT]));*/
}
/******************************************************************************/
static trie_node_ty *TrieCreateIMP(void)
{
	/*	allocate memory and create trie_node struct handler*/
	/*	handle errors if any*/
	
	/*	return trie */
}
/******************************************************************************/
static void TrieDestory(trie_node_ty *root)
{
	
}
