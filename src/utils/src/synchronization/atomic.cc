
namespace utils {
namespace synchronization {
template <typename T>
class Atomic {
 public:
  Atomic();

 private:
  T* obj_;
};
}
}
