/*!
 * @file katwikOpsys.h
 * @brief header with stuff
 * @author Emmanuel K
 */
#ifndef KATWIK_HEADER
#define KATWIK_HEADER

// lol
#define HEADER_OKAY

#ifndef __GNUC__
#error bruhhhh moment no GNU?
#undef HEADER_OKAY
#endif // __GNUC__

#define _POSIX_C_SOURCE 200809L

#include <aio.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

// for printing sum noic stack traces
#include <execinfo.h>

// this one can actually be removed b/c
// no actual code requires it,
// buuut there's some macros of this header's functions
// so yeahh I guess this makes life easier sometimes?
#include <mqueue.h>

// Doxygen gets a massive aneurysm when it sees these declarations twice lol
#if !DOXYGEN
#ifndef ERR_MULTIPROCESS
#pragma GCC error "ERR_MULTIPROCESS macro undefined.\nDefine it above your #include for this file.\nFor multi-process programs:\n#define ERR_MULTIPROCESS 1\nFor single-process programs:\n#define ERR_MULTIPROCESS 0"
#undef HEADER_OKAY
#elif ERR_MULTIPROCESS != 1 && ERR_MULTIPROCESS != 0
#pragma GCC error "ERR_MULTIPROCESS invalid value\nFor multi-process programs:\n#define ERR_MULTIPROCESS 1\nFor single-process programs:\n#define ERR_MULTIPROCESS 0"
#undef HEADER_OKAY
#endif // ERR_MULTIPROCESS

// String for usage error,
// SHOULD be manually defined above include for this file,
// if USAGE macro is going to be used, otherwise define as blank
// string or smthn
#ifndef USAGE_STRING
#pragma GCC warning "USAGE_STRING macro undefined.\nDefine it above your #include for this file.\nEg:\n#define USAGE_STRING \"arg1 arg2 etc\""
#endif // ERR_MULTIPROCESS

// For less dumb header noise at compile time lul:
#ifndef MUNDANE_MESSAGES
#define MUNDANE_MESSAGES 1
#elif MUNDANE_MESSAGES == 1
#pragma message "Mundane messages have been manually turned on"
#elif MUNDANE_MESSAGES != 0
#pragma GCC error "MUNDANE_MESSAGES macro bad values.\nValid values are 0 (off) or 1 (on)"
#undef HEADER_OKAY
#endif // MUNDANE_MESSAGES

// 1 for some fun 4bit colors, 0 for boring
#ifndef ANSI_COLOR_FIESTA
#define ANSI_COLOR_FIESTA 1
#elif ANSI_COLOR_FIESTA == 1
#if MUNDANE_MESSAGES
#pragma message "Noice colorz have been manually turned on"
#endif // MUNDANE_MESSAGES
#elif ANSI_COLOR_FIESTA == 0
#pragma GCC warning "Bruhh no noice colorz?"
#else
#pragma GCC error "ANSI_COLOR_FIESTA macro bad value.\nValid values are 0 (off) or 1 (on)"
#undef HEADER_OKAY
#endif // ANSI_COLOR_FIESTA

// 1 to use rand_r in randomizers
#ifndef USE_RAND_R
#define USE_RAND_R 0
#elif USE_RAND_R == 1
#if MUNDANE_MESSAGES
#pragma message "Usage of rand_r has been manully turned on, you will have to pass a seed to all randomizers"
#endif // MUNDANE_MESSAGES
#elif USE_RAND_R == 0
#pragma message "Usage of rand_r has been manully turned off"
#else
#pragma GCC error "USE_RAND_R macro bad value.\nValid values are 0 (off) or 1 (on)"
#undef HEADER_OKAY
#endif // USE_RAND_R

// 1 for moar info, 0 normally
#ifndef DEBUG_MODE
#define DEBUG_MODE 0
#elif DEBUG_MODE == 1
#if MUNDANE_MESSAGES
#pragma message "Debug mode has been manually turned on"
#endif // MUNDANE_MESSAGES
#elif DEBUG_MODE == 0
#if MUNDANE_MESSAGES
#pragma message "Debug mode has been manually turned off"
#endif // MUNDANE_MESSAGES
#elif DEBUG_MODE == 0
#else
#pragma GCC error "DEBUG_MODE macro bad value.\nValid values are 0 (off) or 1 (on)"
#undef HEADER_OKAY
#endif // DEBUG_MODE

// seems dumb but might want to also have the option to disable these
// even when __GNUC__ is defined 
#ifndef ATTRIBUTES_ALLOWED
#define ATTRIBUTES_ALLOWED 1
#elif ATTRIBUTES_ALLOWED == 1
#if MUNDANE_MESSAGES
#pragma message "Attributes have been manually allowed"
#endif // MUNDANE_MESSAGES
#elif ATTRIBUTES_ALLOWED == 0
#if MUNDANE_MESSAGES
#pragma message "Attributes have been manually disallowed"
#endif // MUNDANE_MESSAGES
#else
#pragma GCC error "ATTRIBUTES_ALLOWED macro bad value.\nValid values are 1 (allowed) or 0 (disallowed)"
#undef HEADER_OKAY
#endif // ATTRIBUTES_ALLOWED

// config for whether or not some int-error functions from this header should just be void,
// immediately using ERR instead of returning an error code
#ifndef RETURN_ERR
#define RETURN_ERR 0
#elif RETURN_ERR == 1
#if MUNDANE_MESSAGES
#pragma message "Returning error codes from this header has been manually allowed"
#endif // MUNDANE_MESSAGES
#elif RETURN_ERR == 0
#if MUNDANE_MESSAGES
#pragma message "Returning error codes from this header has been manually disallowed"
#endif // MUNDANE_MESSAGES
#else
#pragma GCC error "RETURN_ERR macro bad value.\nValid values are 1 (allowed) or 0 (disallowed)"
#undef HEADER_OKAY
#endif // RETURN_ERR

// mainly for braced groups in the seksi macros lol
#ifndef EXTENSIONS_ALLOWED
#define EXTENSIONS_ALLOWED 1
#elif EXTENSIONS_ALLOWED == 1
#if MUNDANE_MESSAGES
#pragma message "header's usage of __extension__ has been manually allowed"
#endif // MUNDANE_MESSAGES
#elif EXTENSIONS_ALLOWED == 0
#if MUNDANE_MESSAGES
#pragma message "header's usage of __extension__ has been manually disallowed"
#endif // MUNDANE_MESSAGES
#else
#pragma GCC error "EXTENSIONS_ALLOWED macro bad value.\nValid values are 1 (allowed) or 0 (disallowed)"
#undef HEADER_OKAY
#endif // EXTENSIONS_ALLOWED

// lol these List methods are just a slightly upgraded version from
// my Sem1 early exam prep
#ifndef LIST_TYPE
#if MUNDANE_MESSAGES
//#pragma message "LIST_TYPE undefined, defaulting to int"
#endif // MUNDANE_MESSAGES
#define LIST_TYPE int
#endif // LIST_TYPE

// unused so far, TODO: implement this lol
#ifndef HEADER_DEV
#define HEADER_DEV 0
#elif HEADER_DEV == 1
#if MUNDANE_MESSAGES
#pragma message "Development mode for this header has been manually enabled"
#endif // MUNDANE_MESSAGES
#elif HEADER_DEV == 0
#if MUNDANE_MESSAGES
#pragma message "Development mode for this header has been manually disabled"
#endif // MUNDANE_MESSAGES
#else
#pragma GCC error "HEADER_DEV macro bad value.\nValid values are 0 (allowed) or 1 (disallowed)"
#undef HEADER_OKAY
#endif // HEADER_DEV

#ifndef TRACE_ON_ERR
#define TRACE_ON_ERR 1
#elif TRACE_ON_ERR == 1
#if MUNDANE_MESSAGES
#pragma message "Tracing when ERR happens has been manually enabled"
#endif // MUNDANE_MESSAGES
#elif TRACE_ON_ERR == 0
#if MUNDANE_MESSAGES
#pragma message "Tracing when ERR happens has been manually disallowed"
#endif // MUNDANE_MESSAGES
#else
#pragma GCC error "TRACE_ON_ERR macro bad value.\nValid values are 1 (allowed) or 0 (disallowed)"
#undef HEADER_OKAY
#endif // TRACE_ON_ERR

#ifndef EXEC_ALLOWED
#define EXEC_ALLOWED 1
#elif EXEC_ALLOWED == 1
#if MUNDANE_MESSAGES
#pragma message "Header's usage of exec (and similar functions) has been manually allowed"
#endif // MUNDANE_MESSAGES
#elif EXEC_ALLOWED == 0
#if MUNDANE_MESSAGES
#pragma message "Header's usage of exec (and similar functions) has been manually disallowed"
#endif // MUNDANE_MESSAGES
#else
#pragma GCC error "EXEC_ALLOWED macro bad value.\nValid values are 1 (allowed) or 0 (disallowed)"
#undef HEADER_OKAY
#endif // EXEC_ALLOWED

// Doxygen shit goes below here b/c for some reason it can't read below
// the HEADER_OKAY conditional compilation bit lmao
// stupid programs, nie rozumiem lul
#else // DOXYGEN
/** @mainpage notitle
 *
 * @section intro_sec Introduction
 *
 * The point of the header is to make OpSys2 a little easier.\n 
 * Why type 3 lines of code when you can type 1?
 *
 * @subsection basic_setup Basic Setup
 * 
 * Below is a simple example program using the header to check that the program has one argument, then print it (along with some extra information)
 * @code {.c}
 * // Valid values are 0 for single process programs,
 * // 1 for multi-process programs
 * #define ERR_MULTIPROCESS 0
 * 
 * // Usually define this as the arguments that your program expects
 * #define USAGE_STRING "name"
 * 
 * #include "katwikOpsys.h"
 * 
 * int main (int argc, char** argv) {
 * 	// simply type what should be true about the arguments for your program to work
 * 	USAGE(argc == 2);
 * 
 * 	// works the same as printf, prints extra info. nice for debugging :)
 * 	DBGprintf("Hey %s!\n", argv[1]);
 * }
 * @endcode
 * 
 * @subsection err_intro Noice ERRs Introduction
 * I'd say the first big point of the header is that it makes error checking a lot easier\n 
 * 
 * Consider the following program to generate and display a string of random numbers then write them to a file (without making use of the header)\n 
 * Below it is the same program written using this header
 * @code {.c}
 * #include <stdio.h>
 * #include <stdlib.h>
 * #include <time.h>
 * #include <errno.h>
 * #include <sys/stat.h>
 * #include <fcntl.h>
 * #include <unistd.h>
 * 
 * void usage(char* name) {
 * 	// this string is the only thing that changes between different programs in this function:
 * 	// can't we just generalize it... ?
 * 	char* usageString = "n filename\nn - amount to generate";
 * 
 * 	printf("Usage:\n$ %s %s\n", name, usageString);
 * 	exit(EXIT_FAILURE);
 * }
 * 
 * #define ERR(source) (perror(source),\
 * 		fprintf(stderr,"%s:%d\n", __FILE__,__LINE__),\
 * 		exit(EXIT_FAILURE))
 * 
 * int main (int argc, char** argv) {
 * 	char* nums;
 * 	int n, fileDescriptor;
 * 
 * 	if (argc != 3)
 * 		usage(argv[0]);
 * 
 * 	n = atoi(argv[1]);
 * 	if (n < 1)
 * 		usage(argv[0]);
 * 
 * // notice how if we misuse the program, we don't know if the first or second usage() call was the issue...
 * 
 * 	if ((fileDescriptor = open(argv[2], O_WRONLY | O_APPEND)) == -1)
 * 		ERR("open");
 * 
 * 	// all this, just to check argv?
 * 
 * 	nums = malloc(n); // notice how we're going to struggle with printing this
 * 	// since there's no space for '\0'
 * 	// contrived, but similar situations definitely happen, you all know
 * 
 * 	if (NULL == nums)
 * 		ERR("malloc");
 * 
 * 	srand(time(NULL));
 * 	for (int i = 0; i < n; ++i)
 * 		nums[i] = '0' + rand() % 10;
 * 
 * 	// now to print this buffer lol:
 * 	for (int i = 0; i < n; ++i)
 * 		if (printf("%c", nums[i]) < 0)
 * 			ERR("printf");
 * 	if (printf("\n") < 0)
 * 		ERR("printf");
 * 
 * 	// now write the numbers and close the file
 * 	if ((write(fileDescriptor, nums, n)) == -1)
 * 		ERR("write");
 * 	if (close(fileDescriptor) == -1)
 * 		ERR("close");
 * 
 * 	free(nums); // hmm...
 * }
 * @endcode
 * 
 * and here is the exact same program using the header:
 * @code {.c}
 * // side efect: a bunch of headers that it needs are already included :)
 * #include <sys/stat.h>
 * #include <fcntl.h>
 * 
 * #define ERR_MULTIPROCESS 0
 * #define USAGE_STRING "n filename\nn - amount to generate"
 * #include "katwikOpsys.h"
 * 
 * int main (int argc, char** argv) {
 * 	char* nums;
 * 	int n, fileDescriptor;
 * 
 * 	USAGE(argc == 3);
 * 	USAGE( (n = atoi(argv[1])) >= 1 );
 * 	ERR_NEG1(fileDescriptor = open(argv[2], O_WRONLY | O_APPEND));
 * 
 * 	ERR_NULL(nums = malloc(n));
 * 
 * 	srand(time(NULL));
 * 	for (int i = 0; i < n; ++i)
 * 		nums[i] = myRand('0', '9'); // so much more readable!
 * 
 *     printBuf(nums, n); // no '\0'? easy :)
 * 
 * 	ERR_NEG1(write(fileDescriptor, nums, n));
 * 	ERR_NEG1(close(fileDescriptor));
 * 
 * 	FREE(nums); // slightly safer, trust me xD
 * }
 * @endcode
 * 
 * if you like how that worked, I'd recommend writing/reducing some code using the header,\n 
 * then maybe check out \ref init_notification, it might be useful for <a href="https://sop.mini.pw.edu.pl/en/sop2/u/l2/" target="_blank">Lab2</a>\n 
 * or if you're really cool, you can dig around for more stuff in <a href="modules.html">Modules</a>,\n 
 * (or try to search for something in the top right)
 * 
 * @subsection syntax_tip Syntax Tip
 * Btw it's usually:
 * @code {.c}
 * ERR_NEG1(...);
 * 
 * // or:
 * int x;
 * ERR_NEG1(x = ...);
 * 
 * // NOT!!:
 * //
 * //ERR_NEG1(int y = ...);
 * //
 * // ^this will actually give you a kiinda weird compile-time error
 * // (and is part of the reason why imo you should have -ftrack-macro-expansion=0 in your GCC flags,\n 
 * // just so you can read some errors more easily lol),
 * //
 * // you can think of it as trying to do:
 * // if ((int y = ...) ...);
 * // (can't declare from there, can assign though)
 * @endcode
 *
 * @section downloads Downloads
 * <a href="./downloads">/html/downloads/</a> has katwikOpsys.h, makefile and *.c files\n
 * @note If you download a *.c file, remember to download a fresh makefile and .h\n
 * I usually update everything without caring about backwards compatibility ÂŻ\_(ă)_/ÂŻ\n
 */

/**
 * @def ERR(source)
 * @brief the usual ERR macro we all know, don't use it tho.
 * The other \ref ERR_Macros "ERR macros" are nicer\n 
 * You can use *them* to check an *entire expression* once, instead of calling this AFTER a check and passing a redundant string
 * @see ERR_Macros
 */
#define ERR(source)

/** \defgroup ERR_Macros ERR Macros
 * 
 * @brief macros for simplifying error checks
 * 
 * MVPs are \ref ERR_NEG1 (can replace most error checks) and \ref ERR_NULL \n 
 * btw if you end up reading my implementation and see a bunch of seemingly stupid loops, I just scooped the idead from <a href="https://stackoverflow.com/questions/154136/" target="_blank">here</a> lol
 * 
 * @see utility_macros
 * @see \ref err_intro
 * @see \ref syntax_tip
 * @{
 */
/**
 * @def ERR_NULL(expr)
 * @brief evaluates if \p expr == NULL, and if so, calls perror then terminates program based on \ref ERR_MULTIPROCESS
 * @param expr is the expression to evaluate and test
 * @note error-checking <a href="https://www.man7.org/linux/man-pages/man3/malloc.3p.html#RETURN_VALUE" target="_blank">malloc/calloc/realloc/etc</a> can be replaced using this macro
 */
#define ERR_NULL(expr)

/**
 * @def ERR_NEG1(expr)
 * @brief evaluates if \p expr == -1, and if so, calls perror then terminates program based on \ref ERR_MULTIPROCESS
 * @param expr is the expression to evaluate and test
 * @note most error checks can be replaced using this macro
 */
#define ERR_NEG1(expr)

/**
 * @def ERR_NEG(expr)
 * @brief evaluates if \p expr < 0, and if so, calls perror then terminates program based on \ref ERR_MULTIPROCESS
 * @param expr is the expression to evaluate and test
 * @note error-checking <a href="https://www.man7.org/linux/man-pages/man3/fprintf.3p.html#RETURN_VALUE" target="_blank">printf/fprintf/sprintf/snprintf/dprintf/etc</a> can be replaced using this macro
 */
#define ERR_NEG(expr)

/**
 * @def ERR_NON_ZERO(expr)
 * @brief evaluates if \p expr != 0, and if so, calls perror then terminates program based on \ref ERR_MULTIPROCESS
 * @param expr is the expression to evaluate and test
 */
#define ERR_NON_ZERO(expr)

/**
 * @def ERR_EOF(expr)
 * @brief evaluates if \p expr == EOF, and if so, calls perror then terminates program based on \ref ERR_MULTIPROCESS
 * @param expr is the expression to evaluate and test
 * @note I only know about <a href="https://www.man7.org/linux/man-pages/man3/fflush.3p.html#RETURN_VALUE" target="_blank">fflush returning EOF</a> as its error code lol
 */
#define ERR_EOF(expr)

/**
 * @def ERR_NULL_(expr, acceptableError)
 * @brief evaluates if \p expr is == NULL, and if errno != \p acceptableError, calls perror then terminates program based on \ref ERR_MULTIPROCESS
 * @param expr is the expression to evaluate and test
 * @param acceptableError is the errno with we can ignore
 */
#define ERR_NULL_(expr, acceptableError)

/**
 * @def ERR_NEG1_(expr, acceptableError)
 * @brief evaluates if \p expr is == -1, and if errno != \p acceptableError, calls perror then terminates program based on \ref ERR_MULTIPROCESS
 * @param expr is the expression to evaluate and test
 * @param acceptableError is the errno with we can ignore
 */
#define ERR_NEG1_(expr, acceptableError)

/**
 * @def ERR_NEG_(expr, acceptableError)
 * @brief evaluates if \p expr is < 0, and if errno != \p acceptableError, calls perror then terminates program based on \ref ERR_MULTIPROCESS
 * @param expr is the expression to evaluate and test
 * @param acceptableError is the errno with we can ignore
 */
#define ERR_NEG_(expr, acceptableError)

/**
 * @def ERR_NON_ZERO_(expr, acceptableError)
 * @brief evaluates if \p expr is != 0, and if errno != \p acceptableError, calls perror then terminates program based on \ref ERR_MULTIPROCESS
 * @param expr is the expression to evaluate and test
 * @param acceptableError is the errno with we can ignore
 */
#define ERR_NON_ZERO_(expr, acceptableError)

/**
 * @def ERR_EOF_(expr, acceptableError)
 * @brief evaluates if \p expr is == EOF, and if errno != \p acceptableError, calls perror then terminates program based on \ref ERR_MULTIPROCESS
 * @param expr is the expression to evaluate and test
 * @param acceptableError is the errno with we can ignore
 */
#define ERR_EOF_(expr, acceptableError)
/**@}*/

/** \defgroup utility_macros Utility Macros
 * 
 * @brief macros to make a few things easier
 * 
 * @see general_functions
 * @see utility_macros
 * @see ERR_Macros
 * 
 * @{
 */
/**
 * @def USAGE(correctUsage)
 * @brief asserts the correct usage of the program based on \p correctUsage being true
 * 
 * kinda similar to <a href="https://www.man7.org/linux/man-pages/man3/assert.3p.html#SYNOPSIS" target="_blank">assert</a> if you've ever used anything like it
 * 
 * @note you can only use this in the scope of argv, (ar at the very least a char** with the same name that has your binary name as a C-string in the first position)
 * (see the example in \ref basic_setup)
 * 
 * @see USAGE_STRING
 * @see settings_macros
 */
#define USAGE(correctUsage)

/**
 Also, unlike printf, you can call this with no arguments!\n 
 * Nice for debugging (will printf only the extra info)
 */
#define DBGprintf(format, ...)

/**
 * @def UNUSED(thing)
 * @brief explicitly tells the compiler that we know a variable is unused and it should shut up
 * @param thing is the variable/parameter
 * 
 * You can use this to dodge warnings for Wunused-parameter and Wunused-variable lol,\n 
 * This is especially useful for callback functions (eg: signal handlers) or functions that are stored in structs\n 
 * Where you'll be forced to have a specific signature, but you don't have any use for some of the parameters\n 
 * If you're with an extremely pedantic u tutor..., this is even more useful
 */
#define UNUSED(thing)

/**
 * @def FREE(ptr)
 * @brief safer version of free
 * @param ptr is the pointer to free
 * 
 * This basically just assigns the pointer to NULL after it frees it lol,\n 
 * sounds dumb, but with multiple/multi-thread frees there's all sorts of mistakes that could be made\n 
 * that you just don't have to think about lol, just type the same thing with capital letters and ASAN is going to scream less :)
 */
#define FREE(ptr)

/**
 * @def GIGA
 * @brief simply a billion
 * 
 * useful for various things, especially timers like nanosleep which do stuff in nanoseconds
 */
#define GIGA 1000000000L
/**@}*/

/** \defgroup settings_macros Settings Macros
 * @brief Macros for setting up the header
 * 
 * @ref ERR_MULTIPROCESS and \ref USAGE_STRING are the most useuful,\n 
 * you don't have to bother with the rest unless you're doing something special\n 
 * 
 * @see \ref basic_setup
 * @{
 */
/**
 * @def ERR_MULTIPROCESS
 * @brief determines how the program will terminate
 * 
 * This is referred to indirectly throughout the header
 * 
 * @warning **MUST** be declared *somewhere* before the include for the header\n 
 * (see the example in \ref basic_setup)
 * 
 * @see \ref basic_setup
 */
#define ERR_MULTIPROCESS

/**
 * @def USAGE_STRING
 * @brief determines what message to print if \ref USAGE fails its assertion
 * 
 * You can usually just define this as the arguments that your program expects\n 
 * The header will print some extra information on its own
 * 
 * @note This should be declared *somewhere* before the include for the header\n
 * (see the example in \ref basic_setup)
 * 
 * @see USAGE
 * @see \ref basic_setup
 */
#define USAGE_STRING

/**
 * @def LIST_TYPE
 * @brief determines the contained in each MyNode of MyList
 * 
 * defaults to int\n 
 * you can define it just like any other setting above\n 
 * check out the example in \ref my_list
 * @see \ref basic_setup
 * @see \ref my_list
 */
#define LIST_TYPE

/**
 * @def USE_RAND_R
 * @brief determines whether randomizers should use rand() or rand_r()
 * 
 * Set 1 to use rand_r(), 0 to use rand()
 * 
 * @note Default value is 0
 * @see MUNDANE_MESSAGES
 */
#define USE_RAND_R

/**
 * @def MUNDANE_MESSAGES
 * @brief determines whether to print a message when settings are changed manually
 * 
 * Set 1 to allow mundane messages from this header, 0 to turn them off
 * 
 * @note Default value is 1\n
 * This only affects settings that have default values
 */
#define MUNDANE_MESSAGES

/**
 * @def ANSI_COLOR_FIESTA
 * @brief determines whether to print in color on \ref ERR /\ref DBGprintf /etc
 * 
 * Set 1 to allow 4-bit ANSI colors from this header, 0 to turn them off
 * 
 * @note Default value is 1\n 
 * You'll get a compile-time warning for turning colors off btw lol\n 
 * I wasted too much time on them, so now you're forced to see them :)
 * @see MUNDANE_MESSAGES
 */
#define ANSI_COLOR_FIESTA

/**
 * @def DEBUG_MODE
 * @brief determines whether the header should print extra information
 * 
 * Set 0 for normal use, 1 for extra information at runtime\n 
 * This will usually \ref DBGprintf the parameters of each function as they're entered\n 
 * Some functions will also \ref DBGprintf additional info
 * 
 * @note Default value is 0
 * @see MUNDANE_MESSAGES
 */
#define DEBUG_MODE

/**
 * @def ATTRIBUTES_ALLOWED
 * @brief determines whether functions can be declared with <a href="https://gcc.gnu.org/onlinedocs/gcc-4.7.2/gcc/Function-Attributes.html" target="_blank">attributes</a>
 * 
 * Set 0 to disallow declarations with attributes, 1 to allow it
 * 
 * @note Default value is 1
 * @see MUNDANE_MESSAGES
 */
#define ATTRIBUTES_ALLOWED

/**
 * @def RETURN_ERR
 * @brief determines whether some functions should return int or void
 * 
 * Set 0 to return void on functions that set EINVAL, \ref ERR will be called instead when something bad happens\n 
 * otherwise set 1 to return int
 * 
 * @note Default value is 1\n 
 * this will usually also declare them with <a href="https://gcc.gnu.org/onlinedocs/gcc-4.7.2/gcc/Function-Attributes.html" target="_blank">\_\_attribute\_\_((warn_unused_result))</a>
 * @see MUNDANE_MESSAGES
 * @see ATTRIBUTES_ALLOWED
 */
#define RETURN_ERR

/**
 * @def HEADER_DEV
 * @brief unused for now
 * will probably be for some development feature stuff
 */
#define HEADER_DEV
/**@}*/

/** \defgroup general_functions General Functions
 * 
 * @brief intended to be useful not just for specific us
 * 
 * These will have stuff like easier-to-use timers, randomizers and stuff for strings,\n 
 * but not stuff like struct initialization\n 
 * MVPs are \ref waitAllChildren , \ref myNanoSleep , \ref myRand , \ref printBuf and \ref removeNinstances
 * 
 * @see u_functions
 * 
 * @{
 */
/**
 * @brief Process waits in a loop until there are no more children <a href="https://www.man7.org/linux/man-pages/man3/wait.3p.html#ERRORS" target="_blank">(ECHILD)</a>
 * 
 * Example:
 * @code
 * pid_t pid;
 * ERR_NEG1(pid = fork());
 *
 * if (pid) { // in parent
 * 	waitAllChildren();
 * } else { // in child
 * 	sleep(1);
 * 	return EXIT_SUCCESS;
 * }
 * @endcode
 */
void waitAllChildren(void);

/**
 * @brief nanosleeps for the given \p nanoseconds
 *
 * @param nanoseconds is the *total* amount of time to sleep for
 * 
 * Example:
 * @code
 * // to sleep for 2.5 seconds:
 * myNanoSleep(2.5 * GIGA);
 * @endcode
 * 
 * @see GIGA
 * @see myNanoSleep2
 */
void myNanoSleep (long nanoseconds);

/**
 * @brief nanosleeps for the given \p seconds and \p nanoseconds
 *
 * @param seconds is the seconds to sleep for
 * @param nanoseconds is the remainder of time to sleep for, in nanoseconds
 * 
 * Example:
 * @code
 * // to sleep for 2.5 seconds:
 * myNanoSleep2(2, 0.5 * GIGA);
 * @endcode
 * 
 * @see GIGA
 * @see myNanoSleep
 */
void myNanoSleep2 (int seconds, long nanoseconds);

/**
 * @brief generates a random integer in the range [\p min, \p max]
 *
 * @param min is the minimum value
 * @param max is the maximum value
 * @return a random unsigned long
 *
 * @see USE_RAND_R
 */
unsigned long myRand(unsigned long min, unsigned long max);

/**
 * @brief generates a random integer in the range [\p min, \p max]
 *
 * 
 * @param min is the minimum value
 * @param max is the maximum value
 * @param seed is a pointer to the seed for the randomizer
 * @return a random unsigned long
 *
 * @see USE_RAND_R
 */
unsigned long myRand(unsigned long min, unsigned long max, unsigned int* seed);

/**
 * @brief generates a random double in the range [\p min, \p max]
 *
 * precision will be about 1/Billion when [0, 1] is passed
 * @param min is the minimum value
 * @param max is the maximum value
 * @param seed is a pointer to the seed for the randomizer
 * @return a random double
 * @see USE_RAND_R
 */
double myRandDouble(double min, double max, unsigned int* seed);

/**
 * @brief generates a random double in the range [\p min, \p max]
 *
 * precision will be about 1/Billion when [0, 1] is passed
 * @param min is the minimum value
 * @param max is the maximum value
 * @return a random double
 * @see USE_RAND_R
 */
double myRandDouble(double min, double max);

/**
 * @brief sleeps for a random amount of time in the range [\p minSec, \p maxSec]
 *
 * @param minSec is the minimum value
 * @param maxSec is the maximum value
 * @param seed is a pointer to the seed for the randomizer
 * @see USE_RAND_R
 */
void myRandSleep(double minSec, double maxSec, unsigned int* seed);

/**
 * @brief sleeps for a random amount of time in the range [\p minSec, \p maxSec]
 *
 * @param minSec is the minimum value
 * @param maxSec is the maximum value
 * @see USE_RAND_R
 */
void myRandSleep(double minSec, double maxSec);

/**
 * @brief writes a \p buffer to stdout
 * 
 * Useful for buffers that aren't "real strings" with a '\0' at the end
 *
 * @param buffer is a pointer to the buffer
 * @param sz is the total length (in bytes) of the buffer
 */
void printBuf(char* buffer, size_t sz);

/**
 * @brief dumb function will probably remove/redo soon lol
 * 
 * @param dest 
 * @param src 
 * @param start 
 * @param length 
 * @return void* 
 */
void* substr(char* dest, char* src, off_t start, size_t length);

/**
 * @brief moves buffer \p amount to the left and replaces the last \p amount bytes with \p c
 * 
 * Useful for deleting the first few characters in a buffer/string
 * 
 * @param buff is a pointer to the buffer
 * @param length is the size of the buffer
 * @param amount is the amount to shift by
 * @param c is the character to fill with
 */
void leftShift_fill(void* buff, size_t length, size_t amount, int c);

/**
 * @brief moves buffer \p amount to the left and replaces the last \p amount bytes with 0s
 * 
 * @param buff is a pointer to the buffer
 * @param length is the size of the buffer
 * @param amount is the amount to shift by
 */
void leftShift(void* buff, size_t length, size_t amount);

/**
 * @brief moves buffer \p amount to the left and moves the first \p amount bytes to the end
 * 
 * @param buff is a pointer to the buffer
 * @param length is the size of the buffer
 * @param amount is the amount to shift by
 */
void leftShift_cycle(void* buff, size_t length, size_t amount);

/**
 * @brief replaces last \p amount bytes in a buffer with \p c
 * 
 * Weird name but whatever lol\n 
 * I wrote this at the same time as the leftShift functions
 * 
 * @param buff is a pointer to the buffer
 * @param length is the size of the buffer
 * @param amount is the amount to shift by
 * @param c is the character to fill with
 */
void rightShift_fill(void* buff, size_t length, size_t amount, int c);

/**
 * @brief replaces last \p amount bytes in a buffer with 0s
 * 
 * Weird name but whatever lol\n 
 * I wrote this at the same time as the leftShift functions
 * 
 * @param buff is a pointer to the buffer
 * @param length is the size of the buffer
 * @param amount is the amount to shift by
 */
void rightShift(void* buff, size_t length, size_t amount);

/**
 * @brief moves buffer to the right \p amount and moves the last \p amount bytes to the beginning
 * 
 * only god knows what this one could be useful for lol\n 
 * was easy to write once I had the other ones tho, so eh
 * 
 * @param buff is a pointer to the buffer
 * @param length is the size of the buffer
 * @param amount is the amount to shift by
 */
void rightShift_cycle(void* buff, size_t length, size_t amount);

/**
 * @brief removes \p n instances of a \p c from the \p str
 * 
 * It is assumed that str is a valid C-string\n 
 * (ie: has a \0 at the end so that strlen can be used)
 * 
 * NB: you can pass \p n < 0 to explicitly remove all occurences of \p c
 * 
 * @param str is a pointer to the string
 * @param c the character to remove
 * @param n the number of \p c to remove
 */
void removeNinstances(char* str, char c, ssize_t n);
/**@}*/

/** \defgroup u_functions Lab Functions
 * @brief will have code for simplifying the overhead for certain us, like initializing structs, etc
 * 
 * most useful in the short term will possibly be \ref init_notification for <a href="https://sop.mini.pw.edu.pl/en/sop2/u/l2/" target="_blank">Ops2Lab2</a>
 * 
 * Example \ref init_notification for message queues, (program adapted directly from <a href="https://www.man7.org/linux/man-pages/man3/mq_notify.3p.html#EXAMPLES" target="_blank">EXAMPLES section in "man 3p mq_notify"</a>,\n 
 * notice how it's does the exact same thing but the use of the hedaer makes it a lot shorter and simpler xD )
 * @code {.c}
 * #include <pthread.h>
 * #include <mqueue.h>
 * #include <assert.h>
 * #include <stdio.h>
 * #include <stdlib.h>
 * #include <unistd.h>
 * 
 * #include <signal.h>
 * 
 * #define ERR_MULTIPROCESS 0
 * 
 * // NB: USAGE_STRING can have multiple lines, just separate them with '\n' and it all works out
 * #define USAGE_STRING "queueName\nwhere queueName is the name of the message queue,\nstarting with a '/' char"
 * 
 * // init_notification will be a void function instead of int:
 * // otherwise we'd have to check it with ERR_NEG1
 * #define RETURN_ERR 0
 * 
 * #include "katwikOpsys.h"
 * 
 * // Thread start function
 * static void tfunc(union sigval sv) {
 * 	struct mq_attr attr;
 * 	ssize_t nr;
 * 	void* buf;
 * 
 * 	// get message queue descriptor from argument 
 * 	mqd_t mqdes = *((mqd_t *) sv.sival_ptr);
 * 	//memcpy(&mqdes, sv.sival_ptr, sizeof(mqd_t)); // is the same idea, possibly more readble
 * 
 * 	// Determine maximum msg size, allocate buffer appropriately
 * 	ERR_NEG1(mq_getattr(mqdes, &attr));
 * 	ERR_NULL(buf = malloc(attr.mq_msgsize));
 * 
 * 	// receive message and show its size
 * 	ERR_NEG1(nr = mq_receive(mqdes, buf, attr.mq_msgsize, NULL));
 * 	DBGprintf("Read %ld bytes from message queue\n", (long) nr);
 * 
 * 	// cleanup and exit
 * 	FREE(buf);
 * 	exit(EXIT_SUCCESS);
 * }
 * 
 * int main(int argc, char** argv) {
 * 	mqd_t mqdes;
 * 	struct sigevent notification;
 * 	USAGE(argc == 2);
 * 
 * 	ERR_NEG1(mqdes = mq_open(argv[1], O_RDONLY));
 * 	init_notification(&notification, SIGEV_THREAD, 0, 0, &mqdes, tfunc, NULL);
 * 	ERR_NEG1(mq_notify(mqdes, &notification));
 * 
 * 	// process is terminated by thread function
 * 	pause();
 * }
 * @endcode
 * @{
 */
/**
 * @brief initializses a <a href="https://man7.org/linux/man-pages/man7/sigevent.7.html#SYNOPSIS" target="_blank">"struct sigevent"</a>
 * 
 * Useful for AIO/message passing and other stuffs
 * 
 * @param notification is a pointer to the struct to initialize, I'd recommend leaving it on the stack if you wanna keep things easy
 * @param notify is the notification method represented, stroed in ->sigev_notify
 * @param signo is the signal used for SIGEV_SIGNAL, stored in ->sigev_signo
 * @param sival_int is stored in ->sigev_value.sival_int
 * @param sival_ptr is stored in ->sigev_value.sival_ptr
 * @param notify_function is the notification function for SIGEV_THREAD
 * @param notify_attributes are the attributes for SIGEV_THREAD (usually just pass NULL lol)
 * @return either void or int (0 normally, -1 indicating an error), depending on \ref RETURN_ERR
 */
init_notification(struct sigevent* notification, int notify, int signo, int sival_int, void* sival_ptr, void (*notify_function) (union sigval), void* notify_attributes);

/**
 * @brief was used to initialize <a href="https://man7.org/linux/man-pages/man7/aio.7.html#DESCRIPTION" target="_blank">aiocb</a> structs in <a href="https://sop.mini.pw.edu.pl/en/sop1/u/l4/" target="_blank">Ops1Lab4</a>
 * 
 * blah blah some description
 * 
 * @param cbp 
 * @param fildes 
 * @param offset 
 * @param nbytes 
 * @param aio_buf 
 * @param notification 
 * @return either void or int (0 normally, -1 indicating an error), depending on \ref RETURN_ERR
 */
init_aiocb(struct aiocb* cbp, int fildes, off_t offset, ssize_t nbytes, volatile void* aio_buf, struct sigevent* notification);

/**
 * @brief @brief was a cleaner version of the suspend function in the <a href="https://sop.mini.pw.edu.pl/en/sop1/u/l4/" target="_blank">tutorial for Ops1Lab4</a> that would wait for a SINGLE aiocb to complete
 * 
 * * (again too lazy to document this)\n 
 * this version was just better kek\n 
 * 
 * @param cbp 
 */
void suspend(struct aiocb* cbp);

/**
 * @brief was used for AIO read/write calls in Ops1Lab4, could handle allocation as well
 * 
 * @param aioArr 
 * @param fildes 
 * @param offset 
 * @param blockSize 
 * @param buf 
 * @param notification 
 * @param parrLevel 
 * @param shouldRead 
 * @return either void or int (0 normally, -1 indicating an error), depending on \ref RETURN_ERR
 */
parallelIO(struct aiocb* aioArr, int fildes, off_t offset, size_t blockSize, void* buf, struct sigevent* notification, int parrLevel, bool shouldRead);
/**@}*/

/** \defgroup my_list MyList Struct
 * 
 * @brief homemade linked list data structure
 *
 * quite nice because it can be used as a stack (with \ref insertValLast + \ref popLastVal) or queue(with \ref insertValLast + \ref popFirstVal)\n
 * and if I didn't misunderstand their question, the previous
 * OpSys group had to create some kind of queue of clients (all are stored, but first reservation is delivered to first, etc?)\n 
 * so we might get the same idea, or a stack\n 
 *
 * Example:
 * @code
 * // this defaults to int, but you can change it like this:
 * #define LIST_TYPE double
 * 
 * #define USAGE_STRING "deletionPosition"
 * #define ERR_MULTIPROCESS 0
 * #include "katwikOpsys.h"
 * 
 * int main(int argc, char** argv) {
 * 	// program setup
 * 	USAGE(argc == 2);
 * 	int deletePos = atoi(argv[1]);
 * 
 * 	// create and print list
 * 	MyList* list = newMyList();
 * 	insertValLast(list, 1.1);
 * 	insertValLast(list, 6.89);
 * 	insertValFirst(list, 4.20);
 * 	printf("List fter creation: "); printMyList(list, "%.2lf "); // prints each with 2 decimal places btw
 * 
 * 	deleteAt(list, deletePos); // frees node and relinks list, no worries
 * 	printf("List after deletion: "); printMyList(list, "%.2lf ");
 * 
 * 	printf("Now popping first value: %.2lf\n", popFirstVal(list));
 * 	printf("List after pop: "); printMyList(list, "%.2lf ");
 * 
 * 	// deallocates remaining nodes as well as list
 * 	// easy memory management :)
 * 	deleteMyList(list); 
 * }
 * @endcode
 * 
 * @see LIST_TYPE
 * @see \ref u_functions
 * @see \ref basic_setup
 * @{
*/

/**
 * @brief structure for the list
 * 
 * it's implemented dw about it \n 
 * some functions will return this tho
 * @see \ref my_list
 * @see MyNode
 * @see LIST_TYPE
 */
typedef struct {} MyList;

/**
 * @brief structure for the nodes of the list
 
 * @see \ref my_list
 * @see MyList
 * @see LIST_TYPE
 */
typedef struct {} MyNode;

// TODO: document this l8r lul
MyNode* newMyNode (LIST_TYPE val);

/**
 * @brief allocates list
 * @return fresh list
 * 
 * @note Allocation! you should \ref deleteMyList when you're done
 * @see deleteMyList
 */
MyList* newMyList (void);

/**
 * @brief prints list
 * @param list is the list to print
 * @param format is the printf-style format to print each value with
 * @see \ref my_list
 */
void printMyList(const MyList* const list, const char* restrict format);

/**
 * @brief gets list size
 * @param list is the list to get size of
 * @return size of the list
 * 
 * @note an empty \p list will safely return 0 as well
 */
size_t myListLength(const MyList* const list);

/**
 * @brief you don't need to use this *directly*
 * 
 * @param list 
 * @param pos 
 * @return MyNode* 
 * @see peekValAt
 */
MyNode* peekNodeAt(const MyList* const list, size_t pos);

/**
 * @brief gets a value at a position in the list
 * @param list self-explanatory
 * @param pos is the position to get from, counting from 0
 * @return is the value at that position
 * @see LIST_TYPE
 */
LIST_TYPE peekValAt(const MyList* const list, size_t pos);

/**
 * @brief gets a value at a position in the list
 * @param list self-explanatory
 * @param pos is the position to get from, counting from 0
 * @return is the value at that position
 * @see LIST_TYPE
 */
LIST_TYPE popValAt(MyList* const list, size_t pos);

/**
 * @brief gets first value in the list
 * @param list self-explanatory
 * @return first value
 * @see LIST_TYPE
 */
LIST_TYPE peekFirstVal(const MyList* const list);

/**
 * @brief gets last value in the list
 * @param list self-explanatory
 * @return last value
 * @see LIST_TYPE
 */
LIST_TYPE peekLastVal(const MyList* const list);

/**
 * @brief removes first value in the list, returns it
 * @param list self-explanatory
 * @return first value
 * @see LIST_TYPE
 */
LIST_TYPE popFirstVal(MyList* const list);

/**
 * @brief removes last value in the list, returns it
 * @param list self-explanatory
 * @return last value
 * @see LIST_TYPE
 */
LIST_TYPE popLastVal(MyList* const list);

/**
 * @brief you don't need to use this *directly*
 * @param list
 * @return MyList*
 * @see popLastVal
 */
MyNode* popLast(MyList* const list);

/**
 * @brief you don't need to use this *directly*
 * 
 * @param list 
 * @return MyNode* 
 * @see popFirstVal
 */
MyNode* popFirst(MyList* const list);

/**
 * @brief frees every MyNode in the list
 * @param list self-explanatory
 * @return the emptied list
 * @note this *doesn't* free the list itself, see \ref deleteMyList
 */
MyList* clearMyList(MyList* const list);

/**
 * @brief frees every MyNode in the list, free the list
 * @param list self-explanatory
 * @note this is usually more useful than clearMyList
 */
void deleteMyList (MyList* list);

/**
 * @brief deletes a node at a position
 * 
 * @param list self explanatory
 * @param pos the position to delete at
 * @return the modified list
 * @see popValAt
 */
MyList* deleteAt(MyList* const list, size_t pos);

/**
 * @brief deletes the last value in the list
 * 
 * @param list self explanatory
 * @return the modified list
 * @see popLastVal
 */
MyList* deleteLast(MyList* const list);

/**
 * @brief deletes the first value in the list
 * 
 * @param list self explanatory
 * @return the modified list
 * @see popFirstVal
 */
MyList* deleteFirst(MyList* const list);

/**
 * @brief you don't need to use this *directly*
 * @param list
 * @param pos
 * @param newMyNode
 * @see insertValAfter
 * @return MyList*
 */
MyList* insertAfter(MyList* const list, size_t pos, MyNode* const newMyNode);

/**
 * @brief you don't need to use this *directly*
 * @param list
 * @param pos
 * @param newMyNode
 * @return MyList*
 * @see insertValBefore
 */
MyList* insertBefore(MyList* const list, size_t pos, MyNode* const newMyNode);

/**
 * @brief inserts a value into the \p list after the given position
 * 
 * @param list self explanatory
 * @param pos the position to insert after
 * @param newVal self explanatory
 * @return the modified \p list
 * 
 * @see insertValBefore
 */
MyList* insertValAfter(MyList* const list, size_t pos, LIST_TYPE newVal);

/**
 * @brief inserts a value into the \p list before the given position
 * 
 * @param list 
 * @param pos the position to insert before
 * @param newVal 
 * @return the modified \p list
 * @see insertValAfter
 */
MyList* insertValBefore(MyList* const list, size_t pos, LIST_TYPE newVal);

/**
 * @brief you don't need to use this *directly*
 * 
 * @param list 
 * @param node 
 * @return void* 
 * @see insertValLast
 */
MyList* insertLast(MyList* const list, MyNode* const node);

/**
 * @brief you don't need to use this *directly*
 * 
 * @param list 
 * @param node 
 * @return MyList*
 * @see insertValFirst
 */
MyList* insertFirst(MyList* const list, MyNode* const node);

/**
 * @brief inserts a value into the first position of the \p list
 * 
 * @param list self explanatory
 * @param newVal the value to insert
 * @return the modified \p list
 */
MyList* insertValLast(MyList* const list, LIST_TYPE newVal);

/**
 * @brief inserts a value into the last position of the \p list
 * 
 * @param list self explanatory
 * @param newVal the value to insert
 * @return the modified \p list
 */
MyList* insertValFirst(MyList* const list, LIST_TYPE newVal);
/**@}*/

/** @defgroup u6 Lab 6 Stuff
 * @brief stuff that will be useful for Lab 6
 *
 * NB: the point is you *will* lose points for not checking for EINTR on this lab <a href="https://sop.mini.pw.edu.pl/en/sop2/lab/l2/" target="_blank">(check the "Attention" bit at the top of their page)</a>
 * 
 * also see \ref init_notification
 *@{
 */

/**
 * @brief safe version of mq_open
 * 
 * Same arguments as <a href="https://www.man7.org/linux/man-pages/man3/mq_open.3p.html#SYNOPSIS" target="_blank">mq_open</a>, but first retries it for EINTR then error checks it as well
 */	
#define mq_open_(name, oflag, ...)

/**
 * @brief safe version of mq_send
 * 
 * Same arguments as <a href="https://www.man7.org/linux/man-pages/man3/mq_send.3p.html#SYNOPSIS" target="_blank">mq_send</a>, but first retries it for EINTR then error checks it as well
 */
#define mq_send_(mqdes, msg_ptr, msg_len, msg_prio)

/**
 * @brief safe version of mq_receive
 * 
 * Same arguments as <a href="https://www.man7.org/linux/man-pages/man3/mq_receive.3p.html#SYNOPSIS" target="_blank">mq_receive</a>, but first retries it for EINTR then error checks it as well
 */
#define mq_receive_(mqdes, msg_ptr, msg_len, msg_prio)

/**@}*/

#endif // DOXYGEN
 
// rest of header will now be invisible after the preprocesser if the first section wasn't set
// up properly, to reduce the flooding of errors from the remaining section being invalid as a consequence.
// in some cases this will in exchange increase "Wimplicit-function-declaration" and dumb linker errors,
// but overall it should make stuff cleaner for new users who haven't yet tried to use anything from
// it, but are confused on why it "doesn't just work" (you know who you are xD)
#ifndef HEADER_OKAY
#pragma message "Some macro wasn't set up properly, rest of header won't be preprocessed"
#else
// long story short, block comments don't nest nicely lol
#define TEMP_REMOVE 0

// moi attribyut
#if ATTRIBUTES_ALLOWED
#define NON_ATTR_IF(expr) if (false)
#define MY_WARN_UNUSED __attribute__((warn_unused_result))
#define MY_NON_NULL(...) __attribute__(( nonnull(__VA_ARGS__) ))
#define MY_DEPRECATE(msg) __attribute__ (( deprecated (msg) ))
#define MY_FORMAT(...) __attribute__(( format (__VA_ARGS__) ))
#define MY_INLINE __attribute__((always_inline))
#else // ATTRIBUTUES_ALLOWED
#define NON_ATTR_IF(expr) if (expr) /* for some parameter checks without getting Wnonnull-compare */
#define MY_WARN_UNUSED
#define MY_NON_NULL(...)
#define MY_DEPRECATE(msg)
#define MY_FORMAT(...)
#define MY_INLINE
#endif // ATTRIBUTUES_ALLOWED

// big number
#define GIGA 1000000000L

#if ANSI_COLOR_FIESTA
#define RESET_ESC		"\033[0m"
#define DBLUE RESET_ESC		"\033[34m"
#define RED_BLD_INV RESET_ESC	"\033[31;1;7m"
#define LBLUE RESET_ESC		"\033[96m"
#define LRED_BLD RESET_ESC	"\033[91;1m"
#define LRED_BLD_INV RESET_ESC	"\033[91;1;7m"
#define VIOLET_BLD RESET_ESC	"\033[35;1m"
#define BWHITE RESET_ESC 	"\033[97m"
#define BWHITE_INV RESET_ESC	"\033[97;7m"
#define GREEN_BLD RESET_ESC	"\033[32;1m"
#define YELLLOW RESET_ESC 	"\033[33m"

#else
#define RESET_ESC		""
#define DBLUE			""
#define RED_BLD_INV		""
#define LBLUE			""
#define LRED_BLD		""
#define LRED_BLD_INV		""
#define VIOLET_BLD		""
#define BWHITE			""
#define BWHITE_INV		""
#define GREEN_BLD		""
#define YELLLOW			""
#endif // ANSI_COLOR_FIESTA

//  requires:
//  __FILE__, __LINE__, __func__, pid, ppid
#define INFO_FORMAT GREEN_BLD"%s" RESET_ESC":" YELLLOW"%d"\
		RESET_ESC" in " VIOLET_BLD"%s" RESET_ESC", PID:"\
		BWHITE"%06ld" RESET_ESC" PPID:" BWHITE"%06ld"\
		RESET_ESC" TID:" BWHITE"%ld" RESET_ESC

// NB: isMultiprocess is known at compile time
// so any regular compiler won't even assemble
// the if statement
#define ERR_EXIT(isMultiprocess) do {\
	if (isMultiprocess) kill(0, SIGKILL); /* Process Group */\
	else exit(EXIT_FAILURE); /* Own Process Only */\
} while(0)

// dodges ASAN sometimes :)
// a similar macro should be in safe-malloc.h but I can't include that for some reason :(
#define FREE(ptr) do {\
	free(ptr);\
	(ptr) = NULL;\
} while(0)
	
// goodbye Wunused-parameter/Wunused-variable lol
#define UNUSED(thing) do {\
	(void) (thing);\
} while(0)

// useful to force stringify some stuff
// 2 layers because uhhhh umm
// something something stackoverflow
#define TO_STR_(s) #s
#define TO_STR(X) TO_STR_(X)

#if EXEC_ALLOWED
#define MAX_EXEC_STR 1000
#define MAX_EXEC_LINE 200
#define EXEC_ONLY if (1)
#else // EXEC_ALLOWED
#define MAX_EXEC_STR 0
#define MAX_EXEC_LINE 0
#define EXEC_ONLY if (0)
#endif // EXEC_ALLOWED

// lmao bruh momnt
static inline ssize_t MY_INLINE MY_NON_NULL(1)
	charPos(const char* s, int c) {
		char* loc = strchr(s, c);
		return loc ? loc - s : -1;
	}

// cutely prints output of "addr2line -f -e filename address" cmd to a stream
static void MY_NON_NULL(1, 2, 3)
	myAddr2LinePrinter(FILE* stream, char* restrict line1, char* restrict line2,
			int oflag
			// possible options for oflag bitfield
#define TRUNCATE_RESERVED 01
#define TRUNCATE_TRACE_FUNCTIONS 02
#define TRUNCATE_UNKNOWN 04
#define TRUNCATE_ALOT TRUNCATE_RESERVED | TRUNCATE_TRACE_FUNCTIONS | TRUNCATE_UNKNOWN
			) {
		if (oflag & TRUNCATE_RESERVED && *line1 == '_') {
			fprintf(stream, VIOLET_BLD"\t[" BWHITE" Reserved Symbol " VIOLET_BLD"]\n"RESET_ESC);
			return;
		} else if (oflag & TRUNCATE_UNKNOWN && *line1 == '?') {
			fprintf(stream, VIOLET_BLD"\t[" BWHITE" ?? " VIOLET_BLD"]\n"RESET_ESC);
			return;
		} else if (oflag & TRUNCATE_TRACE_FUNCTIONS && ( !strcmp(line1, "myStackTracer\n") || !strcmp(line1, "backtrace\n"))) {
			fprintf(stream, VIOLET_BLD"\t[" BWHITE" Stack Trace Function " VIOLET_BLD"]\n"RESET_ESC);
			return;
		}

		fprintf(stream, VIOLET_BLD"\t");
		// lmfao wtf?? print the ling char by char just to ignore the '\n'??
		// lmao make this better
		for (char* curr = line1; *curr && *curr != '\n'; ++curr) {
			fputc(*curr, stream);
		}

		fprintf(stream, BWHITE" ( )\n" GREEN_BLD"\t");
		int lineNumberPrinted = 0;
		for (char* curr = line2; *curr; ++curr) {
			switch (*curr) {
				case ':':
					{
						fprintf(stream, RESET_ESC":" YELLLOW);
						lineNumberPrinted = 1; // i guess lol, usually works anyway
						// just uhh don't have ':' in paths tho? idk lol
						break;
					}
				case '(':
					{
						if (lineNumberPrinted) {
							// for printing discriminator thingy?
							fprintf(stream, RESET_ESC"(");
						} else goto justPutCharLol; // the usual -Wimplicit-fallthrough hax
						break;
					}
				default:
justPutCharLol:
					{
						fputc(*curr, stream);
						break;
					}
			}
		}

		fprintf(stream, RESET_ESC);
		return;
	}

// NB: DON'T link with -rdynamic b/c of this function
// the internet tells lies lol
//
// also this function is pretty unsafe lol
// you can turn it off with #define TRACE_ON_ERR 0
#define MAX_TRACE 150 /* even super complicated programs don't need this much tbh lol */
void myStackTracer(FILE* stream,
		int oflag // passed to myAddr2LinePrinter
		) {
	void* traceBuffer[MAX_TRACE];
	int size = backtrace(traceBuffer, MAX_TRACE);
	char** traceStrings;
	fprintf(stream, RESET_ESC"Call stack trace");

	if (NULL == (traceStrings = backtrace_symbols(traceBuffer, size))) {
		fprintf(stream, LRED_BLD" [Couldn't backtrace_symbols( )]\n"RESET_ESC);
		FREE(traceStrings);
		return;
	}

	FILE* execToFile;
	int ranOutOfSpaceAt;
	EXEC_ONLY {
		// extra char for '\0'
		char execBuffer[MAX_EXEC_STR + 1] = {0};

		// create the execution string for addr2line
		char* s2Curr = execBuffer;

		char* commandStr = "addr2line -f -e ";
		size_t commandStrSz = strlen(commandStr);
		ranOutOfSpaceAt = size;

		// TODO: better variable names here
		// ALSO BRUH WTF WHY DIDN'T I JUST USE MEMCPY AAAAA
		for (int i = 0, fail = 0; i < size; ++i) {
			char* sCurr = traceStrings[i]; 
			//s2Curr += sprintf(s2Curr, "addr2line -f -e ");

			if (s2Curr > execBuffer + MAX_EXEC_STR - commandStrSz)  {
				ranOutOfSpaceAt = i;
				//printf("SPRINTF\n");
				break;
			} else {
				memcpy(s2Curr, commandStr, commandStrSz);
				s2Curr += commandStrSz;
			}

			for (int done = 0; *sCurr && !done; ++sCurr, ++s2Curr) {
				if (s2Curr > execBuffer + MAX_EXEC_STR - 1)  {
					ranOutOfSpaceAt = i;
					//printf("SINGLE\n");
					fail = 1;
					break;
				} else
					switch (*sCurr) {
						case ')':
							{
								done = 1;
								goto replaceBrace; // Wimplicit-fallthrough hax lol
							}
						case '(':
replaceBrace:
							{
								*s2Curr = ' ';
								break;   
							}
						default:
							{
								*s2Curr = *sCurr;
								break;
							}
					}
			}
			if (fail) {
				break;
			}

			if (s2Curr > execBuffer + MAX_EXEC_STR - 1)  {
				ranOutOfSpaceAt = i;
				printf("SINGLE2\n");
				break;
			} else {
				*s2Curr = ';';
				++s2Curr;
			}
		}

		//fprintf(stderr, "%s\n%d\n\n", execBuffer, ranOutOfSpaceAt);
		if (NULL == (execToFile = popen(execBuffer, "r"))) {
			fprintf(stream, LRED_BLD" [Couldn't popen( )]\n"RESET_ESC);
			FREE(traceStrings);
			return;
		}
	} else {
		UNUSED(execToFile); // necessary? idk lol
		UNUSED(ranOutOfSpaceAt);
	}

	fprintf(stream,
	", Top %d frames from top to bottom:\n"
	"god help you if this trace happens in multiple threads at once lol " BWHITE"\u2620" RESET_ESC"\n"
	, size);

	EXEC_ONLY {
		fprintf(stream, "Also, line numbers in this trace are SOMEtimes slightly inaccurate for now, idk whyyy X|\n");
	}

	char line1[MAX_EXEC_LINE + 1], line2[MAX_EXEC_LINE + 1];
	for (int i = 0, badTraceMessagePrinted = 0; i < size; ++i) {
		fprintf(stream, BWHITE"#%d\t" RESET_ESC" %s\n"RESET_ESC, i, traceStrings[i]);

		EXEC_ONLY {
			if (ranOutOfSpaceAt == i) {
				if (!badTraceMessagePrinted) {
					fprintf(stream, LRED_BLD
							"\t[ Ran out of stack space for buffer to pretty-fy stack trace ]\n"
							"\t[ Consider setting MAX_EXEC_STR to a higher value ]\n"RESET_ESC);
					badTraceMessagePrinted = 1;
				}
				continue;
			}

			// extra char for '\0'
			fgets(line1, MAX_EXEC_LINE, execToFile);
			fgets(line2, MAX_EXEC_LINE, execToFile);
			myAddr2LinePrinter(stream, line1, line2, oflag);

#if TEMP_REMOVE
			fprintf(stream, VIOLET_BLD"\t");
			for (int ch, secondLine = 0, lineNumberPrinted = 0, done = 0;
					!done
					//&& i < ranOutOfSpaceAt
					&& !feof(execToFile); // TODO: make this better lol
			    ) {
				ch = fgetc(execToFile);
				switch (ch) {
					case '\n':
						{
							if (secondLine) {
								fprintf(stream, RESET_ESC"\n");
								done = 1;
							} else {
								fprintf(stream, BWHITE" ()" RESET_ESC"\n\tfrom " GREEN_BLD);
								secondLine = 1;
							}
							break;
						}
					case ':':
						{
							if (secondLine) {
								fprintf(stream, RESET_ESC":" YELLLOW);
								lineNumberPrinted = 1;
							} else {
								fputc(ch, stream);
							}
							break;
						}
					case '(':
						{
							if (lineNumberPrinted) {
								// for printing discriminator thingy?
								fprintf(stream, RESET_ESC"(");
							} else {
								fputc(ch, stream);
							}
							break;
						}
						/*
						   case EOF: // ??
						   break;
						   */
					default:
						{
							fputc(ch, stream);
							break;
						}
				}
			}
			fprintf(stream, RESET_ESC);
#endif // TEMP_REMOVE
		}
	}

	EXEC_ONLY {
		if (pclose(execToFile) == -1) {
			fprintf(stream, LRED_BLD"[Couldn't pclose( )]\n"RESET_ESC);
			perror(LRED_BLD"[Couldn't pclose( )]"RESET_ESC);
		}
	}

	fflush(stream);
	FREE(traceStrings);
}

// this next bit is a janky old version lol
#if TEMP_REMOVE
#if EXEC_ALLOWED
#define TRACE_EXEC_STUFF(stream, traceString) do {\
	/* extra char for '\0' */\
	char execBuffer[MAX_EXEC_STR + 1] = {0};\
	char *addr = traceString,\
	*curr = traceString;\
	/* we do a little choppin */\
	do {\
		if (*curr == '(') {\
			*curr = '\0';\
			addr = ++curr;\
			break;\
		}\
		++curr;\
	} while (1);\
	do {\
		if (*curr == ')') {\
			*curr = '\0';\
			break;\
		}\
		++curr;\
	} while (1);\
	snprintf(execBuffer, MAX_EXEC_STR, "addr2line -f -e %s %s; echo lol", traceString, addr);\
\
	FILE* execToFile;\
	if (NULL == (execToFile = popen(execBuffer, "r"))) {\
		fprintf(stream, "[Can't popen]\n");\
		break;\
	}\
\
	/* omg the amount of cheap hacks lmfao */\
	fprintf(stream, VIOLET_BLD);\
	for (int ch, secondLine = 0, lineNumberPrinted = 0; !feof(execToFile);) {\
		ch = fgetc(execToFile);\
		switch(ch) {\
			case '\n':\
				  {\
					  if (secondLine) {\
						  fprintf(stream, RESET_ESC"\n");\
					  } else {\
						  fprintf(stream, BWHITE" ()" RESET_ESC"\n\tin " GREEN_BLD);\
						  secondLine = 1;\
					  }\
					  break;\
				  }\
			case ':':\
				 {\
					 if (secondLine) {\
						 fprintf(stream, RESET_ESC":" YELLLOW);\
						 lineNumberPrinted = 1;\
					 } else {\
						 fputc(ch, stream);\
					 }\
					 break;\
				 }\
			case '(':\
				 {\
					 if (lineNumberPrinted) {\
						 fprintf(stream, RESET_ESC"(");\
					 } else {\
						 fputc(ch, stream);\
					 }\
					 break;\
				 }\
			case EOF:\
				break;\
			default: {\
					 fputc(ch, stream);\
					 break;\
				 }\
		}\
	}\
	fprintf(stream, RESET_ESC);\
	if (pclose(execToFile) == -1) {\
		fprintf(stream, "[Can't pclose]\n");\
		break;\
	}\
} while(0)
#else // EXEC_ALLOWED
#define TRACE_EXEC_STUFF(stream)
#endif // EXEC_ALLOWED
#define PRINT_STACK_TRACE(stream) do {\
	void* traceBuffer[MAX_TRACE];\
	int size = backtrace(traceBuffer, MAX_TRACE);\
	char** traceStrings = backtrace_symbols(traceBuffer, size);\
	fprintf(stream, LBLUE"Call stack trace"RESET_ESC);\
	if (NULL == traceStrings) {\
		fprintf(stream, LRED_BLD" [Couldn't backtrace]\n"RESET_ESC);\
	} else {\
		fprintf(stream, ", Top %d frames from top to bottom:\n", size);\
		fprintf(stream, "(Line numbers in the trace are sometimes slightly inaccurate for now)\n");\
		for (int i = 0; i < size; ++i) {\
			fprintf(stream, BWHITE"#%d\t" RESET_ESC" %s\n\t"RESET_ESC, i, traceStrings[i]);\
			TRACE_EXEC_STUFF(stream, traceStrings[i]);\
		}\
	}\
	fflush(stream);\
	FREE(traceStrings);\
} while(0)
#endif // TEMP_REMOVE

#if TRACE_ON_ERR
#define ERR_STACK_TRACE() myStackTracer(stderr, TRUNCATE_ALOT); fprintf(stderr, "\n")
#else // TRACE_ON_ERR
#define ERR_STACK_TRACE()
#endif // TRACE_ON_ERR

// NB: the manuals state that getpid/getppid are always successful and no errors are reserved
// Also this version can run some optional extra code (usually cleanup) before exiting
#define ERR_(source, cleanup) do {\
	int originalErrno = errno;/* just in case something weird happens lmao */\
	\
	close(STDOUT_FILENO); /* sometimes some weeeird stuff happens without this lol*/\
	/* especially in multithreaded environments */\
	\
	fprintf(stderr,\
			RED_BLD_INV"errno=%d" RESET_ESC" " INFO_FORMAT "\n"\
			, errno, __FILE__, __LINE__, __func__,\
			(long) getpid(), (long) getppid(), (long) pthread_self());\
	ERR_STACK_TRACE();\
	errno = originalErrno;\
	perror(source);\
	cleanup\
	ERR_EXIT(ERR_MULTIPROCESS);\
} while(0)
// 700IQ setup for having macros with optional arguments
// without simply using __VAR_ARGS__ lol
// courtesy of stackoverflow.com/q/3046889
#define ERR_0_ARGS() ERR_(LBLUE"Error Description"RESET_ESC,)
#define ERR_1_ARG(source) ERR_(source,)
#define ERR_2_ARGS(source, cleanup) ERR_(source, cleanup)
#define ERR_X_ARGS(x, A, B, FUNC, ...) FUNC
#define ERR(...) ERR_X_ARGS(, ##__VA_ARGS__,\
	ERR_2_ARGS(__VA_ARGS__),\
	ERR_1_ARG(__VA_ARGS__),\
	ERR_0_ARGS(__VA_ARGS__))\

#if EXTENSIONS_ALLOWED

// kinda overkill? but I guess this version should let you use the
// comparison value afterwards
#define USAGE(correctUsage) (__extension__({\
	bool assertion = (bool) (correctUsage);\
	if (!assertion) {\
		ERR_NEG(fprintf(stderr,\
					RED_BLD_INV"BAD ARGS" RESET_ESC": " LRED_BLD"!" RESET_ESC"( " LBLUE#correctUsage\
					RESET_ESC" )\n\n" LRED_BLD"Usage" RESET_ESC":\n" BWHITE"$ %s" RESET_ESC" %s\n"\
					, argv[0], USAGE_STRING));\
		ERR_EXIT(ERR_MULTIPROCESS);\
	}\
	assertion;\
}))

#define ERR_IF(expr, condition, castType, ...) (__extension__({\
	errno = 0;\
	castType exprVal = (castType) (expr);\
	if ( condition exprVal )\
	{ERR(LRED_BLD#condition RESET_ESC" ( " LBLUE#expr RESET_ESC" ) " RESET_ESC, ##__VA_ARGS__);}\
	exprVal;\
}))
#define DBGprintf(format, ...) (__extension__({\
	int printfRet = ERR_NEG(printf(LRED_BLD_INV"DBG:" RESET_ESC" " INFO_FORMAT "\n" BWHITE format RESET_ESC\
				, __FILE__, __LINE__, __func__,\
				(long) getpid(), (long) getppid(), (long) pthread_self(), ##__VA_ARGS__));\
	ERR_EOF(fflush(stdout));\
	printfRet;\
}))

#else // EXTENSIONS_ALLOWED

#define USAGE(correctUsage) do {\
	if (!(correctUsage)) {\
		ERR_NEG(fprintf(stderr,\
					RED_BLD_INV"BAD ARGS" RESET_ESC": " LRED_BLD"!" RESET_ESC"( " LBLUE#correctUsage\
					RESET_ESC" )\n\n" LRED_BLD"Usage" RESET_ESC":\n" BWHITE"$ %s" RESET_ESC" %s\n"\
					, argv[0], USAGE_STRING));\
		ERR_EXIT(ERR_MULTIPROCESS);\
	}\
} while(0)

// NB: castType is ignored here, because I'm too lazy lol
// not the best solution but whatever
// TODO: FIX THIS LOL
#define ERR_IF(expr, condition, castType, ...) do {\
	errno = 0;\
	castType exprVal = (castType) (expr);\
	if ( condition exprVal )\
	{ERR(LRED_BLD#condition RESET_ESC" ( " LBLUE#expr RESET_ESC" ) " RESET_ESC, ##__VA_ARGS__);}\
} while (0)
#define DBGprintf(format, ...) do {\
	ERR_NEG(printf(LRED_BLD_INV"DBG:" RESET_ESC" " INFO_FORMAT "\n" BWHITE format RESET_ESC\
				, __FILE__, __LINE__, __func__,\
				(long) getpid(), (long) getppid(), (long) pthread_self(), ##__VA_ARGS__));\
	ERR_EOF(fflush(stdout));\
} while(0)

#endif // EXTENSIONS_ALLOWED

#define ERR_NEG1(expr, ...) ERR_IF(expr, -1 ==, int, ##__VA_ARGS__)
#define ERR_NEG(expr, ...) ERR_IF(expr, 0 > , int, ##__VA_ARGS__)
#define ERR_NON_ZERO(expr, ...) ERR_IF(expr, 0 !=, int, ##__VA_ARGS__)
#define ERR_EOF(expr, ...) ERR_IF(expr, EOF ==, int, ##__VA_ARGS__)
#define ERR_NULL(expr, ...) ERR_IF(expr, NULL ==, void*, ##__VA_ARGS__)
#define ERR_SSIZE_T(expr, ...) ERR_IF(expr, -1 ==, ssize_t, ##__VA_ARGS__)
#define ERR_MQ(expr, ...) ERR_IF(expr, (mqd_t) -1 ==, mqd_t, ##__VA_ARGS__)
#define ERR_IN_ADDR_T(expr, ...) ERR_IF(expr, (in_addr_t) -1 ==, in_addr_t, ##__VA_ARGS__)
#define ERR_BARRIER(expr, ...) ERR_IF(expr, PTHREAD_BARRIER_SERIAL_THREAD != exprVal && 0 !=, int, ##__VA_ARGS__)
#define ERR_SEM(expr, ...) ERR_IF(expr, SEM_FAILED ==, sem_t, ##__VA_ARGS__)

// versions that allow a single okay errno value:
#define ERR_IF_(expr, condition, acceptableError, castType, ...) ERR_IF(expr, errno != acceptableError && condition, castType, ##__VA_ARGS__)
#define ERR_NEG1_(expr, acceptableError, ...) ERR_IF_(expr, -1 ==, acceptableError, int, ##__VA_ARGS__)
#define ERR_NEG_(expr, acceptableError, ...) ERR_IF_(expr, 0 >, acceptableError, int, ##__VA_ARGS__)
#define ERR_NON_ZERO_(expr, acceptableError, ...) ERR_IF_(expr, 0 !=, acceptableError, int, ##__VA_ARGS__)
#define ERR_EOF_(expr, acceptableError, ...) ERR_IF_(expr, EOF == , acceptableError, int, ##__VA_ARGS__)
#define ERR_NULL_(expr, acceptableError, ...) ERR_IF_(expr, NULL ==, acceptableError, void*, ##__VA_ARGS__)
#define ERR_SSIZE_T_(expr, acceptableError, ...) ERR_IF(expr, -1 ==, acceptableError, ssize_t, ##__VA_ARGS__)
#define ERR_MQ_(expr, acceptableError, ...) ERR_IF_(expr, (mqd_t) -1 ==, acceptableError, mqd_t, ##__VA_ARGS__)
#define ERR_IN_ADDR_T_(expr, acceptableError, ...) ERR_IF(expr, (in_addr_t) -1 ==, acceptableError, in_addr_t, ##__VA_ARGS__)
#define ERR_BARRIER_(expr, ...) ERR_IF(expr, PTHREAD_BARRIER_SERIAL_THREAD != exprVal && 0 !=, acceptableError, int, ##__VA_ARGS__)
#define ERR_SEM_(expr, acceptableError, ...) ERR_IF(expr, SEM_FAILED ==, acceptableError, sem_t, ##__VA_ARGS__)

// version of DBGprintf that only compiles in DEBUG_MODE
// kinda want DBGprintf to be nice and accesible normally
#if DEBUG_MODE
#define DBGonly(...) DBGprintf(__VA_ARGS__)
#else // DEBUG_MODE
#define DBGonly(...)
#endif // DEBUG_MODE

// bit for functions that sometimes error depending on settings lol
// TODO: generalize RETURN_FAIL? idk
#define MY_ERRNO EINVAL
#if RETURN_ERR
#define MY_ERR_CODE -1

#define MIGHT_ERR_(normalType, errType) errType MY_WARN_UNUSED
#define MIGHT_FAIL_(expr, err, ...) err(expr, ##__VA_ARGS__)

#define RETURN_OKAY return 0

#if EXTENSIONS_ALLOWED
#define RETURN_FAIL(reason) (__extension__({\
	errno = MY_ERRNO;\
	DBGonly(reason "\n");\
	return MY_ERR_CODE;\
}))
#else // EXTENSIONS_ALLOWED
#define RETURN_FAIL(reason) do {\
	errno = MY_ERRNO;\
	DBGonly(reason "\n");\
	return MY_ERR_CODE;\
} while(0)
#endif // EXTENSIONS_ALLOWED

#else // RETURN_ERR
#define MIGHT_ERR_(normalType, errType) normalType
#define MIGHT_FAIL_(expr, err, ...) expr

#define RETURN_OKAY return

#if EXTENSIONS_ALLOWED
#define RETURN_FAIL(reason) (__extension__({\
	errno = MY_ERRNO;\
	ERR(reason);\
}))
#else // EXTENSIONS_ALLOWED
#define RETURN_FAIL(reason) do {\
	errno = MY_ERRNO;\
	ERR(reason);\
} while(0)
#endif // EXTENSIONS_ALLOWED
#endif // RETURN_ERR

// TODO: FIX THIS DUMB MIGHT_ERR STUFF LMFAO
// also add some MIGHT_ERR_CHECK quasi-if thingy
// like NON_ATTR_IF but for MIGHT functions

// more quasi-optional args fiesta eksdi
#define MIGHT_ERR_0_ARGS() MIGHT_ERR_(void, int)
#define MIGHT_ERR_1_ARG(normalType) MIGHT_ERR_(normalType, normalType)
#define MIGHT_ERR_2_ARGS(normalType, errType) MIGHT_ERR_(normalType, errType)
#define MIGHT_ERR_X_ARGS(x, A, B, FUNC, ...) FUNC
#define MIGHT_ERR(...) MIGHT_ERR_X_ARGS(, ##__VA_ARGS__,\
	MIGHT_ERR_2_ARGS(__VA_ARGS__),\
	MIGHT_ERR_1_ARG(__VA_ARGS__),\
	MIGHT_ERR_0_ARGS(__VA_ARGS__))

#if EXTENSIONS_ALLOWED
#define myRetry(expr, castType) (__extension__({\
    castType val;\
    do {val = (castType) (expr);} \
    while(errno == EINTR);\
    val;\
}))
#else // EXTENSIONS_ALLOWED
// lol:
#define myRetry(expr, castType) TEMP_FAILURE_RETRY(expr)
#endif // EXTENSIONS_ALLOWED

// So we use these to just fail if we're in RETURN_ERR
// and the function fails? okayyy
// we boutta need a big rework lol
#define MIGHT_FAIL_NEG1(expr, ...) MIGHT_FAIL_(expr, ERR_NEG1, ##__VA_ARGS__)
#define MIGHT_FAIL_NEG(expr, ...) MIGHT_FAIL_(expr, ERR_NEG, ##__VA_ARGS__)
#define MIGHT_FAIL_NON_ZERO(expr, ...) MIGHT_FAIL_(expr, ERR_NON_ZERO, ##__VA_ARGS__)
#define MIGHT_FAIL_EOF(expr, ...) MIGHT_FAIL_(expr, ERR_EOF, ##__VA_ARGS__)
#define MIGHT_FAIL_NULL(expr, ...) MIGHT_FAIL_(expr, ERR_NULL, ##__VA_ARGS__)
#define MIGHT_FAIL_SSIZE_T(expr, ...) MIGHT_FAIL_(expr, ERR_SSIZE_T, ##__VA_ARGS__)
#define MIGHT_FAIL_IN_ADDR_T(expr, ...) MIGHT_FAIL_(expr, ERR_IN_ADDR_T, ##__VA_ARGS__)

// UGHHH YUCK GROSSS
// TODO: make these names better
#define CHECK_RETRY_BASE(expr, err, errType, ...) err( myRetry(expr, errType) , ##__VA_ARGS__)

#define CHECK_RETRY(expr, ...) CHECK_RETRY_BASE(expr, ERR_NEG1, int, ##__VA_ARGS__)
#define CHECK_RETRY_MQ(expr, ...) CHECK_RETRY_BASE(expr, ERR_MQ, mqd_t, ##__VA_ARGS__)
#define CHECK_RETRY_SSIZE_T(expr, ...) CHECK_RETRY_BASE(expr, ERR_SSIZE_T, ssize_t, ##__VA_ARGS__)
#define CHECK_RETRY_EOF(expr, ...) CHECK_RETRY_BASE(expr, ERR_EOF, int, ##__VA_ARGS__)

#define CHECK_RETRY_(expr, ...) CHECK_RETRY_BASE(expr, ERR_NEG1_, int, ##__VA_ARGS__)
#define CHECK_RETRY_MQ_(expr, ...) CHECK_RETRY_BASE(expr, ERR_MQ_, mqd_t, ##__VA_ARGS__)
#define CHECK_RETRY_SSIZE_T_(expr, ...) CHECK_RETRY_BASE(expr, ERR_SSIZE_T_, ssize_t, ##__VA_ARGS__)
#define CHECK_RETRY_EOF_(expr, ...) CHECK_RETRY_BASE(expr, ERR_EOF_, int, ##__VA_ARGS__)
// in theory there's more types to check but whoooooooo caaaaares

// error checked and retried (if EINTR) versions of some message queue functions
#define mq_send_(mqdes, msg_ptr, msg_len, msg_prio, ...)\
	CHECK_RETRY(mq_send(mqdes, msg_ptr, msg_len, msg_prio), ##__VA_ARGS__)
#define mq_receive_(mqdes, msg_ptr, msg_len, msg_prio, ...)\
	CHECK_RETRY(mq_receive(mqdes, msg_ptr, msg_len, msg_prio), ##__VA_ARGS__)
#define mq_close_(mqdes, ...)\
	CHECK_RETRY(mq_close(mqdes), ##__VA_ARGS__)
#define mq_getattr_(mqdes, mqstat, ...)\
	CHECK_RETRY( mq_getattr(mqdes, mqstat), ##__VA_ARGS__)
#define mq_notify_(mqdes, notification, ...)\
	CHECK_RETRY( mq_notify(mqdes, notification), ##__VA_ARGS__)
#define mq_setattr_(mqdes, mqstat, omgstat, ...)\
	CHECK_RETRY( mq_setattr(mqdes, mqstat, omgstat), ##__VA_ARGS__)
#define mq_timedreceive_(mqdes, msg_ptr, msg_len, msg_prio, ...)\
	CHECK_RETRY(mq_timedreveive(mqdes, mqstat, omgstat), ##__VA_ARGS__)
#define mq_timedsend_(mqdes, msg_ptr, msg_len, msg_prio, abstime, ...)\
	CHECK_RETRY(mq_timedsend(mqdes, msg_ptr, msg_len, msg_prio, abstime), ##__VA_ARGS__)
#define mq_unlink_(name, ...)\
	CHECK_RETRY(mq_unlink(name), ##__VA_ARGS__)
// this one's already got __VA_ARGS__ so we can't cleanup the way we do usually
#define mq_open_(name, oflag, ...)\
	CHECK_RETRY_MQ(mq_open(name, oflag, ##__VA_ARGS__))

// error retried and/or checked versions of socket functions:
#define recvfrom_(socket, buffer, length, flags, address, address_len, ...)\
	CHECK_RETRY_SSIZE_T(recvfrom(socket, buffer, length, flags, address, address_len), ##__VA_ARGS__)
#define sendto_(socket, buffer, length, flags, dest_addr, address_len, ...)\
	CHECK_RETRY_SSIZE_T(sendto(socket, buffer, length, flags, dest_addr, address_len), ##__VA_ARGS__)
#define socket_(domain, type, protocol, ...)\
	ERR_NEG1(socket(domain, type, protocol), ##__VA_ARGS__)
#define close_(fd, ...)\
	CHECK_RETRY(close(fd), ##__VA_ARGS__)
#define bind_(socket, address, address_len, ...)\
	ERR_NEG1(bind(socket, address, address_len), ##__VA_ARGS__)
#define listen_(sockfd, backlog, ...)\
	ERR_NEG1(listen(sockfd, backlog), ##__VA_ARGS__)
#define send_(sockfd, buf, len, flags, ...)\
	CHECK_RETRY_SSIZE_T(send(sockfd, buf, len, flags), ##__VA_ARGS__)
#define recv_(socket, buffer, length, flags, ...)\
	CHECK_RETRY_SSIZE_T(recv(socket, buffer, length, flags), ##__VA_ARGS__)
#define accept_(socket, address, address_len, ...)\
	CHECK_RETRY(accept(socket, address, address_len), ##__VA_ARGS__)
#define select_(nfds, readfds, writefds, errorfds, timeout, ...)\
	CHECK_RETRY(select(nfds, readfds, writefds, errorfds, timeout), ##__VA_ARGS__)
#define setsockopt_(socket, level, option_name, option_value, option_len, ...)\
	ERR_NEG1(setsockopt(socket, level, option_name, option_value, option_len), ##__VA_ARGS__)
#define fcntl_(fildes, cmd, ...)\
	CHECK_RETRY(fcntl(fildes, cmd, ##__VA_ARGS__))
#define sigprocmask_(how, set, oset, ...)\
	ERR_NEG1(sigprocmask(how, set, oset), ##__VA_ARGS__)

// I have no idea if these ones need to handle EINTR lol
#define dprintf_(fildes, format, ...)\
	ERR_NEG_(printf(fildes, format, ##__VA_ARGS__))
#define fprintf_(stream, format, ...)\
	ERR_NEG(printf(stream, format, ##__VA_ARGS__))
#define printf_(format, ...)\
	ERR_NEG_(printf(format, ##__VA_ARGS__), EBADF)
// shhh pretend you didn't see that, but also don't remove it b/c everything breaks lol
#define snprintf_(s, n, format, ...)\
	ERR_NEG(snprintf(s, n, format, ##__VA_ARGS__))
#define sprintf_(s, format, ...)\
	ERR_NEG(sprintf(s, format, ##__VA_ARGS__))

#define fflush_(stream, ...)\
	CHECK_RETRY_EOF(fflush(stream), ##__VA_ARGS__)

// lab 3/8-ish stuff?
#define malloc_(size, ...)\
	ERR_NULL(malloc(size), ##__VA_ARGS__)
#define calloc_(nmemb, size, ...)\
	ERR_NULL(calloc(nmemb, size), ##__VA_ARGS__)
#define pthread_create_(thread, attr, start_routine, arg, ...)\
	ERR_NON_ZERO(pthread_create(thread, attr, start_routine, arg), ##__VA_ARGS__)
#define pthread_join_(thread, value_ptr, ...)\
	ERR_NON_ZERO(pthread_join(thread, value_ptr), ##__VA_ARGS__)
#define pthread_mutex_destroy_(mutex, ...)\
	ERR_NON_ZERO(pthread_mutex_destroy(mutex), ##__VA_ARGS__)
#define pthread_mutex_init_(mutex, attr, ...)\
	ERR_NON_ZERO(pthread_mutex_init(mutex, attr), ##__VA_ARGS__)
#define pthread_mutex_lock_(mutex, ...)\
	ERR_NON_ZERO(pthread_mutex_lock(mutex), ##__VA_ARGS__)
#define pthread_mutex_unlock_(mutex, ...)\
	ERR_NON_ZERO(pthread_mutex_unlock(mutex), ##__VA_ARGS__)
#define pthread_mutex_trylock_(mutex, ...)\
	ERR_NON_ZERO(pthread_mutex_trylock(mutex), ##__VA_ARGS__)
#define pthread_detach_(thread, ...)\
	ERR_NON_ZERO(pthread_detach(thread), ##__VA_ARGS__)
#define pthread_attr_init_(attr, ...)\
	ERR_NON_ZERO(pthread_attr_init(attr), ##__VA_ARGS__)
#define pthread_attr_destroy_(attr, ...)\
	ERR_NON_ZERO(pthread_attr_destroy(attr), ##__VA_ARGS__)
#define pthread_attr_getdetachstate_(attr, detachstate, ...)\
	ERR_NON_ZERO(pthread_attr_getdetachstate(attr, detachstate), ##__VA_ARGS__)
#define pthread_attr_setdetachstate_(attr, detachstate, ...)\
	ERR_NON_ZERO(pthread_attr_setdetachstate(attr, detachstate), ##__VA_ARGS__)
#define pthread_sigmask_(how , set, oset, ...)\
	ERR_NON_ZERO(pthread_sigmask(how , set, oset), ##__VA_ARGS__)
#define sigwait_(set, sig, ...)\
	ERR_NON_ZERO(sigwait(set, sig), ##__VA_ARGS__)
#define pthread_cancel_(thread, ...)\
	ERR_NON_ZERO(pthread_cancel(thread), ##__VA_ARGS__)
#define sigaddset_(set, signo, ...)\
	ERR_NEG1(sigaddset(set, signo), ##__VA_ARGS__)
#define pthread_cond_destroy_(cond, ...)\
	ERR_NON_ZERO(pthread_cond_destroy(cond), ##__VA_ARGS__)
#define pthread_cond_init_(cond, attr, ...)\
	ERR_NON_ZERO(pthread_cond_init(cond, attr), ##__VA_ARGS__)
#define pthread_cond_timedwait_(cond, mutex, abstime, ...)\
	ERR_NON_ZERO(pthread_cond_timedwait(cond, mutex, abstime), ##__VA_ARGS__)
#define pthread_cond_wait_(cond, mutex, ...)\
	ERR_NON_ZERO(pthread_cond_wait(cond, mutex), ##__VA_ARGS__)
#define pthread_cond_broadcast_(cond, ...)\
	ERR_NON_ZERO(pthread_cond_broadcast(cond), ##__VA_ARGS__)
#define pthread_cond_signal_(cond, ...)\
	ERR_NON_ZERO(pthread_cond_signal(cond), ##__VA_ARGS__)
#define pthread_barrier_destroy_(barrier, ...)\
	ERR_NON_ZERO(pthread_barrier_destroy(barrier), ##__VA_ARGS__)
#define pthread_barrier_init_(barrier, attr, count, ...)\
	ERR_NON_ZERO(pthread_barrier_init(barrier, attr, count), ##__VA_ARGS__)
#define pthread_barrier_wait_(barrier, ...)\
	ERR_BARRIER(pthread_barrier_wait(barrier), ##__VA_ARGS__)
#define sem_init_(sem, pshared, value, ...)\
	ERR_NEG1(sem_init(sem, pshared, value), ##__VA_ARGS__)
#define sem_open_(name, flag, ...)\
	ERR_SEM(sem_open(name, flag, ##__VA_ARGS__))
#define sem_trywait_(sem, ...)\
	CHECK_RETRY(sem_trywait(sem), ##__VA_ARGS__)
#define sem_wait_(sem, ...)\
	CHECK_RETRY(sem_wait(sem), ##__VA_ARGS__)
#define sem_post_(sem, ...)\
	ERR_NEG1(sem_post(sem), ##__VA_ARGS__)
#define sem_close_(sem, ...)\
	ERR_NEG1(sem_close(sem), ##__VA_ARGS__)
#define sem_destroy_(sem, ...)\
	ERR_NEG1(sem_destroy(sem), ##__VA_ARGS__)

#define pthread_setcancelstate_(state, oldstate, ...)\
	ERR_NEG1(pthread_setcancelstate(state, oldstate), ##__VA_ARGS__)
#define pthread_setcanceltype_(type, oldtype, ...)\
	ERR_NEG1(pthread_setcanceltype(type, oldtype), ##__VA_ARGS__)

// extra:
#define open_(path, oflag, ...)\
	CHECK_RETRY(open(path, oflag, ##__VA_ARGS__))

// TODO: getaddrinfo and stuff lul

void waitAllChildren(void) {
#if DEBUG_MODE
	int i = 0;
#endif // DEBUG_MODE

	for (pid_t pid; true;) {
		// error check except ECHILD:
		ERR_NEG1_(pid = waitpid(-1, NULL, 0) , ECHILD);

#if DEBUG_MODE
		DBGprintf(BWHITE"pid:%06ld (after " DBLUE"%d" BWHITE" waitpid calls)\n",
				(long) pid, ++i
			 );
#endif // DEBUG_MODE

		if (errno == ECHILD) break;
	}
}

// TODO: check handling of EINTR here
void myNanoSleep (long nanoseconds) {
	/*
	 * nanosleeps for the given nanoseconds
	 */

	DBGonly("ns:%ld\n",
			nanoseconds
	       );

	struct timespec time;
	time.tv_sec = nanoseconds / GIGA; // int division
	time.tv_nsec = nanoseconds % GIGA;

	for (int returnState = -1
#if DEBUG_MODE
			, i = 0
#endif // DEBUG_MODE
			; returnState;) {
		// error check except EINTR:
		ERR_NEG1_(returnState = nanosleep(&time, &time) , EINTR);

		DBGonly("ret:%d, timespec:{s:%ld ns:%ld} (after %d nanosleep calls)\n",
				returnState, time.tv_sec, time.tv_nsec, ++i
		       );
	}
}

// TODO: check handling of EINTR here
void myNanoSleep2(time_t seconds, long nanoseconds) {
	DBGonly("s:%ld ns:%ld\n",
			seconds, nanoseconds
	       );

	struct timespec time;
	time.tv_sec = seconds;
	time.tv_nsec = nanoseconds;

	for (int returnState = -1
#if DEBUG_MODE
			, i = 0
#endif // DEBUG_MODE
			; returnState;) {
		// error check except EINTR:
		ERR_NEG1_(returnState = nanosleep(&time, &time) , EINTR);

		DBGonly("ret:%d, timespec:{s:%ld ns:%ld} (after %d nanosleep calls)\n",
				returnState, time.tv_sec, time.tv_nsec, ++i
		       );
	}
}

int MY_NON_NULL(2)
	read_(int fildes, void* buf, size_t nbyte) {
		int returnState = -1
#if DEBUG_MODE
			, i = 0
#endif // DEBUG_MODE
			; 

		do {
			// error check except EINTR:
			ERR_NEG1_(returnState = read(fildes, buf, nbyte), EINTR);

			DBGonly("ret:%d (after %d read calls)\n",
					returnState, ++i
			       );
		} while (returnState == -1);

		return returnState;
	}

int MY_NON_NULL(2)
	write_(int fildes, void* buf, size_t nbyte) {
		int returnState = -1
#if DEBUG_MODE
			, i = 0
#endif // DEBUG_MODE
			; 

		do {
			// error check except EINTR:
			ERR_NEG1_(returnState = write(fildes, buf, nbyte), EINTR);

			DBGonly("ret:%d (after %d write calls)\n",
					returnState, ++i
			       );
		} while (returnState == -1);

		return returnState;
	}

// TODO: is ulong truly necessary? ...
// TODO: add more randomizers also?
unsigned long MY_WARN_UNUSED
#if USE_RAND_R
MY_NON_NULL(3)
#endif // USE_RAND_R
	myRand(unsigned long min, unsigned long max
#if USE_RAND_R
			, unsigned int* seed
#endif // USE_RAND_R
	      ) {
		// TODO: add seed check for if attributes aren't allowed
#if USE_RAND_R
		DBGonly("min:%ld max:%ld seed:%p\n",
				min, max, (void*) seed
		       );
#else // USE_RAND_R
		DBGonly("min:%ld max:%ld\n",
				min, max
		       );
#endif // USE_RAND_R

		return min +
#if USE_RAND_R
			rand_r(seed)
#else // USE_RAND_R
			rand()
#endif // USE_RAND_R
			% (max - min + 1);
	}

double MY_WARN_UNUSED
#if USE_RAND_R
MY_NON_NULL(3)
#endif // USE_RAND_R
	myRandDouble(double min, double max
#if USE_RAND_R
			, unsigned int* seed
#endif // USE_RAND_R
		    ) {
#if USE_RAND_R
		DBGonly("min:%lf max:%lf seed:%p\n",
				min, max, (void*) seed
		       );
#else // USE_RAND_R
		DBGonly("min:%lf max:%lf\n",
				min, max
		       );
#endif // USE_RAND_R

		return min + (
#if USE_RAND_R
				myRand(0, GIGA, seed)
#else // USE_RAND_R
				myRand(0, GIGA)
#endif // USE_RAND_R
				* 1.0L / GIGA) * (max - min);
	}

void
#if USE_RAND_R
MY_NON_NULL(3)
#endif // USE_RAND_R
	myRandSleep(double minSec, double maxSec
#if USE_RAND_R
			, unsigned int* seed
#endif // USE_RAND_R
		   ) {
#if USE_RAND_R
		DBGonly("minSec:%lf maxSec:%lf seed:%p\n",
				minSec, maxSec, (void*) seed
		       );
#else // USE_RAND_R
		DBGonly("minSec:%lf maxSec:%lf\n",
				minSec, maxSec
		       );
#endif // USE_RAND_R

		myNanoSleep(myRand(minSec * GIGA, maxSec * GIGA
#if USE_RAND_R
					, seed
#endif // USE_RAND_R
				  ));
	}

void printBuf(char* buffer, size_t sz) {
	DBGonly("buffer:%p sz:%zd\n",
			(void*) buffer, sz
	       );

	write_(STDOUT_FILENO, buffer, sz);
	printf_("\n");
}

void* MY_NON_NULL(1, 2)
	substr(char* dest, char* src, off_t start, size_t length) {
		DBGonly("dest:%s src:%s start:%ld length:%ld",
				dest, src, start, length
		       );

		// TODO: should this be an int function?
		// maybe I shouldn't call err here and just return an error code
		if (
#if !ATTRIBUTES_ALLOWED
				dest == NULL || src == NULL || // wtf??? that's a separte check anyway, no? lmfao
#endif // !ATTRIBUTES_ALLOWED
				dest == src) {
			errno = MY_ERRNO;
			ERR(LBLUE"dest" RESET_ESC" (" DBLUE"arg 1" RESET_ESC") "
					LRED_BLD"==" LBLUE" src" RESET_ESC" (" DBLUE"arg 2" RESET_ESC")");
		}

		size_t i = 0;

		// TODO: holy shit rework this to use memmove/memcopy lmfao
		// why actually do the work?
		for (; i < length;
				dest[i] = src[start + i],
				++i);

		dest[i] = '\0';

		return dest;
	}

void* MY_NON_NULL(1)
	leftShift_fill(void* buff, size_t length, size_t amount, int c) {
		DBGonly("buff:%p length:%ld amount:%ld c:(int) %d",
				buff, (long) length, (long) amount, c
		       );
		memmove(buff, ((int8_t*) buff) + amount, length - amount);
		memset(((int8_t*) buff) + length - amount, c, amount);

		return buff;
	}

// TODO: debug-mode the rest of this stuff
void* MY_NON_NULL(1)
	leftShift(void* buff, size_t length, size_t amount) {
		return leftShift_fill(buff, length, amount, 0);
	}

void* MY_NON_NULL(1)
	leftShift_cycle(void* buff, size_t length, size_t amount) {
		void* tmp;
		ERR_NULL(tmp = malloc(amount));
		memcpy(tmp, buff, amount);

		// leftShift(buff, length, amount);
		memmove(buff, ((int8_t*) buff) + amount, length - amount);

		memcpy(((int8_t*) buff) + length - amount, tmp, amount);
		FREE(tmp);

		return buff;
	}

void* MY_NON_NULL(1)
	rightShift_fill(void* buff, size_t length, size_t amount, int c) {
		return memset(((int8_t*) buff) + length - amount, c, amount);
	}

void* MY_NON_NULL(1)
	rightShift(void* buff, size_t length, size_t amount) {
		return rightShift_fill(buff, length, amount, 0);
	}

void* MY_NON_NULL(1)
	rightShift_cycle(void* buff, size_t length, size_t amount) {
		void* tmp;
		ERR_NULL(tmp = malloc(amount));
		memcpy(tmp, ((int8_t*) buff) + length - amount, amount);
		memmove(&((int8_t*) buff)[amount], buff, length - amount);
		//memcpy(buff, tmp, amount);
		FREE(tmp);
		return buff;
	}

void* MY_NON_NULL(1)
	removeNinstances(char* str, char c, ssize_t n) {
		size_t sz = strlen(str);
		for (size_t i = 0; i < sz && n; ++i)
			for (; str[i] == c; --n)
				leftShift(str + i, sz - i, 1);
		return str;
	}

#define SIGEV_INFO_FORMAT "{notify:%d signo:%d value:{int:%d ptr:%p} funct:%p attr:%p tid:%ld}"

MIGHT_ERR()
	init_notification(struct sigevent* notification, int notify, int signo, int sival_int, void* sival_ptr,
			void (*notify_function) (union sigval), void* notify_attributes) {
#if TEMP_REMOVE
		// TODO: maybe some if statements, to make this kinda thing work?
		// TODO: or maybe not? lmfao?

		// btw man 7 sigevent tells lies? lmao
		// there's no sigevent.sigev_notify_thread_id ??
		DBGonly("params: " SIGEV_INFO_FORMAT "%d %d %d %p %p %p\n",
				notification->sigev_notify, notification->sigev_signo,
				notification->sigev_value.sival_int, (void*) notification->sigev_value.sival_ptr,
				(void*) notification->sigev_notify_function, (void*) notification->sigev_notify_attributes,
				(long) notification->_sigev_un._tid

				, notify, signo, sival_int, sival_ptr, (void*) notify_function, (void*) notify_attributes
		       );
#endif // TEMP_REMOVE
		DBGonly("notification:%p notify:%d signo:%d sival_int:%d sival_ptr:%p notify_function:%p notify_attributes:%p\n",
				(void*) notification,
				notify, signo, sival_int, sival_ptr, (void*) notify_function, notify_attributes
		       );

		if (sival_int && sival_ptr) {
			RETURN_FAIL(LBLUE"sival_int" RESET_ESC" (" DBLUE"arg 4" RESET_ESC") passed "
					LRED_BLD"and" LBLUE" sival_ptr" RESET_ESC" (" DBLUE"arg 5" RESET_ESC") passed.\n"
					"(They are members of a union. Only pass one)");
		}

		if ((SIGEV_THREAD == notify) && !notify_function) {
			RETURN_FAIL(LBLUE"notify" RESET_ESC" (" DBLUE"arg 2" RESET_ESC") is SIGEV_THREAD but "
					LBLUE"notify_function" RESET_ESC" (" DBLUE"arg 6" RESET_ESC") is " LRED_BLD"NULL" RESET_ESC"\n");		
		}

		memset(notification, 0, sizeof(struct sigevent));

		notification->sigev_notify = notify;

		union sigval value;
		if (sival_int)
			value.sival_int = sival_int;
		else
			value.sival_ptr = sival_ptr;

		switch (notify) {
			case SIGEV_NONE:
				{
					RETURN_OKAY;
				}
			case SIGEV_SIGNAL:
				{
					notification->sigev_signo = signo;
					notification->sigev_value = value;
					RETURN_OKAY;
				}
			case SIGEV_THREAD:
				{
					notification->sigev_value = value;
					notification->sigev_notify_function = notify_function;
					notification->sigev_notify_attributes = notify_attributes;
					RETURN_OKAY;
				}
			default:
				{
					RETURN_FAIL(LRED_BLD"invalid " LBLUE"notify" RESET_ESC" (" DBLUE"arg 2" RESET_ESC") passed\n");
				}
		}
	}

struct sigevent MY_WARN_UNUSED
	make_notification(int notify, int signo, int sival_int, void* sival_ptr,
			void (*notify_function) (union sigval), void* notify_attributes) {
		struct sigevent notification;
		MIGHT_FAIL_NEG1(init_notification(&notification, notify, signo, sival_int, sival_ptr,
					notify_function, notify_attributes));
		return notification;
	}
// lol:
#define notification_make(notify, signo, sival_int, sival_ptr, notify_function, notify_attributes)\
	make_notification(notify, signo, sival_int, sival_ptr, notify_function, notify_attributes)

#define AIOCB_INFO_FORMAT "{fildes:%d offs:%ld buf:%p n:%lu prio:%d sigev:" SIGEV_INFO_FORMAT " opcode:%d}"

MIGHT_ERR()
	init_aiocb(struct aiocb* cbp, int fildes, off_t offset, ssize_t nbytes, volatile void* aio_buf,
			struct sigevent* notification) {
#if TEMP_REMOVE
		DBGonly("params: " AIOCB_INFO_FORMAT " %d %ld %zd %p " SIGEV_INFO_FORMAT "\n",
				cbp->aio_fildes, cbp->aio_offset, (void*) cbp->aio_buf, cbp->aio_nbytes, cbp->aio_reqprio,

				cbp->aio_sigevent.sigev_notify, cbp->aio_sigevent.sigev_signo,
				cbp->aio_sigevent.sigev_value.sival_int, (void*) cbp->aio_sigevent.sigev_value.sival_ptr,
				(void*) cbp->aio_sigevent.sigev_notify_function, (void*) cbp->aio_sigevent.sigev_notify_attributes,
				(long) cbp->aio_sigevent._sigev_un._tid,

				cbp->aio_lio_opcode,

				fildes, offset, nbytes, (void*) aio_buf,

				notification->sigev_notify, notification->sigev_signo,
				notification->sigev_value.sival_int, (void*) notification->sigev_value.sival_ptr,
				(void*) notification->sigev_notify_function, (void*) notification->sigev_notify_attributes,
				(long) notification->_sigev_un._tid
		       );
#endif // TEMP_REMOVE
		DBGonly("cbp:%p fildes:%d offset:%ld nbytes:%zd aio_buf:%p notification:%p\n",
				(void*) cbp,
				fildes, offset, nbytes, (void*) aio_buf,
				(void*) notification
		       );

		memset(cbp, 0, sizeof(struct aiocb));

		cbp->aio_fildes = fildes;

		if (offset >= 0)
			cbp->aio_offset = offset;
		else {
			RETURN_FAIL(LRED_BLD"negative" RESET_ESC" file " LBLUE"offset" RESET_ESC" (" DBLUE"arg 3"
					RESET_ESC") passed");
		}

		if (aio_buf)
			cbp->aio_buf = aio_buf;
		else ERR_NULL(cbp->aio_buf = malloc(nbytes));

		cbp->aio_nbytes = nbytes;

		if (notification)
			cbp->aio_sigevent = *notification;
		else
			cbp->aio_sigevent.sigev_notify = SIGEV_NONE;

		RETURN_OKAY;
	}

void suspend(struct aiocb* cbp) {
	DBGonly("cbp:%p\n",
			(void*) cbp
	       );

	//struct aiocb* cbpContainer[1]; // wtf was this shit lmfao
	//cbpContainer[0] = cbp;

	// todo: replace with myRetry lul
	for (int ret = -1; ret;) {
		// error check except EINTR:
		ERR_NEG1_(ret = aio_suspend((const struct aiocb* const*) &cbp, 1, NULL) , EINTR);
	}

	ERR_NON_ZERO(aio_error(cbp));
	ERR_NEG1(aio_return(cbp));
}

// shouldRead macros
#define WRITE false
#define READ true

MIGHT_ERR() MY_NON_NULL(5)
	parallelIO(struct aiocb* aioArr, int fildes, off_t offset, size_t blockSize, void* buf,
			struct sigevent* notification, int parrLevel, bool shouldRead) {
		/*
		 * does an IO operation (either read or write) in parallel, doing parrLevel calls
		 * with freshly initialized (or allocated+init, if not provided) aiocbs
		 * if no notification method is provided, it also suspends until they're all done
		 */

		DBGonly("aioArr:%p fildes:%d offset:%ld blockSize:%zd buf:%p notification:%p parrLevel:%d shouldRead:%d\n",
				(void*) aioArr,
				fildes, offset, blockSize, (void*) buf,
				(void*) notification,
				parrLevel, shouldRead
		       );

		bool arrNotPassed = false;
		if (!aioArr) {
			if (notification) {
				RETURN_FAIL(LBLUE"notification" RESET_ESC" (" DBLUE"arg 6" RESET_ESC") passed but "
						LBLUE"aioArr" RESET_ESC" (" DBLUE"arg 1" RESET_ESC") is "
						LRED_BLD"NULL" RESET_ESC);
			}

			ERR_NULL(aioArr = malloc(parrLevel * sizeof(struct aiocb)));
			arrNotPassed = true;
		}

		NON_ATTR_IF (!buf) {
			RETURN_FAIL(LBLUE"buf" RESET_ESC" (" DBLUE"arg 5" RESET_ESC") is "
					LRED_BLD"NULL" RESET_ESC"\n");
		}

		/* here buf's length is assumed to be >= blockSize * parrLevel, anything else is undefined behaviour */
		for (int i = 0; i < parrLevel; ++i) {
			off_t bufferOffset = i * blockSize * sizeof(char);
#if RETURN_ERR
			// pretty lazy lmao
			ERR_NEG1(init_aiocb(&aioArr[i], fildes, offset + bufferOffset, blockSize, ((int8_t*) buf) + bufferOffset,
						notification));
#else // RETURN_ERR
			init_aiocb(&aioArr[i], fildes, offset + bufferOffset, blockSize, ((int8_t*) buf) + bufferOffset,
					notification);
#endif // RETURN_ERR
		}

		if (shouldRead)
			for (int i = 0; i < parrLevel; ++i)
				aio_read(&aioArr[i]);
		else
			for (int i = 0; i < parrLevel; ++i)
				aio_write(&aioArr[i]);

		if (!notification)
			for (int i = 0; i < parrLevel; ++i)
				suspend(&aioArr[i]);

		if (arrNotPassed)
			FREE(aioArr);

		RETURN_OKAY;
	}

// the entire section below this is kinda buggy
// I sometimes get an infinite loop due to EAGAIN, sometimes not. idk.
#if TEMP_REMOVE
#define LINKS_DEPRECATED_MSG "I've gotten some bugs using the Link functions to read, especially with MKFIFO mode, otherwise they kiiinda work?"

// represents descriptors of either pipe/fifo for use with moi Link functions
MY_DEPRECATE(LINKS_DEPRECATED_MSG)
	typedef struct _Link {
		// descriptors:
		int AtoB[2];
		int BtoA[2];

		// if initLink allocates memory for this struct, then the header
		// should be responsible for releasing it at the right time too
		bool freeOnClose;

		// closeLink will remove fifo if this flag is true
		bool removeOnClose;

		// paths, should only be used by removeOnClose
		const char* AtoBfifo;
		const char* BtoAfifo;
	} Link;

#define JUSTINIT 0
#define PIPE 1
#define FIFO 2
#define MKFIFO 3

#define ALLOC true
#define NOALLOC false

#define REMOVE true
#define NOREMOVE false

#define LINK_WR 1
#define LINK_RD 0

// TODO: make this void and add switch for RETURN_ERR
MY_DEPRECATE(LINKS_DEPRECATED_MSG)
	void* initLink(Link* link, int initType, bool shouldAlloc,
			// ignored if initType isn't JUSTINIT:
			int AtoB_READ, int AtoB_WRITE, int BtoA_READ, int BtoA_WRITE,

			// ignored if initType isn't MKFIFO/FIFO:
			const char* AtoBfifo, const char* BtoAfifo, mode_t fifoMode, bool removeOnClose) {
		if (NULL == link && !shouldAlloc) {
			errno = MY_ERRNO;
			// TODO: make this error cool too
			ERR("pepega no link but no want malloc");
		}

		if ( (FIFO == initType || MKFIFO == initType)
				&& (NULL == AtoBfifo || NULL == BtoAfifo) ) {
			errno = MY_ERRNO;
			// TODO: make this error cool too
			ERR("fifo with no fifo? lul");
		}

		if (shouldAlloc)
			ERR_NULL(link = calloc(1, sizeof(Link)));
		link->freeOnClose = true;

		switch (initType) {
			case MKFIFO:
				{
					// error check except EEXIST:
					ERR_NEG1_(mkfifo(AtoBfifo, fifoMode) , EEXIST);
					ERR_NEG1_(mkfifo(BtoAfifo, fifoMode) , EEXIST);

					goto fifo; // or else Wimplicit-fallthrough :(
				}
			case FIFO:
fifo:
				{
					// first check if these files are fifos lol
					struct stat statBuf;

					ERR_NEG1(stat(AtoBfifo, &statBuf));
					if (!S_ISFIFO(statBuf.st_mode)) {
						errno = MY_ERRNO;
						ERR("bruh AtoB not a fifo");
					}

					ERR_NEG1(stat(BtoAfifo, &statBuf));
					if (!S_ISFIFO(statBuf.st_mode)) {
						errno = MY_ERRNO;
						ERR("bruh BtoA not a fifo");
					}

					link->AtoBfifo = AtoBfifo;
					link->BtoAfifo = BtoAfifo;

					link->removeOnClose = removeOnClose;

					// nonblock b/c we're setting everything up at once:
					// pretty sure this is the source of the bugs tho :(
					ERR_NEG1(link->AtoB[LINK_RD] = open(AtoBfifo, O_RDONLY | O_NONBLOCK));
					ERR_NEG1(link->AtoB[LINK_WR] = open(AtoBfifo, O_WRONLY | O_NONBLOCK));

					ERR_NEG1(link->BtoA[LINK_RD] = open(BtoAfifo, O_RDONLY | O_NONBLOCK));
					ERR_NEG1(link->BtoA[LINK_WR] = open(BtoAfifo, O_WRONLY | O_NONBLOCK));

					break;
				}
			case PIPE:
				{
					ERR_NEG1(pipe(link->AtoB));
					ERR_NEG1(pipe(link->BtoA));

					break;
				}
			case JUSTINIT:
				{
					link->AtoB[LINK_WR] = AtoB_WRITE;
					link->AtoB[LINK_RD] = AtoB_READ;

					link->BtoA[LINK_WR] = BtoA_WRITE;
					link->BtoA[LINK_RD] = BtoA_READ;

					break;
				}
			default:
				{
					errno = MY_ERRNO;
					// TODO: make error look cool lol
					ERR("pepeg initType");
				}
		}

		// mainly for if shouldAlloc
		return link;
	}

#define A true
#define B false

// TODO: add switch for RETURN_ERR
MIGHT_ERR() MY_NON_NULL(1)
	closeUseless(Link* link, bool fromA) {
		NON_ATTR_IF (NULL == link) {
			RETURN_FAIL("pepega no link");
		}

		if (fromA) {
			ERR_NEG1(close(link->AtoB[LINK_RD]));
			ERR_NEG1(close(link->BtoA[LINK_WR]));
		} else {
			ERR_NEG1(close(link->BtoA[LINK_RD]));
			ERR_NEG1(close(link->AtoB[LINK_WR]));
		}
	}

// TODO: add switch for RETURN_ERR
MIGHT_ERR() MY_NON_NULL(1)
	closeLink(Link* link, bool fromA) {
		/*
		 * this assumes closeUseless was called at some point earlier,
		 * otherwise some descriptors will remain open
		 */

		NON_ATTR_IF (NULL == link) {
			RETURN_FAIL("pepega no link");
		}

		if (fromA) {
			ERR_NEG1(close(link->BtoA[LINK_RD]));
			ERR_NEG1(close(link->AtoB[LINK_WR]));
		} else {
			ERR_NEG1(close(link->AtoB[LINK_RD]));
			ERR_NEG1(close(link->BtoA[LINK_WR]));
		}

		// this is also hilariously dumb btw lmao, 1 closeLink from each side would double-delete?
		if (link->removeOnClose) {
			ERR_NEG1(remove(link->AtoBfifo));
			ERR_NEG1(remove(link->BtoAfifo));
		}

		if (link->freeOnClose)
			FREE(link);

		RETURN_OKAY;
	}

MIGHT_ERR() MY_NON_NULL(1) MY_DEPRECATE(LINKS_DEPRECATED_MSG)
	linkIO(Link* link, void* buffer, size_t nbyte, bool fromA, bool shouldWrite) {

		NON_ATTR_IF (NULL == link) {
			RETURN_FAIL("pepega no link");
		}

		errno = 0; // ? holy shit what was I even doing
		if (fromA) {
			if (shouldWrite)
				ERR_NEG1(write(link->AtoB[LINK_WR], buffer, nbyte));
			else while(true) {
				ERR_NEG1_(read(link->BtoA[LINK_RD], buffer, nbyte) , EAGAIN);
				if (errno != EAGAIN) break;
			}

		} else {

			if (shouldWrite)
				ERR_NEG1(write(link->BtoA[LINK_WR], buffer, nbyte));
			else while(true) {
				ERR_NEG1_(read(link->AtoB[LINK_RD], buffer, nbyte) , EAGAIN); 
				if (errno != EAGAIN) break;
			}
		}

		RETURN_OKAY;
	}

#endif // TEMP_REMOVE

typedef struct MyNode_ {
	LIST_TYPE val;
	struct MyNode_ *next;
} MyNode;

typedef struct MyList_ {
	MyNode *head,
	       *tail; // okay so let's get real
	// the only real reason to have a tail pointer in a singly
	// linked list is to have fast operations for the ends, but I
	// never used this lol, probably TODO: remove this lol
} MyList;

MyNode* MY_WARN_UNUSED
newMyNode (LIST_TYPE val) {
	MyNode *newMyNode;
	ERR_NULL( newMyNode = malloc(sizeof(MyNode)) );

	newMyNode->val = (LIST_TYPE) val;
	newMyNode->next = NULL;
	return newMyNode;
}

MyList* MY_WARN_UNUSED
newMyList (void) {
	MyList* list;

	// calloc to correctly set NULL pointers
	ERR_NULL( list = calloc(1, sizeof(MyList)) );
	return list;
}

MIGHT_ERR() MY_NON_NULL(1, 2) MY_FORMAT(printf, 2, 0)
	printMyList(const MyList* const list, const char* restrict format) {
		NON_ATTR_IF(!list) {
			RETURN_FAIL("bruh where's the list");
		}

		DBGonly("list:%p format:%s\n[H:%p T:%p] ",
				(void*) list, format,
				(void*) list->head, (void*) list->tail
		       );

		for (MyNode* node = list->head; node; node = node->next) {
			printf_(format, node->val);
		}

		printf_("\n");

		RETURN_OKAY;
	}

size_t MY_NON_NULL(1) MY_WARN_UNUSED
myListLength(const MyList* const list) {
	size_t length = 0;
	for (MyNode* node = list->head; node; node = node->next) {
		++length;
	}

	return length;
}

MyNode* MY_WARN_UNUSED MY_NON_NULL(1)
	popAt(MyList* const list, size_t pos) {
		MyNode *prev = NULL, *node = list->head;

		// is this redundant btw? TODO: remove and check lol
		if (!list->head) {
			return NULL; // Can't delete from empty list
		}

		for (size_t i = 0; i < pos; ++i) {
			if (node) {
				prev = node;
				node = node->next;
			} else {
				return NULL; // Can't delete outside of list
			}
		}

		// idk there's a few SIGSEGVs without this lol
		// it's getting pretty messy now, I should rewrite this whole function tbh
		if (!node) {
			return NULL;
		}

		// If there's a previous node relink, otherwise we're deleting the head node, so update that
		prev ?
			(prev->next = node->next) :
			(list->head = node->next);

		// If we're deleting the tail node, update that
		if (!node->next) {
			list->tail = prev;
		}

		// clean up and return
		node->next = NULL;
		return node;
	}

MyNode* MY_WARN_UNUSED MY_NON_NULL(1)
	peekNodeAt(const MyList* const list, size_t pos) {
		MyNode* node = list->head;

		if (!list->head) {
			return NULL; // peek empty list
		}

		for (size_t i = 0; i < pos; ++i) {
			if (node) {
				node = node->next;
			} else {
				return NULL; // peek outside list
			}
		}

		return node;
	}

LIST_TYPE MY_WARN_UNUSED MY_NON_NULL(1)
	peekValAt(const MyList* const list, size_t pos) {
		MyNode* node;

		// TODO: make this fancy or something lol
		if (NULL == (node = peekNodeAt(list, pos)) ) {
			errno = MY_ERRNO;
			ERR("Can't peek value outside list");
		}

		return node->val;
	}

LIST_TYPE MY_WARN_UNUSED MY_NON_NULL(1)
	popValAt(MyList* const list, size_t pos) {
		MyNode* node;
		LIST_TYPE val;

		if (NULL == (node = popAt(list, pos)) ) {
			errno = MY_ERRNO;
			ERR("Can't pop value outside list"); // ?
		}

		val = node->val;
		FREE(node); // we do a little leakn't

		return val;
	}

LIST_TYPE MY_WARN_UNUSED MY_NON_NULL(1)
	peekFirstVal(const MyList* const list) {
		return peekValAt(list, 0);
	}

LIST_TYPE MY_WARN_UNUSED MY_NON_NULL(1)
	peekLastVal(const MyList* const list) {
		size_t sz = myListLength(list);
		return peekValAt(list, sz - 1);
	}

LIST_TYPE MY_WARN_UNUSED MY_NON_NULL(1)
	popFirstVal(MyList* const list) {
		return popValAt(list, 0);
	}

LIST_TYPE MY_WARN_UNUSED MY_NON_NULL(1)
	popLastVal(MyList* const list) {
		size_t sz = myListLength(list);
		return popValAt(list, sz - 1);
	}

MyNode* MY_WARN_UNUSED MY_NON_NULL(1)
	popLast(MyList* const list) {
		size_t sz = myListLength(list);
		return popAt(list, sz - 1);
	}

MyNode* MY_WARN_UNUSED MY_NON_NULL(1)
	popFirst(MyList* const list) {
		return popAt(list, 0);
	}

MyList* MY_NON_NULL(1)
	clearMyList(MyList* const list) {
		for (MyNode* first; (first = popFirst(list));) {
			FREE(first);
		}

		return list;
	}

void MY_NON_NULL(1)
	deleteMyList (MyList* list) {
		clearMyList(list);
		FREE(list);
	}

MyList* MY_NON_NULL(1)
	deleteAt(MyList* const list, size_t pos) {
		MyNode* node = popAt(list, pos);
		FREE(node);
		return list;
	}

MyList* MY_NON_NULL(1)
	deleteLast(MyList* const list) {
		MyNode* node = popLast(list);
		FREE(node);
		return list;
	}

MyList* MY_NON_NULL(1)
	deleteFirst(MyList* const list) {
		MyNode* node = popAt(list, 0);
		FREE(node);
		return list;
	}

MyList* MY_NON_NULL(1, 3)
	insertAfter(MyList* const list, size_t pos, MyNode* const newMyNode) {
		MyNode *node = list->head;

		for (size_t i = 0; i < pos; ++i) { // Find the node we're inserting after
			if (node && node->next) { // Keep moving if this is a node and there's a next one
				node = node->next;
			} else {
				break; // will by default insert after the last one
			}
		}

		node == list->tail ? (list->tail = newMyNode) : (newMyNode->next = node->next);

		// Be careful in case we insertAfter in an empty list
		!node ? (list->head = newMyNode) : (node->next = newMyNode);
		return list;
	}

MyList* MY_NON_NULL(1, 3)
	insertBefore(MyList* const list, size_t pos, MyNode* const newMyNode) {
		MyNode *prev = NULL, *node = list->head;

		for (size_t i = 0; i < pos; ++i) { // Find the node we're inserting before
			if (node && node->next) {
				prev = node;
				node = node->next;
			} else {
				break; // will by default insert before the last one
			}
		}

		node == list->head ? (list->head = newMyNode) : (prev->next = newMyNode);

		// Be careful in case we insertBefore in an empty list
		!node ? (list->tail = newMyNode) : (newMyNode->next = node);
		return list;
	}

MyList* MY_NON_NULL(1)
	insertValAfter(MyList* const list, size_t pos, LIST_TYPE newVal) {
		// NB: returns list after allocation then insertion
		return insertAfter(list, pos, newMyNode(newVal));
	}

MyList* MY_NON_NULL(1)
	insertValBefore(MyList* const list, size_t pos, LIST_TYPE newVal) {
		return insertBefore(list, pos, newMyNode(newVal));
	}

MyList* MY_NON_NULL(1, 2)
	insertLast(MyList* const list, MyNode* const node) {
		size_t sz = myListLength(list);
		insertAfter(list, sz - 1, node);
		return list;
	}

MyList* MY_NON_NULL(1, 2)
	insertFirst(MyList* const list, MyNode* const node) {
		insertBefore(list, 0, node);
		return list;
	}
MyList* MY_NON_NULL(1)
	insertValLast(MyList* const list, LIST_TYPE newVal) {
		return insertLast(list, newMyNode(newVal));
	}

MyList* MY_NON_NULL(1)
	insertValFirst(MyList* const list, LIST_TYPE newVal) {
		return insertFirst(list, newMyNode(newVal));
	}

// socket stuff will start going below this point

MIGHT_ERR() MY_NON_NULL(1)
	init_sockaddr_in(struct sockaddr_in* addr,
			sa_family_t family, in_port_t port, uint32_t s_addr) {
		NON_ATTR_IF(!addr) {
			RETURN_FAIL("null sockaddr_in struct? bruhhh");
		}

		memset((void*) addr, 0, sizeof(struct sockaddr_in));

		addr->sin_family = family;
		addr->sin_port = port;
		addr->sin_addr.s_addr = s_addr;

		RETURN_OKAY;
	}

struct sockaddr_in MY_WARN_UNUSED
make_sockaddr_in(sa_family_t family, in_port_t port, uint32_t s_addr) {
	struct sockaddr_in addr;
	MIGHT_FAIL_NEG1(init_sockaddr_in(&addr, family, port, s_addr));

	return addr;
}

// should be might_err return type
in_addr_t MY_NON_NULL(1)
	inet_addr_(const char* cp) {
		NON_ATTR_IF(!addr) {
			RETURN_FAIL("null string? bruhhh");
		}

		in_addr_t addr;
		// should be a different macro
		ERR_IN_ADDR_T(addr = inet_addr(cp));
		return addr;
	}

void sethandler(void (*signalHandler) (int), int sigNo) {
	struct sigaction action = {0};
	action.sa_handler = signalHandler;
	ERR_NEG1( sigaction(sigNo, &action, NULL) ); // TODO: change this
}

sigset_t MY_WARN_UNUSED
make_sigset_t_(int signo) {
	sigset_t sigset;
	ERR_NEG1(sigemptyset(&sigset));

	// to allow returning emptyset if signo == 0
	if (signo) {
		sigaddset_(&sigset, signo);
	}

	return sigset;
}
// bigbrane """vararg""" lul
#define make_sigset_t_0_ARGS() make_sigset_t_(0)
#define make_sigset_t_1_ARG(signo) make_sigset_t_(signo)
#define make_sigset_t_X_ARGS(x, A, FUNC, ...) FUNC
#define make_sigset_t(...) make_sigset_t_X_ARGS(, ##__VA_ARGS__,\
		make_sigset_t_1_ARG(__VA_ARGS__),\
		make_sigset_t_0_ARGS(__VA_ARGS__))

#define sigset_make(...) make_sigset_t(__VA_ARGS__)
// gonna start adding ^these b/c the POSIX ones look like this
// will keep the old format too tho b/c I have some old programs with them :(
// we do sum backwards compatibility ig

pthread_mutex_t MY_WARN_UNUSED
make_pthread_mutex_t_(const pthread_mutexattr_t* attr) {
	pthread_mutex_t mutex;
	pthread_mutex_init_(&mutex, attr);
	return mutex;
}
#define make_pthread_mutex_t_0_ARGS() make_pthread_mutex_t_(NULL)
#define make_pthread_mutex_t_1_ARG(attr) make_pthread_mutex_t_(attr)
#define make_pthread_mutex_t_X_ARGS(x, A, FUNC, ...) FUNC
#define make_pthread_mutex_t(...) make_pthread_mutex_t_X_ARGS(, ##__VA_ARGS__,\
		make_pthread_mutex_t_1_ARG(__VA_ARGS__),\
		make_pthread_mutex_t_0_ARGS(__VA_ARGS__))
#define pthread_mutex_make(...) make_pthread_mutex_t(__VA_ARGS__)

pthread_attr_t MY_WARN_UNUSED
make_pthread_attr_t(void) {
	pthread_attr_t attr;
	pthread_attr_init_(&attr);
	return attr;
}
#define pthread_attr_make() make_pthread_attr_t()

pthread_cond_t MY_WARN_UNUSED
make_pthread_cond_t_(const pthread_condattr_t* attr) {
	pthread_cond_t cond;
	pthread_cond_init_(&cond, attr);
	return cond;
}
#define make_pthread_cond_t_0_ARGS() make_pthread_cond_t_(NULL)
#define make_pthread_cond_t_1_ARG(attr) make_pthread_cond_t_(attr)
#define make_pthread_cond_t_X_ARGS(x, A, FUNC, ...) FUNC
#define make_pthread_cond_t(...) make_pthread_cond_t_X_ARGS(, ##__VA_ARGS__,\
		make_pthread_cond_t_1_ARG(__VA_ARGS__),\
		make_pthread_cond_t_0_ARGS(__VA_ARGS__))
#define pthread_cond_make(...) make_pthread_cond_t(__VA_ARGS__)

pthread_barrier_t MY_WARN_UNUSED
make_pthread_barrier_t_(const pthread_barrierattr_t* attr, unsigned count) {
	pthread_barrier_t barrier;
	pthread_barrier_init_(&barrier, attr, count);
	return barrier;
}
#define make_pthread_barrier_t_0_ARGS() make_pthread_barrier_t_(NULL, 2)
#define make_pthread_barrier_t_1_ARG(count) make_pthread_barrier_t_(NULL, count)
#define make_pthread_barrier_t_2_ARGS(attr, count) make_pthread_barrier_t_(attr, count)
#define make_pthread_barrier_t_X_ARGS(x, A, B, FUNC, ...) FUNC
#define make_pthread_barrier_t(...) make_pthread_barrier_t_X_ARGS(, ##__VA_ARGS__,\
	make_pthread_barrier_t_2_ARGS(__VA_ARGS__),\
	make_pthread_barrier_t_1_ARG(__VA_ARGS__),\
	make_pthread_barrier_t_0_ARGS(__VA_ARGS__))
#define pthread_barrier_make(...) make_pthread_barrier_t(__VA_ARGS__)

sem_t MY_WARN_UNUSED
make_sem_t_(int pshared, unsigned value) {
	sem_t sem;
	sem_init_(&sem, pshared, value);
	return sem;
}
#define make_sem_t_0_ARGS() make_sem_t_(0, 1) /* binary sem by default ig lol */
#define make_sem_t_1_ARG(count) make_sem_t_(0, count)
#define make_sem_t_2_ARGS(pshared, count) make_sem_t_(pshared, count)
#define make_sem_t_X_ARGS(x, A, B, FUNC, ...) FUNC
#define make_sem_t(...) make_sem_t_X_ARGS(, ##__VA_ARGS__,\
	make_sem_t_2_ARGS(__VA_ARGS__),\
	make_sem_t_1_ARG(__VA_ARGS__),\
	make_sem_t_0_ARGS(__VA_ARGS__))
#define sem_make(...) make_sem_t(__VA_ARGS__)

#endif // HEADER_OKAY
#undef HEADER_OKAY

#undef DEBUG_MODE
#undef RETURN_ERR
//#undef MY_ERRNO
//#undef MY_ERR_CODE
#endif // KATWIK_HEADER
