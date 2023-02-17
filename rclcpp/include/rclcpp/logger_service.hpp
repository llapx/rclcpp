// Copyright 2015 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef RCLCPP__LOGGER_SERVICE_HPP_
#define RCLCPP__LOGGER_SERVICE_HPP_

#include <memory>
#include <string>

#include "rcl_interfaces/srv/get_logger_levels.hpp"
#include "rcl_interfaces/srv/set_logger_levels.hpp"
#include "rclcpp/executors.hpp"
#include "rclcpp/macros.hpp"
#include "rclcpp/node.hpp"
#include "rclcpp/qos.hpp"
#include "rclcpp/visibility_control.hpp"
#include "rmw/rmw.h"

namespace rclcpp
{

class LoggerService
{
public:
  RCLCPP_SMART_PTR_DEFINITIONS(LoggerService)

  [[deprecated("use rclcpp::QoS instead of rmw_qos_profile_t")]]
  RCLCPP_PUBLIC
  LoggerService(
    const std::shared_ptr<node_interfaces::NodeBaseInterface> node_base,
    const std::shared_ptr<node_interfaces::NodeExecutorInterface> node_executor,
    const std::shared_ptr<node_interfaces::NodeServicesInterface> node_services,
    const rmw_qos_profile_t & qos_profile)
  : LoggerService(
      node_base,
      node_executor,
      node_services,
      rclcpp::QoS(rclcpp::QoSInitialization::from_rmw(qos_profile)))
  {}

  RCLCPP_PUBLIC
  LoggerService(
    const std::shared_ptr<node_interfaces::NodeBaseInterface> node_base,
    const std::shared_ptr<node_interfaces::NodeExecutorInterface> node_executor,
    const std::shared_ptr<node_interfaces::NodeServicesInterface> node_services,
    const rclcpp::QoS & qos_profile = rclcpp::ServicesQoS());

private:
  rclcpp::Service<rcl_interfaces::srv::GetLoggerLevels>::SharedPtr get_loggers_service_;
  rclcpp::Service<rcl_interfaces::srv::SetLoggerLevels>::SharedPtr set_loggers_service_;
  rclcpp::CallbackGroup::SharedPtr callback_group_{nullptr};
};

}  // namespace rclcpp

#endif  // RCLCPP__LOGGER_SERVICE_HPP_
