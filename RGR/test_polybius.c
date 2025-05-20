#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <wchar.h>
#include "polybius.h"

static void test_polybius_encrypt_decrypt(void **state) {
    (void)state;
    const wchar_t* input = L"ПРИМЕР";
    const wchar_t* expected_encrypted = L"ВВВГБВБЕАЕВГ";
    wchar_t* encrypted = Polibi(input);
    assert_non_null(encrypted); 
    assert_memory_equal(encrypted, expected_encrypted, (wcslen(expected_encrypted) + 1) * sizeof(wchar_t)); 
    wchar_t* decrypted = DePolibi(encrypted);
    assert_non_null(decrypted); 
    assert_memory_equal(decrypted, input, (wcslen(input) + 1) * sizeof(wchar_t)); 
    free(encrypted);
    free(decrypted);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_polybius_encrypt_decrypt),};
    return cmocka_run_group_tests(tests, NULL, NULL);
}