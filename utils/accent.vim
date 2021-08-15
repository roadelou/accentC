" Vim syntax highlighting for the accent digraphs.
" Contributors: roadelou
" Contacts: 
" Creation Date: 2021-08-15
" Language: Vim Script

" Depending how your setup is organized, you might need to add the following
" line somewhere in your configuration.
" au! BufRead,BufNewFile *.fr set filetype=accent

" Quit when a syntax file was already loaded.
if exists("b:current_syntax")
	finish
endif

" case is insignificant
syn case ignore

" Matching the digraphs.
syn match accentDigraph "e1"
syn match accentDigraph "e2"
syn match accentDigraph "e3"
syn match accentDigraph "a1"
syn match accentDigraph "a3"
syn match accentDigraph "c4"
syn match accentDigraph "E1"
syn match accentDigraph "E2"
syn match accentDigraph "E3"
syn match accentDigraph "A1"
syn match accentDigraph "A3"
syn match accentDigraph "C4"
syn match accentDigraph "o3"
syn match accentDigraph "O3"
syn match accentDigraph "u3"
syn match accentDigraph "U3"
syn match accentDigraph "i3"
syn match accentDigraph "I3"
syn match accentDigraph "u1"
syn match accentDigraph "U1"

" Class Linking
hi def link accentDigraph Special

let b:current_syntax = "accent"
