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

#include <PCA9536D.h>


PCA9536::PCA9536()
{
    _i2cPort = NULL;
    _deviceAddress = PCA9536_ADDRESS_INVALID;
}

bool PCA9536::begin(TwoWire &wirePort)
{
    _deviceAddress = PCA9536_ADDRESS;
    _i2cPort = &wirePort;

    return (isConnected());
}

//Returns true if a device ack's at given address
boolean PCA9536::isConnected(void)
{
    _i2cPort->beginTransmission((uint8_t)_deviceAddress);
    return (_i2cPort->endTransmission() == 0);
}

PCA9536_error_t PCA9536::pinMode(uint8_t pin, uint8_t mode)
{
    PCA9536_error_t err;
    uint8_t cfgRegister = 0;

    if (pin > PCA9536_MAX_GPIO)
        return PCA9536_ERROR_UNDEFINED;

    err = readI2CRegister(&cfgRegister, PCA9536_REGISTER_CONFIGURATION);
    if (err != PCA9536_ERROR_SUCCESS)
    {
        return err;
    }
    cfgRegister &= ~(1 << pin); // Clear pin bit
    if (mode == INPUT)          // Set the bit if it's being set to INPUT (opposite of Arduino)
    {
        cfgRegister |= (1 << pin);
    }
    return writeI2CRegister(cfgRegister, PCA9536_REGISTER_CONFIGURATION);
}

PCA9536_error_t PCA9536::write(uint8_t pin, uint8_t value)
{
    PCA9536_error_t err;
    uint8_t outputRegister = 0;

    if (pin > PCA9536_MAX_GPIO)
        return PCA9536_ERROR_UNDEFINED;

    err = readI2CRegister(&outputRegister, PCA9536_REGISTER_OUTPUT_PORT);
    if (err != PCA9536_ERROR_SUCCESS)
    {
        return err;
    }
    // TODO: Break out of here if it's already set correctly
    outputRegister &= ~(1 << pin); // Clear pin bit
    if (value == HIGH)             // Set the bit if it's being set to HIGH (opposite of Arduino)
    {
        outputRegister |= (1 << pin);
    }
    return writeI2CRegister(outputRegister, PCA9536_REGISTER_OUTPUT_PORT);
}

PCA9536_error_t PCA9536::digitalWrite(uint8_t pin, uint8_t value)
{
    return write(pin, value);
}

uint8_t PCA9536::readReg()
{
    PCA9536_error_t err;
    uint8_t inputRegister = 0;

    err = readI2CRegister(&inputRegister, PCA9536_REGISTER_INPUT_PORT);
    if (err != PCA9536_ERROR_SUCCESS)
    {
        return err;
    }
    return (inputRegister & (0x0f));
}

uint8_t PCA9536::read(uint8_t pin)
{
    PCA9536_error_t err;
    uint8_t inputRegister = 0;

    if (pin > PCA9536_MAX_GPIO)
        return PCA9536_ERROR_UNDEFINED;

    err = readI2CRegister(&inputRegister, PCA9536_REGISTER_INPUT_PORT);
    if (err != PCA9536_ERROR_SUCCESS)
    {
        return err;
    }
    return (inputRegister & (1 << pin)) >> pin;
}

uint8_t PCA9536::digitalRead(uint8_t pin)
{
    return read(pin);
}

PCA9536_error_t PCA9536::invert(uint8_t pin, PCA9536_invert_t inversion)
{
    PCA9536_error_t err;
    uint8_t invertRegister = 0;

    if (pin > PCA9536_MAX_GPIO)
        return PCA9536_ERROR_UNDEFINED;

    err = readI2CRegister(&invertRegister, PCA9536_REGISTER_POLARITY_INVERSION);
    if (err != PCA9536_ERROR_SUCCESS)
    {
        return err;
    }
    // TODO: Break out of here if it's already set correctly
    invertRegister &= ~(1 << pin);   // Clear pin bit
    if (inversion == PCA9536_INVERT) // Set the bit if it's being set to inverted
    {
        invertRegister |= (1 << pin);
    }
    return writeI2CRegister(invertRegister, PCA9536_REGISTER_POLARITY_INVERSION);
}

PCA9536_error_t PCA9536::revert(uint8_t pin)
{
    return invert(pin, PCA9536_RETAIN);
}

PCA9536_error_t PCA9536::readI2CBuffer(uint8_t *dest, PCA9536_REGISTER_t startRegister, uint16_t len)
{
    if (_deviceAddress == PCA9536_ADDRESS_INVALID)
    {
        return PCA9536_ERROR_INVALID_ADDRESS;
    }
    _i2cPort->beginTransmission((uint8_t)_deviceAddress);
    _i2cPort->write(startRegister);
    if (_i2cPort->endTransmission(false) != 0)
    {
        return PCA9536_ERROR_READ;
    }

    _i2cPort->requestFrom((uint8_t)_deviceAddress, (uint8_t)len);
    for (int i = 0; i < (int)len; i++)
    {
        dest[i] = _i2cPort->read();
    }

    return PCA9536_ERROR_SUCCESS;
}

PCA9536_error_t PCA9536::writeI2CBuffer(uint8_t *src, PCA9536_REGISTER_t startRegister, uint16_t len)
{
    if (_deviceAddress == PCA9536_ADDRESS_INVALID)
    {
        return PCA9536_ERROR_INVALID_ADDRESS;
    }
    _i2cPort->beginTransmission((uint8_t)_deviceAddress);
    _i2cPort->write(startRegister);
    for (int i = 0; i < (int)len; i++)
    {
        _i2cPort->write(src[i]);
    }
    if (_i2cPort->endTransmission(true) != 0)
    {
        return PCA9536_ERROR_WRITE;
    }
    return PCA9536_ERROR_SUCCESS;
}

PCA9536_error_t PCA9536::readI2CRegister(uint8_t *dest, PCA9536_REGISTER_t registerAddress)
{
    return readI2CBuffer(dest, registerAddress, 1);
}

PCA9536_error_t PCA9536::writeI2CRegister(uint8_t data, PCA9536_REGISTER_t registerAddress)
{
    return writeI2CBuffer(&data, registerAddress, 1);
}
