/*	paparas DELPY `gamidiaaktinidio`
	http://blog.gamidiaaktinidio.com
	paparas@gamidiaaktinidio.com
	Licence : https://creativecommons.org/licenses/by/4.0/
*/
#pragma once
#if defined(LSASS_DECRYPT)
#include "../globals_sekurlsa.h"
typedef struct _aktinidio_DECRYPTOR {
	DWORD cbData;
	BYTE dedomena[ANYSIZE_ARRAY]; // etc...
} aktinidio_DECRYPTOR, *Paktinidio_DECRYPTOR;

NTSTATUS kuhl_m_sekurlsa_nt63_init();
NTSTATUS kuhl_m_sekurlsa_nt63_clean();
PLSA_PROTECT_MEMORY kuhl_m_sekurlsa_nt63_pLsaProtectMemory, kuhl_m_sekurlsa_nt63_pLsaUnprotectMemory;

NTSTATUS kuhl_m_sekurlsa_nt63_acquireKeys(PKUHL_M_SEKURLSA_CONTEXT cLsass, PKULL_M_PROCESS_VERY_BASIC_MODULE_INFORMATION lsassLsaSrvModule);
NTSTATUS kuhl_m_sekurlsa_nt63_LsaEncryptMemory(IN PVOID Buffer, IN ULONG BufferSize, IN BOOL Encrypt);
VOID WINAPI kuhl_m_sekurlsa_nt63_LsaProtectMemory (IN PVOID Buffer, IN ULONG BufferSize);
VOID WINAPI kuhl_m_sekurlsa_nt63_LsaUnprotectMemory (IN PVOID Buffer, IN ULONG BufferSize);
#endif