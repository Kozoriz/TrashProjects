#include <boost/program_options.hpp>
#include <fstream>

#include "utils/profile_impl.h"

#include "utils/logger.h"
CREATE_LOGGER("Profile")

namespace utils {

namespace {
template <typename T>
void addOption(boost::program_options::options_description& options_description,
               const std::string& option_name,
               T& variable,
               const std::string& help_description = "") {
  options_description.add_options()(option_name.c_str(),
                                    boost::program_options::value<T>(&variable),
                                    help_description.c_str());
}

void DebulLogAllProperties(
    const boost::program_options::variables_map& boost_var_map) {
  LOG_ERROR(boost_var_map.size());
  for (const auto& pair : boost_var_map) {
    utils::Stringstream debug_string;
    debug_string << "Property : " << pair.first.c_str();
    auto& value = pair.second.value();
    if (auto v = boost::any_cast<utils::UInt>(&value)) {
      debug_string << "= " << *v;
    } else if (auto v = boost::any_cast<utils::String>(&value)) {
      debug_string << "= " << (v->c_str());
    } else if (auto v = boost::any_cast<utils::Float>(&value)) {
      debug_string << "= " << *v;
    }
    LOG_DEBUG(debug_string.str());
  }
}
}  // namespace

ProfileImpl::ProfileImpl(const String& file_name)
    : mover_adapters_count_(0u)
    , engine_centimeters_per_second_(1.f)
    , engine_angle_per_second_(1.f)
    , rotator_max_horyzontal_(0u)
    , rotator_max_vertical_(0u)
    , rotator_min_horyzontal_(0u)
    , rotator_min_vertical_(0u)
    , server_address_("")
    , server_port_(0u) {
  LOG_AUTO_TRACE();
  ProcessIniFile(file_name);
}

UInt ProfileImpl::mover_adapters_count() const {
  return mover_adapters_count_;
}

Float ProfileImpl::engine_centimeters_per_second() const {
  return engine_centimeters_per_second_;
}

Float ProfileImpl::engine_angle_per_second() const {
  return engine_angle_per_second_;
}

UInt ProfileImpl::rotator_max_horyzontal() const {
  return rotator_max_horyzontal_;
}

UInt ProfileImpl::rotator_max_vertical() const {
  return rotator_max_vertical_;
}

UInt ProfileImpl::rotator_min_horyzontal() const {
  return rotator_min_horyzontal_;
}

UInt ProfileImpl::rotator_min_vertical() const {
  return rotator_min_vertical_;
}

const String& ProfileImpl::server_address() const {
  return server_address_;
}

UInt ProfileImpl::server_port() const {
  return server_port_;
}

void ProfileImpl::ProcessIniFile(const String& ini_file) {
  LOG_AUTO_TRACE();
  std::ifstream ifs;
  ifs.open(ini_file);
  assert(ifs.is_open());

  boost::program_options::variables_map temp_variableMap;
  boost::program_options::options_description options_description("Ini");

  addOption(
      options_description, "Mover.MoverAdaptersCount", mover_adapters_count_);
  addOption(options_description,
            "Engine.EngineCentimetersPerSecond",
            engine_centimeters_per_second_);
  addOption(options_description,
            "Engine.EngineAnglePerSecond",
            engine_angle_per_second_);
  addOption(options_description,
            "Servo.RotatorMaxHoryzontal",
            rotator_max_horyzontal_);
  addOption(
      options_description, "Servo.RotatorMaxVertical", rotator_max_vertical_);
  addOption(options_description,
            "Servo.RotatorMinHoryzontal",
            rotator_min_horyzontal_);
  addOption(
      options_description, "Servo.RotatorMinVertical", rotator_min_vertical_);
  addOption(options_description, "TCP.ServerAddress", server_address_);
  addOption(options_description, "TCP.ServerPort", server_port_);

  boost::program_options::store(
      boost::program_options::parse_config_file(ifs, options_description, true),
      temp_variableMap);
  boost::program_options::notify(temp_variableMap);

  DebulLogAllProperties(temp_variableMap);
}

}  // namespace utils
