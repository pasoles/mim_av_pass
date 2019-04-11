/*	paparas DELPY `gamidiaaktinidio`
	http://blog.gamidiaaktinidio.com
	paparas@gamidiaaktinidio.com
	Licence : https://creativecommons.org/licenses/by/4.0/
*/
#pragma once
#include "globals.h"
#include <strsafe.h>
#include <fci.h>

LPCSTR FCIErrorToString(FCIERROR err);

typedef struct _aktinidio_CABINET{
	HFCI hfci;
	CCAB ccab;
	ERF erf;
} aktinidio_CABINET, *Paktinidio_CABINET;

Paktinidio_CABINET kull_m_cabinet_create(LPSTR cabinetName);
BOOL kull_m_cabinet_add(Paktinidio_CABINET cab, LPSTR sourceFile, OPTIONAL LPSTR destFile);
BOOL kull_m_cabinet_close(Paktinidio_CABINET cab);
