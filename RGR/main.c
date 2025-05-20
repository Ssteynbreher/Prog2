#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <locale.h>
#include "polybius.h"

wchar_t* read_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Ошибка открытия файла %s\n", filename);
        return NULL;
    }

    int capacity = 1024;
    wchar_t* buffer = (wchar_t*)malloc(capacity);
    if (!buffer) {
        fclose(file);
        return NULL;
    }

    int pos = 0;
    wchar_t c;
    while ((c = fgetwc(file)) != EOF) {
        if (pos >= capacity - 1) {
            capacity *= 2;
            wchar_t* new_buffer = (wchar_t*)realloc(buffer, capacity);
            if (!new_buffer) {
                free(buffer);
                fclose(file);
                return NULL;
            }
            buffer = new_buffer;
        }
        buffer[pos++] = c;
    }
    buffer[pos] = '\0';
    fclose(file);
    return buffer;
}

// Запись текста в файл
void write_file(const char* filename, const wchar_t* text) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Ошибка открытия файла %s для записи\n", filename);
        return;
    }
    fputws(text, file);
    fclose(file);
}

int main() {
    setlocale(LC_ALL, "");
    // Загрузка динамической библиотеки
    void* handle = dlopen("./libpolybius.so", RTLD_LAZY);
    if (!handle) {
        printf("Ошибка загрузки библиотеки: %s\n", dlerror());
        return 1;
    }

    // Чтение исходного текста из файла input.txt
    wchar_t* input_text = read_file("input.txt");
    if (!input_text) {
        printf("Не удалось прочитать входной файл\n");
        dlclose(handle);
        return 1;
    }

    printf("Исходный текст: %ls\n", input_text);

    // Шифрование
    wchar_t* encrypted = Polibi(input_text);
    if (!encrypted) {
        printf("Ошибка шифрования\n");
        free(input_text);
        dlclose(handle);
        return 1;
    }

    //
    printf("Зашифрованный текст: %ls\n", encrypted);

    // Запись зашифрованного текста в файл output.txt
    write_file("output.txt", encrypted);

    // Дешифрование
    wchar_t* decrypted = DePolibi(encrypted);
    if (!decrypted) {
        printf("Ошибка дешифрования\n");
        free(input_text);
        free(encrypted);
        dlclose(handle);
        return 1;
    }

    printf("Дешифрованный текст: %ls\n", decrypted);

    // Проверка совпадения
    if (wcscmp(input_text, decrypted) == 0) {
        printf("Исходный и дешифрованный тексты совпадают\n");
    } else {
        printf("Исходный и дешифрованный тексты НЕ совпадают\n");
    }

    // Оценка криптостойкости
    printf("Оценка криптостойкости:\n");
    printf("- Шифр Полибия уязвим к частотному анализу, так как каждая буква заменяется фиксированной парой.\n");
    printf("- Рекомендации: использовать случайный порядок строк и столбцов в таблице для каждого сеанса или добавлять шумовые символы.\n");

    // Освобождение памяти
    free(input_text);
    free(encrypted);
    free(decrypted);
    dlclose(handle);

    return 0;
}
