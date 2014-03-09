#ifndef __CC_HELPER_H__
#define __CC_HELPER_H__

#include <string>

using namespace std;

class CCHelper
{
public:
	static void OpeUri(const char* pszUri);
	static void OpeStoreUri(void);
	static string GetVersion(void);
	static void RateApp(void);
	static void ShowAd(void);
	static void ShowInhouseAd(void);
};
#endif
