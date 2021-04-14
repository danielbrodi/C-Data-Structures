/************************************************
* File: operation_func.h						*
* Date: 13/04/2021							    *
* Version: 1.0 								    *
* Description:  Operation Func typdef     		* 
************************************************/
#ifndef	__OPERATION_FUNC_H__
#define	__OPERATION_FUNC_H__

typedef enum
{
    FAILURE = -1,
	DONE = 0,
	NOT_DONE = 1
} oper_ret_ty;

/* Function returns enum:*/
/* -1 FAILURE            */
/*  0 DONE               */
/*  1 NOT DONE           */
typedef oper_ret_ty (*operation_func_ty)(void *param);

#endif  /* __OPERATION_FUNC_H__ */
