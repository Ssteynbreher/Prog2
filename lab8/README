Взяла рабочий код "ShellSort" СиАОД 
Разделила на:
- sort.c - основной файл без main
- sort.h - файл с заголовочными функциями
- test_sorts.c - файл тестирования CMocka
- CMakeLists.txt - файл для CMake и CTest
  
Покрыла unit-тестами, используя CMocka — это фреймворк для модульного тестирования (unit testing) на языке C.

 Плюсы CMocka
1. Простота – минимум кода для тестов
2. Mock-функции – можно подменять реальные функции на тестовые
3. Кросс-платформенность – работает везде, где есть C
4. Интеграция с CMake – легко встроить в CI/CD
 
  Минусы CMocka
1. Меньше возможностей, чем у Google Test
2. Нет встроенного runner (как у Check)
   
Установила:
- sudo apt-get update
- sudo apt-get install libcmocka-dev

В файле test_sorts.c подключила библиотеки:
#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <stdio.h>
#include <string.h>
#include <cmocka.h>

Далее написала CMakeLists.txt.

Собрала проект:
1. mkdir build && cd build
2. cmake ..
3. make

Вывела на экран результаты тестов:
./sort_tests
![image](https://github.com/user-attachments/assets/90ecb0cd-081f-43f4-bf9b-9e1d5151b81d)

