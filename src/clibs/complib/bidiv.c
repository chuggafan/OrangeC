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

#include "bi.h"

void __stdcall _RTL_FUNC ___biminus(UNDERLYING_TYPE* ans, UNDERLYING_TYPE* left, int bits);
void __stdcall _RTL_FUNC ___biudiv(UNDERLYING_TYPE* ans, UNDERLYING_TYPE* left, UNDERLYING_TYPE* right, int bits);
void __stdcall _RTL_FUNC ___bidiv(UNDERLYING_TYPE* ans, UNDERLYING_TYPE* left, UNDERLYING_TYPE* right, int bits)
{
    int lsigned = ISSIGNED(left, bits);
    int rsigned = ISSIGNED(right, bits);
    if (lsigned)
        ___biminus(left, left, bits);
    if (rsigned)
        ___biminus(right, right, bits);
    ___biudiv(ans, left, right, bits);
    if (lsigned != rsigned)
        ___biminus(ans, ans, bits);
    if (lsigned)
        ___biminus(left, left, bits);
    if (rsigned)
        ___biminus(right, right, bits);
}
