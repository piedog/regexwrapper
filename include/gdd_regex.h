#ifndef __GDD_REGEX_H_
#define __GDD_REGEX_H_

#include <string>
#include <sys/types.h>
#include <regex.h>

#ifdef __cplusplus

using namespace std;

class GDDRegex {

    public:
        GDDRegex();
        GDDRegex(const string &expression);
        ~GDDRegex();
        GDDRegex(const GDDRegex &old);
        
        int Compile(const string &expression);
        int Exec(const string &text);    // { 1: successful match | 0: no match }
        int NextGroup(int &startOffset, int &length);    // { 1: group returned | 0: no more groups }


    private:
        regex_t       Preg;
        static const  size_t        MaxGroups = 30;
        regmatch_t   *Groups;
        size_t        CurrentGroup;
        string        Expression;

        static void Shortcut2Posix(string &text);   // convert single char shortcut to posix regex

};
#endif  /**  __cplusplus            **/
#endif  /**  __GDD_REGEX_H_         **/
