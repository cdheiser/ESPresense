#ifndef ESPRESENSE_SPIFFS_COMPAT_H
#define ESPRESENSE_SPIFFS_COMPAT_H

#if !defined(CONFIG_IDF_TARGET_ESP32C6) && __has_include(<SPIFFS.h>)
#include <SPIFFS.h>
#else
#include <LittleFS.h>
#define SPIFFS LittleFS
#endif

#endif
