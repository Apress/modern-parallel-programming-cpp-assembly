//------------------------------------------------
//               MF.h
//------------------------------------------------

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <ctime>
#include <cmath>
#include <chrono>
#include <thread>

#if defined(_MSC_VER)
#include <windows.h>
#elif defined(__GNUG__)
#include <unistd.h>
#else
#error Unexpected target in MF.h
#endif

// This namespace contain miscellaneous functions.
namespace MF
{
    inline std::string GetDT(void)
    {
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        std::chrono::system_clock::duration temp0 = now.time_since_epoch();
        auto temp1 = std::chrono::duration_cast<std::chrono::milliseconds>(temp0).count();
        int millis = (int)(temp1 % 1000);

        char b1[100];
        char b2[200];
        const char* fmt1 = "%F %H:%M:%S";
        const char* fmt2 = "%s.%03d";
        std::time_t tt = std::chrono::system_clock::to_time_t(now);

#if defined(_MSC_VER)
        struct tm timeinfo;
        localtime_s(&timeinfo, &tt);
        strftime(b1, sizeof(b1), fmt1, &timeinfo);
        sprintf_s(b2, sizeof(b2), fmt2, b1, millis);
#endif

#if defined(__GNUC__)
        strftime(b1, sizeof(b1), fmt1, localtime(&tt));
        sprintf(b2, fmt2, b1, millis);
#endif

        return std::string(b2);
    }

    inline unsigned int uipow2(unsigned int n)
    {
        unsigned int x = 1;
        return x << n;
    }

    inline unsigned long long uipow2(unsigned long long n)
    {
        unsigned long long x = 1;
        return x << n;
    }

    inline bool IsExt(const std::string& fn, const std::string& fn_ext_test)
    {
        std::string fn_ext = fn.substr(fn.find_last_of(".") + 1);

        return fn_ext.compare(fn_ext_test) == 0;
    }

    inline bool IsBmpFile(const std::string& fn)
    {
        bool rc = false;
        std::ifstream ifs(fn, std::ios::in | std::ios::binary);

        if (ifs)
        {
	        const char signature[] = { 'B', 'M' };
            char buff[sizeof(signature)];

            ifs.read(buff, sizeof(buff));

            if (ifs)
                rc = memcmp(buff, signature, sizeof(signature)) == 0;

            ifs.close();
        }

        return rc;
    }

    inline bool IsPngFile(const std::string& fn)
    {
        bool rc = false;
        std::ifstream ifs(fn, std::ios::in | std::ios::binary);

        if (ifs)
        {
	        const char signature[] = { '\x89', '\x50', '\x4e', '\x47', '\x0d', '\x0a', '\x1a', '\x0a' };
            char buff[sizeof(signature)];

            ifs.read(buff, sizeof(buff));

            if (ifs)
                rc = memcmp(buff, signature, sizeof(signature)) == 0;

            ifs.close();
        }

        return rc;
    }

    inline void Sleep(unsigned int milliseconds)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    }

    inline std::wstring ToWstring(const char* s)
    {
        // TEMP CODE - only works with ASCII strings
        return std::wstring(s, s + strlen(s));
    }
};
