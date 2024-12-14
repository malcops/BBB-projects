#include "MPU6050.hpp"

int MPU6050::init(){

    const unsigned val[2] = {PWR_MGMT_1, 0};
    int f;
    if ((f = open(i2c_device_string.c_str(), O_RDWR)) < 0){
        std::cout << "Did not open i2c device" << std::endl;
        return -1;
    }
    if (ioctl(f, I2C_SLAVE, I2C_ADDRESS) < 0){
        std::cout << "Ioctl call failed" << std::endl;
        return -1;
    }
    if (write(f, val, 2) != 2){
        std::cout << "Failed to write value to address" << std::endl;
        return -1;
    }
    std::cout << "IMU initialization successful" << std::endl;
    return 0;
}

uint8_t readReg(uint8_t reg){

    int f;
    char namebuf[20];
    snprintf(namebuf, sizeof(namebuf), "/dev/i2c-%d", I2C_BUS);
    char buf[10] = {0};
    buf[0] = reg;

    if ((f = open(namebuf, O_RDWR)) < 0){
        std::cout << "Did not open i2c device" << std::endl;
        return -1;
    }
    if (ioctl(f, I2C_SLAVE, I2C_ADDRESS) < 0){
        std::cout << "Ioctl call failed" << std::endl;
        return -1;
    }
    if(write(f, buf, 1) != 1){
        std::cout << "write before read failed" << std::endl;
    }
    if (read(f, buf, 1) != 1){
        std::cout << "bad result read" << std::endl;
        return -1;
    }
    return buf[0];
}

float accelConversion(int regVal){

    if (regVal >= 0x8000){
        regVal = (65536 - regVal);
        regVal = -1 * regVal;
    }
    return static_cast<float>(regVal)/ACCEL_SCALE_FACTOR;
}

float gyroConversion(int regVal){

    if (regVal >= 0x8000){
        regVal = (65536 - regVal);
        regVal = -1 * regVal;
    }
    return static_cast<float>(regVal)/GYRO_SCALE_FACTOR;
}

float tempConversion(int regVal){

    if (regVal >= 0x8000){
        regVal = (65536 - regVal);
        regVal = -1 * regVal;
    }
    return static_cast<float>(regVal)/340 + 36.53;
}

accelXYZ_t MPU6050::readAccelXYZ(){

    accelXYZ_t ret = {0};
    ret.accel_X = accelConversion(readReg(ACCEL_XOUT_H) << 8 | readReg(ACCEL_XOUT_L));
    ret.accel_Y = accelConversion(readReg(ACCEL_YOUT_H) << 8 | readReg(ACCEL_YOUT_L));
    ret.accel_Z = accelConversion(readReg(ACCEL_ZOUT_H) << 8 | readReg(ACCEL_ZOUT_L));
    return ret;
}

gyroXYZ_t MPU6050::readGyroXYZ(){

    gyroXYZ_t ret = {0};
    ret.gyro_X = gyroConversion(readReg(GYRO_XOUT_H) << 8 | readReg(ACCEL_XOUT_L));
    ret.gyro_Y = gyroConversion(readReg(GYRO_YOUT_H) << 8 | readReg(ACCEL_YOUT_L));
    ret.gyro_Z = gyroConversion(readReg(GYRO_ZOUT_H) << 8 | readReg(ACCEL_ZOUT_L));
    return ret;
}

float MPU6050::readTemp(){
    return tempConversion(readReg(TEMP_OUT_H) << 8 | readReg(TEMP_OUT_L));
}

// TODO
void adjustAccelSensitivity(){

    uint16_t REGISTER = 0x1C;

}

// TODO
void adjustGyroSensitivity(){

    uint16_t REGISTER = 0x1B;

}
