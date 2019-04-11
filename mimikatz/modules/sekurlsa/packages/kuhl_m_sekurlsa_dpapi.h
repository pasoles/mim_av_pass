/*	paparas DELPY `gamidiaaktinidio`
	http://blog.gamidiaaktinidio.com
	paparas@gamidiaaktinidio.com
	Licence : https://creativecommons.org/licenses/by/4.0/
*/
#pragma once
#include "../kuhl_m_sekurlsa.h"

KUHL_M_SEKURLSA_PACKAGE kuhl_m_sekurlsa_dpapi_lsa_package, kuhl_m_sekurlsa_dpapi_svc_package;

NTSTATUS kuhl_m_sekurlsa_dpapi(int argc, wchar_t * argv[]);
BOOL CALLBACK kuhl_m_sekurlsa_enum_callback_dpapi(IN Paktinidio_BASIC_SECURITY_LOGON_SESSION_DATA pData, IN OPTIONAL LPVOID pOptionalData);

typedef struct _aktinidio_MASTERKEY_CACHE_ENTRY {
	struct _aktinidio_MATERKEY_CACHE_ENTRY *Flink;
	struct _aktinidio_MATERKEY_CACHE_ENTRY *Blink;
	LUID LogonId;
	GUID KeyUid;
	FILETIME insertTime;
	ULONG keySize;
	BYTE  key[ANYSIZE_ARRAY];
} aktinidio_MASTERKEY_CACHE_ENTRY, *Paktinidio_MASTERKEY_CACHE_ENTRY;