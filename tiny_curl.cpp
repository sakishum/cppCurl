/**
 * @file tiny_curl.h
 * @Synopsis  A Very Lightweight cURL wrapper.
 * @author Saki Shum, sakishum1118@gmail.com
 * @version 0.0.1
 * @date 2013-03-29
 */

#include "tiny_curl.h"

static size_t WriteBufferCallback(void *ptr, size_t size, size_t nmemb, void *data)
{
	((string*)data)->append((const char*)ptr, size * nmemb);
	return size * nmemb;
}

CTiny_curl::CTiny_curl(void)
:m_pcurl_handle(NULL)
{  /*NOTHING TO DO*/ }

CTiny_curl::~CTiny_curl(void)
{
	if (NULL != m_pcurl_handle)
	{
		// always cleanup curl stuff
		curl_easy_cleanup(m_pcurl_handle);
		/// curl_global_cleanup is "None Thread Safe""
		curl_global_cleanup();
	}
}

int CTiny_curl::Init(void)
{
	/// curl_global_init is "None Thread Safe""
	CURLcode res = curl_global_init(CURL_GLOBAL_ALL);
	if (CURLE_OK != res)
	{
		/// curl_global_init failed.
		return -1;
	}
	// init the curl session
	m_pcurl_handle = curl_easy_init();
	if (NULL == m_pcurl_handle)
	{
		/// curl_easy_init failed.
		return -1;
	}
	// send all data to this function
	curl_easy_setopt(m_pcurl_handle, CURLOPT_WRITEFUNCTION, WriteBufferCallback);
	// some server don't like requests that made without a user-agent
	// field, so we provide one
	curl_easy_setopt(m_pcurl_handle, CURLOPT_USERAGENT, "libcurl-agent/12.0");
	return 1;
}

/**
 * @Synopsis  Get
 *		Http get
 * @Param data
 * @Param url
 *
 * @Returns  content size 
 */
size_t CTiny_curl::Get(string &data, string url)
{
	if (NULL == m_pcurl_handle)
	{
		return 0;
	}
	// clear buffer
	data.clear();
	// we pass our 'chunk' struct to the callback function
	curl_easy_setopt(m_pcurl_handle, CURLOPT_WRITEDATA, (void*)&data);
	// specify URL to get
	curl_easy_setopt(m_pcurl_handle, CURLOPT_URL, Replace_space(url).c_str());
	// get it!
	CURLcode res = curl_easy_perform(m_pcurl_handle);	/* Post away */
	if (CURLE_OK != res)
	{
		return 0;
	}
	return data.size();
}

/**
 * @Synopsis  Post 
 *		Http post
 * @Param data
 * @Param url
 * @Param command
 *
 * @Returns   content size
 */
size_t CTiny_curl::Post(string &data, string url, string &command)
{
	if (NULL == m_pcurl_handle)
	{
		return 0;
	}
	// clear buffer
	data.clear();
	// specify URL to post
	curl_easy_setopt(m_pcurl_handle, CURLOPT_POSTFIELDS, command.c_str());	
	curl_easy_setopt(m_pcurl_handle, CURLOPT_URL, url.c_str());
	// we pass our 'chunk' struct to the callback function
	curl_easy_setopt(m_pcurl_handle, CURLOPT_WRITEDATA, (void*)&data);
	// get it!
	CURLcode res = curl_easy_perform(m_pcurl_handle);	/* Post away */
	if (CURLE_OK != res)
	{
		return 0;
	}
	return data.size();
}

/**
 * @Synopsis  Replace_space 
 *		Replace all the space.
 * @Param url
 *
 * @Returns   no space string
 */
string CTiny_curl::Replace_space(string url)
{
	string new_url;
	const char *cptr = url.c_str();

	while (*cptr)
	{
		if (*cptr == ' ')
		{
			new_url.append("%20");
		}
		else 
		{
			new_url.push_back(*cptr);
		}
		cptr++;
	}
	return new_url;
}

