#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include <stdlib.h>
#include <string.h>
#include <wchar.h>

// Символы строки и столбца (заголовки таблицы)
const wchar_t rows[5] = {L'А', L'Б', L'В', L'Г', L'Д'};
const wchar_t cols[6] = {L'А', L'Б', L'В', L'Г', L'Д', L'Е'};

// Шифрование текста
wchar_t* Polibi(const wchar_t* input) {
    int len = wcslen(input);
    //printf("len %d\n", len);
    // Зашифрованный текст: каждая буква → пара букв, длина удваивается
    wchar_t* output = (wchar_t*)malloc(2 * len + 1);
    if (!output) return NULL;

    int k = 0;
    for (int i = 0; i < len; i++) {
        int row, col;
        find_position(input[i], &row, &col);
        if (row != -1 && col != -1) {
            output[k++] = rows[row]; // Буква строки
            output[k++] = cols[col]; // Буква столбца
        }
    }
    output[k] = L'\0';
    return output;
}