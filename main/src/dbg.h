#ifndef __dbg_h__ //this way you don't include the file twice by accident
#define __dbg_h__

#include <stdio.h> 
#include <errno.h>
#include <string.h>

#ifdef NDEBUG  //lets yu recompile with dbg log messages removed
#define debug(M, ...)
#else
#define debug(M, ...) fprintf(stderr, "DEBUG %s:%d " M "\n", __FILE__, __LINE__, ##__VA_ARGS__) 
//translates any use of debug('format', arg1, arg2) to fprintf call to stderr
//##__VA_ARGS__ allows extra arguments to be placed here
#endif

#define clean_errno() (errno == 0 ? "None" : strerror(errno))//cretes safe readable version of errno

#define log_err(M, ...) fprintf(stderr, "[ERROR] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

#define log_warn(M, ...) fprintf(stderr, "[WARN] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

#define log_info(M, ...) fprintf(stderr, "[INFO] (%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
//3 macros above log messages for end user, can't be compiled out
#define check(A, M, ...) if(!(A)) { log_err(M, ##__VA_ARGS__); errno=0; goto error; }//if A not tru, logs M and goto error: for cleanup

#define sentinel(M, ...) { log_err(M, ##__VA_ARGS__); errno=0; goto error; }
//sentinel placed inside code you don't want to run, like if and switch cases you don't want eg: default

#define check_mem(A) check((A), "Out of memory,")//check if a pointer is valid

#define check_debug(A, M, ...) if(!(A)) { debug(M, ##__VA_ARGS__); errno=0; goto error; }//still checks and handles, but doesn't log error. use for common errors

#endif
