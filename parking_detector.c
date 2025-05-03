#include "parking_detector.h"

static unsigned long spaceStartTime = 0;
static int parkingSpotDetected = 0;

DetectionState currentState = SEARCHING_FIRST_OBSTACLE;

DetectionState updateParkingDetection(float obsatclDistance, unsigned long currentTime, float carSpeed) {
    switch (currentState) {
        case SEARCHING_FIRST_OBSTACLE:
            if (obsatclDistance < OBSTACLE_THRESHOLD_CM) {
                currentState = FOUND_FIRST_OBSTACLE;
            }
            break;

        case FOUND_FIRST_OBSTACLE:
            if (obsatclDistance > OBSTACLE_THRESHOLD_CM) {
                spaceStartTime = currentTime;
                currentState = FOUND_EMPTY_SPACE;
            }
            break;

        case FOUND_EMPTY_SPACE:
            if (obsatclDistance < OBSTACLE_THRESHOLD_CM) {
                float timeInSpace = (currentTime - spaceStartTime) / 1000.0; // ms to sec
                float spaceLength = carSpeed * timeInSpace;

                if (spaceLength >= MIN_PARK_WIDTH_CM) {
                    parkingSpotDetected = 1;
                }

                currentState = FOUND_SECOND_OBSTACLE;
            }
            break;

        case FOUND_SECOND_OBSTACLE:
            currentState = SEARCHING_FIRST_OBSTACLE;
            break;
    }
    return currentState;
}

int isParkingSpotFound(void) {
    return parkingSpotDetected;
}
