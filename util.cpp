#include "util.h"
#include <cctype>

// returns true if all digits
bool isNumber(const char* s) {
    for (int i=0; s[i]; i++) {
        if (!isdigit(s[i])) return false;
    }
    return true;
}
