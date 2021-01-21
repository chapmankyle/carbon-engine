// file      : carbon/resources/command_buffer.hpp
// copyright : Copyright (c) 2020-present, Kyle Chapman
// license   : GPL-3.0; see accompanying LICENSE file

#pragma once

#ifndef RES_COMMAND_BUFFER_HPP
#define RES_COMMAND_BUFFER_HPP

#include "carbon/backend.hpp"

namespace carbon {

	// forward-declare classes that would result in circular dependency
	class LogicalDevice;
	class CommandPool;

	namespace buffer {

		/**
		 * @brief Current state of the command buffer.
		 */
		enum class State : i32 {
			Invalid = -1,
			Ready,
			Recording
		};

	} // namespace buffer

	/**
	 * @brief A wrapper class for the Vulkan command buffer.
	 */
	class CommandBuffer {

	private:

		/**
		 * @brief Device used for recording to command buffer.
		 */
		const class LogicalDevice *m_device;

		/**
		 * @brief Command pool that is used to get the command buffer from.
		 */
		const class CommandPool *m_pool;

		/**
		 * @brief Handle on the underlying Vulkan command buffer.
		 */
		VkCommandBuffer m_command_buffer;

		/**
		 * @brief Current state of the command buffer.
		 */
		buffer::State m_state{ buffer::State::Invalid };

	public:

		/**
		 * @brief Initializes the command buffer.
		 * @param device The logical device to use.
		 * @param pool The command pool to use.
		 */
		CommandBuffer(const class LogicalDevice *device, const class CommandPool *pool);

		/**
		 * @brief Destructor for the command buffer.
		 */
		~CommandBuffer();

		/**
		 * @brief Begins the recording into the command buffer.
		 * @param usage [Optional] The usage for the command buffer. Default is one-time submit.
		 */
		void begin(VkCommandBufferUsageFlagBits usage = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);

		/**
		 * @brief Ends the command buffer recording.
		 */
		void end();

		/**
		 * @returns `true` if the command buffer is currently recording, `false` otherwise.
		 */
		bool inUse() const {
			return m_state == buffer::State::Recording;
		}

		/**
		 * @returns The handle on the command buffer.
		 */
		const VkCommandBuffer& getHandle() const {
			return m_command_buffer;
		}

		/**
		 * @returns The device associated with the command buffer.
		 */
		const class LogicalDevice* getDevice() const;

		/**
		 * @returns The command pool associated with the command buffer.
		 */
		const class CommandPool* getPool() const;

	};

} // namespace carbon

#endif // RES_COMMAND_BUFFER_HPP
