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
  const std::shared_ptr<rclcpp::node_interfaces::NodeServicesInterface> node_services,
  const rclcpp::QoS & qos_profile)
{
  const std::string node_name = node_base->get_name();

  get_loggers_service_ = create_service<rcl_interfaces::srv::GetLoggerLevels>(
    node_base, node_services,
    node_name + "/get_logger_level",
    [](
        const std::shared_ptr<rmw_request_id_t>,
        const std::shared_ptr<rcl_interfaces::srv::GetLoggerLevels::Request> request,
        std::shared_ptr<rcl_interfaces::srv::GetLoggerLevels::Response> response)
    {
      for (auto &n : request->names) {
        std::cout << "Name: " << n << std::endl;
      }
    },
    qos_profile, nullptr);

  set_loggers_service_ = create_service<rcl_interfaces::srv::SetLoggerLevels>(
    node_base, node_services,
    node_name + "/set_logger_level",
    [](
      const std::shared_ptr<rmw_request_id_t>,
      const std::shared_ptr<rcl_interfaces::srv::SetLoggerLevels::Request> request,
      std::shared_ptr<rcl_interfaces::srv::SetLoggerLevels::Response> response)
    {
#if 0
      auto result = rcl_interfaces::msg::SetLoggerLevelsResult();
      for (auto & p : request->parameters) {
        try {
          result = node_params->set_parameters_atomically(
            {rclcpp::Parameter::from_parameter_msg(p)});
        } catch (const rclcpp::exceptions::ParameterNotDeclaredException & ex) {
          RCLCPP_DEBUG(rclcpp::get_logger("rclcpp"), "Failed to set parameter: %s", ex.what());
          result.successful = false;
          result.reason = ex.what();
        }
        response->results.push_back(result);
      }
#endif
    },
    qos_profile, nullptr);
}
