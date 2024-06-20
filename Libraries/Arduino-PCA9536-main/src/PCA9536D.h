/*
  This is a library written for the PCA9536 4-bit I2C I/O Expander
  SparkFun sells these at its website: www.sparkfun.com
  Do you like this library? Help support SparkFun. Buy a board!
  https://www.sparkfun.com/products/14733
  Written by Jim Lindblom @ SparkFun Electronics, May 4th, 2018
  The PCA9536 is a 4-bit I/O digital expander, which communicates via an I2C bus.
  The expander can read or write four separate I/O.
  
  This library handles the initialization of the PCA9536 and supports standard
  pinMode, digitalRead, and digitalWrite functions.
  https://github.com/sparkfunX/SparkFun_PCA9536_Arduino_Library

  Development environment specifics:
  Arduino IDE 1.8.5
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#if (ARDUINO >= 100)
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define DEBUG_PCA9536

#include <Wire.h>

//  Valid PCA9536 addresses
typedef enum
{
    PCA9536_ADDRESS = 0x41,
    PCA9536_ADDRESS_INVALID = 0xFF
} PCA9536_Address_t;

// PCA9536 registers:
typedef enum
{
    PCA9536_REGISTER_INPUT_PORT = 0x00,
    PCA9536_REGISTER_OUTPUT_PORT = 0x01,
    PCA9536_REGISTER_POLARITY_INVERSION = 0x02,
    PCA9536_REGISTER_CONFIGURATION = 0x03,
    PCA9536_REGISTER_INVALID
} PCA9536_REGISTER_t;

// PCA9536 error code returns:
typedef enum
{
    PCA9536_ERROR_READ = -4,
    PCA9536_ERROR_WRITE = -3,
    PCA9536_ERROR_INVALID_ADDRESS = -2,
    PCA9536_ERROR_UNDEFINED = -1,
    PCA9536_ERROR_SUCCESS = 1
} PCA9536_error_t;
const PCA9536_error_t PCA9536_SUCCESS = PCA9536_ERROR_SUCCESS;

// PCA9536 invert/normal values:
typedef enum
{
    PCA9536_RETAIN,
    PCA9536_INVERT,
    PCA9536_INVERT_END
} PCA9536_invert_t;

// rgb, white LED definitions for QWIIC RGB Breakout
enum
{
    PCA9536_WHITE, // 0
    PCA9536_RED,   // 1
    PCA9536_GREEN, // 2
    PCA9536_BLUE   // 3
};

// PCA9536 has four GPIO pins: 0-3
#define PCA9536_MAX_GPIO 3

class PCA9536
{
public:
    PCA9536();

    bool begin(TwoWire &wirePort = Wire);
    bool isConnected();

    // pinMode can set a pin (0-3) to INPUT or OUTPUT
    PCA9536_error_t pinMode(uint8_t pin, uint8_t mode);

    // digitalWrite and write can be used to set a pin HIGH or LOW
    PCA9536_error_t digitalWrite(uint8_t pin, uint8_t value);
    PCA9536_error_t write(uint8_t pin, uint8_t value);

    // readReg can be used to read the whole input register (4 bits)
    uint8_t readReg();

    // digitalRead and read can be used to read a pin (0-3)
    uint8_t digitalRead(uint8_t pin);
    uint8_t read(uint8_t pin);

    // invert and revert can be used to invert (or not) the I/O logic during a read
    PCA9536_error_t invert(uint8_t pin, PCA9536_invert_t inversion = PCA9536_INVERT);
    PCA9536_error_t revert(uint8_t pin);

private:
    TwoWire *_i2cPort; //The generic connection to user's chosen I2C hardware
    PCA9536_Address_t _deviceAddress;

    // I2C Read/Write
    PCA9536_error_t readI2CBuffer(uint8_t *dest, PCA9536_REGISTER_t startRegister, uint16_t len);
    PCA9536_error_t writeI2CBuffer(uint8_t *src, PCA9536_REGISTER_t startRegister, uint16_t len);
    PCA9536_error_t readI2CRegister(uint8_t *dest, PCA9536_REGISTER_t registerAddress);
    PCA9536_error_t writeI2CRegister(uint8_t data, PCA9536_REGISTER_t registerAddress);
};
