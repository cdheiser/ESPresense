#include <regex>
#include <string_utils.h>
#include "string_utils.h"

#include <FSCompat.h>
#include <sstream>
#include <vector>
#include <FS.h>

static constexpr char hexmap[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

std::string hexStr(const uint8_t* data, int len) {
    std::string s = "";
    for (int i = 0; i < len; ++i) {
        s += hexmap[(data[i] & 0xF0) >> 4];
        s += hexmap[data[i] & 0x0F];
    }
    return s;
}

std::string hexStr(const char* data, int len) {
    return hexStr(reinterpret_cast<const uint8_t*>(data), len);
}

std::string hexStr(const std::string& data) {
    return hexStr(reinterpret_cast<const uint8_t*>(data.data()), data.length());
}

std::string hexStrRev(const uint8_t *data, int len) {
    std::string s = "";
    for (int i = len - 1; i >= 0; --i) {
        s += hexmap[(data[i] & 0xF0) >> 4];
        s += hexmap[data[i] & 0x0F];
    }
    return s;
}

std::string hexStrRev(const char *data, int len) {
    return hexStrRev(reinterpret_cast<const uint8_t*>(data), len);
}

std::string hexStrRev(const std::string &s) {
    return hexStrRev(reinterpret_cast<const uint8_t*>(s.data()), s.length());
}

std::string kebabify(const std::string& text) {
    std::string r = "";
    for (unsigned int i = 0; i < text.length(); i++) {
        if (isalnum(text[i]))
            r += (char)tolower(text[i]);
        else if (text[i] == ' ' || text[i] == '-' || text[i] == '_')
            r += '-';
    }
    // Simple deduplication of dashes
    std::string r2 = "";
    bool lastDash = false;
    for (char c : r) {
        if (c == '-') {
            if (!lastDash) r2 += c;
            lastDash = true;
        } else {
            r2 += c;
            lastDash = false;
        }
    }
    if (!r2.empty() && r2[0] == '-') r2.erase(0, 1);
    if (!r2.empty() && r2[r2.length() - 1] == '-') r2.erase(r2.length() - 1, 1);
    return r2;
}

String kebabify(const String& s) {
    return String(kebabify(std::string(s.c_str())).c_str());
}

std::string slugify(const std::string& text) {
    std::string r = "";
    for (unsigned int i = 0; i < text.length(); i++) {
        if (isalnum(text[i]))
            r += (char)tolower(text[i]);
        else if (text[i] == ' ' || text[i] == '-' || text[i] == '_')
            r += '_';
    }
    // Simple deduplication of underscores
    std::string r2 = "";
    bool lastUnderscore = false;
    for (char c : r) {
        if (c == '_') {
            if (!lastUnderscore) r2 += c;
            lastUnderscore = true;
        } else {
            r2 += c;
            lastUnderscore = false;
        }
    }
    if (!r2.empty() && r2[0] == '_') r2.erase(0, 1);
    if (!r2.empty() && r2[r2.length() - 1] == '_') r2.erase(r2.length() - 1, 1);
    return r2;
}

String slugify(const String& s) {
    return String(slugify(std::string(s.c_str())).c_str());
}

bool hextostr(const String &hexStr, uint8_t* output, size_t len) {
    if (hexStr.length() < len * 2) return false;
    for (size_t i = 0; i < len; i++) {
        char c1 = tolower(hexStr[i * 2]);
        char c2 = tolower(hexStr[i * 2 + 1]);
        uint8_t v1 = (c1 >= 'a') ? (c1 - 'a' + 10) : (c1 - '0');
        uint8_t v2 = (c2 >= 'a') ? (c2 - 'a' + 10) : (c2 - '0');
        output[i] = (v1 << 4) | v2;
    }
    return true;
}

bool prefixExists(const String& prefixes, const String& s) {
    if (prefixes.isEmpty()) return false;
    int start = 0;
    int end = prefixes.indexOf(',');
    while (end != -1) {
        if (s.startsWith(prefixes.substring(start, end))) return true;
        start = end + 1;
        end = prefixes.indexOf(',', start);
    }
    return s.startsWith(prefixes.substring(start));
}

bool spurt(const String &fn, const String &content) {
    File f = SPIFFS.open(fn, "w");
    if (!f) return false;
    size_t w = f.print(content);
    f.close();
    return w == content.length();
}