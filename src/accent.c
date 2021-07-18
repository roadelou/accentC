/********************************** METADATA **********************************/

/*
 * Contributors: roadelou
 * Contacts:
 * Creation Date: 2021-07-18
 * Language: C Source
 */

/********************************** INCLUDES **********************************/

// The library we are trying to implement.
#include "accent.h"
//
// Used for malloc and realloc.
#include <stdlib.h>
//
// Used for strlen and other string manipulation functions.
#include <string.h>

/********************************* SINGLETONS *********************************/

/* The static global variables for your code goe here. */

/********************************* PROTOYPES **********************************/

/* The prototypes of your functions go here. */

/************************************ MAIN ************************************/

/* The main function of your code goes here. */

/********************************* FUNCTIONS **********************************/

// Implementation of the functions described in "accent.h".
char *replace(const char *text, const char *pattern, const char *word) {
    // A variable used to store the current length of the allocated string.
    size_t allocated_length = 0;
    //
    // A cursor for our current position in the original `text`.
    const char *cursor = text;
    //
    // The length (in bytes) of the `pattern`, computed once.
    const size_t pattern_length = strlen(pattern);
    //
    // We also cache the length of the `word` so that it is only computed once.
    const size_t word_length = strlen(word);
    //
    // A pointer to the returned string.
    char *returned_string;
    //
    // We go over each byte of the input string.
    while (*cursor != '\0') {
        //
        // For each position of the `cursor`, we check if it matches the
        // `pattern`.
        if (strncmp(cursor, pattern, pattern_length) == 0) {
            // We write the `word` into the returned string. We first resize the
            // allocated string. We assume that malloc will never fail here,
            // which is reasonable.
            returned_string =
                realloc(returned_string, allocated_length + word_length);
            //
            // We copy the `word` into the result string.
            memcpy(returned_string + allocated_length, word, word_length);
            //
            // We update the `allocated_length` for the next iteration.
            allocated_length += word_length;
            //
            // We also have to move our `cursor` right at the end of the
            // `pattern`.
            cursor += pattern_length;
        } else {
            // If the pattern does not match, we simply copy the character from
            // the original `text` to the new string. This invokes realloc at
            // each iteration, which is bad for performance but easier to write.
            // Since I am in no hurry for now I will leave this easy
            // implementation and update it later.
            returned_string = realloc(returned_string, allocated_length + 1);
            //
            // We copy character from the original `text`.
            *(returned_string + allocated_length) = *cursor;
            //
            // We update the `allocated_length` for the next iteration.
            allocated_length++;
            //
            // We also have to move our `cursor` to the next character.
            cursor++;
        }
    }
    // We have reached the end of the string, we have to add the terminating
    // null byte.
    allocated_length++;
    returned_string = realloc(returned_string, allocated_length);
    *(returned_string + allocated_length - 1) = '\0';
    //
    // We return the expected string.
    return returned_string;
}

/************************************ EOF *************************************/
