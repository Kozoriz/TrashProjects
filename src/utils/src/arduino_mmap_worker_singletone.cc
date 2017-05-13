#include "utils/arduino_mmap_worker_singletone.h"

#include "utils/logger.h"

CREATE_LOGGER("ArduionoMmap")

namespace utils {
static const char* mmapFilePath = "/tmp/arduino";

MmapWorker* MmapWorker::instance_ = NULL;

MmapWorker* MmapWorker::getInstance() {
  LOG_AUTO_TRACE();
  if (!instance_) {
    instance_ = new MmapWorker();
  }
  return instance_;
}

void MmapWorker::WriteNewStateToMap(const DroneAction act,
                                    const int32_t act_data) {
    LOG_AUTO_TRACE();
  if (pthread_mutex_lock(&(mmapData_->mutex_)) != 0) {
    LOG_ERROR("pthread_mutex_lock");
    return;
  }

  mmapData_->act_ = act;
  mmapData_->action_data_ = act_data;

  if (pthread_mutex_unlock(&(mmapData_->mutex_)) != 0) {
    LOG_ERROR("pthread_mutex_unlock");
    return;
  }
  if (pthread_cond_signal(&(mmapData_->cond_)) != 0) {
    LOG_ERROR("pthread_cond_signal");
    return;
  }
}

MmapWorker::MmapWorker() {
  LOG_AUTO_TRACE();
  int fd_mmapFile;  // file descriptor for memory mapped file

  /* Create shared memory object and set its size */
  fd_mmapFile = open(mmapFilePath, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
  if (fd_mmapFile == -1) {
    LOG_ERROR("fd error; check errno for details");
    return;
  }

  /* Map shared memory object read-writable */
  mmapData_ = static_cast<struct mmapData*>(mmap(NULL,
                                                 sizeof(struct mmapData),
                                                 PROT_READ | PROT_WRITE,
                                                 MAP_SHARED,
                                                 fd_mmapFile,
                                                 0));
  if (mmapData_ == MAP_FAILED) {
    LOG_ERROR("mmap error");
    return;
  }
}

}  // namespace utils
