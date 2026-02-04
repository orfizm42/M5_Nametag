#pragma once

#include <M5Unified.h>
#include <vector>

// ---------------------------------------------------------------------------
// Page – a single badge screen
// ---------------------------------------------------------------------------
struct Page {
    String title;
    std::vector<String> contents;
};

// ---------------------------------------------------------------------------
// PageManager – owns pages, handles drawing and auto‑advance
// ---------------------------------------------------------------------------
class PageManager {
public:
    /// Call after M5.begin() to allocate the off‑screen canvas.
    void begin();

    /// Add a page with a title and content lines.
    /// Lines containing [tag] notation are rendered with bordered tags.
    void addPage(const String& title, const std::vector<String>& contents);

    /// Render the current page to the display (double‑buffered).
    void drawCurrentPage();

    /// Advance to the next page (wraps around).
    void nextPage();

    /// Returns true when AUTO_PAGE_INTERVAL_MS has elapsed.
    bool shouldAutoAdvance() const;

    /// Reset the auto‑advance timer (called on manual / auto advance).
    void resetTimer();

    int getCurrentIndex() const;
    int getPageCount() const;

private:
    std::vector<Page> pages_;
    int currentIndex_           = 0;
    unsigned long lastSwitchTime_ = 0;
    M5Canvas* canvas_           = nullptr;

    // Drawing helpers
    void drawTitleBar(const String& title);
    void drawContentArea(const std::vector<String>& contents);
    void drawStatusBar();
    void drawTagLine(const String& line, int& y);

    // Tag utilities
    std::vector<String> parseTags(const String& line) const;
    bool hasTags(const String& line) const;
};
