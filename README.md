# ESP8266 WiFi Auto Configuration using WiFiManager
This code is for ESP8266 devices using the WiFiManager library to handle WiFi configuration via a captive portal. It allows you to configure WiFi credentials through a web interface and includes a button reset feature.
# 🔧 Features
- Automatically connects to a saved WiFi network.
- If no WiFi is configured or if the FLASH button is held for 3 seconds, it launches a captive portal for WiFi setup.
- Saves credentials in EEPROM.
- LED indicator shows success or reset.
- Displays full network and device information via Serial Monitor.
# 📥 Setup
Libraries Required
- ESP8266WiFi.h
- WiFiManager.h (install via Library Manager or GitHub)
# ⚙️ Pin Configuration
Component	    GPIO	        Description
Flash Button	D3 (GPIO 0)	    Triggers WiFi reset on long press
LED_BUILTIN	    D0 (GPIO 16)	Blinks on reset or successful connect
# 📘 How it Works
1. Startup Sequence:
- Serial monitor starts.
- Button state is read.
- If held for 3 seconds, WiFi credentials are reset and LED blinks 5 times.
- Otherwise, attempts to connect to stored WiFi using autoConnect().
2. Access Point Fallback:
- If WiFi connection fails or no credentials are stored, it launches an AP named ESP-PPXD with password 12345678.
- Access it from any device to enter WiFi credentials.
3. Successful Connection:
- LED blinks 3 times.
- Detailed network info (IP, MAC, SSID, etc.) is printed to the Serial Monitor.
# 🔁 Notes
- You can change the captive portal timeout with setConfigPortalTimeout(180) (in seconds).
- The non-blocking mode (wm_nonblocking = true) allows your code to run other tasks during WiFi setup, but it is disabled by default here.


