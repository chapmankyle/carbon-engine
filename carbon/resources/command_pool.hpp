#pragma once

#ifndef RES_COMMAND_POOL_HPP
#define RES_COMMAND_POOL_HPP

#include "carbon/backend.hpp"

namespace carbon {

	/**
	 * @brief A wrapper for the Vulkan command pool, which allows command buffer
	 * memory to be allocated from. Must not be used across multiple threads.
	 */
	class CommandPool {

	private:

		/**
		 * @brief Handle on the command pool object.
		 */
		VkCommandPool m_pool;

		/**
		 * @brief The flags used to create the command pool.
		 */
		VkCommandPoolCreateFlags m_flags;

		/**
		 * @brief Queue family that supports the graphics commands.
		 */
		u32 m_queue_family;

	public:

		/**
		 * @brief Initializes the command pool.
		 * @param queueFamily The queue family to use for the command pool.
		 * @param flags [Optional] The flags used to indicate usage of command pool.
		 */
		explicit CommandPool(u32 queueFamily, const VkCommandPoolCreateFlags &flags = 0u);

		CommandPool(const CommandPool &other) = delete;

		CommandPool& operator=(const CommandPool&) = delete;

		/**
		 * @brief Destructor for the command pool.
		 */
		~CommandPool();

		/**
		 * @brief Destroys the command pool.
		 */
		void destroy();

		/**
		 * @returns The handle on the underlying command pool.
		 */
		const VkCommandPool& getHandle() const {
			return m_pool;
		}

		/**
		 * @returns The flags associated with the command pool.
		 */
		const VkCommandPoolCreateFlags& getFlags() const {
			return m_flags;
		}

		/**
		 * @returns The queue family associated with the command pool.
		 */
		const u32 getQueueFamily() const {
			return m_queue_family;
		}

	};

} // namespace carbon

#endif // RES_COMMAND_POOL_HPP
