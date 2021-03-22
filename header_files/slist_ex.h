/******************************************************************************\
* File: slist_ex.h						 		   
* Date: 23/03/2021							   
* Version: 1.0 							   
* Description: Single Linked List API		    
*******************************************************************************/
#ifndef	__SLIST_EX_H__
#define	__SLIST_EX_H__

typedef struct node node_t;

/* Reverses the order of a given slist. */

node_t *Flip(node_t *head);

/* Tells whether a given slists has loop. */

int HasLoop(const node_t *head);

/* Returns a pointer to a first node matual to both slists, if any. */

node_t *FindIntersection(node_t *head_1, node_t *head_2);	
				 
#endif	/* __SLIST_EX_H__ */
