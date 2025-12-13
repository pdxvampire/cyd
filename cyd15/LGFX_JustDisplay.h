// ======= Display Setup for ST7789 on ESP32 =======

// Got this online from https://github.com/pay191/DIY_Malls-JC2432W328C_Tests/blob/main/BigYellowDisplay_4_LVGL/BigYellowDisplay_4_LVGL.ino
// and modified it.

#include <LovyanGFX.hpp>   // Display library
#include "pins_arduino.h"  // friendly names

class LGFX_JustDisplay : public lgfx::LGFX_Device
{
    lgfx::Panel_ST7789 _panel_instance;
    lgfx::Bus_SPI _bus_instance;
    lgfx::Light_PWM _light_instance;

  public:
    LGFX_JustDisplay(void)
    {
        {
            // SPI bus config

            auto cfg = _bus_instance.config();
            cfg.spi_host = VSPI_HOST;   // Use VSPI (default high-speed SPI)
            cfg.spi_mode = 0;           // SPI mode 0
            ////cfg.freq_write = 27000000;  // Write speed: 27 MHz
      cfg.freq_write = 40000000;    // 40MHz (ST7789 supports higher speeds)
    
            cfg.freq_read = 16000000;   // Read speed (not used here)
            cfg.spi_3wire = false;
            cfg.use_lock = true;
            //////cfg.dma_channel = 1;
            //////cfg.dma_channel = SPI_DMA_CH_AUTO;  // Set the DMA channel (0=DMA not used / 1=1ch / 2=2ch / SPI_DMA_CH_AUTO=automatic)
            // Due to the ESP-IDF version upgrade, SPI_DMA_CH_AUTO is recommended. Specifying 1ch or 2ch is no longer recommended.
            //////cfg.pin_sclk = CYD_TFT_SCK;   // Set the SPI SCLK pin
            //////cfg.pin_mosi = CYD_TFT_MOSI;  // Set the SPI MOSI pin
            //////cfg.pin_miso = CYD_TFT_MISO;  // Set the SPI MISO pin (-1 = disable)
            //////cfg.pin_dc = CYD_TFT_DC;      // Set the SPI D/C  pin (-1 = disable)
            // When you use a common SPI bus with the SD card, be sure to set MISO and do not omit it.
            /////            cfg.pin_sclk = 14;
            /////            cfg.pin_mosi = 13;
            /////            cfg.pin_miso = -1;
            /////            cfg.pin_dc = 2;

            cfg.dma_channel = 1;  // Use DMA channel 1
            cfg.pin_sclk = 14;    // Clock pin
            cfg.pin_mosi = 13;    // Data out (MOSI)
            cfg.pin_miso = -1;    // No data in
            cfg.pin_dc = 2;       // Data/command pin


            _bus_instance.config(cfg);
            _panel_instance.setBus(&_bus_instance);
        }

        {
            // Display panel config

            auto cfg = _panel_instance.config();
            ////cfg.pin_cs = CYD_TFT_CS;  // CS   pin number (-1 = disable)
            ////cfg.pin_rst = -1;         // RST  pin number (-1 = disable) CYD_TFT_RS = CYD_TFT_CS, RESET is connected to board RST
            ////cfg.pin_busy = -1;        // BUSY pin number (-1 = disable)

            /////cfg.pin_cs = 15;
            ////cfg.panel_width = 240;      // Panel width
            ////        cfg.panel_height = 320;     // Panel height
            ////    cfg.offset_x = 0;           // Panel offset in X direction
            //// cfg.offset_y = 0;           // Panel offset in Y direction
            //// cfg.offset_rotation = 0;    // Rotation direction offset 0~7 (4~7 are upside down)
            //// cfg.dummy_read_pixel = 16;  // Number of dummy read bits before pixel read


            /////cfg.dummy_read_pixel = 8;
            ////cfg.dummy_read_bits = 1;
            /////cfg.readable = false;
            ////cfg.readable = true;
            ////cfg.invert = false;

            ////cfg.rgb_order = false;   // Set to true if the red and blue of the panel are swapped
            ////cfg.dlen_16bit = false;  // Set to true if the panel ////transmit data in 16-bit via 16-bit parallel or SPI
            ////cfg.bus_shared = false;  // Set to true if the bus is shared with the SD card (The bus is controlled for drawJpg etc.)

            /////            cfg.rgb_order = 0;
            /////            cfg.bus_shared = true;

            // Set the following only if your display is misaligned, such as ST7735 or ILI9163, which have variable pixel counts.
            ////cfg.memory_width = 240;   // Maximum width  supported by driver IC
            ////cfg.memory_height = 320;  // Maximum height supported by driver IC

            cfg.pin_cs = 15;           // Chip select
            cfg.pin_rst = -1;          // No reset pin
            cfg.pin_busy = -1;         // Not used
            cfg.panel_width = 240;     // Native width
            cfg.panel_height = 320;    // Native height
            cfg.offset_rotation = 0;   // No offset
            cfg.dummy_read_pixel = 8;  // For compatibility
            cfg.dummy_read_bits = 1;
            cfg.readable = false;
            cfg.invert = false;  // No inversion
            cfg.rgb_order = 0;   // RGB (not BGR)
            cfg.dlen_16bit = false;
            cfg.bus_shared = true;


            _panel_instance.config(cfg);
        }

        {                                         // Set the backlight control. (Delete if not required)
            auto cfg = _light_instance.config();  // Get the backlight setting structure

            cfg.pin_bl = CYD_TFT_BL;  // Backlight pin number
            cfg.invert = false;       // Set to true if the backlight brightness is inverted
            cfg.freq = 12000;         // Backlight PWM frequency
            cfg.pwm_channel = 7;      // The PWM channel number

            _light_instance.config(cfg);
            _panel_instance.setLight(&_light_instance);  // Set the backlight on the panel.
        }

        setPanel(&_panel_instance);  // Set the panel to be used.
    }
};