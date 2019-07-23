/*
Library to make printf available in Arduino.
*/

#include <stdio.h> // for printf
#include <stdint.h> // for uint64_t
#include <stdarg.h> // for printf

///
/// @brief The ulltoa function converts an uint64_t to a string. Will always write a '\0'-terminated string
/// in buffer. Will write "too big" (eventually truncated) in buffer if buffer is to small to hold the
/// representation of ll.
/// @param ll the uint64_t to convert
/// @param buffer a char array where the string will be written
/// @param bufsize size of buffer
/// @param radix to use for the string representation
/// @return pointer to first char of buffer
///
char * ulltoa(uint64_t ll, char *buffer, const size_t bufsize, const unsigned int radix=10);

template <unsigned int BUF_SIZE>
class CircularBuffer {
    
    public :
        /// @brief To be called very frequently. Will write one char to Serial if there are data in the buffer.
        void engine(){
            if (oldestI != nextI) {
                Serial.print(buffer[oldestI]);
                if (buffer[oldestI] == '\n') {
                    Serial.flush();
                }
                oldestI = (oldestI + 1)%BUF_SIZE ;
            }
        }
        
        
        /// @brief Adds a string to the circular buffer, to be printed to the serial port. Will truncate the string if there is not enough space left in the buffer
        /// @param str address of a null-terminated string.
        int enqueueString(const char *str){
            int queued = 0;
            while (str[queued] != '\0' && nextI != ( (oldestI + BUF_SIZE - 1) % BUF_SIZE)  ){
                buffer[nextI] = str[queued];
                queued++;
                nextI = (nextI + 1) % BUF_SIZE;
            }
            return queued;
        }
        
        /// @brief Prints a formatted string into the buffer.
        int printf(const char *format, ...){
            char buffer2[BUF_SIZE];
            va_list vargs;
            va_start(vargs, format);
            vsnprintf(buffer2, BUF_SIZE, format, vargs);
            va_end(vargs);
            return enqueueString(buffer2);
        }
        
        /// @brief Returns the available size in the circular bufffer.
        int availableSize(){
            return BUF_SIZE - ((nextI + BUF_SIZE - oldestI) % BUF_SIZE);
        }
        
    private :
        int oldestI = 0;        // oldest index (next to be written on the serial port)
        int nextI = 0;          // next position to write to.
        char buffer[BUF_SIZE];  // the buffer.


};

