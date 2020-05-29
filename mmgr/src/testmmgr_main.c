#include <stdio.h>
#include <string.h>

#include "debugf.h"
#include "mmgr.h"

int test_init();
int test_malloc(char** ptr1, char** ptr2);
int test_free(char* ptr1, char* ptr2);
int test_realloc(char** ptr1, char** ptr2, char** ptr3);
int test_cleanup();

int main(void){
	int statuses = 0;
	
	char* name1;
	char* name2;
	char* name3;
	char* name4;
	char* name5;
	
	debugf(DEBUG_LEVEL_INFO, "[MMGR Test Harness] STARTING TESTS\n");
	
	statuses += test_init();
	statuses += test_malloc(&name1, &name2);
	statuses += test_free(name1, name2);
	statuses += test_realloc(&name3, &name4, &name5);
	statuses += test_cleanup();
	
	debugf(DEBUG_LEVEL_INFO, "[MMGR Test Harness] TESTS COMPLETED WITH %d\n", statuses);
	
	if(statuses > 0)
		return 1;
	else
		return 0;
}

int test_init(void){
	debugf(DEBUG_LEVEL_INFO, "[MMGR Test Harness] Init test started\n");
	
	int status = 0;
	g_MEM = mmgr_init();
	
	if(g_MEM != NULL)
		status = 0;

	debugf(DEBUG_LEVEL_INFO, "[MMGR Test Harness] Init test completed with status %d\n", status);
	return status;
}

int test_malloc(char** ptr1, char** ptr2){
	debugf(DEBUG_LEVEL_INFO, "[MMGR Test Harness] Malloc test started\n");
	int status = 0;
	
	*ptr1 = mmgr_malloc(g_MEM, sizeof(char*) * 9);
	*ptr2 = mmgr_malloc(g_MEM, sizeof(char*) * 10);
	
	if(ptr1 == NULL || ptr2 == NULL)
		status = 1;
	
	strcpy(*ptr1, "charlton");
	strcpy(*ptr2, "trezevant");
	
	if(strlen(*ptr1) != 8 || strlen(*ptr2) != 9)
		status = 1;
		
	debugf(DEBUG_LEVEL_INFO, "[MMGR Test Harness] Malloc test completed with status %d\n", status);
	
	return status;
}

int test_free(char* ptr1, char* ptr2){
	debugf(DEBUG_LEVEL_INFO, "[MMGR Test Harness] Free test started\n");
	mmgr_free(g_MEM, ptr1);
	mmgr_free(g_MEM, ptr2);
	
	debugf(DEBUG_LEVEL_INFO, "[MMGR Test Harness] Free test completed\n");
	return 0;
}

int test_realloc(char** ptr1, char** ptr2, char** ptr3){
	debugf(DEBUG_LEVEL_INFO, "[MMGR Test Harness] Reallocation test started\n");
	int status = 0;
	
	*ptr1 = mmgr_malloc(g_MEM, sizeof(char*) * 10);
	*ptr2 = mmgr_malloc(g_MEM, sizeof(char*) * 10);
	*ptr3 = mmgr_malloc(g_MEM, sizeof(char*) * 10);
	
	if(ptr1 == NULL || ptr2 == NULL || ptr3 == NULL)
		status = 1;
	
	strcpy(*ptr1, "teezevang");
	strcpy(*ptr2, "teezevago");
	strcpy(*ptr3, "tersevono");
	
	if(strlen(*ptr1) != 9 || strlen(*ptr2) != 9 || strcmp(*ptr3, "tersevono") != 0)
		status = 1;
	
	debugf(DEBUG_LEVEL_INFO, "[MMGR Test Harness] Reallocation test completed with status %d\n", status);
	
	return status;
}

int test_cleanup(){
	debugf(DEBUG_LEVEL_INFO, "[MMGR Test Harness] Cleanup test started\n");
	
	mmgr_cleanup(g_MEM);
	
	debugf(DEBUG_LEVEL_INFO, "[MMGR Test Harness] Cleanup test completed\n");
	
	return 0;
}
