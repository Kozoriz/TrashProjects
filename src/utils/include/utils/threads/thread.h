#pragma once

#include <thread>

#include "utils/threads/thread_runnable.h"

namespace utils {
namespace threads {
class Thread {
 public:
  Thread(ThreadRunnable& runnable);
  bool StartThread();
  void JoinThread();

 private:
  ThreadRunnable& runnable_;
  std::thread std_thread_;
};
}
}
