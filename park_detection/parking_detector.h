#ifndef PARKING_DETECTOR_H
#define PARKING_DETECTOR_H

// Thresholds and constants
#define OBSTACLE_THRESHOLD_CM 10.0
#define MIN_PARK_WIDTH_CM    20.0

typedef enum {
    SEARCHING_FIRST_OBSTACLE,
    FOUND_FIRST_OBSTACLE,
    FOUND_EMPTY_SPACE,
    FOUND_SECOND_OBSTACLE
} DetectionState;

// Function declarations
DetectionState updateParkingDetection(float obstacleDistance, unsigned long currentTime, float carSpeed);
int isParkingSpotFound(void);

#endif
