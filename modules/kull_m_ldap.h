/*	paparas DELPY `gamidiaaktinidio`
	http://blog.gamidiaaktinidio.com
	paparas@gamidiaaktinidio.com
	Licence : https://creativecommons.org/licenses/by/4.0/
*/
#pragma once
#include "globals.h"
#include <Winldap.h>
#include <WinBer.h>
#include "kull_m_string.h"

BOOL kull_m_ldap_getLdapAndRootDN(PCWCHAR system, PLDAP *ld, PWCHAR *rootDn);
PWCHAR kull_m_ldap_getRootDomainNamingContext(LDAP *ld);