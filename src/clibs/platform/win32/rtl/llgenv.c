/*  Software License Agreement
 *  
 *      Copyright(C) 1994-2025 David Lindauer, (LADSoft)
 *  
 *      This file is part of the Orange C Compiler package.
 *  
 *      The Orange C Compiler package is free software: you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation, either version 3 of the License, or
 *      (at your option) any later version.
 *  
 *      The Orange C Compiler package is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *  
 *      You should have received a copy of the GNU General Public License
 *      along with Orange C.  If not, see <http://www.gnu.org/licenses/>.
 *  
 *      contact information:
 *          email: TouchStone222@runbox.com <David Lindauer>
 *  
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <time.h>

extern int _RTL_DATA _osenv;

int __ll_getenvsize(int id)
{
    char* env = _osenv;
    while (id--)
    {
        while (*env)
            env++;
        if (*++env == 0)
            return 0;
    }
    return strlen(env);
}
int __ll_getenv(char* buf, int id)
{
    int count = 0;
    int rv;
    char* env = _osenv;
    if (buf)
    {
        while (id--)
        {
            while (*env)
                env++;
            if (*++env == 0)
                return 0;
        }
        strcpy(buf, env);
        return (int)env;
    }
    else
    {
        if (!*env)
            return 0;
        do
        {
            count++;
            while (*env)
                env++;
            env++;
        } while (*env);
        return count;
    }
}
