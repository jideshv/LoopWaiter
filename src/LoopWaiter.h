// Copyright (c) 2018 Jidesh Veeramachaneni
// Distributed under the MIT License (license terms are at http://opensource.org/licenses/MIT).

#pragma once

/**
 * The LoopWaiter class can be used on any microcontroller to 
 * simplify waiting without blocking the main loop() function
 * with a delay(). It works even if the millis() counter has
 * overflowed.
 *
 * @tparam T the type used by the millis() function
 */
template <typename T>
class LoopWaiter
{
public:
  /**
   * Construct the LoopWaiter with a function pointer to
   * the millis() function on your platform.
   *
   * @param millis the system millis function
   * @param repeat set to false if you do not want to repeat
   */
  LoopWaiter(std::function<T()> millis, bool repeat = true) :
  m_started(false),
  m_repeat(repeat),
  m_start(0),
  m_wait_time(0),
  m_millis(millis) {}

  ~LoopWaiter() {}
  
  /**
   * Sets the wait time and starts the timer.
   * You must call Expired() to trigger a calculation
   * of the duration and check if the timer has
   * expired. Calling Start() after the timer is 
   * already started will reset the interval.
   *
   * @param wait_time set how many milliseconds to wait
   */
  void Start(T wait_time) {
    m_start = m_millis();
    m_wait_time = wait_time;
    m_started = true;
  }
  
  /**
   * Stops the timer. Calls to Expired when the
   * timer is stopped will always return false.
   */
  void Stop() {
    m_started = false;
  }
    
  /**
   * If the timer has already been started, Expired will
   * return true after the specified milliseconds has passed.
   * 
   * @return true if wait_time has passed since a Start() call or a repeat
   */
  bool Expired() {
    if (!m_started) {
      return false;
    }
    
    T diff = TimeDiff(m_millis());
    bool expired = (m_wait_time <= diff);
    
    if (expired && m_repeat) {
      Repeat();
    } else if (expired) {
      Stop();
    }
    
    return expired;
  }
  
private:
  bool m_started;
  bool m_repeat;
  T m_start;
  T m_wait_time;
  std::function<T()> m_millis;
  
  void Repeat() {
    if (!m_started) {
      return;
    }
    m_start = m_millis();
  }

  T TimeDiff (T now) {
    if (now < m_start) {
      // timer has overflowed
      return (std::numeric_limits<T>::max() - m_start + now);
    } else {
      return (now - m_start);
    }
  }
};
