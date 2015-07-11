#ifndef GLOBAL_H
#define GLOBAL_H

#include <string>

//Algo configs
#define EPSILON 0.00001 ///< user-defined tolerance for inequality comparisons
#define MAX_FSS 128 ///< max number of search queries
#define MAX_THREADS 128 ///< max number of concurrent threads
#define RESERVED_MEM_STATS 20000000 ///< size of the cache of all stats
#define RESERVED_MEM_CACHED_STATS 10000000 ///< size of the cache for stats of a combination size
//Input Configs
#define FILE_INPUT_DELIMITER "," ///< delimiter for input file
#define MAX_DOCS 100000000 ///< maximum number of documents
//Output Configs
#define APP_NAME "SensPrecOptimizer"
#define MAX_OUTPUT_ROWS 500000 ///< max number of rows in each output file
#define FILE_OUTPUT_STATS "SPO_Statistics" ///< prefix of the output file
#define FILE_OUTPUT_LOG "SPO_Log" ///< prefix of the log file
#define FILE_OUTPUT_EXTEN ".csv" ///< extension of the output statistics
#define FILE_OUTPUT_DELIMITER "," ///< delimiter for the output statistics
//Menus
#define ABOUT_PATH "About.html"
#define HELP_PATH "https://github.com/mesgarpour/sens-prec-optimizer"

static const std::string OUTPUT_TITLES[7] = ///< titles of the output statistics
{
    "#",
    "\"Search Queries\"",
    "Length",
    "\"Sensitivity (%)\"",
    "\"Precision (%)\""
};

//OS specfic configs
#ifdef __APPLE__  //the compiler in Mac
    #define PATH_SUB_CHAR "/" ///< path delimiter
    #define POSIX_LIB true
#elif _WIN32 //__MINGW32__ //MinGW compiler in windows
    #define PATH_SUB_CHAR "\\"
    #define POSIX_LIB false
#elif __GNUC__ //GCC compiler in Linux
    #define PATH_SUB_CHAR "/"
    #define POSIX_LIB true
#else
    #error "Unknown platform in the global header!"
#endif

#endif // GLOBAL_H

