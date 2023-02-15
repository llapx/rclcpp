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

#ifndef RCLCPP__NODE_INTERFACES__NODE_EXECUTOR_HPP_
#define RCLCPP__NODE_INTERFACES__NODE_EXECUTOR_HPP_

#include "rclcpp/callback_group.hpp"
#include "rclcpp/macros.hpp"
#include "rclcpp/node_interfaces/node_base_interface.hpp"
#include "rclcpp/node_interfaces/node_executor_interface.hpp"
#include "rclcpp/executors.hpp"
#include "rclcpp/visibility_control.hpp"

namespace rclcpp
{
namespace node_interfaces
{

/// Implementation of the NodeExecutor part of the Node API.
class NodeExecutor : public NodeExecutorInterface
{
public:
  RCLCPP_SMART_PTR_ALIASES_ONLY(NodeExecutor)

  RCLCPP_PUBLIC
  explicit NodeExecutor(rclcpp::node_interfaces::NodeBaseInterface::SharedPtr node_base);

  RCLCPP_PUBLIC
  virtual
  ~NodeExecutor();

  /// Add a callback group to the node.
  RCLCPP_PUBLIC
  void
  add_callback_group(rclcpp::CallbackGroup::SharedPtr group_ptr) override;

  /// Remove a callback group to the node.
  RCLCPP_PUBLIC
  void
  remove_callback_group(rclcpp::CallbackGroup::SharedPtr group_ptr) override;

private:
  RCLCPP_DISABLE_COPY(NodeExecutor)

  rclcpp::node_interfaces::NodeBaseInterface::SharedPtr node_base_;
  rclcpp::executors::SingleThreadedExecutor::SharedPtr executor_;
  std::promise<void> cancel_executor_promise_;
  std::thread thread_;
};

}  // namespace node_interfaces
}  // namespace rclcpp

#endif  // RCLCPP__NODE_INTERFACES__NODE_EXECUTOR_HPP_
