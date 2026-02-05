#pragma once

#include <cstdint>

// ---------------------------------------------------------------------------
// Display
// ---------------------------------------------------------------------------
constexpr int SCREEN_WIDTH      = 240;
constexpr int SCREEN_HEIGHT     = 135;
constexpr int DISPLAY_ROTATION  = 1;   // Landscape (USB on right)
constexpr int DISPLAY_BRIGHTNESS = 80;

// ---------------------------------------------------------------------------
// Colors – RGB565 helper
// ---------------------------------------------------------------------------
constexpr uint16_t rgb565(uint8_t r, uint8_t g, uint8_t b) {
    return static_cast<uint16_t>(((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3));
}

// Background & general
constexpr uint16_t COLOR_BG          = rgb565(15,  15,  40);
constexpr uint16_t COLOR_DIVIDER     = rgb565(50,  50,  80);

// Title bar
constexpr uint16_t COLOR_TITLE_BG    = rgb565(25,  25,  60);
constexpr uint16_t COLOR_TITLE_TEXT  = rgb565(255, 220, 100);

// Content text
constexpr uint16_t COLOR_TEXT        = rgb565(220, 220, 230);

// Tags
constexpr uint16_t COLOR_TAG_BG     = rgb565(25,  30,  55);
constexpr uint16_t COLOR_TAG_BORDER = rgb565(80,  180, 255);
constexpr uint16_t COLOR_TAG_TEXT   = rgb565(180, 220, 255);

// Status bar
constexpr uint16_t COLOR_INDICATOR   = rgb565(80,  180, 255);
constexpr uint16_t COLOR_BATTERY_OK  = rgb565(100, 220, 100);
constexpr uint16_t COLOR_BATTERY_LOW = rgb565(255, 80,  80);
constexpr uint16_t COLOR_STATUS_TEXT = rgb565(120, 120, 150);

// ---------------------------------------------------------------------------
// Timing
// ---------------------------------------------------------------------------
constexpr unsigned long AUTO_PAGE_INTERVAL_MS = 7000;

// ---------------------------------------------------------------------------
// Layout – Title
// ---------------------------------------------------------------------------
constexpr int MARGIN_X           = 8;
constexpr int TITLE_HEIGHT       = 24;
constexpr int TITLE_TEXT_SIZE    = 2;   // default font * 2 → 12×16 px

// ---------------------------------------------------------------------------
// Layout – Content
// ---------------------------------------------------------------------------
constexpr int CONTENT_TEXT_SIZE  = 2;
constexpr int CONTENT_START_Y   = 28;
constexpr int CONTENT_LINE_HEIGHT = 18;

// ---------------------------------------------------------------------------
// Layout – Tags
// ---------------------------------------------------------------------------
constexpr int TAG_TEXT_SIZE      = 2;
constexpr int TAG_PADDING_X     = 4;
constexpr int TAG_PADDING_Y     = 2;
constexpr int TAG_MARGIN         = 5;
constexpr int TAG_RADIUS         = 3;
constexpr int TAG_LINE_HEIGHT   = 21;
// ---------------------------------------------------------------------------
// Layout – Status bar
// ---------------------------------------------------------------------------
constexpr int STATUS_BAR_HEIGHT  = 18;
constexpr int STATUS_BAR_Y       = SCREEN_HEIGHT - STATUS_BAR_HEIGHT;
constexpr int STATUS_TEXT_SIZE   = 1;

// ---------------------------------------------------------------------------
// Battery
// ---------------------------------------------------------------------------
constexpr int BATTERY_LOW_THRESHOLD = 20;
