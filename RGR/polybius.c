#include "polybius.h"
#include <stdlib.h>
#include <string.h>

// Таблица Полибия (5x6, как в задании)
const wchar_t polybius[5][6] = {
    {L'А', L'Б', L'В', L'Г', L'Д', L'Е'},
    {L'Ж', L'З', L'И', L'К', L'Л', L'М'},
    {L'Н', L'О', L'П', L'Р', L'С', L'Т'},
    {L'У', L'Ф', L'Х', L'Ц', L'Ч', L'Ш'},
    {L'Щ', L'Ъ', L'Ы', L'Ь', L'Э', L'Ю'}
};

// Символы строки и столбца (заголовки таблицы)
const wchar_t rows[5] = {L'А', L'Б', L'В', L'Г', L'Д'};
const wchar_t cols[6] = {L'А', L'Б', L'В', L'Г', L'Д', L'Е'};

// Поиск позиции буквы в таблице Полибия
void find_position(wchar_t c, int* row, int* col) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 6; j++) {
            if (polybius[i][j] == c) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
    *row = -1; // Если символ не найден
    *col = -1;
}

// Поиск индекса символа в массиве rows или cols
int find_index(wchar_t c, const wchar_t* array, int size) {
    for (int i = 0; i < size; i++) {
        if (array[i] == c) return i;
    }
    return -1;
}

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

// Дешифрование текста
wchar_t* DePolibi(const wchar_t* input) {
    int len = wcslen(input);
    // Дешифрованный текст: пара букв → одна буква, длина уменьшается вдвое
    wchar_t* output = (wchar_t*)malloc(len / 2 + 1);
    if (!output) return NULL;

    int k = 0;
    for (int i = 0; i < len; i += 2) {
        int row = find_index(input[i], rows, 5);
        int col = find_index(input[i + 1], cols, 6);
        if (row != -1 && col != -1) {
            output[k++] = polybius[row][col];
        }
    }
    output[k] = L'\0';
    return output;
}
