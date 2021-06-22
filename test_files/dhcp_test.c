/************************
*File: dhcp_test.c		*
*Owner: Eran			*
*Reviewer: Danel		*
*************************/
#include <stddef.h>	/* size_t */
#include <stdio.h>	/*  */
#include "dhcp.h"
#include "utils_testing_eran.h"
#include "utils_eran.h"

/********************* Test Function Declarations ***********************/
static void TestCreateDestroy(void);
static void TestAllocateIP(void);
static void TestFreeIP(void);

/********************* Main ***********************/
int main ()
{
	TestCreateDestroy();
	TestAllocateIP();
	TestFreeIP();
	
	return 0;
}

static void TestCreateDestroy(void)
{
	status_ty status = SUCCESS;
	address_ty subnet = 0xABCDEF00;
	size_t variable_bits = 4;
	dhcp_ty *dhcp = DhcpCreate(subnet, variable_bits);
	
	PRINT_TEST_CASE("Creating several dhcp's and counting free IPs\n")
	
	STATUS_TEST(DhcpCountFree, dhcp, (1<<4) - 3, "CountFree, Create")
	DhcpDestroy(dhcp);
	
	variable_bits = 8;
	dhcp = DhcpCreate(subnet, variable_bits);
	STATUS_TEST(DhcpCountFree, dhcp, (1<<8) - 3, "CountFree, Create")
	DhcpDestroy(dhcp);
	
	variable_bits = 3;
	dhcp = DhcpCreate(subnet, variable_bits);
	STATUS_TEST(DhcpCountFree, dhcp, (1<<3) - 3, "CountFree, Create")
	DhcpDestroy(dhcp);

	variable_bits = 2;
	dhcp = DhcpCreate(subnet, variable_bits);
	STATUS_TEST(DhcpCountFree, dhcp, (1<<2) - 3, "CountFree, Create")
	DhcpDestroy(dhcp);
	
	PRINT_SUCCESS(status)
}

static void TestAllocateIP(void)
{
	status_ty status = SUCCESS;
	address_ty subnet = 0xABCDEF00;
	address_ty wanted = 0xABCDEF01;
	address_ty used =   0xABCDEF02;
	address_ty any = 0;
	size_t variable_bits = 2;
	dhcp_ty *dhcp = DhcpCreate(subnet, variable_bits);

	PRINT_TEST_CASE("Allocating IPs - both existing and not and after freeing\n")

	STATUS_TEST(DhcpCountFree, dhcp, (1<<2) - 3, "CountFree")

	STATUS_TEST_2PARAM(DhcpAllocateIp, dhcp, &wanted, 0, "Allocate IP")
	STATUS_TEST(DhcpCountFree, dhcp, (1<<2) - 4, "CountFree")
	STATUS_TEST_2PARAM(DhcpAllocateIp, dhcp, &wanted, 1, "Allocate IP")
	STATUS_TEST_2PARAM(DhcpAllocateIp, dhcp, &any, 1, "Allocate IP")
	wanted = 0xABCDEF01;
	DhcpFreeIp(dhcp, wanted);
	STATUS_TEST(DhcpCountFree, dhcp, (1<<2) - 3, "CountFree")
	STATUS_TEST_2PARAM(DhcpAllocateIp, dhcp, &used, 0, "Allocate IP")
	STATUS_TEST(DhcpCountFree, dhcp, (1<<2) - 4, "CountFree")

	wanted = 0xABCDEF01;
	DhcpFreeIp(dhcp, wanted);
	STATUS_TEST(DhcpCountFree, dhcp, (1<<2) - 3, "CountFree")
	STATUS_TEST_2PARAM(DhcpAllocateIp, dhcp, &any, 0, "Allocate IP")
	STATUS_TEST(DhcpCountFree, dhcp, (1<<2) - 4, "CountFree")

	DhcpDestroy(dhcp);
	PRINT_SUCCESS(status)
}

static void TestFreeIP(void)
{
	status_ty status = SUCCESS;
	address_ty subnet = 0xABCDEF00;
	size_t variable_bits = 3;
	dhcp_ty *dhcp = DhcpCreate(subnet, variable_bits);

	PRINT_TEST_CASE("Freeing IPs - both existing and not\n")

	STATUS_TEST(DhcpCountFree, dhcp, (1<<3) - 3, "CountFree, Free")

	DhcpFreeIp(dhcp, subnet);
	STATUS_TEST(DhcpCountFree, dhcp, (1<<3) - 2, "CountFree, Free")
	
	DhcpFreeIp(dhcp, 0xABCDEF03);
	STATUS_TEST(DhcpCountFree, dhcp, (1<<3) - 2, "CountFree, Free")

	DhcpFreeIp(dhcp, 0xABCDEF06);
	STATUS_TEST(DhcpCountFree, dhcp, (1<<3) - 1, "CountFree, Free")

	DhcpFreeIp(dhcp, 0xABCDEF07);
	STATUS_TEST(DhcpCountFree, dhcp, (1<<3), "CountFree, Free")

	DhcpDestroy(dhcp);
	PRINT_SUCCESS(status)
}
