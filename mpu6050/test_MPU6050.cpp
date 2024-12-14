#include "MPU6050.hpp"
#include "gtest/gtest.h"

TEST(accelConversion, 0000) {
  EXPECT_NEAR(accelConversion(0x0000), 0.0, 0.05);
}

TEST(accelConversion, be28) {
  EXPECT_NEAR(accelConversion(0xbe28), -1.0, 0.05);
}

TEST(accelConversion, bd0c) {
  EXPECT_NEAR(accelConversion(0xbd0c), -1.0, 0.05);
}

TEST(accelConversion, 3ff8) {
  EXPECT_NEAR(accelConversion(0x3ff8), 1.0, 0.05);
}

TEST(accelConversion, 4074) {
  EXPECT_NEAR(accelConversion(0x4074), 1.0, 0.05);
}

// almost 2g -> maximum measurement
TEST(accelConversion, 7fff) {
  EXPECT_NEAR(accelConversion(0x7fff), 2.0, 0.05);
}

// -2g -> maximum measurement
TEST(accelConversion, 8000) {
  EXPECT_NEAR(accelConversion(0x8000), -2.0, 0.05);
}

TEST(accelConversion, 8001) {
  EXPECT_NEAR(accelConversion(0x8001), -2.0, 0.05);
}

TEST(accelConversion, ffff) {
  EXPECT_NEAR(accelConversion(0xffff), -0.0, 0.05);
}

TEST(gyroConversion, 0000){
  EXPECT_NEAR(gyroConversion(0x0000), 0.0, 0.25);
}

TEST(gyroConversion, 4000){
  EXPECT_NEAR(gyroConversion(0x4000), 125.0, 0.25);
}

TEST(gyroConversion, 7fff){
  EXPECT_NEAR(gyroConversion(0x7fff), 250.0, 0.25);
}

TEST(gyroConversion, 8000){
  EXPECT_NEAR(gyroConversion(0x8000), -250.0, 0.25);
}

TEST(gyroConversion, 8001){
  EXPECT_NEAR(gyroConversion(0x8001), -250.0, 0.25);
}

TEST(gyroConversion, ffff){
  EXPECT_NEAR(gyroConversion(0xffff), -0.0, 0.25);
}

// TODO
TEST(tempConversion, 0000){
  EXPECT_NEAR(tempConversion(0x0000), 36.53, 0.1);
}

TEST(tempConversion, 4000){
  EXPECT_NEAR(tempConversion(0x4000), 84.7, 0.1);
}

TEST(tempConversion, 7fff){
  EXPECT_NEAR(tempConversion(0x7fff), 132.9, 0.1);
}

TEST(tempConversion, 8000){
  EXPECT_NEAR(tempConversion(0x8000), -59.8, 0.1);
}

TEST(tempConversion, b000){
  EXPECT_NEAR(tempConversion(0xb000), -23.7, 0.1);
}

TEST(tempConversion, ffff){
  EXPECT_NEAR(tempConversion(0xffff), 36.5, 0.1);
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
