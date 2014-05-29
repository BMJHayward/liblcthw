#ifndef string_algos_h
#define string_algos_h
#include "bstrlib.h"
#include "darray.h"
//will use boyer moore horspool algorithm with skip_char list. useful for finding sub-string in string
typedef struct StringScanner {
    bstring in;
    const unsigned char *haystack;
    ssize_t hlen;
    const unsigned char *needle;
    ssize_t nlen;
    size_t skip_chars[UCHAR_MAX + 1];
} StringScanner;
//will have 2 versions of BMH alg: string_find and stringscanner_scan
int String_find(bstring in, bstring what);//will find 1st instance of one string in another, does entire alg in one shot

StringScanner *StringScanner_create(bstring in);

int StringScanner_scan(StringScanner *scan, bstring tofind);//uses struct to separate skip list fn from search fn. can scan for all instances of substring in parent string

void StringScanner_destroy(StringScanner *scan);

#endif