#include <cstring> // strncmp
#include <optional>
#include <utility> // std::pair
#include <vector>

constexpr size_t const_strlen(const char* str) noexcept
{
	if (*str == 0) return 0;
	return 1 + const_strlen(str + 1);
}

bool isQuote(char c) { return c == '"' || c == '\''; }

bool isUrlLike(const char* str)
{
	constexpr int minUrlLen = 11; // Len of "http://ab.cd"

	for (int i = 0; i < minUrlLen; ++i)
		if (str[i] == 0) return false;

	if (strncmp(str, "http", 4) != 0) return false;

	return (str[4] == 's') ? strncmp(&str[5], "://", 3) == 0
	                       : strncmp(&str[4], "://", 3) == 0;
}

std::optional<std::pair<size_t, size_t>> findLink(std::string const& str,
                                                  size_t pos)
{
	pos = str.find("href=", pos);

	if (pos == std::string::npos) return {};

	pos += const_strlen("href=");

	// a `href=` might be followed by either a ' or a ", which are not part of
	// the ink
	if (isQuote(str[pos])) ++pos;

	// Search the end of the link - a space or a quote
	size_t linkLength = 0;
	while (pos + linkLength < str.size() && str[pos + linkLength] != ' ' &&
	       !isQuote(str[pos + linkLength]))
		++linkLength;

	return {{pos, linkLength}};
}

void makeLinkAbsolute(std::string& link, const std::string& url)
{
	if (isUrlLike(link.c_str())) return;

	if (link[0] == '/') {
		size_t firstSlashAfterDomain = url.find('/', 9);

		link = url.substr(0, firstSlashAfterDomain) + link;
	} else {
		size_t lastSlash = url.find_last_of('/');

		if (lastSlash < 10)          // The slashes after 'http' were found
			link = url + '/' + link; // i.e. the url is a bare domain
		else
			link = url.substr(0, lastSlash + 1) + link;
	}
}

void makeAllLinksAbsolute(std::vector<std::string>& links,
                          const std::string& url)
{
	for (std::string& link : links) {
		makeLinkAbsolute(link, url);
	}
}

size_t findBodyStart(const std::string& webPage)
{
	return webPage.find('>', webPage.find("<body")) +
	       1; // Add 'one' to exclude the '>' char
}

std::vector<std::string> extractLinks(std::string webPage)
{
	std::vector<std::string> links;

	size_t bodyStart = findBodyStart(webPage);
	size_t pageSize = webPage.size();

	size_t i = bodyStart;

	while (i < pageSize) {
		auto searchRes = findLink(webPage, i);

		if (!searchRes.has_value()) break;

		links.push_back(webPage.substr(searchRes->first, searchRes->second));

		i = searchRes->first + searchRes->second;
	}

	return links;
};
