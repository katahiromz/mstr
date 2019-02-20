// mstr-test.cpp --- tests for C++ string manipulation library
// Copyright (C) 2019 Katayama Hirofumi MZ <katayama.hirofumi.mz@gmail.com>.
// This file is public domain software.

#include "mstr.hpp"

bool
mstr_split_join_test(const std::string& raw, const std::string& sep,
                     size_t num_expected)
{
    std::vector<std::string> splitted;
    size_t num = mstr_split(splitted, raw, sep);
    if (num != num_expected)
    {
        std::printf("mstr_split_join_test: raw '%s', num_expected %u, num was %u\n",
                    raw.c_str(), (int)num_expected, (int)num);
        assert(0);
        return false;
    }
    std::string joined = mstr_join(splitted, sep);
    if (raw != joined)
    {
        std::printf("mstr_split_join_test: raw '%s', joined '%s'\n",
                    raw.c_str(), joined.c_str());
        assert(0);
        return false;
    }
    return true;
}

bool
mstr_replace_test(const std::string& raw,
                  const std::string& from,
                  const std::string& to,
                  const std::string& expected)
{
    std::string str = raw;
    mstr_replace(str, from, to);
    if (str != expected)
    {
        std::printf("mstr_replace_test: raw '%s', result '%s', expected '%s'\n",
                    raw.c_str(), str.c_str(), expected.c_str());
        assert(0);
        return false;
    }
    return true;
}

bool mstr_trim_test(const std::string& raw,
                    const std::string& spaces,
                    const std::string& expected)
{
    std::string str = raw;
    mstr_trim(str, spaces);
    if (str != expected)
    {
        std::printf("mstr_trim_test: raw '%s', result '%s', expected '%s'\n",
                    raw.c_str(), str.c_str(), expected.c_str());
        assert(0);
        return false;
    }
    return true;
}

bool mstr_trim_left_test(const std::string& raw,
                         const std::string& spaces,
                         const std::string& expected)
{
    std::string str = raw;
    mstr_trim_left(str, spaces);
    if (str != expected)
    {
        std::printf("mstr_trim_left_test: raw '%s', result '%s', expected '%s'\n",
                    raw.c_str(), str.c_str(), expected.c_str());
        assert(0);
        return false;
    }
    return true;
}

bool mstr_trim_right_test(const std::string& raw,
                          const std::string& spaces,
                          const std::string& expected)
{
    std::string str = raw;
    mstr_trim_right(str, spaces);
    if (str != expected)
    {
        std::printf("mstr_trim_right_test: raw '%s', result '%s', expected '%s'\n",
                    raw.c_str(), str.c_str(), expected.c_str());
        assert(0);
        return false;
    }
    return true;
}

bool
mstr_escape_test(const std::string& raw, const std::string& expected)
{
    std::string ret = mstr_escape(raw);
    if (ret != expected)
    {
        std::printf("mstr_escape_test: raw '%s', result '%s', expected '%s'\n",
                    raw.c_str(), ret.c_str(), expected.c_str());
        assert(0);
        return false;
    }
    return true;
}

#ifdef _WIN32
    bool
    mstr_escape_wide_test(const std::wstring& raw, const std::wstring& expected)
    {
        std::wstring ret;
        mstr_escape(ret, raw);
        if (ret != expected)
        {
            std::printf("mstr_escape_wide_test: FAILED\n");
            assert(0);
            return false;
        }
        return true;
    }
#endif

bool mstr_unittest(void)
{
    assert(mstr_escape("\n") == "\\n");
    assert(mstr_escape("\1") == "\\001");
    assert(mstr_quote("\n") == "\"\\n\"");
    assert(mstr_quote("\1") == "\"\\001\"");

    std::vector<std::string> vec;
    mstr_split(vec, "T,E,S,T", ",");
    assert(vec.size() == 4);

    return mstr_replace_test("", "TT", "MM", "") &&
           mstr_replace_test("A", "A", "BBB", "BBB") &&
           mstr_replace_test("A", "A", "BBBB", "BBBB") &&
           mstr_replace_test("123", "3", "34", "1234") &&
           mstr_replace_test("TESTTEST", "STT", "mmm", "TEmmmEST") &&
           mstr_trim_test("", "", "") &&
           mstr_trim_test("", " \t", "") &&
           mstr_trim_test("T T", "", "T T") &&
           mstr_trim_test("T T", " \t", "T T") &&
           mstr_trim_test(" T T", " \t", "T T") &&
           mstr_trim_test("T T ", " \t", "T T") &&
           mstr_trim_test(" T T ", " \t", "T T") &&
           mstr_trim_test("TAT", "T", "A") &&
           mstr_trim_test("TEST", "TEST", "") &&
           mstr_trim_test(" TEST ", "TEST", " TEST ") &&
           mstr_trim_test("<TEST>", "<>", "TEST") &&
           mstr_trim_left_test("", "", "") &&
           mstr_trim_left_test("", " \t", "") &&
           mstr_trim_left_test("T T", "", "T T") &&
           mstr_trim_left_test("T T", " \t", "T T") &&
           mstr_trim_left_test(" T T", " \t", "T T") &&
           mstr_trim_left_test("T T ", " \t", "T T ") &&
           mstr_trim_left_test(" T T ", " \t", "T T ") &&
           mstr_trim_left_test("TAT", "T", "AT") &&
           mstr_trim_left_test("TEST", "TEST", "") &&
           mstr_trim_left_test(" TEST ", "TEST", " TEST ") &&
           mstr_trim_left_test("<TEST>", "<>", "TEST>") &&
           mstr_trim_right_test("", "", "") &&
           mstr_trim_right_test("", " \t", "") &&
           mstr_trim_right_test("T T", "", "T T") &&
           mstr_trim_right_test("T T", " \t", "T T") &&
           mstr_trim_right_test(" T T", " \t", " T T") &&
           mstr_trim_right_test("T T ", " \t", "T T") &&
           mstr_trim_right_test(" T T ", " \t", " T T") &&
           mstr_trim_right_test("TAT", "T", "TA") &&
           mstr_trim_right_test("TEST", "TEST", "") &&
           mstr_trim_right_test(" TEST ", "TEST", " TEST ") &&
           mstr_trim_right_test("<TEST>", "<>", "<TEST") &&
           mstr_escape_test("", "") &&
           mstr_escape_test("A", "A") &&
           mstr_escape_test("AB", "AB") &&
           mstr_escape_test("ABC", "ABC") &&
           mstr_escape_test("ABC\n", "ABC\\n") &&
           mstr_escape_test("ABC\x01", "ABC\\001") &&
           mstr_escape_test("ABC\x01\x02", "ABC\\001\\002") &&
#ifdef _WIN32
           mstr_escape_wide_test(L"", L"") &&
           mstr_escape_wide_test(L"A", L"A") &&
           mstr_escape_wide_test(L"AB", L"AB") &&
           mstr_escape_wide_test(L"ABC", L"ABC") &&
           mstr_escape_wide_test(L"ABC\n", L"ABC\\n") &&
           mstr_escape_wide_test(L"ABC\x01", L"ABC\\u0001") &&
           mstr_escape_wide_test(L"ABC\x01\x02", L"ABC\\u0001\\u0002") &&
#endif
           mstr_split_join_test("", "|", 1) &&
           mstr_split_join_test("A", "|", 1) &&
           mstr_split_join_test("A|", "|", 2) &&
           mstr_split_join_test("A|B", "|", 2) &&
           mstr_split_join_test("A|B|C", "|", 3) &&
           mstr_split_join_test("A|B|C|", "|", 4) &&
           mstr_split_join_test("A", "<>", 1) &&
           mstr_split_join_test("A<>", "<>", 2) &&
           mstr_split_join_test("A<>B", "<>", 2) &&
           mstr_split_join_test("A<>B<>C", "<>", 3) &&
           mstr_split_join_test("A<>B<>C<>", "<>", 4) &&
           mstr_split_join_test("A>B>C", ">", 3) &&
           mstr_split_join_test("A>B>C>", ">", 4) &&
#ifndef MSTR_SPLIT_NO_SPECIAL_HANDLING
           mstr_split_join_test("", "", 0) &&
           mstr_split_join_test("AB", "", 2) &&
           mstr_split_join_test("ABC", "", 3) &&
#endif
           mstr_split_join_test("ABC", ">", 1) &&
           true;
}

int main(void)
{
    mstr_unittest();
    return 0;
}
