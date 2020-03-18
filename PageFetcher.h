#include <curl/curl.h>
#include <sstream>

class PageFetcher
{
	CURL* curl;
	char errorBuffer[CURL_ERROR_SIZE];

	static size_t write_callback(char* ptr, size_t, size_t nmemb, void* stream)
	{
		static_cast<std::ostringstream*>(stream)->write(ptr, (long)nmemb);
		return nmemb;
	}

public:
	PageFetcher() : curl{curl_easy_init()}
	{
		if (!curl) {
			throw std::runtime_error("Couldn't init curl!");
		}

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
		curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);
	}

	std::string fetchPage(std::string const& url)
	{
		std::ostringstream webpage;

		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &webpage);

		if (curl_easy_perform(curl) != CURLE_OK) {
			std::string errorPrefix = "Error occurred while fetching page: ";
			throw std::runtime_error(errorPrefix + errorBuffer);
		}

		return webpage.str();
	}

	~PageFetcher() { curl_easy_cleanup(curl); }
};
