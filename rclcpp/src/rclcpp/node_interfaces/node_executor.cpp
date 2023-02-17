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

#include "rclcpp/node_interfaces/node_executor.hpp"

#include <string>

#include "tracetools/tracetools.h"

using rclcpp::node_interfaces::NodeExecutor;

NodeExecutor::NodeExecutor(rclcpp::node_interfaces::NodeBaseInterface::SharedPtr node_base)
: node_base_(node_base)
{
  rclcpp::ExecutorOptions exec_options;
  exec_options.context = node_base_->get_context();
  executor_ = std::make_shared<rclcpp::executors::SingleThreadedExecutor>(exec_options);
  if (!thread_.joinable()) {
    cancel_executor_promise_ = std::promise<void>{};
    thread_ = std::thread(
      [this]() {
        auto future = cancel_executor_promise_.get_future();
        executor_->spin_until_future_complete(future);
      }
    );
  }
}

NodeExecutor::~NodeExecutor()
{
  if (thread_.joinable()) {
    cancel_executor_promise_.set_value();
    executor_->cancel();
    thread_.join();
  }
}

void
NodeExecutor::add_callback_group(rclcpp::CallbackGroup::SharedPtr group_ptr)
{
  executor_->add_callback_group(group_ptr, node_base_);
}

void
NodeExecutor::remove_callback_group(rclcpp::CallbackGroup::SharedPtr group_ptr)
{
  executor_->remove_callback_group(group_ptr);
}
