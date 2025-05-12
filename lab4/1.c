#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Функция для переворота строки
void reverse_string(char *str) {
    int length = strlen(str); //длина строки
    // Меняем симметричные символы местами
    for (int i = 0; i < length / 2; i++) { //проходит до середины строки
        char temp = str[i]; //сохраняет текущий символ во временной переменной
        str[i] = str[length - i - 1]; //заменяет текущий символ симметричным из конца строки
        str[length - i - 1] = temp; //заменяет симметричный символ сохранённым
    }
}

int main(int argc, char *argv[]) {
     //Проверка аргументов командной строки 
     if (argc != 2) {
        fprintf(stderr, "Фигня все %s файл\n", argv[0]);
        return 1;
    }

    //Открываем файл для чтения
    FILE *file = fopen("2.txt", "r");
    if (file == NULL) {
        perror("Ошибка открытия файла");
        exit(1);
    }

    //Создаём выходной файл
    char output_filename[256];
    // Безопасное формирование имени выходного файла
    snprintf(output_filename, sizeof(output_filename), "reversed_%s", argv[1]);
    FILE *output = fopen(output_filename, "w");
    if (output == NULL) {
        perror("Ошибка создания файла");
        fclose(file);
        return 1;
    }
    //Чтение и обработка
    char line[256]; // Буфер для хранения одной строки
    while (fgets(line, sizeof(line), file)) {
        //Разбиваем строку на слова
        char *word = strtok(line, " \t\n"); // Первое слово
        while (word != NULL) {
            //Переворачиваем слово
            reverse_string(word);
            //Записываем слово в выходной файл 
            fprintf(output, "%s ", word);
            //Переходим к следующему слову
            word = strtok(NULL, " \t\n");
        }
        //Добавляем перенос строки после обработки всех слов
        fprintf(output, "\n");
    }
    //ЗАКРЫТИЕ ФАЙЛОВ
    fclose(file);
    fclose(output);

    printf("Файл обработан. Результат сохранён в %s\n", output_filename);
}
