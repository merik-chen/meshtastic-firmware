#ifndef _VARIANT_ESP32S3_E22P_915M30S_H_
#define _VARIANT_ESP32S3_E22P_915M30S_H_

#define BUTTON_PIN 0 // BOOT 按鈕

#define HAS_SCREEN 1

#ifdef HAS_SCREEN // EBYTE E22P-915M30S 版本預設使用 OLED 顯示器
#define USE_OLED// 使用 OLED 顯示器 (SSD1306)
#define USE_SSD1306
#endif

#define I2C_SDA 17
#define I2C_SCL 18

// #define BATTERY_PIN 1
// #define ADC_MULTIPLIER 2.0 

// ==========================================
// 射頻模組腳位映射 (EBYTE E22P-915M30S)
// ==========================================
#define USE_SX1262

// 高速 SPI 匯流排腳位
#define LORA_SCK 4
#define LORA_CS 5
#define LORA_MISO 6
#define LORA_MOSI 7

// SX126x 核心控制介面
#define SX126X_CS LORA_CS
#define SX126X_BUSY 8
#define SX126X_DIO1 9
#define SX126X_RESET 10

// ==========================================
// E22P 射頻前端狀態控制與極限功率配置
// ==========================================
#undef SX126X_DIO2_AS_RF_SWITCH

// 根據 E22P 真值表：TX 需為 1/1，RX 需為 1/0
// 傳統 RadioLib 在 TX 時會將 RXEN 拉低 (0/1)，導致 E22P 進入 CLOSE 狀態而無法發射。
// 解法：停用 RXEN，將 EN (Pin 6) 連接至 ESP32 S3 3V3，使其在喚醒時恆為 1。
#define SX126X_RXEN RADIOLIB_NC // 停用原生的反相 RXEN 邏輯，設為未連接
#define SX126X_TXEN 12// 綁定 T/R CTRL (Pin 7)，交由底層切換：1 為發射，0 為接收

// E22P 內建高精度 TCXO，由 DIO3 供電 (1.8V)
#define SX126X_DIO3_TCXO_VOLTAGE 1.8

// 功率補償與輸出限制計算
// E22P-915M30S 最大輸出 30dBm。限制 SX1262 內部輸出 22dBm，外部 FEM 增益為 8dB。
#define REGULATORY_GAIN_LORA 8
#define SX126X_MAX_POWER 22

#endif // _VARIANT_ESP32S3_E22P_915M30S_H_