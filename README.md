# OpenCRSFSensor
Connecting various Telemetry Sensors, such as Voltage, Current, Baro (Vario) to Crossfire capable RC (Radio Control) Receivers, using an ESP32
Microcontroller.

Currently supported and tested are the following components:

RC Receivers:
- <em>Radiomaster ER8</em> ELRS (Express LRS) Receiver

Microcontrollers:
- WROOM ESP32
- ESP32-C3 SuperMini

```mermaid
graph LR;
    vs(Voltage Sensor)-->esp["ESP32
                              Microcontroller"];
    cs(Current Sensor)-->esp;
    baro(Baro)-->esp
    gps(GPS)-->esp
    esp-->rc["ExpressLRS
RC Receiver"]
```
## ESP32 Super Mini wiring example
![ESP32 SuperMini Connections](https://github.com/icebreaker-ch/OpenCRSFSensor/assets/3645375/0644d657-7215-4514-9575-bd55a2f53a8d)
