#pragma once

#include "json.hpp"
#ifdef max
	#undef max
#endif

using json = nlohmann::json;

class cNetworkManager
{
public:
	cNetworkManager();
	~cNetworkManager();

	json getJson(std::string url);

private:
	static size_t writeCallback(void *contents, size_t size, size_t nmemb, void *userp);
};

extern cNetworkManager* Network;