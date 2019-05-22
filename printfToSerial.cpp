/*
Library to make printf available in Arduino.
*/

#include <Arduino.h>

extern "C" {
    int _write(int file, const char * data, int length) {
        asm(".global _printf_float");
        return Serial.write(data, length);
    }
}

char * ulltoa(uint64_t ll, char *buffer, const size_t bufsize, const unsigned int radix){
    int pseudoLog = 1;  // this should be the number of characters required to print <ll> in base <radix>,
                        // so ceil(log(<ll>)/log(<radix>)) (or bufsize-1 if it is lower)
    uint64_t max = radix;
    uint64_t ofLimit = (0xFFFFFFFFFFFFFFFF)/radix;  // limit to detect edge case where number is
                                                    // printable, but detecting it with max < ll
                                                    // is impossible because max*radix would overflow
    // computing pseudoLog without using math.h
    while (max < ll && max <= ofLimit && pseudoLog < bufsize-2 ){
        max *= radix;
        pseudoLog++;
    }
    if (max != ll && ll <= ofLimit ) pseudoLog--; // edge cases to remove leading '0'

    // handle number too big to be printed in this buffer
    if (max < ll && max <= ofLimit && pseudoLog == (bufsize-2) ){
        strncpy(buffer, "too big", bufsize);
        buffer[bufsize-1] = '\0'; // ensure that buffer is \0-terminated, because strncpy does not
        return buffer;
    }


    // write end of string char
    buffer[pseudoLog+1] = '\0';
    //
    while (pseudoLog >= 0) {
        buffer[pseudoLog] = (ll%radix) + '0x30';
        ll /= radix;
        pseudoLog--;
    }
    return buffer;
}
