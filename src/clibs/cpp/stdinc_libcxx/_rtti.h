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

#define XD_X_MASK 0x3f /* a count for extension bytes */
#define XD_ARRAY 0x40
#define XD_POINTER 0x80
#define XD_REF 0x100
#define XD_CL_PRIMARY 0x400
#define XD_CL_BASE 0x800
#define XD_CL_VIRTUAL 0x1000
#define XD_CL_ENCLOSED 0x2000
#define XD_CL_BASETYPE 0x4000
#define XD_CL_VTAB 0x8000
#define XD_CL_TRYBLOCK 0x10000
#define XD_CL_CONST 0x20000
#define XD_CL_BYREF 0x40000
#define XD_CM_SYM (XD_CL_PRIMARY | XD_CL_BASE | XD_CL_ENCLOSED | XD_CL_VIRTUAL)
#define XD_THIS 0x80000
#define XD_VARARRAY 0x100000
#define XD_INUSE 0x200000
#define VTAB_XT_OFFS 12 /* VTAB offset - pointer to exception data offset */

typedef struct _rttiArray
{
    int elems;  // number of elems
} RTTIARRAY;
typedef struct _rttiStruct
{
    int flags;
    struct _rtti* xt;
    int offset;
} RTTISTRUCT;
typedef struct _rtti
{
    union
    {
        void (*destructor)(void*); /* void * = the this pointer */
        struct _rtti* base;        /* the base type declarator for pointer types */
    };
    int size;  // total size of type
    int flags;
    char name[1];  // enumerated name, followed by a NULL.
    // if describing an array, following this will be an RTTIARRAY
    // if describing a struct, following this will be list of RTTISTRUCT structures
    //  end of structure is a NULL DWORD;
} RTTI;

// xcept block header
#define XD_NOXC 1
#define XD_ALLXC 2
#define XD_DYNAMICXC 4
typedef struct
{

    int flags;              // 0 = no specification 1= noexcept(FALSE), 2 = noexcept(TRUE);
    RTTI thrownClasses[1];  // list of thrown classes, followed by a zero
} THROWREC;
typedef struct
{
    THROWREC* throwRecord;  // exception specification
    int frameOffs;          // offset from xception table to frame
} XCEPTHEAD;

// things in xcept block
typedef struct _xcept
{
    int flags;  // can be XD_CL_PRIMARY or XD_CL_TRYBLOCK
    struct _rtti* xt;
    union
    {

        int ebpoffs;  /* symbol offset from exception block */
        int trylabel; /* catch block label */
    };
    int startOffs;  // offset from function where item comes in scope
    int endOffs;    // offset from function item leaves scope
} XCEPT;

#define XC_SIG 0x4c41445a

// on stack for func
typedef struct _xctab
{
    struct _xctab* next;   /* link to next exception higher function */
    void* _xceptfunc;      /* windows exception handler */
    int esp;               /* esp at start of try block; code gen generates for this, don't move*/
    int ebp;               /* ebp of this function; code gen generates this */
    XCEPTHEAD* xceptBlock; /* pointer to the function's xception block, code gen generates this */
    int funcIndex;         /* index of constructors/destructors, roughly follows EIP , code gen generates this*/
    void *throwninstance;  /* instance being caught, code gen generates this, don't move */
    // things beyond this are used by throw()
    int eip;              /* eip this function where the catch occurred */
    XCEPT* thisxt;        /* pointer to this XT table list in case of throws
               through nested tries */
} XCTAB;

