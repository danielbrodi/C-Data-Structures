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
typdef struct trie_node
{
	struct trie_node *children[2];
	struct trie_node *parent;
	int is_full;
}

/* trie struct. may need more members */
typedef struct trie
{
	trie_node_ty *root;
}trie_ty;



/* DHCP manager */
struct dhcp
{
	trie_ty *trie;
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
int DhcpAllocateIp(dhcp_ty *dhcp, address_ty *preferred_ip)
{
	/*	asserts*/
	
	/* undefined if preferred_ip is not dhc's subnet */
	
	/*	if trie of dhcp is full:*/
	/*		return 1*/
	
	/*	if preferred_ip is not 0:*/
	/*		traverse the trie to find out if its available or not*/
	/*		trie insert each time to allocate this preferred_ip*/
	
	/*		if preferred_ip is not available or preferred_ip is 0:*/
	/*		scan for te first available ip*/
	/*		if (FindIpIMP(dhcp)) //
			 helper function to find IP and if it was not found or not free
	 	 		return first available ip after it*/
	/*			return 0*/
	/*		if null it means no available ip addresses -> return 1;*/
}	
/*-------------------------------_RECURSIVE_----------------------------------*/

/*	if next  is full:*/
	/*		return 1*/

	/*if no node:*/
	/*	allocate node*/

	/*move to child node by the needed ip*/
	

/******************************************************************************/
void DhcpFreeIp(dhcp_ty *dhcp, address_ty ip)
{
	/*	asserts*/
	/* use FindIpIMP to find ip 	*/
	/* if found: */
	
/*	if null: return*/

/*	if reach the end of ip:*/
/*		return*/
/*		decrement ip pointer by one*/

/*	reach the end of ip*/
/*		free(node)*/
}
/******************************************************************************/
size_t DhcpCountFree(dhcp_ty *dhcp)
{
	/*	traverse the trie and count free nodes*/
}
/******************************************************************************/
trie_ty *TrieCreateIMP(root?)
{
/*	allocate memory and create trie_ty struct handler*/
/*	handle errors if any*/
/*	*/
/*	allocate memory and create node that will be used as a root*/
/*	handle errors if any*/
/*	*/
/*	return trie */
}
