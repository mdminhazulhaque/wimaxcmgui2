#ifndef DEFINES_HPP
#define DEFINES_HPP

#define PREF_FREQ 2600
#define MIN_FREQ 1900
#define MAX_FREQ 5000
#define STEP_FREQ 10

#define SHELL "/bin/sh"
#define WCM_SCANALL "wimaxc status | egrep \"Link|NOT\""
#define WCM_BSID "wimaxc status | grep Base | cut -d':' -f2-6"
#define WCM_CINR "wimaxc linkstats | egrep CINR | awk '{ print $3 }'"
#define WCM_RSSI "wimaxc linkstats | egrep RSSI | awk '{ print $3 }'"
#define WCM_UPLOAD "wimaxc linkstats | egrep UL | awk '{ print $4 }'"
#define WCM_DOWNLOAD "wimaxc linkstats | egrep DL | awk '{ print $4 }'"
#define WCM_UPTIME "wimaxc status | grep Connection | cut -d' ' -f3"
#define WCM_FREQ "wimaxc status | grep DL | cut -d' ' -f4 | sed s/00000/00/"
#define WCM_MAC "wimaxc versions | grep MAC | cut -d' ' -f3"
#define WCM_GREPINET " | grep 'inet addr:' | cut -d: -f2 | awk '{print $1}'"
#define WCM_GREPETH "ifconfig -a | grep -i "
#define WCM_GREPIFCONFIG "ifconfig "
#define WCM_CUT " | cut -d' ' -f1"

#endif // DEFINES_HPP
