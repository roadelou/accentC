/* Include once header guard */
#ifndef ACCENT_INCLUDED
#define ACCENT_INCLUDED

/********************************** METADATA **********************************/

/*
 * Contributors: roadelou
 * Contacts:
 * Creation Date: 2021-07-18
 * Language: C Header
 */

/********************************** INCLUDES **********************************/

// Used for size_t.
#include <stddef.h>

/*********************************** MACROS ***********************************/

// A chunk size used to allocate strings at once instead of
// character-per-character.
#ifndef ACCENT_CHUNK_SIZE
#define ACCENT_CHUNK_SIZE 1024
#endif

/********************************** STRUCTS ***********************************/

/* The enums of your header go here */

// Description
// ===========
// This struct is used by the "match" function to report the number and
// locations of matches of a substring within a string.
//
// Fields
// ======
//  - count: The number of matches in the string, also the length of the
//  "position" array.
//  - position: A dynamically allocated array containing the positions of the
//  matched substring within the string. The return index corresponds to the
//  offset of the beginning of the match from the beginning of the string.
//
struct MatchList {
    size_t count;
    size_t *position;
};

/* The unions of your header go here */

/* The typedefs of your header go here */

/********************************* PROTOTYPES *********************************/

// Description
// ===========
// This function returns a copy of the original `text` where all occurences of
// `pattern` have been replaced with `word`. The match has to be an exact one.
//
// Arguments
// =========
//  - text: The initial text one which the replacement should take place.
//  - pattern: The pattern that should be replaced. It has to be exactly matched
//  in order for the replacement to be triggered. This is not a regular
//  expression.
//  - word: The word with which the pattern should be replaced.
//
// Returns
// =======
// A heap-allocated copy of `text` where all instances of `pattern` have been
// replaced with `word`.
//
char *replace(const char *text, const char *pattern, const char *word);

// Description
// ===========
// This function is used to find all occurences of `pattern` within `text`.
//
// Arguments
// =========
//  - text: The string in which the `pattern` should be found one or more times.
//  Must be null-terminated.
//  - pattern: The substring which should be looked for in the `text`. Should be
//  null-terminated.
//
// Returns
// =======
// A MatchList struct containing a list of all the position where the `pattern`
// is found in the `text`.
//
struct MatchList match(const char *text, const char *pattern);

// Description
// ===========
// Helper function to free the content of a MatchList object.
//
// Arguments
// =========
//  - match_list: The match_list object whose content should be freed.
//
void match_list_free(struct MatchList *match_list);

/* End of include once header guard */
#endif

/************************************ EOF *************************************/
