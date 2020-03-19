#include <iostream>
#include <string>

#include "PageFetcher.h"
#include "linkUtils.h"
#include "wordExtractor.h"

using namespace std;

int main(int argc, char** argv)
{
	if (argc < 2) {
		cout << "Please pass a URL for scanning or some keywords for "
		        "searching\n";
		return -1;
	}

	if (argc == 2 && isUrlLike(argv[1])) {
		cout << "Will scan page" << endl;

		string url = argv[1];

		PageFetcher fetcher;
		string page = fetcher.fetchPage(url);

		auto links = extractLinks(page);
		makeAllLinksAbsolute(links, url);

		auto words = extractWords(page);
	} else {
		cout << "Will lookup words" << endl;
	}

	return 0;
}
