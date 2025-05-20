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
    wchar_t* buffer = (wchar_t*)malloc(capacity * sizeof(wchar_t));
    if (!buffer) {
        fclose(file);
        return NULL;
    }

    int pos = 0;
    wint_t c;
    while ((c = fgetwc(file)) != WEOF) {
        if (pos >= capacity - 1) {
            capacity *= 2;
            wchar_t* new_buffer = (wchar_t*)realloc(buffer, capacity * sizeof(wchar_t));
            if (!new_buffer) {
                free(buffer);
                fclose(file);
                return NULL;
            }
            buffer = new_buffer;
        }
        buffer[pos++] = (wchar_t)c;
    }
    buffer[pos] = L'\0';
    fclose(file);
    return buffer;
}

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
    void* handle = dlopen("./libpolybius.so", RTLD_LAZY);
    if (!handle) {
        printf("Ошибка загрузки библиотеки: %s\n", dlerror());
        return 1;
    }

    wchar_t* input_text = read_file("input.txt");
    if (!input_text) {
        printf("Не удалось прочитать входной файл\n");
        dlclose(handle);
        return 1;
    }

    printf("Исходный текст: %ls\n", input_text);

    wchar_t* encrypted = Polibi(input_text);
    if (!encrypted) {
        printf("Ошибка шифрования\n");
        free(input_text);
        dlclose(handle);
        return 1;
    }

    printf("Зашифрованный текст: %ls\n", encrypted);
    write_file("output.txt", encrypted);

    wchar_t* decrypted = DePolibi(encrypted);
    if (!decrypted) {
        printf("Ошибка дешифрования\n");
        free(input_text);
        free(encrypted);
        dlclose(handle);
        return 1;
    }

    printf("Дешифрованный текст: %ls\n", decrypted);

    if (wcscmp(input_text, decrypted) == 0) {
        printf("Исходный и дешифрованный тексты совпадают\n");
    } else {
        printf("Исходный и дешифрованный тексты НЕ совпадают\n");
    }

    printf("Оценка криптостойкости:\n");
    printf("- Каждая буква заменяется фиксированной парой.\n");
    printf("- Из-за статичной таблицы для всех сообщений исползуется одинаковые замены букв и пар символов, что делает шифр предсказуемым.\n");
    printf("- Пробелы остаются неизменными в зашифрованном тексте, вследствие этого задачу злоумышленникам при дешифровке текста.\n");
    printf("- Рекомендации: \n");
    printf("- 1. Вместо фиксированной таблицы использовать каждый раз новую(перед применением сгенерировать случайную таблицу и передать ее как часть ключа). \n" );
    printf(" Или же просто сгенерировать случайный порядок строк и столбцов.\n");  
    printf("- 2. Шифровать пробелы тоже. Не оставлять пустоту, а также заменять их на пару символов, не используемую для других символов. \n");

    free(input_text);
    free(encrypted);
    free(decrypted);
    dlclose(handle); 
    return 0;
}
