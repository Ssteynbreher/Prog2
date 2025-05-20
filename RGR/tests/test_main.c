#include "test_polybius.h"
#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <locale.h>

// Тест шифрования
void test_polibi_encrypt(void **state) {
    (void)state;
    const wchar_t *input = L"ПРИВЕТ";
    const wchar_t *expected = L"ВГВБГДВВ"; // Ожидаемый результат
    
    wchar_t *encrypted = Polibi(input);
    assert_non_null(encrypted);
    assert_wstring_equal(encrypted, expected);
    free(encrypted);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_polibi_encrypt),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}


