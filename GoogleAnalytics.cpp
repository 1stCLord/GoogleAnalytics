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

#ifdef _UTF16_STRINGS
#define TOSTRING(v) to_wstring(v)
#define PREFIX L
#else
#define TOSTRING(v) to_string(v)
#define PREFIX 
#endif

using namespace web::http;
using namespace web::http::client;

#define API_VERSION 1

#define API_SCHEME PREFIX"http"

#define API_HOST PREFIX"www.google-analytics.com"
//#define API_HOST L"http://www.google.com"
#define API_PATH PREFIX"collect"

#define API_PARAM_VERSION PREFIX"v"
#define API_PARAM_TRACKINGID PREFIX"tid"
#define API_PARAM_APPNAME PREFIX"an"
#define API_PARAM_APPVERSION PREFIX"av"
#define API_PARAM_CLIENTID PREFIX"cid"
#define API_PARAM_HITTYPE PREFIX"t"

#define API_PARAM_SESSIONCONTROL PREFIX"sc"
#define API_PARAM_SCREENRESOLUTION PREFIX"sr"

#define API_PARAM_CATEGORY PREFIX"ec"
#define API_PARAM_ACTION PREFIX"ea"
#define API_PARAM_LABEL PREFIX"el"
#define API_PARAM_VALUE PREFIX"ev"

#define API_VALUE_HITTYPE_EVENT PREFIX"event"

#define API_VALUE_SC_BEGIN PREFIX"begin"
#define API_VALUE_SC_END PREFIX"end"

#define RESOLUTION_SEPERATOR PREFIX"x"

GoogleAnalytics::GoogleAnalytics(const utility::string_t &property, const utility::string_t &appName, utility::string_t &client)
{
    m_property = property;
    m_client = client;
	m_appName = appName;
}

void GoogleAnalytics::beginSession(uint32_t width, uint32_t height) const
{

	utility::string_t resolutionString = TOSTRING(width) + utility::string_t(RESOLUTION_SEPERATOR) + TOSTRING(height);

    uri_builder buildEventUri;
	addStandardQueries(&buildEventUri);
    buildEventUri.append_query(API_PARAM_HITTYPE, API_VALUE_HITTYPE_EVENT);
	buildEventUri.append_query(API_PARAM_SESSIONCONTROL, API_VALUE_SC_BEGIN);
	buildEventUri.append_query(API_PARAM_SCREENRESOLUTION, resolutionString);

	wstring uri = buildEventUri.to_string();

    http_client client(buildEventUri.to_uri());
	client.request(methods::POST).then([](http_response response){});
	return;
}

void GoogleAnalytics::endSession() const
{
	uri_builder buildEventUri;
	addStandardQueries(&buildEventUri);
    buildEventUri.append_query(API_PARAM_HITTYPE, API_VALUE_HITTYPE_EVENT);
	buildEventUri.append_query(API_PARAM_SESSIONCONTROL, API_VALUE_SC_END);

	wstring uri = buildEventUri.to_string();

    http_client client(buildEventUri.to_uri());
	client.request(methods::POST).then([](http_response response){});
	return;
}

void GoogleAnalytics::sendEvent(const utility::string_t &category, const utility::string_t &action, const utility::string_t &label, uint32_t value) const
{
    uri_builder buildEventUri;
	addStandardQueries(&buildEventUri);
    buildEventUri.append_query(API_PARAM_HITTYPE, API_VALUE_HITTYPE_EVENT);
	buildEventUri.append_query(API_PARAM_CATEGORY, category);
	buildEventUri.append_query(API_PARAM_ACTION, action);
	buildEventUri.append_query(API_PARAM_LABEL, label);
	buildEventUri.append_query(API_PARAM_VALUE, value);

	wstring uri = buildEventUri.to_string();

    http_client client(buildEventUri.to_uri());
	client.request(methods::POST).then([](http_response response){});
	return;
}

void GoogleAnalytics::addStandardQueries(uri_builder *uri) const
{
	uri->set_scheme(API_SCHEME);
    uri->set_host(API_HOST);
    uri->set_path(API_PATH);
    uri->append_query(API_PARAM_VERSION, API_VERSION);
    uri->append_query(API_PARAM_TRACKINGID, m_property);
	uri->append_query(API_PARAM_APPNAME, m_appName);
	uri->append_query(API_PARAM_APPVERSION, GAMEVERSION);
    uri->append_query(API_PARAM_CLIENTID, m_client);
}