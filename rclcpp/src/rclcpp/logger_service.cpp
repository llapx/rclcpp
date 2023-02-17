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

#include "rclcpp/logger_service.hpp"

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

#include "rclcpp/logging.hpp"

using rclcpp::LoggerService;

LoggerService::LoggerService(
  const std::shared_ptr<rclcpp::node_interfaces::NodeBaseInterface> node_base,
  const std::shared_ptr<rclcpp::node_interfaces::NodeExecutorInterface> node_executor,
  const std::shared_ptr<rclcpp::node_interfaces::NodeServicesInterface> node_services,
  const rclcpp::QoS & qos_profile)
{
  const std::string node_name = node_base->get_name();
  callback_group_ = node_base->create_callback_group(
    rclcpp::CallbackGroupType::MutuallyExclusive,
    false
  );
  node_executor->add_callback_group(callback_group_);

  get_loggers_service_ = create_service<rcl_interfaces::srv::GetLoggerLevels>(
    node_base, node_services,
    node_name + "/get_logger_levels",
    [](
      const std::shared_ptr<rmw_request_id_t>,
      const std::shared_ptr<rcl_interfaces::srv::GetLoggerLevels::Request> request,
      std::shared_ptr<rcl_interfaces::srv::GetLoggerLevels::Response> response)
    {
      int ret = 0;
      for (auto & n : request->names) {
        auto level = rcl_interfaces::msg::LoggerLevel();
        level.name = n;
        ret = rcutils_logging_get_logger_level(n.c_str());
        if (ret < 0) {
          ret = 0;
        }
        level.level = (uint8_t)ret;
        response->levels.push_back(level);
      }
    },
    qos_profile, callback_group_);

  set_loggers_service_ = create_service<rcl_interfaces::srv::SetLoggerLevels>(
    node_base, node_services,
    node_name + "/set_logger_levels",
    [](
      const std::shared_ptr<rmw_request_id_t>,
      const std::shared_ptr<rcl_interfaces::srv::SetLoggerLevels::Request> request,
      std::shared_ptr<rcl_interfaces::srv::SetLoggerLevels::Response> response)
    {
      int ret = 0;
      auto result = rcl_interfaces::msg::SetLoggerLevelsResult();
      for (auto & l : request->levels) {
        ret = rcutils_logging_set_logger_level(l.name.c_str(), l.level);
        if (ret != RCUTILS_RET_OK) {
          result.successful = false;
          result.reason = "Unsupported log level!";
        } else {
          result.successful = true;
        }
        response->results.push_back(result);
      }
    },
    qos_profile, callback_group_);
}
