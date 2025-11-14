/* Basicio.cpp
 * Simple implementation of Basicio functions. This file centralizes all
 * I/O so the rest of the simulator can avoid using std::iostream or
 * printf directly.
 *
 * Note: This implementation uses C stdio as the low-level backend. All
 * simulator code must call only the functions declared in Basicio.h.
 */

#include "../include/Basicio.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>

extern "C" {

int basicio_read_int() {
    int x = 0;
    if (std::scanf("%d", &x) != 1) {
        // If reading fails, consume remainder and return 0
        int c;
        while ((c = std::getchar()) != EOF && c != '\n') {}
        return 0;
    }
    // consume trailing newline
    int c;
    while ((c = std::getchar()) != EOF && c != '\n') {}
    return x;
}

void basicio_read_line(char* buffer, int maxLen) {
    if (!buffer || maxLen <= 0) return;
    if (!std::fgets(buffer, maxLen, stdin)) {
        buffer[0] = '\0';
        return;
    }
    // strip newline
    size_t len = std::strlen(buffer);
    if (len > 0 && buffer[len-1] == '\n') buffer[len-1] = '\0';
}

void basicio_write(const char* s) {
    if (!s) return;
    std::fputs(s, stdout);
}

void basicio_writeln(const char* s) {
    if (!s) return;
    std::fputs(s, stdout);
    std::fputc('\n', stdout);
}

void basicio_write_int(int x) {
    std::printf("%d", x);
}

} // extern "C"
