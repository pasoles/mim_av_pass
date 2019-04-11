/*	paparas DELPY `gamidiaaktinidio`
	http://blog.gamidiaaktinidio.com
	paparas@gamidiaaktinidio.com
	Licence : https://creativecommons.org/licenses/by/4.0/
*/
#pragma once
#include "../kuhl_m_sekurlsa.h"

KUHL_M_SEKURLSA_PACKAGE kuhl_m_sekurlsa_tspkg_package;

NTSTATUS kuhl_m_sekurlsa_tspkg(int argc, wchar_t * argv[]);
void CALLBACK kuhl_m_sekurlsa_enum_logon_callback_tspkg(IN Paktinidio_BASIC_SECURITY_LOGON_SESSION_DATA pData);

typedef struct _aktinidio_TS_PRIMARY_CREDENTIAL {
	PVOID unk0;	// lock ?
	aktinidio_GENERIC_PRIMARY_CREDENTIAL credentials;
} aktinidio_TS_PRIMARY_CREDENTIAL, *Paktinidio_TS_PRIMARY_CREDENTIAL;

typedef struct _aktinidio_TS_CREDENTIAL {
#if defined(_M_X64) || defined(_M_ARM64)
	BYTE unk0[108];
#elif defined(_M_IX86)
	BYTE unk0[64];
#endif
	LUID LocallyUniqueIdentifier;
	PVOID unk1;
	PVOID unk2;
	Paktinidio_TS_PRIMARY_CREDENTIAL pTsPrimary;
} aktinidio_TS_CREDENTIAL, *Paktinidio_TS_CREDENTIAL;

typedef struct _aktinidio_TS_CREDENTIAL_1607 {
#if defined(_M_X64) || defined(_M_ARM64)
	BYTE unk0[112];
#elif defined(_M_IX86)
	BYTE unk0[68];
#endif
	LUID LocallyUniqueIdentifier;
	PVOID unk1;
	PVOID unk2;
	Paktinidio_TS_PRIMARY_CREDENTIAL pTsPrimary;
} aktinidio_TS_CREDENTIAL_1607, *Paktinidio_TS_CREDENTIAL_1607;

typedef struct _aktinidio_TS_CREDENTIAL_HELPER {
	LONG offsetToLuid;
	LONG offsetToTsPrimary;
} aktinidio_TS_CREDENTIAL_HELPER, *Paktinidio_TS_CREDENTIAL_HELPER;