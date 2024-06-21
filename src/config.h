#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

/**
 * Define this if you want to have a battery sensor
*/
#define BATTERY_SENSOR

/**
 * Define this if you want to have a Baro (Vario) sensor
*/
#define BARO_ALTITUDE_SENSOR

/**
 * Define this if you want to have a GPS sensor
*/
#define GPS_SENSOR

/**
 * Analog pin for Voltage sensor
*/
#define VOLTAGE_ANALOG_PIN GPIO_NUM_32

/**
 * Analog pin for Current sensor
*/
#define CURRENT_ANALOG_PIN GPIO_NUM_33

/**
 * Baudrade for CRSF communication
*/
#define CRSF_BAUDRATE 420000

/**
 * Pins for CRSF communication
*/
#define RX_PIN GPIO_NUM_16
#define TX_PIN GPIO_NUM_17

/**
 * Baudrate for GPS communication
*/
#define GPS_BAUDRATE 9600

/**
 * Pins for GPS communication
*/
#define GPS_RX_PIN GPIO_NUM_18
#define GPS_TX_PIN GPIO_NUM_19

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