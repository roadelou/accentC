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

struct MatchList match(const char *text, const char *pattern) {
    // A cursor for our current position in the original `text`.
    const char *cursor = text;
    //
    // The length (in bytes) of the `pattern`, computed once.
    const size_t pattern_length = strlen(pattern);
    //
    // A compile time constant which tells us how many positions can be held in
    // one allocated chunk.
    const size_t pos_per_chunk = ACCENT_CHUNK_SIZE / sizeof(size_t);
    //
    // The MatchList object we intend to return.
    struct MatchList match_list;
    //
    // We initialize the MatchList.
    match_list.count = 0;
    match_list.position = NULL;
    //
    // We go over all the possible positions of the `text` to try and find the
    // pattern. Note that strncmp is aware of null-terminating bytes and won't
    // read beyond them, avoiding segmentation faults and out-of bounds reads.
    while (*cursor != '\0') {
        //
        // For each position of the `cursor`, we check if it matches the
        // `pattern`.
        if (strncmp(cursor, pattern, pattern_length) == 0) {
            // We have found an occurence of the `pattern`. We first update the
            // count of the MatchList.
            match_list.count++;
            //
            // We check whether we must allocate more memory for our array of
            // positions. This will happen only when the number of occurences is
            // one more than can be held in a ACCENT_CHUNK_SIZE (for instance
            // 1). Using a division here works better because it will account
            // for cases where ACCENT_CHUNK_SIZE is not a multiple of
            // sizeof(size_t).
            if (match_list.count % (pos_per_chunk) == 1) {
                // We assume malloc never fails here. Also note that
				// `match_list.count / pos_per_chunk` is the number of chunks
				// already allocated.
                match_list.position = realloc(
                    match_list.position,
                    (1 + match_list.count / pos_per_chunk) * ACCENT_CHUNK_SIZE);
            }
            // At this point, the position array has enough memory allocated to
            // hold the newly found position.
            *(match_list.position + match_list.count - 1) =
                (size_t)cursor - (size_t)text;
        }
        // We update the cursor for the next iteration.
        cursor++;
    }
    // At this point we have gone over the entire text, we may return the
    // expected MatchList.
    return match_list;
}

void match_list_free(struct MatchList *match_list) {
    // We set the count of values back to zero.
    match_list->count = 0;
    // We free the memory allocated for the positions.
    free(match_list->position);
}

/************************************ EOF *************************************/
