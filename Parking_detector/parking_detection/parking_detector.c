#include "parking_detector.h"

// State and timing for the left sensor
static unsigned long leftSpaceStartTime = 0;
static int leftParkingSpotDetected = 0;
static DetectionState leftSensorState = SEARCHING_FIRST_OBSTACLE;

// State and timing for the right sensor
static unsigned long rightSpaceStartTime = 0;
static int rightParkingSpotDetected = 0;
static DetectionState rightSensorState = SEARCHING_FIRST_OBSTACLE;

// Common function to update the parking detection state for a given sensor
DetectionState updateSensorParkingDetection(DetectionState *sensorState, 
                                             unsigned long *spaceStartTime, 
                                             int *parkingSpotDetected, 
                                             float obsatclDistance, 
                                             unsigned long currentTime, 
                                             float carSpeed) {
    switch (*sensorState) {
        case SEARCHING_FIRST_OBSTACLE:
            if (obsatclDistance < OBSTACLE_THRESHOLD_CM) {
                *sensorState = FOUND_FIRST_OBSTACLE;
            }
            break;

        case FOUND_FIRST_OBSTACLE:
            if (obsatclDistance > OBSTACLE_THRESHOLD_CM) {
                *spaceStartTime = currentTime;
                *sensorState = FOUND_EMPTY_SPACE;
            }
            break;

        case FOUND_EMPTY_SPACE:
            if (obsatclDistance < OBSTACLE_THRESHOLD_CM) {
                float timeInSpace = (currentTime - *spaceStartTime) / 1000.0; // ms to sec
                float spaceLength = carSpeed * timeInSpace;

                if (spaceLength >= MIN_PARK_WIDTH_CM) {
                    *parkingSpotDetected = 1;
                }

                *sensorState = FOUND_SECOND_OBSTACLE;
            }
            break;

        case FOUND_SECOND_OBSTACLE:
            *sensorState = SEARCHING_FIRST_OBSTACLE;
            break;
    }

    return *sensorState;
}

int isParkingSpotFoundLeft(void) {
    return leftParkingSpotDetected;
}

int isParkingSpotFoundRight(void) {
    return rightParkingSpotDetected;
}

int updateParkingDetection(float obsatclDistanceLeft, float obsatclDistanceRight, unsigned long currentTime, float carSpeed) {
    // Update parking detection for both left and right sensors
    leftSensorState = updateSensorParkingDetection(&leftSensorState, &leftSpaceStartTime, &leftParkingSpotDetected, obsatclDistanceLeft, currentTime, carSpeed);
    rightSensorState = updateSensorParkingDetection(&rightSensorState, &rightSpaceStartTime, &rightParkingSpotDetected, obsatclDistanceRight, currentTime, carSpeed);

    // Return true if parking spot is found on either side
    return leftParkingSpotDetected || rightParkingSpotDetected;
}
