#include <fcntl.h>
#include "stdint.h"
#include <iostream>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <unistd.h>

// AD0 = 0 - 1101000
// AD0 = 1 - 1101001
#define I2C_ADDRESS_LOW 0x68
#define I2C_ADDRESS_HI  0x69
#define I2C_ADDRESS I2C_ADDRESS_LOW

#define I2C_BUS 2

// data are 16 bits wide
// e.g. high byte at 0x3b = 0x30
//       low byte at 0x3c = 0xf8
#define ACCEL_XOUT_H 0x3B
#define ACCEL_XOUT_L 0x3C
#define ACCEL_YOUT_H 0x3D
#define ACCEL_YOUT_L 0x3E
#define ACCEL_ZOUT_H 0x3F
#define ACCEL_ZOUT_L 0x40
#define GYRO_XOUT_H  0x43
#define GYRO_XOUT_L  0x44
#define GYRO_YOUT_H  0x45
#define GYRO_YOUT_L  0x46
#define GYRO_ZOUT_H  0x47
#define GYRO_ZOUT_L  0x48

#define ACCEL_SCALE_FACTOR 16384
#define GYRO_SCALE_FACTOR 131

#define TEMP_OUT_H 0x41
#define TEMP_OUT_L 0x42

#define PWR_MGMT_1 0x6B

static const std::string i2c_device_string = "/dev/i2c-2";

struct accelXYZ_t {
    float accel_X;
    float accel_Y;
    float accel_Z;
};

struct gyroXYZ_t {
    float gyro_X;
    float gyro_Y;
    float gyro_Z;
};

class MPU6050 {
    public:
        int init();
        accelXYZ_t readAccelXYZ(void);
        gyroXYZ_t readGyroXYZ(void);
        float readTemp(void);
};

uint8_t readReg(uint8_t reg);
float accelConversion(int regVal);
float gyroConversion(int regVal);
float tempConversion(int regVal);

