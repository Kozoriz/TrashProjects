#include "utils/threads/thread.h"

utils::threads::Thread::Thread(utils::threads::ThreadRunnable& runnable)
    : runnable_(runnable) {
}

bool utils::threads::Thread::StartThread() {}
void utils::threads::Thread::JoinThread() {}
