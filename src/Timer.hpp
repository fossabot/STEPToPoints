/**
 * @file Timer.hpp
 * @brief A simple high-resolution timer class for measuring elapsed time
 */

#pragma once
#include <chrono>

/**
 * @class Timer
 * @brief A simple timer utility for measuring elapsed time with millisecond precision
 *
 * This class provides a straightforward way to measure elapsed time using
 * std::chrono::steady_clock. It supports starting, stopping, and querying
 * elapsed time in both milliseconds and seconds. The timer can be queried
 * while running or after being stopped.
 *
 * @note The timer uses steady_clock which is monotonic and not affected by
 *       system clock adjustments.
 *
 * Example usage:
 * @code
 * Timer timer;
 * timer.start();
 * // ... do some work ...
 * timer.stop();
 * std::cout << "Elapsed time: " << timer.elapsed_seconds() << " seconds\n";
 * @endcode
 */
class Timer
{
    /// Type alias for the clock used by the timer
    using clock = std::chrono::steady_clock;

public:
    /**
     * @brief Starts the timer
     *
     * Records the current time as the start time and sets the timer to running state.
     * Can be called multiple times to restart the timer.
     */
    void start()
    {
        m_start_time = clock::now();
        m_is_running = true;
    }

    /**
     * @brief Stops the timer
     *
     * Records the current time as the end time and sets the timer to stopped state.
     * After stopping, elapsed time queries will return the time between start() and stop().
     */
    void stop()
    {
        m_end_time = clock::now();
        m_is_running = false;
    }

    /**
     * @brief Returns the elapsed time in milliseconds
     *
     * If the timer is running, returns the time elapsed since start() was called.
     * If the timer is stopped, returns the time between start() and stop().
     *
     * @return The elapsed time in milliseconds as a double
     */
    [[nodiscard]] double elapsed_milliseconds() const
    {
        std::chrono::time_point<clock> end_time;

        if(m_is_running)
        {
            end_time = clock::now();
        }
        else
        {
            end_time = m_end_time;
        }
        const std::chrono::duration<double, std::milli> ms = end_time - m_start_time;
        return ms.count();
    }

    /**
     * @brief Returns the elapsed time in seconds
     *
     * Convenience method that returns elapsed_milliseconds() / 1000.0.
     *
     * @return The elapsed time in seconds as a double
     */
    [[nodiscard]] double elapsed_seconds() const
    {
        return elapsed_milliseconds() / 1000.0;
    }

private:
    /// The time point when the timer was started
    std::chrono::time_point<clock> m_start_time;

    /// The time point when the timer was stopped
    std::chrono::time_point<clock> m_end_time;

    /// Flag indicating whether the timer is currently running
    bool m_is_running{false};
};