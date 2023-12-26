<!-- ![Example Image](https://github.com/alieffsl/Robotics-Lab-II-Line-Following/blob/main/Project-Rule/Robotics%20Lab%20II%20-%20Project%20Rule_1.png)
![Example Image](https://github.com/alieffsl/Robotics-Lab-II-Line-Following/blob/main/Project-Rule/Robotics%20Lab%20II%20-%20Project%20Rule_2.png)
![Example Image](https://github.com/alieffsl/Robotics-Lab-II-Line-Following/blob/main/Project-Rule/Robotics%20Lab%20II%20-%20Project%20Rule_3.png)
![Example Image](https://github.com/alieffsl/Robotics-Lab-II-Line-Following/blob/main/Project-Rule/Robotics%20Lab%20II%20-%20Project%20Rule_4.png) -->

# Line Following Project - Robotics Lab II

<!-- BlackPink Team:
    - M.Alief Faisal Hakim
    - M. Syahnabil Hammam Sungkar
    - Lakki Taj Roid
    - Saddam Alfattah Putra Adi
    - Muhammad Sandi R. Saepudin
    - Edbert Fernando -->

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Library Usage](#usage)
  - [Servo Functions](#servo-functions)
  - [Motor Functions](#motor-functions)
  - [Line Following Functions](#line-following-functions)
  - [Encoder Functions](#encoder-functions)
- [Project Rules](#project-rule)

## Introduction

This project is undertaken to fulfill the requirements for the Robotics Experiment 2 course.

## Features

This robot utilizes 4 mechanum DC motors, equipped with a dynamixel servo lifter and line sensors tcrt5000 module. The robot is capable of following line patterns with customizable commands according to desired conditions.

## Library Usage

### Servo Functions
- `servoAngkut(dtime)`
- `servoTaruh(dtime)`
- `servoReset(dtime)`

### Motor Functions
- `motorDrivePID(speedL, speedR)`
- `move(speedFL, speedFR, speedRL, speedRR)`
- `StopMotors()`

### Line Following Functions
- `autolinefollow(duration, dbreaktime)`
- `line(desiredMode, desiredSpeed, dbreaktime)`
- `turn(action)`
- `findline(speedL, speedR, dbreaktime)`
- `dnext()`
- `spinheading(sudut)`
- `linedelay(speed, dtime, dbreaktime)`
- `linefoll()`
- `lineIntersect(n)`

### Encoder Functions
- `FWD(distanceCM, speed)`
- `BWD(distanceCM, speed)`
- `R(distanceCM, speed)`
- `L(distanceCM, speed)`
- `FWD_XR(distanceCM, speed)`
- `FWD_XL(distanceCM, speed)`
- `BWD_XR(distanceCM, speed)`
- `BWD_XL(distanceCM, speed)`
- `TR(distanceCM=25, speed=200)`
- `TL(distanceCM=25, speed=200)`

## Project Rules

The attached project rules can be found at the following link: 