#include <stdio.h>
#include <stdlib.h>

void mergeFiles(const char *file1, const char *file2) {
    FILE *f1 = fopen(file1, "r"); // открытие первого файла для чтения
    if (f1 == NULL) {
        fprintf(stderr, "Error opening file %s", file1); // вывод сообщения об ошибке, если первый файл не удалось открыть
        exit(EXIT_FAILURE); // выход из программы с кодом ошибки
    }

    FILE *f2 = fopen(file2, "r"); // открытие второго файла для чтения
    if (f2 == NULL) {
        fclose(f1); // закрытие первого файла, если второй файл не удалось открыть
        fprintf(stderr, "Error opening file %s", file2); // вывод сообщения об ошибке, если второй файл не удалось открыть
        exit(EXIT_FAILURE); // выход из программы с кодом ошибки
    }

    char line1[512];
    char line2[512];

    while (1) {
        if (fgets(line1, sizeof(line1), f1)) { // чтение строки из первого файла
            printf("%s", line1); // вывод строки из первого файла
        } else if (fgets(line2, sizeof(line2), f2)) { // чтение строки из второго файла, если первый файл уже закончился
            printf("%s", line2); // вывод строки из второго файла
        } else { // если оба файла закончились, выходим из цикла
            break;
        }
        if (fgets(line2, sizeof(line2), f2)) { // чтение строки из второго файла
            printf("%s", line2); // вывод строки из второго файла
        } else if (fgets(line1, sizeof(line1), f1)) { // чтение строки из первого файла, если второй файл уже закончился
            printf("%s", line1); // вывод строки из первого файла
        } else { // если оба файла закончились, выходим из цикла
            break;
        }
    }

    fclose(f1); // закрытие первого файла
    fclose(f2); // закрытие второго файла
}

int main(int argc, char *argv[]) {
    if (argc != 3) { // проверка на количество аргументов командной строки
        fprintf(stderr, "Usage: %s <file1> <file2>\n", argv[0]);
        return EXIT_FAILURE; // выход из программы с кодом ошибки
    }
    
    const char *file1 = argv[1]; // имя первого файла
    const char *file2 = argv[2]; // имя второго файла
    
    mergeFiles(file1, file2); // вызов функции для вывода строк из файлов в перемешку
    
    return EXIT_SUCCESS; // успешное завершение программы
}
