/**
 * @file tiny_curl.h
 * @Synopsis  A Very Lightweight cURL wrapper.
 * @author Saki Shum, sakishum1118@gmail.com
 * @version 0.0.1
 * @date 2013-03-29
 */

#ifndef __TINY_CURL_H__
#define __TINY_CURL_H__

#include <curl/curl.h>
///#include <curl/types.h>
/// Doesn't compile: curl/types.h: No such file or directory
/// This is a problem on archlinux which just got curl 7.21.7.
/// curl devs removed curl/types.h and put its content in curl/curl.h.
#include <curl/easy.h>
#include <string>

using namespace std;

class CTiny_curl
{
private:
	CURL *m_pcurl_handle;
	string Replace_space(string url);

public:
	CTiny_curl(void);
	~CTiny_curl(void);
	int		Init(void);
	size_t	Get(string &data, string url);
	size_t	Post(string &data, string url, string &command);
};

#endif /*__TINY_CURL_H__*/

