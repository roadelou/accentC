# Accent (C)

`accent` is a simple CLI tool to add french accents to a text file using markup. I wrote this program because my keyboard doesn't have shortcuts for those and I often have to write long essays in french.

## Usage

To compile and install `accent`, use the provided [Makefile](Makefile):

```bash
# This command will install `accent` in /usr/bin.
sudo make install
```

To use `accent`, simply pipe the markup text to stdin and retrieve the text with the accents on stdout.

```bash
# Example that can be run from the root of the git repository.
cat ./examples/gateaux | accent
```

The input file should be __ASCII__ only, the output file is __UTF-8__.

## Markup

The following substitution patterns will be replaced by the associated french accents.

| Format Sequence | Replaced By |
----------------- | -------------
| e1 | è |
| e2 | é |
| e3 | ê |
| a1 | à |
| a3 | â |
| c4 | ç |
| E1 | È |
| E2 | É |
| E3 | Ê |
| A1 | À |
| A3 | Â |
| C4 | Ç |
| o3 | ô |
| O3 | Ô |
| u3 | û |
| U3 | Û |
| i3 | î |
| I3 | Î |
| u1 | ù |
| U1 | Ù |
| *newline* - | *newline*    • |

Note that there are no escape characters for the defined markup language, so use with caution.

## Fedora Package

To build the fedora package for `accent`, go to the root of the repository and then use:

```bash
# Assuming all the tools have been installed already.
fedpkg --release f33 local
```

### METADATA

Field | Value
--- | ---
:pencil: Contributors | roadelou
:email: Contacts | 
:date: Creation Date | 2021-07-22
:bulb: Language | Markdown Document

### EOF
