/************************************************************************

Copyright mooby 2002

CDRMooby2 Preferences.hpp
http://mooby.psxfanatics.com

  This file is protected by the GNU GPL which should be included with
  the source code distribution.

************************************************************************/

#ifndef PREFERENCES_HPP
#define PREFERENCES_HPP

#include <map>
#include <list>
#include <string>

static const char* repeatString = "repeat";
static const char* volumeString = "volume";
static const char* cacheSizeString = "cachesize";

// these are the repeat mode strings
static const char* repeatAllString = "repeatAll";
static const char* repeatOneString = "repeatOne";
static const char* playOneString = "playOne";

// a wrapper for preference information.
class Preferences
{
public:
   Preferences();

private:
   bool initialized;

public:
   std::map<std::string, std::string> prefsMap;
   std::list<std::string> allPrefs;
};

#endif
