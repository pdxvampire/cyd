#ifndef LV_CONF_H
#define LV_CONF_H

#define LV_USE_PERF_MONITOR     0
#define LV_USE_LOG              0
#define LV_USE_ASSERT_NULL      1
#define LV_USE_DRAW_SW          1
#define LV_USE_DEV_CUSTOM       0

#define LV_COLOR_DEPTH          16
#define LV_COLOR_SCREEN_TRANSP  0

#define LV_TICK_CUSTOM          0

#define LV_USE_USER_DATA        1
#define LV_USE_LAYER            1
#define LV_MEM_SIZE             (48U * 1024U)  // 48KB heap

#define LV_USE_TIMER            1
#define LV_USE_LABEL            1
#define LV_USE_BTN              1
#define LV_USE_DISPLAY          1

// Add other widgets as needed
#define LV_USE_BTNMATRIX        1
#define LV_USE_SWITCH           1
#define LV_USE_SLIDER           1
#define LV_USE_ARC              1
#define LV_USE_IMG              1

#define LV_FS_DEFAULT_DRIVER_LETTER '\0'

/** API for fopen, fread, etc. */
#define LV_USE_FS_STDIO 1
#if LV_USE_FS_STDIO
#define LV_FS_STDIO_LETTER 'A'
#define LV_FS_STDIO_PATH ""      /**< Set the working directory. File/directory paths will be appended to it. */
#define LV_FS_STDIO_CACHE_SIZE 0 /**< >0 to cache this number of bytes in lv_fs_read() */
#endif
/*
#define LV_USE_LODEPNG          1
#define LV_USE_PNG              1
*/
/** Decode bin images to RAM */
/*#define LV_BIN_DECODER_RAM_LOAD 1*/

/** Setting a default driver letter allows skipping the driver prefix in filepaths. */
#define LV_FS_DEFAULT_DRIVE_LETTER 'A'

#endif // LV_CONF_H
