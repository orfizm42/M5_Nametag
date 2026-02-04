#include "pages.h"
#include "config.h"

// ===================================================================
// Lifecycle
// ===================================================================

void PageManager::begin() {
    canvas_ = new M5Canvas(&M5.Display);
    canvas_->createSprite(SCREEN_WIDTH, SCREEN_HEIGHT);
    lastSwitchTime_ = millis();
}

void PageManager::addPage(const String& title,
                          const std::vector<String>& contents) {
    pages_.push_back({title, contents});
}

// ===================================================================
// Page navigation
// ===================================================================

void PageManager::nextPage() {
    if (pages_.empty()) return;
    currentIndex_ = (currentIndex_ + 1) % static_cast<int>(pages_.size());
    resetTimer();
}

bool PageManager::shouldAutoAdvance() const {
    return (millis() - lastSwitchTime_) >= AUTO_PAGE_INTERVAL_MS;
}

void PageManager::resetTimer() {
    lastSwitchTime_ = millis();
}

int PageManager::getCurrentIndex() const { return currentIndex_; }
int PageManager::getPageCount()    const { return static_cast<int>(pages_.size()); }

// ===================================================================
// Drawing – main entry
// ===================================================================

void PageManager::drawCurrentPage() {
    if (pages_.empty() || !canvas_) return;

    const Page& page = pages_[currentIndex_];

    canvas_->fillSprite(COLOR_BG);
    drawTitleBar(page.title);
    drawContentArea(page.contents);
    drawStatusBar();
    canvas_->pushSprite(0, 0);
}

// ===================================================================
// Drawing – title bar
// ===================================================================

void PageManager::drawTitleBar(const String& title) {
    canvas_->fillRect(0, 0, SCREEN_WIDTH, TITLE_HEIGHT, COLOR_TITLE_BG);

    const int textHeight = 8 * TITLE_TEXT_SIZE;
    const int yOffset    = (TITLE_HEIGHT - textHeight) / 2;

    canvas_->setTextSize(TITLE_TEXT_SIZE);
    canvas_->setTextColor(COLOR_TITLE_TEXT);
    canvas_->setCursor(MARGIN_X, yOffset);
    canvas_->print(title);

    canvas_->drawFastHLine(0, TITLE_HEIGHT, SCREEN_WIDTH, COLOR_DIVIDER);
}

// ===================================================================
// Drawing – content area
// ===================================================================

void PageManager::drawContentArea(const std::vector<String>& contents) {
    int y = CONTENT_START_Y;

    for (const auto& line : contents) {
        if (y >= STATUS_BAR_Y - 4) break;

        if (hasTags(line)) {
            drawTagLine(line, y);
        } else {
            canvas_->setTextSize(CONTENT_TEXT_SIZE);
            canvas_->setTextColor(COLOR_TEXT);
            canvas_->setCursor(MARGIN_X, y);
            canvas_->print(line);
            y += CONTENT_LINE_HEIGHT;
        }
    }
}

// ===================================================================
// Drawing – tag line (flow layout with wrapping)
// ===================================================================

void PageManager::drawTagLine(const String& line, int& y) {
    std::vector<String> tags = parseTags(line);
    if (tags.empty()) return;

    const int charW   = 6 * TAG_TEXT_SIZE;
    const int charH   = 8 * TAG_TEXT_SIZE;
    int x = MARGIN_X;

    canvas_->setTextSize(TAG_TEXT_SIZE);

    for (const auto& tag : tags) {
        const int textW = static_cast<int>(tag.length()) * charW;
        const int tagW  = textW + TAG_PADDING_X * 2;
        const int tagH  = charH + TAG_PADDING_Y * 2;

        // Wrap to next row when the tag would exceed the right margin
        if (x + tagW > SCREEN_WIDTH - MARGIN_X && x > MARGIN_X) {
            x = MARGIN_X;
            y += TAG_LINE_HEIGHT;
            if (y >= STATUS_BAR_Y - 4) return;
        }

        // Rounded rectangle background + border
        canvas_->fillRoundRect(x, y, tagW, tagH, TAG_RADIUS, COLOR_TAG_BG);
        canvas_->drawRoundRect(x, y, tagW, tagH, TAG_RADIUS, COLOR_TAG_BORDER);

        // Tag label
        canvas_->setTextColor(COLOR_TAG_TEXT);
        canvas_->setCursor(x + TAG_PADDING_X, y + TAG_PADDING_Y);
        canvas_->print(tag);

        x += tagW + TAG_MARGIN;
    }

    y += TAG_LINE_HEIGHT;
}

// ===================================================================
// Drawing – status bar (page indicator + battery)
// ===================================================================

void PageManager::drawStatusBar() {
    canvas_->drawFastHLine(0, STATUS_BAR_Y - 1, SCREEN_WIDTH, COLOR_DIVIDER);

    const int textY = STATUS_BAR_Y + (STATUS_BAR_HEIGHT - 8) / 2;
    canvas_->setTextSize(STATUS_TEXT_SIZE);

    // Page indicator (left)
    canvas_->setTextColor(COLOR_INDICATOR);
    canvas_->setCursor(MARGIN_X, textY);
    canvas_->printf("%d/%d", currentIndex_ + 1,
                    static_cast<int>(pages_.size()));

    // Battery level (right)
    int battery = M5.Power.getBatteryLevel();

    String batStr;
    uint16_t batColor;
    if (battery < 0) {
        batStr  = "USB";
        batColor = COLOR_STATUS_TEXT;
    } else {
        if (battery > 100) battery = 100;
        batStr  = String(battery) + "%";
        batColor = (battery > BATTERY_LOW_THRESHOLD)
                       ? COLOR_BATTERY_OK
                       : COLOR_BATTERY_LOW;
    }

    const int batW = static_cast<int>(batStr.length()) * 6 * STATUS_TEXT_SIZE;
    canvas_->setTextColor(batColor);
    canvas_->setCursor(SCREEN_WIDTH - MARGIN_X - batW, textY);
    canvas_->print(batStr);
}

// ===================================================================
// Tag utilities
// ===================================================================

std::vector<String> PageManager::parseTags(const String& line) const {
    std::vector<String> tags;
    int i = 0;
    const int len = static_cast<int>(line.length());

    while (i < len) {
        if (line[i] == '[') {
            int end = line.indexOf(']', i);
            if (end > i) {
                tags.push_back(line.substring(i + 1, end));
                i = end + 1;
            } else {
                break;
            }
        } else {
            ++i;
        }
    }
    return tags;
}

bool PageManager::hasTags(const String& line) const {
    int open = line.indexOf('[');
    return open >= 0 && line.indexOf(']', open) > open;
}
