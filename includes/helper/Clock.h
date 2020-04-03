#pragma once

#include "Types.h"
#include "Singleton.h"

/*!
 * keaps track of timing e.g. deltatime betwen frames
 */
class Clock
{
	GE_DECLARE_SINGLETON(Clock)

public:

	/*!
	 * @brief setup and startup
	 */
	void Initialize(void);

	/*!
	 * @return	the elapst time to last funktion call in milliseconds
	 * @remarks	resets the timer
	 */
	u64 GetElapsedTime(void);

	/*!
	 * @return	the timescale thats been set. default value 1.0f
	 */
	real GetTimeScale(void) const;
	/*!
	 * @return	the time elapsed since \link Initialize() \endlink
	 */
	u64 GetTimeSinceStart(void) const;

	/*!
	 * @brief			sets the internal timescale
	 * @param timeScale	the new timescale to use
	 */
	void SetTimeScale(real timeScale);

private:

	u64 miEngineStartTime = 0;
	u64 miLastFrameTime = 0;
	real mfTimeScale = 1.0f;

};