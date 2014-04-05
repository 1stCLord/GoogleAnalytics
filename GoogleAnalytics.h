/*
 *  GoogleAnalytics.h
 *  GoogleAnalytics
 *
 *  Created by Andrew Haining on 04/04/2014.
 *  Copyright (c) 2014 Ratus Apparatus. All rights reserved.
 *
 */
#pragma once
#include "System.h"
#include "cpprest/http_client.h"

class GoogleAnalytics
{
    private:
    utility::string_t m_property;
    utility::string_t m_client;
	utility::string_t m_appName;

	public:
    GoogleAnalytics(const utility::string_t &property, const utility::string_t &appName, utility::string_t &client);
    void sendEvent(const utility::string_t &category, const utility::string_t &action, const utility::string_t &label, uint32_t value) const;
};
