CC=g++

.PHONY: test example

all: test example

test:
	$(CC) MPU6050.cpp test_MPU6050.cpp -lgtest -lpthread -o gtest

example:
	$(CC) MPU6050.cpp main.cpp -o example
