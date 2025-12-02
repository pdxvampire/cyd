// ======= Display Setup for ST7789 on ESP32 =======
class LGFX_JustDisplay : public lgfx::LGFX_Device
{
    lgfx::Panel_ST7789 _panel_instance;
    lgfx::Bus_SPI _bus_instance;

    //////
    lgfx::Light_PWM _light_instance;
    //lgfx::Touch_XPT2046 _touch_instance;
    //////

  public:
    LGFX_JustDisplay(void)
    {
        {
            // SPI config

            auto cfg = _bus_instance.config();
            /////cfg.spi_host = VSPI_HOST;
            cfg.spi_host = HSPI_HOST;
            cfg.spi_mode = 0;
            //////cfg.freq_write = 27000000;
            //////cfg.freq_read = 16000000;
            cfg.freq_write = 55000000;
            cfg.freq_read = 20000000;
            cfg.spi_3wire = false;
            cfg.use_lock = true;
            //////cfg.dma_channel = 1;
            cfg.dma_channel = SPI_DMA_CH_AUTO;  // Set the DMA channel (0=DMA not used / 1=1ch / 2=2ch / SPI_DMA_CH_AUTO=automatic)
            // Due to the ESP-IDF version upgrade, SPI_DMA_CH_AUTO is recommended. Specifying 1ch or 2ch is no longer recommended.
            cfg.pin_sclk = CYD_TFT_SCK;   // Set the SPI SCLK pin
            cfg.pin_mosi = CYD_TFT_MOSI;  // Set the SPI MOSI pin
            cfg.pin_miso = CYD_TFT_MISO;  // Set the SPI MISO pin (-1 = disable)
            cfg.pin_dc = CYD_TFT_DC;      // Set the SPI D/C  pin (-1 = disable)
                                          // When you use a common SPI bus with the SD card, be sure to set MISO and do not omit it.
                                          /////            cfg.pin_sclk = 14;
                                          /////            cfg.pin_mosi = 13;
                                          /////            cfg.pin_miso = -1;
                                          /////            cfg.pin_dc = 2;


            _bus_instance.config(cfg);
            _panel_instance.setBus(&_bus_instance);
        }

        {
            // Panel config

            auto cfg = _panel_instance.config();
            cfg.pin_cs = CYD_TFT_CS;  // CS   pin number (-1 = disable)
            cfg.pin_rst = -1;         // RST  pin number (-1 = disable) CYD_TFT_RS = CYD_TFT_CS, RESET is connected to board RST
            cfg.pin_busy = -1;        // BUSY pin number (-1 = disable)

            /////cfg.pin_cs = 15;


            cfg.panel_width = 240;      // Panel width
            cfg.panel_height = 320;     // Panel height
            cfg.offset_x = 0;           // Panel offset in X direction
            cfg.offset_y = 0;           // Panel offset in Y direction
            cfg.offset_rotation = 0;    // Rotation direction offset 0~7 (4~7 are upside down)
            cfg.dummy_read_pixel = 16;  // Number of dummy read bits before pixel read


            /////cfg.dummy_read_pixel = 8;
            cfg.dummy_read_bits = 1;
            /////cfg.readable = false;
            cfg.readable = true;
            cfg.invert = false;

            cfg.rgb_order = false;   // Set to true if the red and blue of the panel are swapped
            cfg.dlen_16bit = false;  // Set to true if the panel transmit data in 16-bit via 16-bit parallel or SPI
            cfg.bus_shared = false;  // Set to true if the bus is shared with the SD card (The bus is controlled for drawJpg etc.)



            /////            cfg.rgb_order = 0;
            /////            cfg.bus_shared = true;

            // Set the following only if your display is misaligned, such as ST7735 or ILI9163, which have variable pixel counts.
            cfg.memory_width = 240;   // Maximum width  supported by driver IC
            cfg.memory_height = 320;  // Maximum height supported by driver IC

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
        /*
        {  // Configure touch screen control (delete if not needed)
            auto cfg = _touch_instance.config();

            cfg.x_min = 240;           // Minimum X value (raw value) from touch screen
            cfg.x_max = 3800;          // Maximum X value (raw value) from touch screen
            cfg.y_min = 3700;          // Minimum Y value (raw value) from touch screen
            cfg.y_max = 200;           // Maximum Y value (raw value) from touch screen
            cfg.pin_int = CYD_TP_IRQ;  // Interrupt pin number
            cfg.bus_shared = false;    // Set to true if the bus shared with the screen
#if DISPLAY_CYD_2USB
            cfg.offset_rotation = 2;  // Adjust when display and touch orientation do not match (0~7)
#else
            cfg.offset_rotation = 0;  // Adjust when display and touch orientation do not match (0~7)
#endif

            // For SPI connection
            cfg.spi_host = -1;           // Select the SPI (HSPI_HOST or VSPI_HOST) or only XPT2046 can be set to -1.
            cfg.freq = 1000000;          // Set the SPI clock
            cfg.pin_sclk = CYD_TP_CLK;   // SCLK pin number
            cfg.pin_mosi = CYD_TP_MOSI;  // MOSI pin number
            cfg.pin_miso = CYD_TP_MISO;  // MISO pin number
            cfg.pin_cs = CYD_TP_CS;      // CS   pin number

            // For I2C connection
            //cfg.i2c_port = 1;      // Select the I2C (0 or 1)
            //cfg.i2c_addr = 0x38;   // I2C device addres
            //cfg.pin_sda  = 23;     // SDA pin number
            //cfg.pin_scl  = 32;     // SCL pin number
            //cfg.freq = 400000;     // Set the I2C clock

            _touch_instance.config(cfg);
            _panel_instance.setTouch(&_touch_instance);  // Set the touch screen on the panel.
        }
        */
        setPanel(&_panel_instance);  // Set the panel to be used.
    }
};