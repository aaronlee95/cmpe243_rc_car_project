#ifndef TRIP_DETECTOR_H_
#define TRIP_DETECTOR_H_

#include <stdint.h>
#include <stdbool.h>

typedef struct {
  uint32_t threshold;
  uint32_t counter;
} trip_detector_S;

trip_detector_S trip_detector_init(uint32_t threshold_sample_count);

void trip_detector_add_sample(trip_detector_S *trip_detector, bool sample);

bool trip_detector_is_tripped(trip_detector_S *trip_detector);

#endif /* TRIP_DETECTOR_H_ */
