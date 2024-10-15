#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

/**
 * Standard pin configurations
 * 
 * Purpose       ESP32 WROOM  ESP32 Super Mini  Arduino Pro micro            Arduino Pro mini
 * ------------  -----------  ----------------  ---------------------------  ----------------
 * CRSF RX (ws)  GPIO_NUM_16  GPIO20/RX         undefined (Standard RX pin)  undifined
 * CRSF TX (gn)  GPIO_NUM_17  GPIO21/TX         undefined (Standard TX pin)  undefined
 * Voltage       GPIO_NUM_32  ADC1-0/GPIO0      A0                           A0
 * Current       GPIO_NUM_33  ADC1-1/GPIO1      A1                           A1
 * Baro SDA      GPIO_NUM_21  GPIO6/SDA
 * Baro SCL      GPIO_NUM_22  GPIO7/SCL
 * GPS RX (og)   GPIO_NUM_18  --            
 * GPS TX (bl)   GPIO_NUM_19  --
 */

//-----------------------------------------------------------------------------
// CRSF communication
//-----------------------------------------------------------------------------

/**
 * Pins for CRSF communication (leave out for Arduino Pro micro and mini)
*/
//#define CRSF_RX_PIN GPIO_NUM_16
//#define CRSF_TX_PIN GPIO_NUM_17

/**
 * Baudrade for CRSF communication 416666, 420000
*/
#define CRSF_BAUDRATE 416666

#ifdef CONFIGURE_ANALOG_REFERENCE_SOURCE
/**
 * The Source of analog Voltage reference for boards supporting the setting.
 * - DEFAULT (VCC)
 * - INTERNAL (1.1 or 2.56 V)
 * - EXTERNAL (external voltage at AREF pin)
 */
#define ANALOG_REFERENCE_SOURCE INTERNAL
#endif

//-----------------------------------------------------------------------------
// Voltage Sensor
//-----------------------------------------------------------------------------

/**
 * Define this if you want to have a voltage sensor
*/
#define VOLTAGE_SENSOR

#ifdef VOLTAGE_SENSOR
/**
 * Analog pin for Voltage sensor
*/
#define VOLTAGE_ANALOG_PIN A0

/**
 * Values for voltage divider
 */
#define RESISTOR_TO_VOLTAGE 22000
#define RESISTOR_TO_GROUND  1000

#endif
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
#define CURRENT_ANALOG_PIN A1

/**
 * Current sensor parameters
 */
//#define MILLIVOLTS_FOR_ZERO_AMP 2063 // not required for AutoCurrentSensor
#define MILLIVOLTS_PER_AMP 16.6

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
//#define BARO_ALTITUDE_SENSOR

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
 * Reference voltage for analog measurments [mV]
*/
#define ANALOG_REFERENCE_VOLTAGE INTERNAL_REFERENCE_VOLTAGE

/**
 * Readout for maximum analog voltage.
 * Possible values: 1024, 4096 etc.
*/
#define MAX_ANALOG_READ ADC_RESOLUTION

/**
 * Period at startup to calibrate sensors [ms]
 */
#define CALIBRATION_PERIOD 5000

/**
 * Interval to report new values [ms]
*/
#define STANDARD_REPORT_INTERVAL 500

/**
 * Number of milliseconds for sensor timeout [ms]
 */
#define SENSOR_TIMEOUT 10000

/**
 * Update rate for all sensors [ms]
*/
#define UPDATE_RATE 100

#endif