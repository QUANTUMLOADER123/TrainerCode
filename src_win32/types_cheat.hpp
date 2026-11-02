#pragma once
#include <string>
#include <vector>

struct TypeInfo {
    std::wstring type_name;
    std::wstring bytes_x86;
    std::wstring bytes_x64;
    std::wstring range_info;
    std::wstring printf_spec;
    std::wstring description;
};

inline std::vector<TypeInfo> get_all_types() {
    return {
        {L"char", L"1", L"1", L"-128 .. 127", L"%c / %d", L"Символ ASCII или 8-битное целое со знаком"},
        {L"unsigned char", L"1", L"1", L"0 .. 255", L"%u / %c", L"Символ ASCII или 8-битный байт без знака"},
        {L"short", L"2", L"2", L"-32,768 .. 32,767", L"%hd", L"Короткое целое число со знаком"},
        {L"unsigned short", L"2", L"2", L"0 .. 65,535", L"%hu", L"Короткое целое без знака"},
        {L"int", L"4", L"4", L"-2,147,483,648 .. 2,147,483,647", L"%d, %i", L"Базовое целое со знаком (32 бита)"},
        {L"unsigned int", L"4", L"4", L"0 .. 4,294,967,295", L"%u", L"Базовое целое без знака (32 бита)"},
        {L"long", L"4", L"4 (Win) / 8 (Lin)", L"-2*10^9 .. 2*10^9", L"%ld", L"Длинное целое (на Windows всегда 32 бита, LLP64)"},
        {L"unsigned long", L"4", L"4 (Win) / 8 (Lin)", L"0 .. 4*10^9", L"%lu", L"Беззнаковое длинное целое"},
        {L"long long", L"8", L"8", L"-9,223,372,036,854,775,808 .. 9,223,372,036,854,775,807", L"%lld", L"64-битное целое число со знаком"},
        {L"unsigned long long", L"8", L"8", L"0 .. 18,446,744,073,709,551,615", L"%llu", L"64-битное целое число без знака"},
        {L"float", L"4", L"4", L"±1.18*10^-38 .. ±3.4*10^38 (~7 цифр)", L"%f, %e", L"Вещественное число одинарной точности IEEE 754"},
        {L"double", L"8", L"8", L"±2.23*10^-308 .. ±1.79*10^308 (~15-17 цифр)", L"%lf, %f", L"Вещественное число двойной точности IEEE 754"},
        {L"size_t", L"4", L"8", L"0 .. SIZE_MAX (беззнаковый)", L"%zu", L"Тип для размеров объектов и массивов (<stddef.h>)"},
        {L"ptrdiff_t", L"4", L"8", L"PTRDIFF_MIN .. PTRDIFF_MAX", L"%td", L"Знаковая разность двух указателей"},
        {L"void*", L"4", L"8", L"0x00000000 .. 0xFFFFFFFFFFFFFFFF", L"%p", L"Универсальный сырой указатель на область памяти"},
        {L"bool (C++) / _Bool (C)", L"1", L"1", L"0 (false) или 1 (true)", L"%d / boolalpha", L"Логический тип данных"}
    };
}
