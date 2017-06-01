
#pragma once

#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <cstdio>
#include <pthread.h>

namespace utils {
enum DroneAction {
  STOP = 0,
  SCAN,
  HOR_SERVO,
  VER_SERVO,
  LEFT_TRACK,
  RIGHT_TRACK,
  BOTH_TRACKS
};

struct mmapData {
  pthread_mutex_t mutex_;
  pthread_cond_t cond_;
  DroneAction act_ = STOP;
  int32_t action_data_ = 0;
};

class MmapWorker {
 public:
  static MmapWorker* getInstance();
  void WriteNewStateToMap(const DroneAction act, const int32_t act_data);
  int32_t GetCurrentActData();
  DroneAction GetCurrentAct();

 private:
  MmapWorker();

 private:
  static MmapWorker* instance_;

  struct mmapData* mmapData_;
};

}  // namespace utils
