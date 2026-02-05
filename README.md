# M5_Nametag

イベントやオフ会で「今何してる人?」「どんなことに興味ある?」を視覚的に伝えられる、M5StickCPlus2 用のデジタル名札システムです。
VRChat のタグシステムにインスパイアされ、自分の情報をタグ付きで動的に表示することで、初対面の人とのコミュニケーションをスムーズにします。

## 機能

- 複数ページの自動切り替え（7 秒間隔）
- ボタン A (M5ボタン) で手動ページ送り
- `[タグ]` 記法による枠線付きタグ表示
- バッテリー残量 & ページインジケーター表示
- ダブルバッファリングによるちらつきのない描画

## 必要なもの

- [M5StickCPlus2](https://shop.m5stack.com/products/m5stickc-plus2-esp32-mini-iot-development-kit)
- USB-C ケーブル
- [PlatformIO](https://platformio.org/) (VS Code 拡張 または CLI)

## セットアップ手順

### 1. リポジトリをクローン

```bash
git clone https://github.com/orfizm42/M5_Nametag.git
cd M5_Nametag
```

### 2. 表示内容を編集

`src/main.cpp` を開き、`addPage()` の部分を自分の情報に書き換えてください。

```cpp
// --- ここを自分の情報に書き換える ---

pageManager.addPage("Profile", {
    "Taro Yamada",       // 名前
    "@taro_dev",         // SNS ハンドル
    "github.com/taro",   // URL など
});

pageManager.addPage("Now", {
    "[IoT] [M5Stack]",   // [xxx] はタグとして枠線付きで表示される
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
```

- `addPage("タイトル", { "行1", "行2", ... })` でページを追加できます。ページ数に制限はありません。
- 行の中に `[xxx]` を書くと、その部分が枠線付きのタグとして描画されます。
- `[xxx]` を含まない行は通常のテキストとして表示されます。

### 3. 必要に応じて見た目を調整

色やレイアウトを変えたい場合は `include/config.h` を編集してください（詳細は後述）。

### 4. ビルド & 書き込み

M5StickCPlus2 を USB-C で PC に接続し、PlatformIO でビルド・書き込みを行います。

**VS Code の場合:**
画面下部のステータスバーから Upload (→) ボタンをクリック。

**CLI の場合:**

```bash
pio run -t upload
```

## config.h パラメータ一覧

`include/config.h` で定義されている定数を変更することで、表示をカスタマイズできます。

### ディスプレイ

| 定数 | デフォルト | 説明 |
|---|---|---|
| `DISPLAY_ROTATION` | `1` | 画面の向き。`1` = 横向き (USB 右側)、`3` = 横向き (USB 左側) |
| `DISPLAY_BRIGHTNESS` | `80` | 画面の明るさ (0 - 255) |

### 色

`rgb565(R, G, B)` 関数で RGB 値 (各 0-255) を指定します。

| 定数 | 説明 |
|---|---|
| `COLOR_BG` | 画面全体の背景色 |
| `COLOR_TITLE_BG` | タイトルバーの背景色 |
| `COLOR_TITLE_TEXT` | タイトルの文字色 |
| `COLOR_TEXT` | コンテンツの文字色 |
| `COLOR_TAG_BG` | タグの背景色 |
| `COLOR_TAG_BORDER` | タグの枠線色 |
| `COLOR_TAG_TEXT` | タグの文字色 |
| `COLOR_DIVIDER` | 区切り線の色 |
| `COLOR_INDICATOR` | ページインジケーターの色 |
| `COLOR_BATTERY_OK` | バッテリー残量 (正常時) の色 |
| `COLOR_BATTERY_LOW` | バッテリー残量 (低下時) の色 |

### タイミング

| 定数 | デフォルト | 説明 |
|---|---|---|
| `AUTO_PAGE_INTERVAL_MS` | `7000` | ページ自動切り替え間隔 (ミリ秒) |

### レイアウト

| 定数 | デフォルト | 説明 |
|---|---|---|
| `MARGIN_X` | `8` | 左右の余白 (px) |
| `TITLE_HEIGHT` | `24` | タイトルバーの高さ (px) |
| `TITLE_TEXT_SIZE` | `2` | タイトルのフォント倍率 |
| `CONTENT_TEXT_SIZE` | `2` | コンテンツのフォント倍率 |
| `CONTENT_LINE_HEIGHT` | `18` | コンテンツの行間 (px) |
| `TAG_TEXT_SIZE` | `1` | タグのフォント倍率 |
| `TAG_PADDING_X` | `4` | タグ内の左右パディング (px) |
| `TAG_PADDING_Y` | `2` | タグ内の上下パディング (px) |
| `TAG_MARGIN` | `4` | タグ同士の間隔 (px) |
| `TAG_RADIUS` | `3` | タグの角丸半径 (px) |
| `BATTERY_LOW_THRESHOLD` | `20` | バッテリー低下警告の閾値 (%) |

## ファイル構成

```
M5_Nametag/
├── platformio.ini        # PlatformIO 設定
├── include/
│   ├── config.h          # 定数定義 (色・レイアウト・タイミング)
│   └── pages.h           # PageManager クラス ヘッダー
└── src/
    ├── main.cpp          # エントリポイント & ページ定義
    └── pages.cpp         # PageManager クラス 実装
```

## 操作方法

- **ボタン A (正面)**: 次のページへ手動切り替え
- **自動**: 7 秒ごとに次のページへ切り替わります

## ライセンス

MIT
