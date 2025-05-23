#ifndef _SECURITY_H
#define _SECURITY_H

#ifdef __ORANGEC__ 
#pragma GCC system_header
#endif

/* Security aware components definitions (toplevel) */

#ifndef NTLMSP_NAME_A
#define NTLMSP_NAME_A  "NTLM"
#define NTLMSP_NAME  L"NTLM"
#endif

#ifndef MICROSOFT_KERBEROS_NAME_A
#define MICROSOFT_KERBEROS_NAME_A  "Kerberos"
#define MICROSOFT_KERBEROS_NAME_W  L"Kerberos"
#ifdef WIN32_CHICAGO
#define MICROSOFT_KERBEROS_NAME MICROSOFT_KERBEROS_NAME_A
#else
#define MICROSOFT_KERBEROS_NAME MICROSOFT_KERBEROS_NAME_W
#endif
#endif /* MICROSOFT_KERBEROS_NAME_A */

#ifndef NEGOSSP_NAME
#define NEGOSSP_NAME_W  L"Negotiate"
#define NEGOSSP_NAME_A  "Negotiate"

#ifdef UNICODE
#define NEGOSSP_NAME  NEGOSSP_NAME_W
#else
#define NEGOSSP_NAME  NEGOSSP_NAME_A
#endif
#endif /* NEGOSSP_NAME */

#include <sspi.h>

#if defined(SECURITY_WIN32) || defined(SECURITY_KERNEL)
#include <secext.h>
#endif

#endif /* _SECURITY_H */
