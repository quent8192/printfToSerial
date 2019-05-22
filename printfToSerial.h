/*
Library to make printf available in Arduino.
*/

#include <stdio.h> // for printf
#include <stdint.h> // for uint64_t


///
/// @brief The ulltoa function converts an uint64_t to a string. Will always write a '\0'-terminated string
/// in buffer. Will write "too big" (eventually truncated) in buffer if buffer is to small to hold the
/// representation of ll.
/// @param ll the uint64_t to convert
/// @param buffer a char array where the string will be written
/// @param bufsize size of buffer
/// @param radix to use for the string representation
///
char * ulltoa(uint64_t ll, char *buffer, const size_t bufsize, const unsigned int radix=10);
