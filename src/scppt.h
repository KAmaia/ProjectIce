#include <time.h>
#include <stdio.h>

#define _TO_STRING(value) #value
#define TO_STRING(value) _TO_STRING(value)


//Disable colors on windows, cmd doesn't like them
#ifdef LINUX
#define LINEINFO printf("[" TO_STRING(__FILE__)":" TO_STRING(__LINE__)"] ");

#define SCPPT_OK REPORT_TIMER PRINTLN("\x1b[32mOK\x1b[37m"); testOks++;
#define SCPPT_FAIL REPORT_TIMER PRINTLN("\x1b[31mFAIL\x1b[37m"); testFails++;
#define PRINT(p_msg) printf("\x1b[33m" p_msg "\x1b[37m");
#define PRINTLN(p_msg) printf("\x1b[34m" p_msg "\x1b[37m""\n");
#else
#define LINEINFO 

#define SCPPT_OK REPORT_TIMER PRINTLN("OK"); testOks++;
#define SCPPT_FAIL REPORT_TIMER PRINTLN("FAIL"); testFails++;
#define PRINT(p_msg) printf("[" p_msg "]");
#define PRINTLN(p_msg) printf("[" p_msg "]" "\n");
#endif

#define ECHO(p_msg) LINEINFO printf(p_msg"\n");

#define START_TIMER scppt_timer = clock();
#define REPORT_TIMER printf(" [%fs] ",((double)(clock() - scppt_timer))/CLOCKS_PER_SEC);


#define SCPPT_COMPARE(p_name,p_var1,p_check,p_var2) LINEINFO START_TIMER PRINT("< " p_name " > \n") \
	if(p_var1 p_check p_var2){ \
	SCPPT_OK\
	}else{\
	SCPPT_FAIL\
	}

#define SCPPT_START clock_t scppt_timer; int testFails = 0; int testOks = 0; clock_t scppt_starttime = clock();
#define SCPPT_END printf("Ok: %i Fail: %i\n",testOks,testFails); \
	clock_t scppt_exectime = clock() - scppt_starttime;\
	double scppt_time = ((double)scppt_exectime)/CLOCKS_PER_SEC;\
	printf("Exec time: %f\n",scppt_time); \
	if(testFails > 0){ return 1; }else{ return 0; }
