# Linked Country Dictionary

A simple C program that maintains a dictionary of country names using an array of linked lists.

Each country is stored based on its starting letter (A–Z) and kept in sorted order.  
Data is loaded from and saved to a text file (`CNAMES.TXT`).

## Features

- Add a new country
- Search for an existing country
- Save new entries to a text file
- Keep the country list alphabetically ordered in memory

## How to Use

### Compile
```bash
gcc -std=c11 -Wall -Wextra -o country_dict clist.c
