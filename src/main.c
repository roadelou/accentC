/********************************** METADATA **********************************/

/*
 * Contributors: roadelou
 * Contacts:
 * Creation Date: 2021-07-18
 * Language: C Source
 */

/********************************** INCLUDES **********************************/

// The library used to substitute the accents.
#include "accent.h"
//
// Used for fread and fprinf.
#include <stdio.h>
//
// Used for malloc and free.
#include <stdlib.h>

/********************************* SINGLETONS *********************************/

// TODO
// ====
// Use an array of struct to keep the patterns close to their words.
//
// Array used to hold all of the pattern to match for the various accents.
static const char *patterns[] = {
    "e1", "e2", "e3", "a1", "a3", "c4", "E1",
    "E2", "E3", "A1", "A3", "C4", "o3", "O3",
};
//
// Array used to hold the words that the patterns will be replaced with.
static const char *words[] = {
    "\xc3"
    "\xa8",
    "\xc3"
    "\xa9",
    "\xc3"
    "\xaa",
    "\xc3"
    "\xa0",
    "\xc3"
    "\xa2",
    "\xc3"
    "\xa7",
    "\xc3"
    "\x88",
    "\xc3"
    "\x89",
    "\xc3"
    "\x90",
    "\xc3"
    "\x80",
    "\xc3"
    "\x82",
    "\xc3"
    "\x87",
    "\xc3"
    "\xb4",
    "\xc3"
    "\x94",
};

/********************************* PROTOYPES **********************************/

// Utility function to consume all of stdin at once and return it as one
// heap-allocated string. Will allocate the string using the chunk size defined
// by `ACCENT_CHUNK_SIZE`.
static char *consume_stdin(void);

/************************************ MAIN ************************************/

int main(int argc, char **argv) {
    // We read stdin until the stream is closed.
    char *old_text = consume_stdin();
    //
    // Variable used to hold the replaced text during the iterations.
    char *new_text;
    //
    // Cursor used to iterate over the patterns.
    size_t cursor;
    //
    // The total number of patterns to go through, computed from the storage
    // size of the array of patterns.
    size_t pattern_count = sizeof(patterns) / sizeof(char *);
    //
    // We go over each pattern an replace them in the source string.
    for (cursor = 0; cursor < pattern_count; cursor++) {
        // We perform the ith replacement on the old text.
        new_text = replace(old_text, *(patterns + cursor), *(words + cursor));
        //
        // We free the old string.
        free(old_text);
        //
        // we exchange the pointers for the next iteration.
        old_text = new_text;
    }
    //
    // We print the final text.
    fprintf(stdout, "%s", old_text);
    //
    // We free the memory allocated by the program.
    free(old_text);
    //
    // If we reach this line, the execution was a success.
    return 0;
}

/********************************* FUNCTIONS **********************************/

// Implementation of our helper function.
static char *consume_stdin(void) {
    // The current allocated size of the returned string.
    size_t memory_size = ACCENT_CHUNK_SIZE * sizeof(char);
    //
    // The returned string.
    char *consumed_stdin = malloc(memory_size);
    //
    // The current used size of the returned string.
    size_t string_size = 0;
    //
    // The number of characters fetched from stdin during the last call to
    // fread.
    size_t next_characters;
    //
    // We try reading a chunk of the input and writing after what has already
    // been read.
    while ((next_characters = fread(consumed_stdin + string_size, sizeof(char),
                                    ACCENT_CHUNK_SIZE, stdin)) ==
           ACCENT_CHUNK_SIZE) {
        // We update the used size of the string.
        string_size = memory_size;
        //
        // We allocate more space for the rest of the input. We assume malloc
        // won't fail here, which is reasonable.
        memory_size += ACCENT_CHUNK_SIZE * sizeof(char);
        consumed_stdin = realloc(consumed_stdin, memory_size);
    }
    // We have reached the EOF, we update the size of our string one last time
    // to add the null-terminating byte. We know that we have room left since
    // not all of the allocated chunk has been used.
    string_size += next_characters;
    *(consumed_stdin + string_size) = '\0';
    // We resize the memory allocated to the string to avoid wasting space, and
    // return the resulting string. `+1` if for the null-byte.
    return realloc(consumed_stdin, string_size + 1);
}

/************************************ EOF *************************************/
