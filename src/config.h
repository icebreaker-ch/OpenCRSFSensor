#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

/**
 * Standard pin configurations
 * 
 * Purpose          ESP32 WROOM     ESP32 Super Mini
 * ------------     -----------     ----------------
 * CRSF RX (ws)     GPIO16          GPIO20/RX
 * CRSF TX (gn)     GPIO17          GPIO21/TX
 * Voltage          GPIO32          ADC1-0/GPIO0
 * Current          GPIO33          ADC1-1/GPIO1
 * Baro SDA         GPIO21          GPIO6/SDA
 * Baro SCL         GPIO22          GPIO7/SCL
 * GPS RX (og)      GPIO18          --            
 * GPS TX (bl)      GPIO19          --
 */

//-----------------------------------------------------------------------------
// CRSF communication
//-----------------------------------------------------------------------------

/**
 * Pins for CRSF communication
*/
#define CRSF_RX_PIN GPIO_NUM_20
#define CRSF_TX_PIN GPIO_NUM_21

/**
 * Baudrade for CRSF communication
*/
#define CRSF_BAUDRATE 416666 //420000

//-----------------------------------------------------------------------------
// Voltage Sensor
//-----------------------------------------------------------------------------

/**
 * Define this if you want to have a voltage sensor
*/
#define VOLTAGE_SENSOR

/**
 * Analog pin for Voltage sensor
*/
#define VOLTAGE_ANALOG_PIN GPIO_NUM_0

/**
 * Values for voltage divider
 */
#define RESISTOR_TO_VOLTAGE 3000
#define RESISTOR_TO_GROUND  1000

//-----------------------------------------------------------------------------
// Current Sensor
//-----------------------------------------------------------------------------

/**
 * Define this if you want to have a current sensor
*/
#define CURRENT_SENSOR

#ifdef CURRENT_SENSOR
/**
 * Analog pin for Current sensor
*/
#define CURRENT_ANALOG_PIN GPIO_NUM_1

/**
 * Current sensor parameters
 */
//#define MILLIVOLTS_FOR_ZERO_AMP 2063 // not required for AutoCurrentSensor
#define MILLIVOLTS_PER_AMP 30

#endif

//-----------------------------------------------------------------------------
// Battery Sensor (Voltage, Current)
//-----------------------------------------------------------------------------
#if defined(VOLTAGE_SENSOR) || defined(CURRENT_SENSOR)
#define BATTERY_SENSOR
#endif

//-----------------------------------------------------------------------------
// Baro/Altitude Sensor (Vario)
//-----------------------------------------------------------------------------

/**
 * Define this if you want to have a Baro (Vario) sensor
*/
#define BARO_ALTITUDE_SENSOR

#ifdef BARO_ALTITUDE_SENSOR

/**
 * Pins for Baro I2C communication
 */
#define BARO_SDA_PIN GPIO_NUM_6
#define BARO_SCL_PIN GPIO_NUM_7

#endif

//-----------------------------------------------------------------------------
// GPS Sensor
//-----------------------------------------------------------------------------

/**
 * Define this if you want to have a GPS sensor
*/
//#define GPS_SENSOR

#ifdef GPS_SENSOR

/**
 * Baudrate for GPS communication
*/
#define GPS_BAUDRATE 9600

/**
 * Pins for GPS communication
*/
#define GPS_RX_PIN GPIO_NUM_18
#define GPS_TX_PIN GPIO_NUM_19

#endif

//-----------------------------------------------------------------------------
// Flight Mode Sensor (experimental)
//-----------------------------------------------------------------------------

/**
 * Define this if you want to have a FlightMode sensor
*/
//#define FLIGHT_MODE_SENSOR


//-----------------------------------------------------------------------------
// General config
//-----------------------------------------------------------------------------
/**
 * Reference voltage for analog measurments
*/
#define ANALOG_REFERENCE_VOLTAGE 3.3

/**
 * Readout for maximum analog voltage
*/
#define MAX_ANALOG_READ 4096

/**
 * Period at startup to calibrate sensors
 */
#define CALIBRATION_PERIOD 5000 // ms

/**
 * Interval to report new values
*/
#define STANDARD_REPORT_INTERVAL 500

/**
 * Number of milliseconds for sensor timeout
 */
#define SENSOR_TIMEOUT 10000

/**
 * Update rate for all sensors [ms]
*/
#define UPDATE_RATE 100

#endif