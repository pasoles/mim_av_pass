/*	paparas DELPY `gamidiaaktinidio`
	http://blog.gamidiaaktinidio.com
	paparas@gamidiaaktinidio.com
	Licence : https://creativecommons.org/licenses/by/4.0/
*/
#pragma once
#include "../kuhl_m_sekurlsa.h"

KUHL_M_SEKURLSA_PACKAGE kuhl_m_sekurlsa_wdigest_package;

NTSTATUS kuhl_m_sekurlsa_wdigest(int argc, wchar_t * argv[]);
void CALLBACK kuhl_m_sekurlsa_enum_logon_callback_wdigest(IN Paktinidio_BASIC_SECURITY_LOGON_SESSION_DATA pData);

typedef struct _aktinidio_WDIGEST_LIST_ENTRY {
	struct _aktinidio_WDIGEST_LIST_ENTRY *Flink;
	struct _aktinidio_WDIGEST_LIST_ENTRY *Blink;
	ULONG	UsageCount;
	struct _aktinidio_WDIGEST_LIST_ENTRY *This;
	LUID LocallyUniqueIdentifier;
} aktinidio_WDIGEST_LIST_ENTRY, *Paktinidio_WDIGEST_LIST_ENTRY;