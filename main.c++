#include <iostream>
#include <string>

#include "PageFetcher.h"
using namespace std;


int main()
{
	PageFetcher fetcher;

	string url;
	cin >> url;

	cout << fetcher.fetchPage(url);

	return 0;
}
