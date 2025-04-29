#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_NAME_LEN 20

void addtolist(int, const char *);
int search_list(int, const char *);

struct clist {
    char name[MAX_NAME_LEN];
    struct clist *link;
};

struct clist *a[26] = {NULL};

int main(void) {
    char country[MAX_NAME_LEN];
    char response[10];
    int sflag, l;
    FILE *fp = fopen("CNAMES.TXT", "r+");

    // Fallback to create file if it doesn't exist
    if (fp == NULL) {
        fp = fopen("CNAMES.TXT", "w+");
        if (fp == NULL) {
            perror("Failed to open or create CNAMES.TXT");
            return EXIT_FAILURE;
        }
    }

    // Load existing countries into linked lists
    while (fgets(country, sizeof(country), fp)) {
        l = strlen(country);
        if (country[l - 1] == '\n')
            country[l - 1] = '\0'; // remove newline
        addtolist(toupper(country[0]) - 'A', country);
    }

    while (1) {
        printf("Enter the Country to Search:\n");
        if (!fgets(country, sizeof(country), stdin))
            break;
        country[strcspn(country, "\n")] = '\0'; // remove newline

        sflag = search_list(toupper(country[0]) - 'A', country);

        if (sflag)
            printf("%s is present in the List\n", country);
        else {
            printf("Misspelled\n");
            printf("Do you want to Add it in the List (Y/N):\n");
            if (!fgets(response, sizeof(response), stdin))
                break;
            response[strcspn(response, "\n")] = '\0';

            if (tolower(response[0]) == 'y') {
                fseek(fp, 0L, SEEK_END);
                fputs(country, fp);
                fputs("\n", fp);
                addtolist(toupper(country[0]) - 'A', country);
            }
        }

        printf("Any More Countries to Search (Y/N):\n");
        if (!fgets(response, sizeof(response), stdin))
            break;
        response[strcspn(response, "\n")] = '\0';

        if (tolower(response[0]) != 'y')
            break;
    }

    fclose(fp);
    return EXIT_SUCCESS;
}

void addtolist(int index, const char *str) {
    struct clist *new_node = malloc(sizeof(struct clist));
    if (!new_node) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    strncpy(new_node->name, str, MAX_NAME_LEN);
    new_node->name[MAX_NAME_LEN - 1] = '\0';  // Ensure null-terminated
    new_node->link = NULL;

    if (!a[index] || strcmp(a[index]->name, str) > 0) {
        new_node->link = a[index];
        a[index] = new_node;
    } else {
        struct clist *current = a[index];
        while (current->link && strcmp(current->link->name, str) < 0) {
            current = current->link;
        }
        new_node->link = current->link;
        current->link = new_node;
    }
}

int search_list(int index, const char *str) {
    struct clist *current = a[index];
    while (current) {
        if (strcmp(current->name, str) == 0)
            return 1;
        current = current->link;
    }
    return 0;
}
