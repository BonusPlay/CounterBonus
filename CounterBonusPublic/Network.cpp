#pragma once
#include "Network.hpp"

#include <curl/curl.h>
#include "Console.hpp"

#pragma region Singleton

cNetworkManager* Network;

cNetworkManager::cNetworkManager()
{
	Console->DebugMessage("NetworkManager starting up");
	curl_global_init(CURL_GLOBAL_ALL);
}

cNetworkManager::~cNetworkManager()
{
	Console->DebugMessage("NetworkManager shutting down");
}

#pragma endregion 

json cNetworkManager::getJson(std::string url)
{
	CURL* curl;
	curl = curl_easy_init();

	std::string readBuffer;

	if(curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		CURLcode res = curl_easy_perform(curl);
		
		curl_easy_cleanup(curl);
		return json::parse(readBuffer.c_str());
	}
	return json::parse("{}");
}

size_t cNetworkManager::writeCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}