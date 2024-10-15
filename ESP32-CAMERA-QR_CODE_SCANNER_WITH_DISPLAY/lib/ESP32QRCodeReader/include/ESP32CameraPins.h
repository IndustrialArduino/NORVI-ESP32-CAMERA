#ifndef ESP32_CAMERA_PINS_H_
#define ESP32_CAMERA_PINS_H_

struct CameraPins
{
  int PWDN_GPIO_NUM;
  int RESET_GPIO_NUM;
  int XCLK_GPIO_NUM;
  int SIOD_GPIO_NUM;
  int SIOC_GPIO_NUM;
  int Y9_GPIO_NUM;
  int Y8_GPIO_NUM;
  int Y7_GPIO_NUM;
  int Y6_GPIO_NUM;
  int Y5_GPIO_NUM;
  int Y4_GPIO_NUM;
  int Y3_GPIO_NUM;
  int Y2_GPIO_NUM;
  int VSYNC_GPIO_NUM;
  int HREF_GPIO_NUM;
  int PCLK_GPIO_NUM;
};

#define CAMERA_MODEL_WROVER_KIT \
  {                             \
    .PWDN_GPIO_NUM = 41,        \
    .RESET_GPIO_NUM = 42,       \
    .XCLK_GPIO_NUM = 15,        \
    .SIOD_GPIO_NUM = 4,        \
    .SIOC_GPIO_NUM = 5,        \
    .Y9_GPIO_NUM = 16,          \
    .Y8_GPIO_NUM = 17,          \
    .Y7_GPIO_NUM = 18,          \
    .Y6_GPIO_NUM = 12,          \
    .Y5_GPIO_NUM = 10,          \
    .Y4_GPIO_NUM = 8,          \
    .Y3_GPIO_NUM = 9,           \
    .Y2_GPIO_NUM = 11,           \
    .VSYNC_GPIO_NUM = 6,       \
    .HREF_GPIO_NUM = 7,        \
    .PCLK_GPIO_NUM = 13,        \
  }

#define CAMERA_MODEL_ESP_EYE \
  {                          \
    .PWDN_GPIO_NUM = 41,     \
    .RESET_GPIO_NUM = 42,    \
    .XCLK_GPIO_NUM = 15,      \
    .SIOD_GPIO_NUM = 4,     \
    .SIOC_GPIO_NUM = 5,     \
    .Y9_GPIO_NUM = 16,       \
    .Y8_GPIO_NUM = 17,       \
    .Y7_GPIO_NUM = 18,       \
    .Y6_GPIO_NUM = 12,       \
    .Y5_GPIO_NUM = 10,       \
    .Y4_GPIO_NUM = 8,       \
    .Y3_GPIO_NUM = 9,       \
    .Y2_GPIO_NUM = 11,       \
    .VSYNC_GPIO_NUM = 6,     \
    .HREF_GPIO_NUM = 7,     \
    .PCLK_GPIO_NUM = 13,     \
  }

#define CAMERA_MODEL_M5STACK_PSRAM \
  {                                \
    .PWDN_GPIO_NUM = 41,           \
    .RESET_GPIO_NUM = 42,          \
    .XCLK_GPIO_NUM = 15,           \
    .SIOD_GPIO_NUM = 4,           \
    .SIOC_GPIO_NUM = 5,           \
    .Y9_GPIO_NUM = 16,             \
    .Y8_GPIO_NUM = 17,             \
    .Y7_GPIO_NUM = 18,             \
    .Y6_GPIO_NUM = 12,             \
    .Y5_GPIO_NUM = 10,              \
    .Y4_GPIO_NUM = 8,             \
    .Y3_GPIO_NUM = 9,             \
    .Y2_GPIO_NUM = 11,             \
    .VSYNC_GPIO_NUM = 6,          \
    .HREF_GPIO_NUM = 7,           \
    .PCLK_GPIO_NUM = 13,           \
  }

#define CAMERA_MODEL_M5STACK_V2_PSRAM \
  {                                   \
    .PWDN_GPIO_NUM = 41,              \
    .RESET_GPIO_NUM = 42,             \
    .XCLK_GPIO_NUM = 15,              \
    .SIOD_GPIO_NUM = 4,              \
    .SIOC_GPIO_NUM = 5,              \
    .Y9_GPIO_NUM = 16,                \
    .Y8_GPIO_NUM = 17,                \
    .Y7_GPIO_NUM = 18,                \
    .Y6_GPIO_NUM = 12,                \
    .Y5_GPIO_NUM = 10,                 \
    .Y4_GPIO_NUM = 8,                \
    .Y3_GPIO_NUM = 9,                \
    .Y2_GPIO_NUM = 11,                \
    .VSYNC_GPIO_NUM = 6,             \
    .HREF_GPIO_NUM = 7,              \
    .PCLK_GPIO_NUM = 13,              \
  }

#define CAMERA_MODEL_M5STACK_WIDE \
  {                               \
    .PWDN_GPIO_NUM = 41,          \
    .RESET_GPIO_NUM = 42,         \
    .XCLK_GPIO_NUM = 15,          \
    .SIOD_GPIO_NUM = 4,          \
    .SIOC_GPIO_NUM = 5,          \
    .Y9_GPIO_NUM = 16,            \
    .Y8_GPIO_NUM = 17,            \
    .Y7_GPIO_NUM = 18,            \
    .Y6_GPIO_NUM = 12,            \
    .Y5_GPIO_NUM = 10,             \
    .Y4_GPIO_NUM = 8,            \
    .Y3_GPIO_NUM = 9,            \
    .Y2_GPIO_NUM = 11,            \
    .VSYNC_GPIO_NUM = 6,         \
    .HREF_GPIO_NUM = 7,          \
    .PCLK_GPIO_NUM = 13,          \
  }

#define CAMERA_MODEL_M5STACK_ESP32CAM \
  {                                   \
    .PWDN_GPIO_NUM = 41,              \
    .RESET_GPIO_NUM = 42,             \
    .XCLK_GPIO_NUM = 15,              \
    .SIOD_GPIO_NUM = 4,              \
    .SIOC_GPIO_NUM = 5,              \
    .Y9_GPIO_NUM = 16,                \
    .Y8_GPIO_NUM = 17,                \
    .Y7_GPIO_NUM = 18,                \
    .Y6_GPIO_NUM = 12,                \
    .Y5_GPIO_NUM = 10,                 \
    .Y4_GPIO_NUM = 8,                \
    .Y3_GPIO_NUM = 9,                \
    .Y2_GPIO_NUM = 11,                \
    .VSYNC_GPIO_NUM = 6,             \
    .HREF_GPIO_NUM = 7,              \
    .PCLK_GPIO_NUM = 13,              \
  }

#define CAMERA_MODEL_AI_THINKER \
  {                             \
    .PWDN_GPIO_NUM = 41,        \
    .RESET_GPIO_NUM = 42,       \
    .XCLK_GPIO_NUM = 15,         \
    .SIOD_GPIO_NUM = 4,        \
    .SIOC_GPIO_NUM = 5,        \
    .Y9_GPIO_NUM = 16,          \
    .Y8_GPIO_NUM = 17,          \
    .Y7_GPIO_NUM = 18,          \
    .Y6_GPIO_NUM = 12,          \
    .Y5_GPIO_NUM = 10,          \
    .Y4_GPIO_NUM = 8,          \
    .Y3_GPIO_NUM = 9,          \
    .Y2_GPIO_NUM = 11,           \
    .VSYNC_GPIO_NUM = 6,       \
    .HREF_GPIO_NUM = 7,        \
    .PCLK_GPIO_NUM = 13,        \
  }

#define CAMERA_MODEL_TTGO_T_JOURNAL \
  {                                 \
    .PWDN_GPIO_NUM = 41,             \
    .RESET_GPIO_NUM = 42,           \
    .XCLK_GPIO_NUM = 15,            \
    .SIOD_GPIO_NUM = 4,            \
    .SIOC_GPIO_NUM = 5,            \
    .Y9_GPIO_NUM = 16,              \
    .Y8_GPIO_NUM = 17,              \
    .Y7_GPIO_NUM = 18,              \
    .Y6_GPIO_NUM = 12,              \
    .Y5_GPIO_NUM = 10,               \
    .Y4_GPIO_NUM = 8,              \
    .Y3_GPIO_NUM = 9,              \
    .Y2_GPIO_NUM = 11,              \
    .VSYNC_GPIO_NUM = 6,           \
    .HREF_GPIO_NUM = 7,            \
    .PCLK_GPIO_NUM = 13,            \
  }

#endif //ESP32_CAMERA_PINS_H_