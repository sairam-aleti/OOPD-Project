/* Basicio.h
 * Minimal Basic I/O wrapper used by the simulator.
 * All project code must use the functions declared here for I/O.
 */
#ifndef BASICIO_H
#define BASICIO_H

extern "C" {
    /** Read an integer from stdin. Blocks until a valid integer is read. */
    int basicio_read_int();

    /** Read a line (up to maxLen-1 chars) into buffer. Null-terminates. */
    void basicio_read_line(char* buffer, int maxLen);

    /** Write a C-string to stdout (no newline). */
    void basicio_write(const char* s);

    /** Write a C-string to stdout followed by newline. */
    void basicio_writeln(const char* s);

    /** Write an integer to stdout. */
    void basicio_write_int(int x);
}

#endif // BASICIO_H
