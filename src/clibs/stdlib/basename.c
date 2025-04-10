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

#include <libgen.h>
#include <string.h>
char* _RTL_FUNC basename(char* path)
{
    if (!path || !path[0])
        return ".";
    if (!strcmp(path, "/") || !strcmp(path, "\\") || !strcmp(path, ".") || !strcmp(path, ".."))
        return path;
    char* p = strrchr(path, '/');
    if (!p)
        p = strrchr(path, '\\');
    if (!p)
        return path;
    if (p[1])
        return p + 1;
    *p = 0;
    return path + 1;
}
