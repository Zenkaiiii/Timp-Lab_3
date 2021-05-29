#include <UnitTest++/UnitTest++.h>
#include "/home/danila/timp_lab_3/1_ccc/modAlphaCipher.h"
#include "/home/danila/timp_lab_3/1_ccc/modAlphaCipher.cpp"

SUITE(KeyTest)
{
    TEST(ValidKey) {
        CHECK_EQUAL("БВГБВ",modAlphaCipher("БВГ").encrypt("ААААА"));
    }
    TEST(LongKey) {
        CHECK_EQUAL("БВГДЕ",modAlphaCipher("БВГДЕЁЖЗИЙ").encrypt("ААААА"));
    }
    TEST(LowCaseKey) {
        CHECK_EQUAL("БВГБВ",modAlphaCipher("бвг").encrypt("ААААА"));
    }
    TEST(DigitsInKey) {
        CHECK_THROW(modAlphaCipher cp("Б1"),cipher_error);
    }
    TEST(PunctuationInKey) {
        CHECK_THROW(modAlphaCipher cp("Б,В"),cipher_error);
    }
    TEST(WhitespaceInKey) {
        CHECK_THROW(modAlphaCipher cp("Б В"),cipher_error);
    }
    TEST(EmptyKey) {
        CHECK_THROW(modAlphaCipher cp(""),cipher_error);
    }
    TEST(WeakKey) {
        CHECK_THROW(modAlphaCipher cp("ААА"),cipher_error);
    }
}

struct KeyB_fixture {
    modAlphaCipher * p;
    KeyB_fixture()
    {
        p = new modAlphaCipher("Б");
    }
    ~KeyB_fixture()
    {
        delete p;
    }
};

SUITE(EncryptTest)
{
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        CHECK_EQUAL("РПТЛПМЭИЛПКЕПСПДЁ",
                    p->encrypt("ПОСКОЛЬЗКОЙДОРОГЕ"));
    }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK_EQUAL("РПТЛПМЭИЛПКЕПСПДЁ",
                    p->encrypt("поскользкойдороге"));
    }
    TEST_FIXTURE(KeyB_fixture, StringWithWhitspaceAndPunct) {
        CHECK_EQUAL("РПТЛПМЭИЛПКЕПСПДЁ",
                    p->encrypt("ПО СКОЛЬЗКОЙ ДОРОГЕ!!!"));
    }
    TEST_FIXTURE(KeyB_fixture, StringWithNumbers) {
        CHECK_EQUAL("ОПГЬКДПЕ", p->encrypt("Новый 2021 Год"));
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->encrypt(""),cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, NoAlphaString) {
        CHECK_THROW(p->encrypt("1234+8765=9999"),cipher_error);
    }
    TEST(MaxShiftKey) {
        CHECK_EQUAL("ОНРЙНКЫЖЙНИГНПНВД",
                    modAlphaCipher("Я").encrypt("ПО СКОЛЬЗКОЙ ДОРОГЕ"));
    }
}

SUITE(DecryptText)
{
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        CHECK_EQUAL("ПОСКОЛЬЗКОЙДОРОГЕ",
                    p->decrypt("РПТЛПМЭИЛПКЕПСПДЁ"));
    }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK_THROW(p->decrypt("рптлпмэилпкЕПСПДЁ"),cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, WhitespaceString) {
        CHECK_THROW(p->decrypt("РП ТЛПМЭИЛПК ЕПСПДЁ"),cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, DigitsString) {
        CHECK_THROW(p->decrypt("ОПГЬК2021ДПЕ"),cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, PunctString) {
        CHECK_THROW(p->decrypt("ОПГЬ,КДПЕ"),cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->decrypt(""),cipher_error);
    }
    TEST(MaxShiftKey) {
        CHECK_EQUAL("ПОСКОЛЬЗКОЙДОРОГЕ",
                    modAlphaCipher("Я").decrypt("АЪРСПЯЮАТПЯЮКЗРЯ"));
    }
}

int main(int argc, char **argv)
{
    return UnitTest::RunAllTests();
}

