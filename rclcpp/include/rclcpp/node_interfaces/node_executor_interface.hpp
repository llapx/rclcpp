// Copyright 2016 Open Source Robotics Foundation, Inc.
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

#ifndef RCLCPP__NODE_INTERFACES__NODE_EXECUTOR_INTERFACE_HPP_
#define RCLCPP__NODE_INTERFACES__NODE_EXECUTOR_INTERFACE_HPP_

#include "rclcpp/callback_group.hpp"
#include "rclcpp/macros.hpp"
#include "rclcpp/node_interfaces/detail/node_interfaces_helpers.hpp"
#include "rclcpp/visibility_control.hpp"

namespace rclcpp
{
namespace node_interfaces
{

/// Pure virtual interface class for the NodeExecutor part of the Node API.
class NodeExecutorInterface
{
public:
  RCLCPP_SMART_PTR_ALIASES_ONLY(NodeExecutorInterface)

  RCLCPP_PUBLIC
  virtual
  ~NodeExecutorInterface() = default;

  /// Add a callback group to the node.
  RCLCPP_PUBLIC
  virtual
  void
  add_callback_group(rclcpp::CallbackGroup::SharedPtr group_ptr) = 0;
};

}  // namespace node_interfaces
}  // namespace rclcpp

RCLCPP_NODE_INTERFACE_HELPERS_SUPPORT(rclcpp::node_interfaces::NodeExecutorInterface, executor)

#endif  // RCLCPP__NODE_INTERFACES__NODE_EXECUTOR_INTERFACE_HPP_
