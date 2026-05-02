#ifndef URL_HISTORY_H
#define URL_HISTORY_H

#include "../assign1/url.h"  // Needed: URL type in public interface
#include <list>              // Needed: std::list in private member

class UrlHistory {
public:
    void addUrl(const URL& url);
    const std::list<URL>& getHistory() const;  // std::list in return type
    bool empty() const;
    size_t size() const;

private:
    std::list<URL> history;  // std::list in member variable
};

#endif