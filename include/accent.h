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

/* The includes for your header go here */

/*********************************** MACROS ***********************************/

// A chunk size used to allocate strings at once instead of
// character-per-character.
#ifndef ACCENT_CHUNK_SIZE
#define ACCENT_CHUNK_SIZE 1024
#endif

/********************************** STRUCTS ***********************************/

/* The enums of your header go here */

/* The structs of your header go here */

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

/* End of include once header guard */
#endif

/************************************ EOF *************************************/
