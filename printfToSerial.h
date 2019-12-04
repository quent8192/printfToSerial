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
        /// @brief Removes chars from circular buffer, and puts them into *to
        /// @param to : destination where to put the taken chars
        /// @param maxSize : maximum number of chars to take
        /// @return actual number of chars taken
        int take(char* to, int maxSize){
            int count = 0;
            while (oldestI != nextI && count < maxSize ) {
                to[count] = buffer[oldestI];
                oldestI = (oldestI + 1)%BUF_SIZE ;
                count++;
            }
            return count;
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
            va_list vargs;
            va_start(vargs, format);
            int ret = this->vprintf(format, vargs);
            va_end(vargs);
            return ret;
        }

        /// @brief Prints a formatted string into the buffer.
        int vprintf(const char *format, va_list ap){
            int maxSize = availableSize();
            char buffer2[maxSize];
            vsnprintf(buffer2, maxSize, format, ap);
            return enqueueString(buffer2);
        }

        /// @brief Prints a formatted string into the buffer, pre-pended with an integer (example : timestamp). Pre-pending can be disabled by enableTSPrint(bool)
        int printf(uint32_t ts, const char *format, ...){
            int ret = 0;
            if ( TSPrintEnabled ) printf("%" PRIu32 " ", ts);
            va_list vargs;
            va_start(vargs, format);
            ret += this->vprintf(format, vargs);
            va_end(vargs);
            return ret;
        }

        /// @brief Returns the available size in the circular bufffer.
        int availableSize(){
            return BUF_SIZE - ((nextI + BUF_SIZE - oldestI) % BUF_SIZE);
        }

        /// @brief Returns the number of characters to send
        int charactersToSend(){
            return (nextI + BUF_SIZE - oldestI) % BUF_SIZE;
        }

        /// @brief discards everything in the circular buffer
        void clear(){
            oldestI = 0;
            nextI = 0;
            buffer[0] = '\0';
        }

        /// @brief Returns the available size in the circular bufffer.
        int availableChars(){
            return ((nextI + BUF_SIZE - oldestI) % BUF_SIZE);
        }

        /// @brief Returns the available size in the circular bufffer.
        void enableTSPrint(bool enable) {
            TSPrintEnabled = enable;
        }

    private :
        int oldestI = 0;        // oldest index (next to be written on the serial port)
        int nextI = 0;          // next position to write to.
        char buffer[BUF_SIZE];  // the buffer.
        bool TSPrintEnabled = false; // disables timestamp printing in "int printf(uint32_t, const char *, ...)"


};

