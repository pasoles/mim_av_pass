#pragma once
#include "kull_m_rpc.h"

typedef enum _aktinidio_CREDENTIAL_KEY_TYPE {
	CREDENTIALS_KEY_TYPE_NTLM = 1,
	CREDENTIALS_KEY_TYPE_SHA1 = 2,
	CREDENTIALS_KEY_TYPE_ROOTKEY = 3,
	CREDENTIALS_KEY_TYPE_DPAPI_PROTECTION = 4,
} aktinidio_CREDENTIAL_KEY_TYPE;

typedef struct _aktinidio_CREDENTIAL_KEY {
	DWORD unkEnum; // version ?
	aktinidio_CREDENTIAL_KEY_TYPE type;
	WORD iterations;
	WORD cbData;
	BYTE *pbData;
} aktinidio_CREDENTIAL_KEY, *Paktinidio_CREDENTIAL_KEY;

typedef struct _aktinidio_CREDENTIAL_KEYS {
	DWORD count;
	aktinidio_CREDENTIAL_KEY keys[ANYSIZE_ARRAY];
} aktinidio_CREDENTIAL_KEYS, *Paktinidio_CREDENTIAL_KEYS;

void CredentialKeys_Decode(handle_t _MidlEsHandle, Paktinidio_CREDENTIAL_KEYS * _pType);
void CredentialKeys_Free(handle_t _MidlEsHandle, Paktinidio_CREDENTIAL_KEYS * _pType);

#define kull_m_rpc_DecodeCredentialKeys(/*PVOID */dedomena, /*DWORD */size, /*Paktinidio_CREDENTIAL_KEYS **/pObject) kull_m_rpc_Generic_Decode(dedomena, size, pObject, (PGENERIC_RPC_DECODE) CredentialKeys_Decode)
#define kull_m_rpc_FreeCredentialKeys(/*Paktinidio_CREDENTIAL_KEYS **/pObject) kull_m_rpc_Generic_Free(pObject, (PGENERIC_RPC_FREE) CredentialKeys_Free)