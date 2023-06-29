#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_N 5 // количество строк для вывода по умолчанию

void tail(const char *filename, int n) {
    FILE *file = fopen(filename, "r"); // открытие файла для чтения
    if (file == NULL) {
        fprintf(stderr, "Error opening file.\n"); // вывод сообщения об ошибке, если файл не удалось открыть
        exit(EXIT_FAILURE); // выход из программы с кодом ошибки
    }

    char line[512];
    char lines[n][512]; // массив строк, размером n x 512
    int count = 0; // счетчик количества считанных строк

    while (fgets(line, sizeof(line), file)) { // чтение строки из файла
        strcpy(lines[count % n], line); // копирование строки в массив строк
        count++;
    }

    fclose(file); // закрытие файла

    for (int i = count >= n ? count - n : 0; i < count; i++) { // вывод n последних строк файла
        printf("%s", lines[i % n]); // вывод строки из массива строк
    }
}

int main(int argc, char *argv[]) {
    int n = DEFAULT_N; // количество строк для вывода
    const char *filename; // имя файла

    if (argc > 2) { // если заданы и имя файла, и количество строк для вывода
        filename = argv[1];
        n = atoi(argv[2]); // преобразование строки в число
    } else if (argc > 1) {  // если задано только имя файла
        filename = argv[1];
    } else { // если аргументы не заданы
        fprintf(stderr, "Usage: %s <filename> [<n>]\n", argv[0]);
        return EXIT_FAILURE; // выход из программы с кодом ошибки
    }

    tail(filename, n); // вызов функции для вывода последних строк файла

    return EXIT_SUCCESS; // успешное завершение программы
}
