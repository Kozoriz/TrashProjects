#include "utils/threads/synchronization/lock.h"

utils::synchronization::Lock::Lock()
    : std_unique_lock_(mutex_, std::defer_lock) {}

void utils::synchronization::Lock::Acquire() {
  try {
    std_unique_lock_.lock();
  } catch (...) {
    std_unique_lock_.lock();
  }
}
void utils::synchronization::Lock::Release() {
  try {
    std_unique_lock_.unlock();
  } catch (...) {
    std_unique_lock_.unlock();
  }
}

void utils::synchronization::Lock::Try() {
  std_unique_lock_.try_lock();
}
