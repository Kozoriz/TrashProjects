#pragma once

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
};
}
}
