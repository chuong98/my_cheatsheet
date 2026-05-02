#include "url_history.h"
#include <algorithm>

void UrlHistory::addUrl(const URL& url) {
    // Find if URL already exists
    auto it = std::find(history.begin(), history.end(), url);
    
    if (it != history.end()) {
        // URL exists, move it to front
        history.erase(it);
    }
    
    // Add to front (whether new or moved)
    history.push_front(url);
}

const std::list<URL>& UrlHistory::getHistory() const {
    return history;
}

bool UrlHistory::empty() const {
    return history.empty();
}

size_t UrlHistory::size() const {
    return history.size();
}