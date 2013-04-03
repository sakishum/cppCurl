/**
 * @file main.cpp
 * @Synopsis  Example for tiny curl with CPP. 
 * @author Saki Shum, sakishum1118@gmail.com
 * @version 0.0.1
 * @date 2013-03-29
 */

#include <iostream>
#include <time.h> 
#include "tiny_curl.h"

using namespace std;

int main(int argc, char argv[])
{
	clock_t tStart, tStop;

	CTiny_curl tinyCurl;
	size_t size;
	string data;
	string url1 = "http://192.168.1.226/areaapi/test.php?act=test_getrolename";
	string url2 = "http://192.168.1.226/areaapi/test.php";
	string command = "act=test_getrolename";
	tinyCurl.Init();
	tStart = clock();
	size = tinyCurl.Get(data, url1);
	tStop = clock();
	cout<<"size: "<<size<<endl;
	cout<<"Data: "<<data<<endl;
	printf("Get: %ldus.\n",(tStop - tStart) * 1000000 / CLOCKS_PER_SEC);
	tStart = clock();
	size = tinyCurl.Post(data, url2, command);
	tStop = clock();
	cout<<"size: "<<size<<endl;
	cout<<"Data: "<<data<<endl;
	printf("Post: %ldus.\n",(tStop - tStart) * 1000000 / CLOCKS_PER_SEC);

	cout<<"--Done.--"<<endl;
	return 0;
}
