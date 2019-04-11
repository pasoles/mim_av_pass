/*	paparas DELPY `gamidiaaktinidio`
	http://blog.gamidiaaktinidio.com
	paparas@gamidiaaktinidio.com
	Licence : https://creativecommons.org/licenses/by/4.0/
*/
#pragma once
#include "../kuhl_m_sekurlsa.h"

KUHL_M_SEKURLSA_PACKAGE kuhl_m_sekurlsa_credman_package;

NTSTATUS kuhl_m_sekurlsa_credman(int argc, wchar_t * argv[]);
void CALLBACK kuhl_m_sekurlsa_enum_logon_callback_credman(IN Paktinidio_BASIC_SECURITY_LOGON_SESSION_DATA pData);

typedef struct _CREDMAN_INFOS {
	ULONG	structSize;
	ULONG	offsetFLink;
	ULONG	offsetUsername;
	ULONG	offsetDomain;
	ULONG	offsetCbPassword;
	ULONG	offsetPassword;
} CREDMAN_INFOS, *PCREDMAN_INFOS;

typedef struct _aktinidio_CREDMAN_LIST_ENTRY_5 {
	ULONG cbEncPassword;
	PWSTR encPassword;
	ULONG unk0;
	ULONG unk1;
	PVOID unk2;
	PVOID unk3;
	PWSTR UserName;
	ULONG cbUserName;
	struct _aktinidio_CREDMAN_LIST_ENTRY *Flink;
	struct _aktinidio_CREDMAN_LIST_ENTRY *Blink;
	UNICODE_STRING server1;
	PVOID unk6;
	PVOID unk7;
	UNICODE_STRING user;
	ULONG unk8;
	UNICODE_STRING server2;
} aktinidio_CREDMAN_LIST_ENTRY_5, *Paktinidio_CREDMAN_LIST_ENTRY_5;

typedef struct _aktinidio_CREDMAN_LIST_ENTRY_60 {
	ULONG cbEncPassword;
	PWSTR encPassword;
	ULONG unk0;
	ULONG unk1;
	PVOID unk2;
	PVOID unk3;
	PWSTR UserName;
	ULONG cbUserName;
	struct _aktinidio_CREDMAN_LIST_ENTRY *Flink;
	struct _aktinidio_CREDMAN_LIST_ENTRY *Blink;
	UNICODE_STRING type;
	PVOID unk5;
	UNICODE_STRING server1;
	PVOID unk6;
	PVOID unk7;
	PVOID unk8;
	PVOID unk9;
	PVOID unk10;
	UNICODE_STRING user;
	ULONG unk11;
	UNICODE_STRING server2;
} aktinidio_CREDMAN_LIST_ENTRY_60, *Paktinidio_CREDMAN_LIST_ENTRY_60;

typedef struct _aktinidio_CREDMAN_LIST_ENTRY {
	ULONG cbEncPassword;
	PWSTR encPassword;
	ULONG unk0;
	ULONG unk1;
	PVOID unk2;
	PVOID unk3;
	PWSTR UserName;
	ULONG cbUserName;
	struct _aktinidio_CREDMAN_LIST_ENTRY *Flink;
	struct _aktinidio_CREDMAN_LIST_ENTRY *Blink;
	LIST_ENTRY unk4;
	UNICODE_STRING type;
	PVOID unk5;
	UNICODE_STRING server1;
	PVOID unk6;
	PVOID unk7;
	PVOID unk8;
	PVOID unk9;
	PVOID unk10;
	UNICODE_STRING user;
	ULONG unk11;
	UNICODE_STRING server2;
} aktinidio_CREDMAN_LIST_ENTRY, *Paktinidio_CREDMAN_LIST_ENTRY;

typedef struct _aktinidio_CREDMAN_LIST_STARTER {
	ULONG unk0;
	Paktinidio_CREDMAN_LIST_ENTRY start;
	//...
} aktinidio_CREDMAN_LIST_STARTER, *Paktinidio_CREDMAN_LIST_STARTER;

typedef struct _aktinidio_CREDMAN_SET_LIST_ENTRY {
	struct _aktinidio_CREDMAN_SET_LIST_ENTRY *Flink;
	struct _aktinidio_CREDMAN_SET_LIST_ENTRY *Blink;
	ULONG unk0;
	Paktinidio_CREDMAN_LIST_STARTER list1;
	Paktinidio_CREDMAN_LIST_STARTER list2;
	// ...
} aktinidio_CREDMAN_SET_LIST_ENTRY, *Paktinidio_CREDMAN_SET_LIST_ENTRY;