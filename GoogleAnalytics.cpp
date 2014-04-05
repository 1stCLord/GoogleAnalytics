/*
 *  GoogleAnalytics.cp
 *  GoogleAnalytics
 *
 *  Created by Andrew Haining on 04/04/2014.
 *  Copyright (c) 2014 Ratus Apparatus. All rights reserved.
 *
 */

#include <iostream>
#include "GoogleAnalytics.h"

using namespace web::http;
using namespace web::http::client;

#define API_VERSION 1

#define API_HOST L"www.google-analytics.com"
//#define API_HOST L"http://www.google.com"
#define API_PATH L"collect"

#define API_PARAM_VERSION L"v"
#define API_PARAM_TRACKINGID L"tid"
#define API_PARAM_APPNAME L"an"
#define API_PARAM_APPVERSION L"av"
#define API_PARAM_CLIENTID L"cid"
#define API_PARAM_HITTYPE L"t"

#define API_VALUE_HITTYPE_EVENT L"event"

GoogleAnalytics::GoogleAnalytics(const utility::string_t &property, const utility::string_t &appName, utility::string_t &client)
{
    m_property = property;
    m_client = client;
	m_appName = appName;
}

void GoogleAnalytics::sendEvent(const utility::string_t &category, const utility::string_t &action, const utility::string_t &label, uint32_t value) const
{
    uri_builder buildEventUri;
	buildEventUri.set_scheme(L"http");
    buildEventUri.set_host(API_HOST);
    buildEventUri.set_path(API_PATH);
    buildEventUri.append_query(API_PARAM_VERSION, API_VERSION);
    buildEventUri.append_query(API_PARAM_TRACKINGID, m_property);
	buildEventUri.append_query(API_PARAM_APPNAME, m_appName);
	buildEventUri.append_query(API_PARAM_APPVERSION, GAMEVERSION);
    buildEventUri.append_query(API_PARAM_CLIENTID, m_client);
    buildEventUri.append_query(API_PARAM_HITTYPE, API_VALUE_HITTYPE_EVENT);

	wstring uri = buildEventUri.to_string();

    http_client client(buildEventUri.to_uri());
	client.request(methods::POST).then([](http_response response){});
	return;
}