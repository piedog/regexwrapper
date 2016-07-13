#include <iostream>
#include <fstream>
#include <string>
#include "gdd_regex.h"

using namespace std;
const string expression("^\\s*(\\d+)\\s+(\\d{4}-\\d{2}-\\d{2})\\s+(\\d{2}:\\d{2}:\\d{2})\\s+(\\w+)\\s+(\\w+)\\s+(\\d*)\\s*$");
const string text("2 2016-04-22 20:13:35 9188181111 VoiceMail 12");

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
