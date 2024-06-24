#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

//-----------------------------------------------------------------------------
// CRSF communication
//-----------------------------------------------------------------------------

/**
 * Pins for CRSF communication
*/
#define CRSF_RX_PIN GPIO_NUM_16
#define CRSF_TX_PIN GPIO_NUM_17

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
#define VOLTAGE_ANALOG_PIN GPIO_NUM_32

/**
 * Values for voltage divider
 */
#define RESISTOR_TO_VOLTAGE 2700
#define RESISTOR_TO_GROUND  1000

//-----------------------------------------------------------------------------
// Current Sensor
//-----------------------------------------------------------------------------

/**
 * Define this if you want to have a current sensor
*/
#define CURRENT_SENSOR

/**
 * Analog pin for Current sensor
*/
#define CURRENT_ANALOG_PIN GPIO_NUM_33

/**
 * Current sensor parameters
 */
#define MILLIVOLTS_FOR_ZERO_AMP 0
#define MILLIVOLTS_PER_AMP 20

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

/**
 * Pins for Baro I2C communication
 */
#define BARO_SDA_PIN GPIO_NUM_21
#define BARO_SCL_PIN GPIO_NUM_22

//-----------------------------------------------------------------------------
// GPS Sensor
//-----------------------------------------------------------------------------

/**
 * Define this if you want to have a GPS sensor
*/
#define GPS_SENSOR

/**
 * Baudrate for GPS communication
*/
#define GPS_BAUDRATE 9600

/**
 * Pins for GPS communication
*/
#define GPS_RX_PIN GPIO_NUM_18
#define GPS_TX_PIN GPIO_NUM_19

//-----------------------------------------------------------------------------
// Flight Mode Sensor (experimental)
//-----------------------------------------------------------------------------

/**
 * Define this if you want to have a FlightMode sensor
*/
#define FLIGHT_MODE_SENSOR


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