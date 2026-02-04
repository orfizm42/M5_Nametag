#include <M5Unified.h>
#include "config.h"
#include "pages.h"

PageManager pageManager;

// ===================================================================
// Setup – initialise hardware and register badge pages
// ===================================================================
void setup() {
    auto cfg = M5.config();
    M5.begin(cfg);

    M5.Display.setRotation(DISPLAY_ROTATION);
    M5.Display.setBrightness(DISPLAY_BRIGHTNESS);

    pageManager.begin();

    // ------------------------------------------------------------------
    // Define your badge pages below.
    // Lines containing [tag] notation are rendered with bordered tags.
    // ------------------------------------------------------------------

    pageManager.addPage("Profile", {
        "Taro Yamada",
        "@taro_dev",
        "github.com/taro",
    });

    pageManager.addPage("Now", {
        "[IoT] [M5Stack]",
        "[PlatformIO]",
    });

    pageManager.addPage("Skills", {
        "[C++] [Python]",
        "[TypeScript] [React]",
        "[Arduino] [ESP32]",
    });

    pageManager.addPage("Hobbies", {
        "[3DPrint] [Electronics]",
        "[Coffee] [Camera]",
    });

    pageManager.drawCurrentPage();
}

// ===================================================================
// Loop – button handling and auto‑advance
// ===================================================================
void loop() {
    M5.update();

    bool needRedraw = false;

    // Button A → manual page advance
    if (M5.BtnA.wasPressed()) {
        pageManager.nextPage();
        needRedraw = true;
    }

    // Auto‑advance after the configured interval
    if (pageManager.shouldAutoAdvance()) {
        pageManager.nextPage();
        needRedraw = true;
    }

    if (needRedraw) {
        pageManager.drawCurrentPage();
    }

    delay(10);
}
