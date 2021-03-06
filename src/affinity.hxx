#ifndef AFFINITY__HXX
#define AFFINITY__HXX

#include <vector>
#include <system_error>
#include <stdexcept>
#include <sched.h>

namespace pcat
{
	struct affinity_t
	{
	private:
		std::vector<uint32_t> processors;

		void pinTo(const pthread_t thread, const uint32_t index) const
		{
			if (index >= processors.size())
				throw std::out_of_range{"index into thread affinity object too large"};
			cpu_set_t affinity{};
			CPU_SET(processors[index], &affinity);
			pthread_setaffinity_np(thread, sizeof(cpu_set_t), &affinity);
		}

	public:
		affinity_t() : processors{}
		{
			cpu_set_t affinity{};
			if (sched_getaffinity(0, sizeof(cpu_set_t), &affinity) != 0)
				throw std::system_error{errno, std::system_category()};
			for (uint32_t i{0}; i < CPU_SETSIZE; ++i)
			{
				if (CPU_ISSET(i, &affinity))
				{
					processors.push_back(i);
					CPU_CLR(i, &affinity);
				}
				else if (!CPU_COUNT(&affinity))
					break;
			}
		}

		[[nodiscard]] size_t numProcessors() const noexcept { return processors.size(); }
		[[nodiscard]] auto begin() const noexcept { return processors.begin(); }
		[[nodiscard]] auto end() const noexcept { return processors.end(); }

		void pinThreadTo(std::thread &thread, const uint32_t index) const
			{ pinTo(thread.native_handle(), index); }
		void pinThreadTo(const uint64_t index) const { pinTo(pthread_self(), index); }
	};
} // namespace pcat

#endif /*AFFINITY__HXX*/
