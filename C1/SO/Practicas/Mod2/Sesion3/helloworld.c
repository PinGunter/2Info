/**
 * @file fork-helloWorld.c
 * @brief   Understanding fork in C language.
 *
 * @details
 *
 * The PROGRAM shows how POSIX compliant OSs implement fork() syscall.
 * It enphasizes the trace of execution that each process follows through the program.
 *
 * @author  Alejandro Leon Salas (aleon@ugr.es)
 * @date    19/10/2018
 * @version 1.0
 *
 * @section COMPILE
 * gcc  -std=c99 -Wall -Wpedantic -Wextra -o fork-helloWorld fork-helloWorld.c
 *
 */
#define _GNU_SOURCE         /* for non POSIX features. See feature_test_macros(7) */
#include <sys/syscall.h>    /* For SYS_xxx definitions. gettid hasn't got a wrapper. \
                   See syscall(2) and syscalls(2) */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/wait.h>

int
main(int argc, char* argv[])
{
  pid_t forkRetVal;    /**< Stores the value returned by fork() syscall */ 

  /* Check arguments */
  if (argc > 1) {
    printf("USAGE:\n %s\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  /*
   *  fork() creates a new process named child process. The process which creates is
   *  named the parent process.
   */
  forkRetVal= fork();

  /*
   * fork() returns 0 in the child process and the child process' PID in the parent process.
   */
  
  if (forkRetVal == 0) {  /* This code is ONLY executed by the child process */
    /* Things to do exclusively by child process */
    printf("Child -- Hello, I was born! forkRetVal = %d\n",forkRetVal);
  }
  else {  /* This code is ONLY executed by the parent process */
    /* Things to do exclusively by the parent process. */
    printf("Parent -- Hello, I created a child! forkRetVal = %d\n",forkRetVal);
  }

  /* This code is executed both by the child and parent processes */
  printf("Bye, bye!\n\n");
  
  return EXIT_SUCCESS;
  
}
