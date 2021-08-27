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
    // We compute the length of the text once.
    const size_t text_length = strlen(text);
    //
    // The length (in bytes) of the `pattern`, computed once.
    const size_t pattern_length = strlen(pattern);
    //
    // We also cache the length of the `word` so that it is only computed once.
    const size_t word_length = strlen(word);
    //
    // We start by finding all occurences of the `pattern` within the `text`
    // using the `match` function.
    struct MatchList match_list = match(text, pattern);
    //
    // We compute the size we need to allocate for the new text with the
    // replacements and allocate it. The `+1` is for the terminating '\0'.
    char *returned_string = malloc(
        (text_length + 1 + match_list.count * (word_length - pattern_length)) *
        sizeof(char));
    //
    // This position points to the last byte copied from the original `text` to
    // the `returned_string`. It is initially set to the beginning of the `text`
    // since we haven't copied anything.
    const char *old_cursor = text;
    //
    // A variable used to store the amount of characters copied from the `text`
    // to the `returned_string` to update the `write_head`.
    size_t character_count;
    //
    // This write head is used to keep track of where the next bytes should be
    // written to in the `returned_string`. It is initially set to the beginning
    // of the `returned_string` since we haven't written anything yet.
    char *write_head = returned_string;
    //
    // A simple iterator used for our for loop.
    size_t i;
    //
    // We go over all of the matched positions where the `pattern` appears in
    // the `text`.
    for (i = 0; i < match_list.count; i++) {
        //
        // We first copy all the non-pattern characters from the end of the
        // previous match until before the beginning of the current one.
        character_count =
            (size_t)text + *(match_list.position + i) - (size_t)old_cursor;
        //
        // We perform the copy.
        memcpy(write_head, old_cursor, character_count);
        //
        // We update the `old_cursor` and the `write_head`.
        write_head += character_count;
        old_cursor += character_count;
        //
        // We replace the `pattern` by the `word` in the `returned_string`.
        memcpy(write_head, word, word_length);
        //
        // We update the `old_cursor` and the `write_head`.
        write_head += word_length;
        old_cursor += pattern_length;
    }
    //
    // We copy the bytes between the final match and the end of the `text`.
    character_count = (size_t)text + text_length - (size_t)old_cursor;
    //
    // We perform the copy.
    memcpy(write_head, old_cursor, character_count);
    //
    // We update the `write_head`.
    write_head += character_count;
    //
    // We add a final null-termination byte just in case.
    *write_head = '\0';
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
