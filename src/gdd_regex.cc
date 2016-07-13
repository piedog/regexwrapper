#include "gdd_regex.h"
#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>



GDDRegex::GDDRegex()
{
 
    Groups = new regmatch_t[MaxGroups]();
    Expression = "";
    CurrentGroup = -1;
}


GDDRegex::GDDRegex(const string &_expression)
{
    Groups = new regmatch_t[MaxGroups]();
    Expression = _expression;
    CurrentGroup = -1;

    Compile(Expression);
}



GDDRegex::~GDDRegex()
{
    regfree(&Preg);
    delete []Groups;
}


GDDRegex::GDDRegex(const GDDRegex &old)
{
    Groups = new regmatch_t[MaxGroups]();
    Expression = old.Expression;
    CurrentGroup = old.CurrentGroup;

    Compile(Expression);
    
}



int GDDRegex::Compile(const string &_expression)
{
    if (_expression.length() == 0) {
        cerr << "TODO [error] [" << __FILE__ << "," << __LINE__ << "] zero string length" << endl;
        return 0;
    }

    string tmp = _expression;
    Shortcut2Posix(tmp);
    int status = regcomp(&Preg, tmp.c_str(), REG_EXTENDED | REG_NEWLINE);
    if (status != 0) {
        char errbuf[1026];
        size_t errstatus = regerror(status, &Preg, errbuf, sizeof(errbuf));
        cerr << "TODO [error] [" << __FILE__ << "," << __LINE__ << "] errstatus=" << errstatus << endl;
        cerr << "TODO [error] [" << __FILE__ << "," << __LINE__ << "] errbuf=" << errbuf << endl;
        return 0;
    }
    return 1;
}



int GDDRegex::Exec(const string &text)
{
    int flags = 0;
    int status = regexec(&Preg, text.c_str(), MaxGroups, Groups, flags);
    if (status != 0) {
        // non-zero is a no match or an error
        char errbuf[1026];
        cerr << "TODO [error] [" << __FILE__ << "," << __LINE__ << "] status=" << status << endl;
        size_t errstatus = regerror(status, &Preg, errbuf, sizeof(errbuf));
        cerr << "TODO [error] [" << __FILE__ << "," << __LINE__ << "] errstatus=" << errstatus << endl;
        cerr << "TODO [error] [" << __FILE__ << "," << __LINE__ << "] errbuf=" << errbuf << endl;
        return 0;
    }

    CurrentGroup = 0;
    return 1;
}
        
int GDDRegex::NextGroup(int &s_offs, int &lng)
{
    if (CurrentGroup == MaxGroups) return 0;
    if (Groups[CurrentGroup].rm_so < 0)  return 0;

    s_offs = Groups[CurrentGroup].rm_so;
    lng    = Groups[CurrentGroup].rm_eo - s_offs;
    CurrentGroup++;
    return 1;
}


void GDDRegex::Shortcut2Posix(string &text)
{   // convert digit shortcut and posix character classes because glibc does not define \d, \D
    // Note: untested with non-greedy symbol
    // see https://en.wikipedia.org/wiki/Regular_expression#POSIX

    const unsigned int N = 2;
    static const string singles[] = {
        "\\d", "\\D"
    };

    static const string Posix[] = {
        "[0-9]", "[^0-9]"
    };

    for (unsigned int i=0; i<N; i++) {
        while (text.find(singles[i]) != string::npos) {
            text.replace(text.find(singles[i]), singles[i].size(), Posix[i]);
        }
    }
}
