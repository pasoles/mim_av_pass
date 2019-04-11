#include "kull_m_rpc_ms-credentialkeys.h"

#if defined(_M_X64) || defined(_M_ARM64) // TODO:ARM64
#define _ms_credentialkeys_MIDL_TYPE_FORMAT_STRING_SIZE	73
#elif defined(_M_IX86)
#define _ms_credentialkeys_MIDL_TYPE_FORMAT_STRING_SIZE	69
#endif

typedef struct _ms_credentialkeys_MIDL_TYPE_FORMAT_STRING {
	SHORT Pad;
	UCHAR Format[_ms_credentialkeys_MIDL_TYPE_FORMAT_STRING_SIZE];
} ms_credentialkeys_MIDL_TYPE_FORMAT_STRING;

extern const ms_credentialkeys_MIDL_TYPE_FORMAT_STRING ms_credentialkeys__MIDL_TypeFormatString;
static const RPC_CLIENT_INTERFACE mscredentialkeys___RpcClientInterface = {sizeof(RPC_CLIENT_INTERFACE), {{0xd9ae4745, 0x178e, 0x4561, {0xa5, 0x3f, 0xf0, 0x84, 0xf9, 0x92, 0x13, 0xe5}}, {1, 0}}, {{0x8a885d04, 0x1ceb, 0x11c9, {0x9f, 0xe8, 0x08, 0x00, 0x2b, 0x10, 0x48, 0x60}}, {2, 0}}, 0, 0, 0, 0, 0, 0x00000000};
static const MIDL_TYPE_PICKLING_INFO __MIDL_TypePicklingInfo = {0x33205054, 0x3, 0, 0, 0,};
static RPC_BINDING_HANDLE mscredentialkeys__MIDL_AutoBindHandle;
static const MIDL_STUB_DESC mscredentialkeys_StubDesc = {(void *) &mscredentialkeys___RpcClientInterface, MIDL_user_allocate, MIDL_user_free, &mscredentialkeys__MIDL_AutoBindHandle, 0, 0, 0, 0, ms_credentialkeys__MIDL_TypeFormatString.Format, 1, 0x60000, 0, 0x8000253, 0, 0, 0, 0x1, 0, 0, 0};

void CredentialKeys_Decode(handle_t _MidlEsHandle, Paktinidio_CREDENTIAL_KEYS * _pType)
{
	NdrMesTypeDecode2(_MidlEsHandle, (PMIDL_TYPE_PICKLING_INFO) &__MIDL_TypePicklingInfo, &mscredentialkeys_StubDesc, (PFORMAT_STRING) &ms_credentialkeys__MIDL_TypeFormatString.Format[2], _pType);
}

void CredentialKeys_Free(handle_t _MidlEsHandle, Paktinidio_CREDENTIAL_KEYS * _pType)
{
	NdrMesTypeFree2(_MidlEsHandle, (PMIDL_TYPE_PICKLING_INFO) &__MIDL_TypePicklingInfo, &mscredentialkeys_StubDesc, (PFORMAT_STRING) &ms_credentialkeys__MIDL_TypeFormatString.Format[2], _pType);
}
#if defined(_M_X64) || defined(_M_ARM64) // TODO:ARM64
static const ms_credentialkeys_MIDL_TYPE_FORMAT_STRING ms_credentialkeys__MIDL_TypeFormatString = {0, {
	0x00, 0x00, 0x12, 0x00, 0x38, 0x00, 0x1b, 0x00, 0x01, 0x00, 0x17, 0x00, 0x0a, 0x00, 0x01, 0x00, 0x01, 0x5b, 0x1a, 0x03, 0x18, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x0d, 0x0d, 0x06, 0x06, 0x40, 0x36,
	0x5c, 0x5b, 0x12, 0x00, 0xe2, 0xff, 0x21, 0x03, 0x00, 0x00, 0x09, 0x00, 0xf8, 0xff, 0x01, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x4c, 0x00, 0xda, 0xff, 0x5c, 0x5b, 0x1a, 0x03, 0x08, 0x00,
	0xe6, 0xff, 0x00, 0x00, 0x08, 0x40, 0x5c, 0x5b, 0x00,
}};
#elif defined(_M_IX86)
static const ms_credentialkeys_MIDL_TYPE_FORMAT_STRING ms_credentialkeys__MIDL_TypeFormatString = {0, {
	0x00, 0x00, 0x12, 0x00, 0x36, 0x00, 0x1b, 0x00, 0x01, 0x00, 0x17, 0x00, 0x0a, 0x00, 0x01, 0x00, 0x01, 0x5b, 0x1a, 0x03, 0x10, 0x00, 0x00, 0x00, 0x08, 0x00, 0x0d, 0x0d, 0x06, 0x06, 0x36, 0x5b,
	0x12, 0x00, 0xe4, 0xff, 0x21, 0x03, 0x00, 0x00, 0x09, 0x00, 0xfc, 0xff, 0x01, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x4c, 0x00, 0xdc, 0xff, 0x5c, 0x5b, 0x1a, 0x03, 0x04, 0x00, 0xe6, 0xff,
	0x00, 0x00, 0x08, 0x5b, 0x00,
}};
#endif