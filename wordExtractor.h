#include <optional>
#include <string>
#include <vector>

std::optional<std::pair<size_t, size_t>> findWord(const std::string& str, size_t pos)
{
	size_t strlen = str.size();
	size_t beginWord = pos;
	while (beginWord < str.size() && !isalpha(str[beginWord]))
		++beginWord;

	if (beginWord == strlen) return {};

	size_t wordLen = 0;
	while (beginWord + wordLen < strlen && isalpha(str[beginWord + wordLen]))
		++wordLen;

	if(wordLen < 3) return {};

	return {{ beginWord, wordLen }};
}

std::vector<std::string> extractWords(const std::string& webPage) {
	size_t i = 0;
	size_t len = webPage.size();

	std::vector<std::string> words;

	while ( i < len) {
		auto res = findWord(webPage, i);
		if(!res) break;

		words.push_back(webPage.substr(res->first, res->second));

		i = res ->first + res->second;
	}

	return words;
}
