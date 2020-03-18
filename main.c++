#include <cstring> // strncmp
#include <iostream>
#include <string>

#include "PageFetcher.h"

using namespace std;

bool isUrlLike(char* str)
{
	constexpr int minUrlLen = 11; // Len of "http://ab.cd"

	for (int i = 0; i < minUrlLen; ++i)
		if (str[i] == 0) return false;

	if (strncmp(str, "http", 4) != 0) return false;

	return (str[4] == 's') ? strncmp(&str[5], "://", 3) == 0
	                       : strncmp(&str[4], "://", 3) == 0;
}

int main(int argc, char** argv)
{
	if (argc < 2) {
		cout << "Please pass a URL for scanning or some keywords for "
		        "searching\n";
		return -1;
	}

	if (argc == 2 && isUrlLike(argv[1])) {
		cout << "Will scan page" << endl;

		PageFetcher fetcher;
		cout << fetcher.fetchPage(argv[1]);
	}
	else {
		cout << "Will lookup words" << endl;
	}

	return 0;
}
