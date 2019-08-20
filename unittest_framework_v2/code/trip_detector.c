#include "trip_detector.h"

trip_detector_S trip_detector_init(uint32_t threshold_sample_count) {
  trip_detector_S trip_detector = (trip_detector_S) {.threshold = threshold_sample_count};
  return trip_detector;
}

void trip_detector_add_sample(trip_detector_S *trip_detector, bool sample) {
  trip_detector->counter += sample ? 1 : 0;
}

bool trip_detector_is_tripped(trip_detector_S *trip_detector) {
  return (trip_detector->counter >= trip_detector->threshold);
}
