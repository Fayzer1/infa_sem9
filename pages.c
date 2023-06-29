#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void split_file_into_pages(const char* file_name, int lines_per_page, int max_line_length) {
    FILE* file = fopen(file_name, "r");
    if (file == NULL) {
        printf("Не удалось открыть файл.\n");
        return;
    }
    
    char line_buffer[max_line_length + 1];
    
    int current_page = 1;
    int lines_on_page = 0;
    
    printf("-- Страница %d --\n", current_page);
    
    while (fgets(line_buffer, sizeof(line_buffer), file) != NULL) {
        line_buffer[strcspn(line_buffer, "\n")] = '\0';
        
        if (strlen(line_buffer) > max_line_length) {
            line_buffer[max_line_length] = '\0';  // Обрезаем строку, если она превышает максимальную длину
        }
        
        lines_on_page++;
        
        if (lines_on_page > lines_per_page) {
            current_page++;
            printf("-- Страница %d --\n", current_page);
            lines_on_page = 1;
        }
        
        printf("%d: %s\n", lines_on_page, line_buffer);
    }
    
    fclose(file);
}

int main(int argc, char* argv[]) {
    if (argc != 5) {
        printf("Неверное количество аргументов.\n");
        printf("Использование: ./page -p <количество_строк_на_странице> -n <максимальная_длина_строки>\n");
        return 1;
    }
    
    if (strcmp(argv[1], "-p") != 0 || strcmp(argv[3], "-n") != 0) {
        printf("Неверные аргументы.\n");
        printf("Использование: ./page -p <количество_строк_на_странице> -n <максимальная_длина_строки>\n");
        return 1;
    }
    
    int lines_per_page = atoi(argv[2]);
    int max_line_length = atoi(argv[4]);
    
    split_file_into_pages("file.txt", lines_per_page, max_line_length);
    
    return 0;
}



