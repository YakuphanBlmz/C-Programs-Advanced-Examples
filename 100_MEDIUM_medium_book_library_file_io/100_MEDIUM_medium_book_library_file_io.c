#include <stdio.h>
#include <string.h>
#define MAX_TITLE_LEN 50
#define MAX_AUTHOR_LEN 30
#define NUM_BOOKS 3
typedef struct {
    char title[MAX_TITLE_LEN];
    char author[MAX_AUTHOR_LEN];
    int page_count;
} Book;
int main() {
    Book library[NUM_BOOKS];
    FILE *file_ptr;
    int i;
    printf("Enter details for %d books:\n", NUM_BOOKS);
    for (i = 0; i < NUM_BOOKS; i++) {
        printf("\nBook %d:\n", i + 1);
        printf("Title: ");
        fgets(library[i].title, MAX_TITLE_LEN, stdin);
        library[i].title[strcspn(library[i].title, "\n")] = 0;
        printf("Author: ");
        fgets(library[i].author, MAX_AUTHOR_LEN, stdin);
        library[i].author[strcspn(library[i].author, "\n")] = 0;
        printf("Page Count: ");
        scanf("%d", &library[i].page_count);
        while (getchar() != '\n');
    }
    file_ptr = fopen("library.dat", "wb");
    if (file_ptr == NULL) {
        printf("Error opening file for writing!\n");
        return 1;
    }
    fwrite(library, sizeof(Book), NUM_BOOKS, file_ptr);
    fclose(file_ptr);
    printf("\nBooks saved to library.dat\n");
    Book loaded_library[NUM_BOOKS];
    file_ptr = fopen("library.dat", "rb");
    if (file_ptr == NULL) {
        printf("Error opening file for reading!\n");
        return 1;
    }
    fread(loaded_library, sizeof(Book), NUM_BOOKS, file_ptr);
    fclose(file_ptr);
    printf("\nBooks loaded from library.dat:\n");
    for (i = 0; i < NUM_BOOKS; i++) {
        printf("\nBook %d:\n", i + 1);
        printf("Title: %s\n", loaded_library[i].title);
        printf("Author: %s\n", loaded_library[i].author);
        printf("Page Count: %d\n", loaded_library[i].page_count);
    }
    return 0;
}