/****************************
	file: bs_tree_test.c
	owner: Eran
	Reviewer: Kobi
*****************************/
#include <stddef.h>	/* NULL, ptrdiff_t */
#include <string.h>	/* strcmp */
#include <stdio.h>

#include "utils_testing.h"
#include "utils.h"	/* status_ty */
#include "bs_tree.h"

/************** Macros and Structs ************/
#define PARAM	(void *)(long)5

enum {NUM_ELEMENTS = 10, STEPS_FORWARD = 5, STEPS_BACK = 3};
enum {INITIAL_LETTER = 'a'};

typedef struct bot
{
	char name[8];
	ptrdiff_t age;
} bot_ty;

/**************** Function Declarations **************/
static int SortByAge(const void *bot1, const void *bot2, const void *param);
static int PrintName(void *bot, void *unacceptable);

static void TestEmptyBST(bst_ty *bst);
static void TestInserting(bst_ty *bst, bot_ty bots[], size_t size);
static void TestIterators(bst_ty *bst);
static void TestFind(bst_ty *bst, bot_ty *to_find, char expected_letter);
static void TestForEach(bst_ty *bst);
static void TestRemove(bst_ty *bst, bot_ty *bot_to_remove);

/**************** MAIN *****************/
int main()
{
	bst_ty *bst = NULL;
	bot_ty bots[NUM_ELEMENTS] =
		{{"dog", 4},
		{"bob", 2},
		{"fel", 6},
		{"avi", 1},
		{"cat", 3},
		{"ema", 5},
		{"ish", 10},
		{"jak", 12},
		{"geb", 8},
		{"hil", 9}};
	
	bst = BSTCreate(SortByAge, PARAM);
	
	TestEmptyBST(bst);
	TestInserting(bst, bots, NUM_ELEMENTS);
	TestIterators(bst);
	TestFind(bst, &bots[8], bots[8].name[0]);
	TestForEach(bst);
	TestRemove(bst, &bots[0]);
		
	BSTDestroy(bst);

	return (0);
}

/***************** Function Implementations ***************/
static int SortByAge(const void *bot1, const void *bot2, const void *param)
{
	(void)param;

	return (((bot_ty *)bot2)->age - ((bot_ty *)bot1)->age);
}

/*-----------------*/
static int PrintName(void *bot, void *unacceptable)
{
	if (!strcmp(((bot_ty *)bot)->name, (char *)unacceptable))
	{
		return (1);
	}
	
	printf("%c ", ((bot_ty *)bot)->name[0]);
	
	return (0);
}

/*-----------------*/
static void TestEmptyBST(bst_ty *bst)
{
	status_ty status = SUCCESS;
	
	PRINT_TEST_CASE("Checking Size, IsEmpty, Iters, ForEach on empty BST\n")
	STATUS_TEST(BSTSize, bst, 0, "Size")
	STATUS_TEST(BSTIsEmpty, bst, 1, "IsEmpty")
	STATUS_TEST_2PARAM(BSTIterIsEqual, BSTIterBegin(bst), BSTIterEnd(bst), 1, "IsEqual, Begin, or End")
	BSTForEach(BSTIterBegin(bst), BSTIterEnd(bst), PrintName, "bob");
	PRINT_SUCCESS(status)
}

/*-----------------*/
static void TestInserting(bst_ty *bst, bot_ty bots[], size_t size)
{
	status_ty status = SUCCESS;
	size_t i = 0;
	
	PRINT_TEST_CASE("Checking Inserting\n")
	STATUS_TEST(BSTSize, bst, 0, "Size")
	for (i = 0; i < size; ++i)
	{
		BSTInsert(bst, &bots[i]);
		STATUS_TEST(BSTSize, bst, i+1, "Size")
	}
	STATUS_TEST(BSTSize, bst, size, "Size")
	printf("CASE1");
	STATUS_TEST(BSTIsEmpty, bst, 0, "IsEmpty")
	printf("CASE2");
	STATUS_TEST_2PARAM(BSTIterIsEqual, BSTIterBegin(bst), BSTIterEnd(bst), 0, "IsEqual, Begin, or End")
	printf("\tExpect:\ta b c d e f g h i j\n");
	printf("\tResult:\t");
	BSTForEach(BSTIterBegin(bst), BSTIterEnd(bst), PrintName, "xxx");
	printf("\n");
	PRINT_SUCCESS(status)
}

/*-----------------*/
static void TestIterators(bst_ty *bst)
{
	status_ty status = SUCCESS;
	char starting_letter = INITIAL_LETTER;
	char current_letter = starting_letter;
	bst_iter_ty current = BSTIterBegin(bst);
	size_t remaining_steps = NUM_ELEMENTS - STEPS_FORWARD + STEPS_BACK;
	size_t i = 0;

	PRINT_TEST_CASE("Checking Iterators\n")
	STRUCT_STATUS_TEST(name[0], (bot_ty *)BSTGetData, current, current_letter, "Begin, GetData")
	STATUS_TEST_2PARAM(BSTIterIsEqual, current, BSTIterBegin(bst), 1, "IsEqual, Begin")
	for (i = 0; i < STEPS_FORWARD; ++i)
	{
		current = BSTIterNext(current);
	}
	current_letter += STEPS_FORWARD;
	STRUCT_STATUS_TEST(name[0], (bot_ty *)BSTGetData, current, current_letter, "Next, GetData")
	STATUS_TEST_2PARAM(BSTIterIsEqual, current, BSTIterBegin(bst), 0, "IsEqual, Begin, Next")

	for (i = 0; i < STEPS_BACK; ++i)
	{
		current = BSTIterPrev(current);
	}
	current_letter -= STEPS_BACK;
	STRUCT_STATUS_TEST(name[0], (bot_ty *)BSTGetData, current, current_letter, "Prev, GetData")

	for (i = 0; i < remaining_steps; ++i)
	{
		current = BSTIterNext(current);
	}
	STATUS_TEST_2PARAM(BSTIterIsEqual, current, BSTIterEnd(bst), 1, "IsEqual, Next")

	PRINT_SUCCESS(status)
}

/*-----------------*/
static void TestFind(bst_ty *bst, bot_ty *to_find, char expected_letter)
{
	status_ty status = SUCCESS;
	bot_ty fake_bot = {"wrong", 7};

	PRINT_TEST_CASE("Checking Find\n")
	STATUS_TEST_2PARAM(BSTIterIsEqual, BSTFind(bst, (void *)&fake_bot), BSTIterEnd(bst), 1, "IsEqual, Find")
	STRUCT_STATUS_TEST(name[0], (bot_ty *)BSTGetData, BSTFind(bst, (void *)to_find), expected_letter, "Find, GetData")
	PRINT_SUCCESS(status)
}

/*-----------------*/
static void TestForEach(bst_ty *bst)
{
/*	status_ty status = SUCCESS;*/
	bst_iter_ty begin = BSTIterBegin(bst);
	bst_iter_ty end = BSTIterEnd(bst);
	bst_iter_ty from_iter = BSTIterNext(BSTIterNext(begin));
	bst_iter_ty to_iter = BSTIterPrev(BSTIterPrev(end));
	
	PRINT_TEST_CASE("Checking ForEach\n")
	printf("\tExpect:\tc d e f g h\n");
	printf("\tResult:\t");
	BSTForEach(from_iter, to_iter, PrintName, "xxx");
	printf("\n");

	printf("\tExpect:\tc d e\n");
	printf("\tResult:\t");
	BSTForEach(from_iter, to_iter, PrintName, "fel");
	printf("\n");

/*	PRINT_SUCCESS(status)*/
}

/*-----------------*/
static void TestRemove(bst_ty *bst, bot_ty *bot_to_remove)
{
	status_ty status = SUCCESS;
	bst_iter_ty end = BSTIterEnd(bst);
	bst_iter_ty to_remove = BSTIterPrev(end);

	PRINT_TEST_CASE("Checking Removing\n")
	STATUS_TEST_2PARAM(BSTIterIsEqual, BSTRemoveIter(to_remove), BSTIterEnd(bst), 1, "IsEqual, Remove")
	STATUS_TEST(BSTSize, bst, NUM_ELEMENTS - 1, "Size")
	BSTRemoveIter(BSTFind(bst, (void *)bot_to_remove));
	STATUS_TEST(BSTSize, bst, NUM_ELEMENTS - 1 - 1, "Size")
	printf("\tExpect:\ta b c e f g h i\n");
	printf("\tResult:\t");
	BSTForEach(BSTIterBegin(bst), BSTIterEnd(bst), PrintName, "xxx");
	printf("\n");
	PRINT_SUCCESS(status)
}
