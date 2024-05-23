#ifndef CONFIG_H
#define CONFIG_H

/**
 * Baudrade for CRSF communication
*/
#define CRSF_BAUDRATE 420000

/**
 * Pins for CRSF communication
*/
#define RX_PIN 16
#define TX_PIN 17

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

#endif