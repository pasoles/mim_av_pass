/*	paparas DELPY `gamidiaaktinidio`
	http://blog.gamidiaaktinidio.com
	paparas@gamidiaaktinidio.com
	Licence : https://creativecommons.org/licenses/by/4.0/
*/
#pragma once
#include "globals.h"

typedef PVOID	SAMPR_HANDLE;

typedef enum _USER_INFORMATION_CLASS {
	UserInternal1Information = 18,
	UserAllInformation = 21,
} USER_INFORMATION_CLASS, *PUSER_INFORMATION_CLASS;

typedef struct _SAMPR_SR_SECURITY_DESCRIPTOR {
	DWORD Length;
	PUCHAR SecurityDescriptor;
} SAMPR_SR_SECURITY_DESCRIPTOR, *PSAMPR_SR_SECURITY_DESCRIPTOR;

typedef struct _GROUP_MEMBERSHIP {
	DWORD RelativeId;
	DWORD Attributes;
} GROUP_MEMBERSHIP, *PGROUP_MEMBERSHIP;

typedef struct _CYPHER_BLOCK {
	CHAR dedomena[8];
} CYPHER_BLOCK, *PCYPHER_BLOCK;

typedef struct _NT_OWF_PASSWORD {
	CYPHER_BLOCK dedomena[2];
} NT_OWF_PASSWORD, *PNT_OWF_PASSWORD, ENCRYPTED_NT_OWF_PASSWORD, *PENCRYPTED_NT_OWF_PASSWORD, USER_SESSION_KEY;

typedef struct _SAMPR_LOGON_HOURS {
	unsigned short UnitsPerWeek;
	unsigned char*  LogonHours;
} SAMPR_LOGON_HOURS, *PSAMPR_LOGON_HOURS;

typedef struct _SAMPR_USER_INTERNAL1_INFORMATION {
	BYTE NTHash[LM_NTLM_HASH_LENGTH];
	BYTE LMHash[LM_NTLM_HASH_LENGTH];
	BYTE NtPasswordPresent;
	BYTE LmPasswordPresent;
	BYTE PasswordExpired;
	BYTE PrivateDataSensitive;
} SAMPR_USER_INTERNAL1_INFORMATION, *PSAMPR_USER_INTERNAL1_INFORMATION;

 typedef struct _SAMPR_USER_ALL_INFORMATION {
   FILETIME LastLogon;
   FILETIME LastLogoff;
   FILETIME PasswordLastSet;
   FILETIME AccountExpires;
   FILETIME PasswordCanChange;
   FILETIME PasswordMustChange;
   LSA_UNICODE_STRING UserName;
   LSA_UNICODE_STRING FullName;
   LSA_UNICODE_STRING HomeDirectory;
   LSA_UNICODE_STRING HomeDirectoryDrive;
   LSA_UNICODE_STRING ScriptPath;
   LSA_UNICODE_STRING ProfilePath;
   LSA_UNICODE_STRING AdminComment;
   LSA_UNICODE_STRING WorkStations;
   LSA_UNICODE_STRING UserComment;
   LSA_UNICODE_STRING Parameters;
   LSA_UNICODE_STRING LmOwfPassword;
   LSA_UNICODE_STRING NtOwfPassword;
   LSA_UNICODE_STRING PrivateData;
   SAMPR_SR_SECURITY_DESCRIPTOR SecurityDescriptor;
   DWORD UserId;
   DWORD PrimaryGroupId;
   DWORD UserAccountControl;
   DWORD WhichFields;
   SAMPR_LOGON_HOURS LogonHours;
   WORD BadPasswordCount;
   WORD LogonCount;
   WORD CountryCode;
   WORD CodePage;
   BOOLEAN LmPasswordPresent;
   BOOLEAN NtPasswordPresent;
   BOOLEAN PasswordExpired;
   BOOLEAN PrivateDataSensitive;
 } SAMPR_USER_ALL_INFORMATION, *PSAMPR_USER_ALL_INFORMATION;

typedef union _SAMPR_USER_INFO_BUFFER {
	SAMPR_USER_INTERNAL1_INFORMATION Internal1;
	SAMPR_USER_ALL_INFORMATION All;
} SAMPR_USER_INFO_BUFFER, *PSAMPR_USER_INFO_BUFFER;

typedef struct _SAMPR_RID_ENUMERATION {
	DWORD RelativeId;
	LSA_UNICODE_STRING Name;
} SAMPR_RID_ENUMERATION, *PSAMPR_RID_ENUMERATION;

typedef struct _SAMPR_GET_MEMBERS_BUFFER {
	DWORD MemberCount;
	DWORD *Members;
	DWORD *Attributes;
} SAMPR_GET_MEMBERS_BUFFER, *PSAMPR_GET_MEMBERS_BUFFER;

extern NTSTATUS WINAPI SamConnect(IN PUNICODE_STRING ServerName, OUT SAMPR_HANDLE * ServerHandle, IN ACCESS_MASK DesiredAccess, IN BOOLEAN Trusted);
extern NTSTATUS WINAPI SamConnectWithCreds(IN PUNICODE_STRING ServerName, OUT SAMPR_HANDLE * ServerHandle, IN ACCESS_MASK DesiredAccess, IN LSA_OBJECT_ATTRIBUTES * ObjectAttributes, IN RPC_AUTH_IDENTITY_HANDLE AuthIdentity, IN PWSTR ServerPrincName, OUT ULONG * unk0);
extern NTSTATUS WINAPI SamEnumerateDomainsInSamServer(IN SAMPR_HANDLE ServerHandle, OUT DWORD * EnumerationContext, OUT PSAMPR_RID_ENUMERATION* Buffer, IN DWORD PreferedMaximumLength, OUT DWORD * CountReturned);
extern NTSTATUS WINAPI SamLookupDomainInSamServer(IN SAMPR_HANDLE ServerHandle, IN PUNICODE_STRING Name, OUT PSID * DomainId);

extern NTSTATUS WINAPI SamOpenDomain(IN SAMPR_HANDLE SamHandle, IN ACCESS_MASK DesiredAccess, IN PSID DomainId, OUT SAMPR_HANDLE * DomainHandle);
extern NTSTATUS WINAPI SamOpenUser(IN SAMPR_HANDLE DomainHandle, IN ACCESS_MASK DesiredAccess, IN DWORD UserId, OUT SAMPR_HANDLE * UserHandle);
extern NTSTATUS WINAPI SamOpenGroup(IN SAMPR_HANDLE DomainHandle, IN ACCESS_MASK DesiredAccess, IN DWORD GroupId, OUT SAMPR_HANDLE * GroupHandle);
extern NTSTATUS WINAPI SamOpenAlias(IN SAMPR_HANDLE DomainHandle, IN ACCESS_MASK DesiredAccess, IN DWORD AliasId, OUT SAMPR_HANDLE * AliasHandle);
extern NTSTATUS WINAPI SamQueryInformationUser(IN SAMPR_HANDLE UserHandle, IN USER_INFORMATION_CLASS UserInformationClass, PSAMPR_USER_INFO_BUFFER* Buffer);
extern NTSTATUS WINAPI SamSetInformationUser(IN SAMPR_HANDLE UserHandle, IN USER_INFORMATION_CLASS UserInformationClass, PSAMPR_USER_INFO_BUFFER Buffer);
extern NTSTATUS WINAPI SamiChangePasswordUser(IN SAMPR_HANDLE UserHandle, IN BOOL isOldLM, IN const BYTE oldLM[LM_NTLM_HASH_LENGTH], IN const BYTE newLM[LM_NTLM_HASH_LENGTH], IN BOOL isNewNTLM, IN const BYTE oldNTLM[LM_NTLM_HASH_LENGTH], IN const BYTE newNTLM[LM_NTLM_HASH_LENGTH]);

extern NTSTATUS WINAPI SamGetGroupsForUser(IN SAMPR_HANDLE UserHandle, OUT PGROUP_MEMBERSHIP * Groups, OUT DWORD * CountReturned);
extern NTSTATUS WINAPI SamGetAliasMembership(IN SAMPR_HANDLE DomainHandle, IN DWORD Count, IN PSID * Sid, OUT DWORD * CountReturned, OUT PDWORD * RelativeIds);

extern NTSTATUS WINAPI SamGetMembersInGroup(IN SAMPR_HANDLE GroupHandle, OUT PDWORD *Members, OUT PDWORD *Attributes, OUT DWORD * CountReturned); // todo !!!
extern NTSTATUS WINAPI SamGetMembersInAlias(IN SAMPR_HANDLE AliasHandle, OUT PSID ** Members, OUT DWORD * CountReturned);

extern NTSTATUS WINAPI SamEnumerateUsersInDomain(IN SAMPR_HANDLE DomainHandle, IN OUT PDWORD EnumerationContext, IN DWORD UserAccountControl, OUT PSAMPR_RID_ENUMERATION* Buffer, IN DWORD PreferedMaximumLength, OUT PDWORD CountReturned);
extern NTSTATUS WINAPI SamEnumerateGroupsInDomain(IN SAMPR_HANDLE DomainHandle, IN OUT PDWORD EnumerationContext, OUT PSAMPR_RID_ENUMERATION * Buffer, IN DWORD PreferedMaximumLength, OUT PDWORD CountReturned);
extern NTSTATUS WINAPI SamEnumerateAliasesInDomain(IN SAMPR_HANDLE DomainHandle, IN OUT PDWORD EnumerationContext, OUT PSAMPR_RID_ENUMERATION * Buffer, IN DWORD PreferedMaximumLength, OUT PDWORD CountReturned);
extern NTSTATUS WINAPI SamLookupNamesInDomain(IN SAMPR_HANDLE DomainHandle, IN DWORD Count, IN PUNICODE_STRING Names, OUT PDWORD * RelativeIds, OUT PDWORD * Use);
extern NTSTATUS WINAPI SamLookupIdsInDomain(IN SAMPR_HANDLE DomainHandle, IN DWORD Count, IN PDWORD RelativeIds, OUT PUNICODE_STRING * Names, OUT PDWORD * Use);
extern NTSTATUS WINAPI SamRidToSid(IN SAMPR_HANDLE ObjectHandle, IN DWORD Rid, OUT PSID * Sid);
extern NTSTATUS WINAPI SamCloseHandle(IN SAMPR_HANDLE SamHandle);
extern NTSTATUS WINAPI SamFreeMemory(IN PVOID Buffer);

#define SAM_SERVER_CONNECT				0x00000001
#define SAM_SERVER_SHUTDOWN				0x00000002
#define SAM_SERVER_INITIALIZE			0x00000004
#define SAM_SERVER_CREATE_DOMAIN		0x00000008
#define SAM_SERVER_ENUMERATE_DOMAINS	0x00000010
#define SAM_SERVER_LOOKUP_DOMAIN		0x00000020
#define SAM_SERVER_ALL_ACCESS			0x000f003f
#define SAM_SERVER_READ					0x00020010
#define SAM_SERVER_WRITE				0x0002000e
#define SAM_SERVER_EXECUTE				0x00020021

#define SAM_DOMAIN_OBJECT				0x00000000
#define SAM_GROUP_OBJECT				0x10000000
#define SAM_NON_SECURITY_GROUP_OBJECT	0x10000001
#define SAM_ALIAS_OBJECT				0x20000000
#define SAM_NON_SECURITY_ALIAS_OBJECT	0x20000001
#define SAM_USER_OBJECT					0x30000000
#define SAM_MACHINE_ACCOUNT				0x30000001
#define SAM_TRUST_ACCOUNT				0x30000002
#define SAM_APP_BASIC_GROUP				0x40000000
#define SAM_APP_QUERY_GROUP				0x40000001

#define DOMAIN_READ_PASSWORD_PARAMETERS	0x00000001
#define DOMAIN_WRITE_PASSWORD_PARAMS	0x00000002
#define DOMAIN_READ_OTHER_PARAMETERS	0x00000004
#define DOMAIN_WRITE_OTHER_PARAMETERS	0x00000008
#define DOMAIN_CREATE_USER				0x00000010
#define DOMAIN_CREATE_GROUP				0x00000020
#define DOMAIN_CREATE_ALIAS				0x00000040
#define DOMAIN_GET_ALIAS_MEMBERSHIP		0x00000080
#define DOMAIN_LIST_ACCOUNTS			0x00000100
#define DOMAIN_LOOKUP					0x00000200
#define DOMAIN_ADMINISTER_SERVER		0x00000400
#define DOMAIN_ALL_ACCESS				0x000f07ff
#define DOMAIN_READ						0x00020084
#define DOMAIN_WRITE					0x0002047a
#define DOMAIN_EXECUTE					0x00020301

#define GROUP_READ_INFORMATION			0x00000001
#define GROUP_WRITE_ACCOUNT				0x00000002
#define GROUP_ADD_MEMBER				0x00000004
#define GROUP_REMOVE_MEMBER				0x00000008
#define GROUP_LIST_MEMBERS				0x00000010
#define GROUP_ALL_ACCESS				0x000F001F
#define GROUP_READ						0x00020010
#define GROUP_WRITE						0x0002000E
#define GROUP_EXECUTE					0x00020001

#define ALIAS_ADD_MEMBER				0x00000001
#define ALIAS_REMOVE_MEMBER				0x00000002
#define ALIAS_LIST_MEMBERS				0x00000004
#define ALIAS_READ_INFORMATION			0x00000008
#define ALIAS_WRITE_ACCOUNT				0x00000010
#define ALIAS_ALL_ACCESS				0x000F001F
#define ALIAS_READ						0x00020004
#define ALIAS_WRITE						0x00020013
#define ALIAS_EXECUTE					0x00020008

#define USER_READ_GENERAL				0x00000001
#define USER_READ_PREFERENCES			0x00000002
#define USER_WRITE_PREFERENCES			0x00000004
#define USER_READ_LOGON					0x00000008
#define USER_READ_ACCOUNT				0x00000010
#define USER_WRITE_ACCOUNT				0x00000020
#define USER_CHANGE_PASSWORD			0x00000040
#define USER_FORCE_PASSWORD_CHANGE		0x00000080
#define USER_LIST_GROUPS				0x00000100
#define USER_READ_GROUP_INFORMATION		0x00000200
#define USER_WRITE_GROUP_INFORMATION	0x00000400
#define USER_ALL_ACCESS					0x000f07ff
#define USER_READ						0x0002031a
#define USER_WRITE						0x00020044
#define USER_EXECUTE					0x00020041

#define USER_ALL_USERNAME				0x00000001
#define USER_ALL_FULLNAME				0x00000002
#define USER_ALL_USERID					0x00000004
#define USER_ALL_PRIMARYGROUPID			0x00000008
#define USER_ALL_ADMINCOMMENT			0x00000010
#define USER_ALL_USERCOMMENT			0x00000020
#define USER_ALL_HOMEDIRECTORY			0x00000040
#define USER_ALL_HOMEDIRECTORYDRIVE		0x00000080
#define USER_ALL_SCRIPTPATH				0x00000100
#define USER_ALL_PROFILEPATH			0x00000200
#define USER_ALL_WORKSTATIONS			0x00000400
#define USER_ALL_LASTLOGON				0x00000800
#define USER_ALL_LASTLOGOFF				0x00001000
#define USER_ALL_LOGONHOURS				0x00002000
#define USER_ALL_BADPASSWORDCOUNT		0x00004000
#define USER_ALL_LOGONCOUNT				0x00008000
#define USER_ALL_PASSWORDCANCHANGE		0x00010000
#define USER_ALL_PASSWORDMUSTCHANGE		0x00020000
#define USER_ALL_PASSWORDLASTSET		0x00040000
#define USER_ALL_ACCOUNTEXPIRES			0x00080000
#define USER_ALL_USERACCOUNTCONTROL		0x00100000
#define USER_ALL_PARAMETERS				0x00200000
#define USER_ALL_COUNTRYCODE			0x00400000
#define USER_ALL_CODEPAGE				0x00800000
#define USER_ALL_NTPASSWORDPRESENT		0x01000000
#define USER_ALL_LMPASSWORDPRESENT		0x02000000
#define USER_ALL_PRIVATEDATA			0x04000000
#define USER_ALL_PASSWORDEXPIRED		0x08000000
#define USER_ALL_SECURITYDESCRIPTOR		0x10000000
#define USER_ALL_UNDEFINED_MASK			0xc0000000

#define USER_NORMAL_ACCOUNT				0x00000010
#define USER_DONT_EXPIRE_PASSWORD		0x00000200

//
// Special Values and Constants - User
//

//
//  Bit masks for field usriX_flags of USER_INFO_X (X = 0/1).
//

#define UF_SCRIPT							0x0001
#define UF_ACCOUNTDISABLE					0x0002
#define UF_HOMEDIR_REQUIRED					0x0008
#define UF_LOCKOUT							0x0010
#define UF_PASSWD_NOTREQD					0x0020
#define UF_PASSWD_CANT_CHANGE				0x0040
#define UF_ENCRYPTED_TEXT_PASSWORD_ALLOWED	0x0080

//
// Account type bits as part of usri_flags.
//

#define UF_TEMP_DUPLICATE_ACCOUNT			0x0100
#define UF_NORMAL_ACCOUNT					0x0200
#define UF_INTERDOMAIN_TRUST_ACCOUNT		0x0800
#define UF_WORKSTATION_TRUST_ACCOUNT		0x1000
#define UF_SERVER_TRUST_ACCOUNT				0x2000

#define UF_MACHINE_ACCOUNT_MASK	( UF_INTERDOMAIN_TRUST_ACCOUNT | UF_WORKSTATION_TRUST_ACCOUNT | UF_SERVER_TRUST_ACCOUNT ) // !!!

#define UF_ACCOUNT_TYPE_MASK	( UF_TEMP_DUPLICATE_ACCOUNT | UF_NORMAL_ACCOUNT | UF_INTERDOMAIN_TRUST_ACCOUNT | UF_WORKSTATION_TRUST_ACCOUNT | UF_SERVER_TRUST_ACCOUNT ) // !!!

#define UF_DONT_EXPIRE_PASSWD				0x10000
#define UF_MNS_LOGON_ACCOUNT				0x20000
#define UF_SMARTCARD_REQUIRED				0x40000
#define UF_TRUSTED_FOR_DELEGATION			0x80000
#define UF_NOT_DELEGATED					0x100000
#define UF_USE_DES_KEY_ONLY					0x200000
#define UF_DONT_REQUIRE_PREAUTH				0x400000
#define UF_PASSWORD_EXPIRED					0x800000
#define UF_TRUSTED_TO_AUTHENTICATE_FOR_DELEGATION	0x1000000
#define UF_NO_AUTH_DATA_REQUIRED			0x2000000
#define UF_PARTIAL_SECRETS_ACCOUNT			0x4000000
#define UF_USE_AES_KEYS						0x8000000



#define UF_SETTABLE_BITS	( \
	UF_SCRIPT | \
	UF_ACCOUNTDISABLE | \
	UF_LOCKOUT | \
	UF_HOMEDIR_REQUIRED  | \
	UF_PASSWD_NOTREQD | \
	UF_PASSWD_CANT_CHANGE | \
	UF_ACCOUNT_TYPE_MASK | \
	UF_DONT_EXPIRE_PASSWD | \
	UF_MNS_LOGON_ACCOUNT |\
	UF_ENCRYPTED_TEXT_PASSWORD_ALLOWED |\
	UF_SMARTCARD_REQUIRED | \
	UF_TRUSTED_FOR_DELEGATION | \
	UF_NOT_DELEGATED | \
	UF_USE_DES_KEY_ONLY  | \
	UF_DONT_REQUIRE_PREAUTH |\
	UF_PASSWORD_EXPIRED |\
	UF_TRUSTED_TO_AUTHENTICATE_FOR_DELEGATION |\
	UF_NO_AUTH_DATA_REQUIRED \
) // !!!