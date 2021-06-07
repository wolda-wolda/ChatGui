/*C Chat GUI Copyright (C) 2021 Marcel Walder
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once
#ifndef __STRINGS_H_868520A6_2F4E_4B49_AF4B_02B5A21CF6BB__
#define __STRINGS_H_868520A6_2F4E_4B49_AF4B_02B5A21CF6BB__

#ifndef _WIN32

#pragma message("this strings.h implementation is for Windows only!")

#else /* _WIN32 */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <string.h>
#include <ctype.h>

    static int bcmp(const void * s1, const void * s2, size_t n)
    {
        return memcmp(s1, s2, n);
    }

    static void bcopy(const void * src, void * dest, size_t n)
    {
        memcpy(dest, src, n);
    }

    static void bzero(void * s, size_t n)
    {
        memset(s, 0, n);
    }

    static void explicit_bzero(void * s, size_t n)
    {
        volatile char * vs = (volatile char *) s;
        while (n)
        {
            *vs++ = 0;
            n--;
        }
    }

    static char * index(const char * s, int c)
    {
        return strchr(s, c);
    }

    static char * rindex(const char * s, int c)
    {
        return strrchr(s, c);
    }

    static int ffs(int i)
    {
        int bit;

        if (0 == i)
            return 0;

        for (bit = 1; !(i & 1); ++bit)
            i >>= 1;
        return bit;
    }

    static int ffsl(long i)
    {
        int bit;

        if (0 == i)
            return 0;

        for (bit = 1; !(i & 1); ++bit)
            i >>= 1;
        return bit;
    }

    static int ffsll(long long i)
    {
        int bit;

        if (0 == i)
            return 0;

        for (bit = 1; !(i & 1); ++bit)
            i >>= 1;
        return bit;
    }

#ifndef __MINGW32__

    static int strcasecmp(const char * s1, const char * s2)
    {
        const unsigned char * u1 = (const unsigned char*) s1;
        const unsigned char * u2 = (const unsigned char*) s2;
        int result;

        while ((result = tolower(*u1) - tolower(*u2)) == 0 && *u1 != 0)
        {
            *u1++;
            *u2++;
        }

        return result;
    }

    static int strncasecmp(const char * s1, const char * s2, size_t	 n)
    {
        const unsigned char * u1 = (const unsigned char*) s1;
        const unsigned char * u2 = (const unsigned char*) s2;
        int result;

        for (; n != 0; n--)
        {
            result = tolower(*u1) - tolower(*u2);
            if (result)
                return result;
            if (*u1 == 0)
                return 0;
        }
        return 0;
    }

    static int strcasecmp_l(const char * s1, const char * s2, _locale_t loc)
    {
        const unsigned char * u1 = (const unsigned char*) s1;
        const unsigned char * u2 = (const unsigned char*) s2;
        int result;

        while ((result = _tolower_l(*u1, loc) - _tolower_l(*u2, loc)) == 0 && *u1 != 0)
        {
            *u1++;
            *u2++;
        }

        return result;
    }

    static int strncasecmp_l(const char * s1, const char * s2, size_t n, _locale_t loc)
    {
        const unsigned char * u1 = (const unsigned char*) s1;
        const unsigned char * u2 = (const unsigned char*) s2;
        int result;

        for (; n != 0; n--)
        {
            result = _tolower_l(*u1, loc) - _tolower_l(*u2, loc);
            if (result)
                return result;
            if (*u1 == 0)
                return 0;
        }
        return 0;
    }


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _WIN32 */

#endif /* __STRINGS_H_868520A6_2F4E_4B49_AF4B_02B5A21CF6BB__ */
