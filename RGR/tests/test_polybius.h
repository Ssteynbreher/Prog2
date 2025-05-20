#ifndef TEST_POLYBIUS_H
#define TEST_POLYBIUS_H

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <wchar.h>
#include "/home/sofya/prog/rgr/polybius.h"

// Объявляем функции, которые будем тестировать
wchar_t* Polibi(const wchar_t* input);

#endif
