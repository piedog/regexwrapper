# regexwrapper

C++ class to parse text strings using regular expressions.
Motivation: provide a simple C++ class to handle regular expressions on unix and linux systems.
Objectives:
    1. determine if a text string matches the regular expression pattern
    2. if parentheses are used for grouping, provide the ability to retrieve each group
    3. limit dependencies to the POSIX regex library

Usage:

    Constructors:

        GDDRegex()
            The regular expression must be passed using Compile member functions

        GDDRegex(const string &expression)
            expression - the regular expression used to parse the text string (see Exec member function)
            When this constructor is used, there is no need to call the Compile member function.

    Member functions:

        int Compile(const string &expression)       
            expression - the regular expression used to parse the text string (see Exec member function)
            This member function must be called when the empty constructor is used.
            Returns int type:  0=failure, 1=successful compile of regex

        int Exec(const string &text)
            text - the text string that is to be parsed
            Returns int type: 0=no match, 1=match

        int NextGroup(int &startOffset, int &length)
            Returns the offset from the beginning offset and the length of the group in text.
            startOffset - offset (from zero) where current character group begins
            length - size of character group
            Returns int type: 0=no more groups found in string, 1=next group has been found

    

Example:
    
    #include <iostream>
    #include <fstream>
    #include <string>
    #include "gdd_regex.h"

    using namespace std;

    const string expression("^\\s*(\\d+)\\s+(\\d{4}-\\d{2}-\\d{2})");
    const string text("2 2016-04-22");

    int main(int argc, char** argv)
    {
        cout << "Regex Read Test" << endl;
        GDDRegex rgx(expression);
    
        int status = rgx.Exec(text);
        if (status) {
            cout << "regex match    : " << status << endl;
        }
        else {
            cout << "regex no match : " << status << endl;
        }
        int startOffset, length;
        while ( (status=rgx.NextGroup(startOffset, length)) ) {
            cout <<"[" << text.substr(startOffset, length) << "]" << endl;
        }
        cout << "End of Regex Test" << endl;
        return 0;
    }


See https://en.wikipedia.org/wiki/Regular_expression#POSIX
Also see: http://stackoverflow.com/questions/37956719/when-using-regex-in-c-d-does-not-work-but-0-9-does
Other libraries: http://www.pcre.org/

