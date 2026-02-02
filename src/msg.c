#include "stdarg.h"
#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "string.h"

#include "../cutils.h"

int DEBUG = 0;
char* DEBUG_FN = NULL;
char* DEBUG_FILE = NULL;

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

int msg(enum level msgLevel, const char* message,...) {
    va_list args;
    //initialize va_list args
    if (message == NULL) message = "(null)";
    va_start(args, message);
    int tmp = vsnprintf(NULL, 0, message, args);
    va_end(args);
    size_t size = tmp < 0 ? 0 : (size_t)tmp;

    char* strDest = malloc(size + 2);
    if (!strDest) return -1;

    va_start(args, message);
    int wrote = vsnprintf(strDest, size + 1, message, args);
    va_end(args);
    if (wrote < 0) strDest[0] = '\0';


    switch (msgLevel)
    {
        case INFO:
            fprintf(stderr, "%sINFO: %s%s%s%s\n",BOLDBLUE,RESET,BLUE,strDest,RESET);
            break;
        case WARNING:
            fprintf(stderr, "%sWARNING: %s%s%s%s\n",BOLDYELLOW,RESET,YELLOW,strDest,RESET);
            break;
        case ERROR:
            fprintf(stderr, "%sERROR: %s%s%s%s\n",BOLDMAGENTA,RESET,MAGENTA,strDest,RESET);
            break;
        case FATAL:
            fprintf(stderr, "%sFATAL: %s%s%s%s\n",BOLDRED,RESET,RED,strDest,RESET);
            exit(1);
        default:
            fprintf(stderr, "UNKNOWN: %s\n",strDest);
            break;
    }
    

    free(strDest);
    return 0;
}

// the debug function is bad
int f_dbg__(int level,int line,const char* function,const char* file,const char* message,...) {

    const char* short_file = NULL;
    if (file) {
        char* p = strrchr(file, '/');
        if (p) short_file = p + 1;
        else short_file = file;
    }
    /* WARNING : EXPERIMENTAL */
    if (DEBUG_FN != NULL) {
        if (function == NULL || strcmp(DEBUG_FN,function) != 0) {
            return 1;
        }
    }

    if (DEBUG_FILE != NULL) {
        if (short_file == NULL || strcmp(DEBUG_FILE, short_file) != 0) {
            return 1;
        }
    }

    if (message == NULL) message = "(null)";
    va_list args;
    va_start(args, message);
    int tmp = vsnprintf(NULL, 0, message, args);
    va_end(args);
    size_t size = tmp < 0 ? 0 : (size_t)tmp;

    char* strDest = malloc(size + 2);
    if (!strDest) return -1;

    va_start(args, message);
    int wrote = vsnprintf(strDest, size + 1, message, args);
    va_end(args);
    if (wrote < 0) strDest[0] = '\0';

    if (DEBUG >= level)
    {
        const char* file_to_print = short_file ? short_file : "<unknown>";
        // Write pieces individually to avoid printf-family internals
        if (BOLDCYAN) write(STDERR_FILENO, BOLDCYAN, strlen(BOLDCYAN));
        write(STDERR_FILENO, "[", 1);
        if (file_to_print) write(STDERR_FILENO, file_to_print, strlen(file_to_print));
        write(STDERR_FILENO, ":", 1);
        // convert line number to decimal without printf
        char numbuf[32];
        int nlen = 0;
        int v = line;
        if (v == 0) {
            numbuf[nlen++] = '0';
        } else {
            int neg = 0;
            if (v < 0) { neg = 1; v = -v; }
            char rev[32]; int r = 0;
            while (v > 0 && r < (int)sizeof(rev)) { rev[r++] = '0' + (v % 10); v /= 10; }
            if (neg) numbuf[nlen++] = '-';
            while (r > 0) numbuf[nlen++] = rev[--r];
        }
        numbuf[nlen++] = ']';
        numbuf[nlen++] = ' ';
        if (nlen > 0) write(STDERR_FILENO, numbuf, nlen);
        if (RESET) write(STDERR_FILENO, RESET, strlen(RESET));
        write(STDERR_FILENO, " ", 1);
        if (strDest) write(STDERR_FILENO, strDest, strlen(strDest));
        write(STDERR_FILENO, "\n", 1);
    }
    free(strDest);
    return 0;
}