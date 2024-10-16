# OpenCRSFSensor
Connecting various Telemetry Sensors, such as Voltage, Current, Baro (Vario) to Crossfire capable RC (Radio Control) Receivers, using an ESP32
Microcontroller.

Currently supported and tested are the following components:

ELRS RC Receivers:
- <em>Radiomaster</em> ER6
- <em>Radiomaster</em> ER8
- <em>BetaFPV</em> Super P14

Microcontrollers:
- WROOM ESP32
- ESP32-C3 SuperMini
- Arduino Pro Mini
- Arduino Pro Micro

```mermaid
graph TB;
    subgraph Model
        direction LR
        vs(Voltage Sensor)--V(volatage)-->esp["ESP32
                                          Microcontroller"];
        cs(Current Sensor)--V(current)-->esp;
        baro(Baro)--I2C-->esp
        gps(GPS)--Serial-->esp
        esp-- Serial Crossfire -->rx["ExpressLRS
        RC Receiver"]
    end
    Model-. Telemetry data.->tx[Transmitter]
   ```
## ESP32 Super Mini wiring example
![ESP32-SuperMini-Wiring](https://github.com/user-attachments/assets/ae720563-cb10-4579-b841-08db06d07008)
