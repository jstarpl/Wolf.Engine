/*
	Project			 : Wolf Engine. Copyright(c) Pooya Eimandar (http://PooyaEimandar.com) . All rights reserved.
	Source			 : Please direct any bug to https://github.com/PooyaEimandar/Wolf.Engine/issues
	Website			 : http://WolfSource.io
	Name			 : w_timer.h
	Description		 : A timer based on QueryPerformanceCounter
	Comment          :
*/

#ifndef __W_TIMER_H__
#define __W_TIMER_H__

#if _MSC_VER > 1000
#pragma once
#endif

#include "w_game_time.h"

namespace wolf
{
	namespace system
	{
		class w_timer
		{
			friend class w_timer_callback;
		public:
			// Constructor of Timer
			w_timer()
			{
				_timer.set_fixed_time_step(false);
			}

			~w_timer()
			{
			}

			void start()
			{
				_timer.tick([]() { /*NOP*/ });
			}

			void stop()
			{
				_timer.tick([]() { /*NOP*/ });
			}

			//Get total time in seconds
			double get_seconds()
			{
				return _timer.get_total_seconds();
			};

			//Get total time in milliseconds
			double get_milliseconds()
			{
				return _timer.get_total_seconds() * 1000;
			};
			
		private:
			w_game_time		_timer;
		};
	}
}

#endif //__W_TIMER_H__