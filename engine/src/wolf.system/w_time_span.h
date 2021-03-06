/*
	Project			 : Wolf Engine. Copyright(c) Pooya Eimandar (http://PooyaEimandar.com) . All rights reserved.
	Source			 : Please direct any bug to https://github.com/PooyaEimandar/Wolf.Engine/issues
	Website			 : http://WolfSource.io
	Name			 : w_time_span.h
	Description		 : time span represents a duration of time, same as TimeSpan of .NetFrameWork
	Comment			 : 10/18/2016 : Optimized for Android	
*/

#ifndef __W_TIME_SPAN_H__
#define __W_TIME_SPAN_H__

#if _MSC_VER > 1000
#pragma once
#endif

#include "w_system_export.h"
#include <assert.h>
#include <string>

#ifdef __ANDROID
#include "w_std.h"
#endif

namespace wolf
{
	namespace system
	{
		class w_time_span
		{
		public:
			WSYS_EXP w_time_span();
			WSYS_EXP w_time_span(INT64 pTicks);
			WSYS_EXP w_time_span(int pHours, int pMinutes, int pSeconds);
			WSYS_EXP w_time_span(int pDays, int pHours, int pMinutes, int pSeconds, int pMilliseconds = 0);
			WSYS_EXP ~w_time_span();

			//Add two timespans with each other
			WSYS_EXP w_time_span add(w_time_span pTS);
			//Return duration in timespan
			WSYS_EXP w_time_span duration();
			//Make timespan negative
			WSYS_EXP w_time_span negate();
			//Returns time in string
			WSYS_EXP std::string to_string();
			//Returns time in wstring
			WSYS_EXP std::wstring to_wstring();

			//Returns timespan with zero value
			WSYS_EXP static w_time_span zero();
			//Create timespan from now
			WSYS_EXP static w_time_span now();
			//Returns timespan with minimum value
			WSYS_EXP static w_time_span min_value();
			//Returns timespan with maximum value
			WSYS_EXP static w_time_span max_value();
			//Create timeSpan from days
			WSYS_EXP static w_time_span from_days(double pValue);
			//Create timeSpan from hours
			WSYS_EXP static w_time_span from_hours(double pValue);
			//Create timeSpan from milliSeconds
			WSYS_EXP static w_time_span from_milliseconds(double pValue);
			//Create timeSpan from minutes
			WSYS_EXP static w_time_span from_minutes(double pValue);
			//Create timespan from seconds
			WSYS_EXP static w_time_span from_seconds(double pValue);
			//Create timespan from ticks
			WSYS_EXP static w_time_span from_ticks(INT64 pValue);
			//Create timespan from string in the format of "00:00:00:00:000"
			WSYS_EXP static w_time_span from_string(std::string pValue);

#pragma region Getters

			//Returns total ticks
			WSYS_EXP INT64 get_ticks() const;
			//Returns days
			WSYS_EXP int get_days() const;
			//Returns hours
			WSYS_EXP int get_hours() const;
			//Returns milliseconds
			WSYS_EXP int get_milliseconds() const;
			//Returns minutes
			WSYS_EXP int get_minutes() const;
			//Returns seconds
			WSYS_EXP int get_seconds() const;
			//Returns total days
			WSYS_EXP double get_total_days() const;
			//Returns total hours
			WSYS_EXP double get_total_hours() const;
			//Returns total milliseconds
			WSYS_EXP double get_total_milliseconds() const;
			//Returns total minutes
			WSYS_EXP double get_total_minutes() const;
			//Returns total seconds
			WSYS_EXP double get_total_seconds() const;

#pragma endregion

		private:
			static w_time_span _interval(double pValue, int pScale);
			static INT64 _time_to_ticks(int pHour, int pMinute, int pSecond);
		
			INT64 _ticks;
		};

		inline bool operator == (const w_time_span& pLeft, const w_time_span& pRight)
		{
			return pLeft.get_ticks() == pRight.get_ticks();
		}
		
		inline bool operator != (const w_time_span& pLeft, const w_time_span& pRight)
		{
			return !(pLeft == pRight);
		}

		inline w_time_span operator - (w_time_span& pLeft, w_time_span& pRight)
		{
			auto t1 = pLeft.get_ticks();
			auto t2 = pRight.get_ticks();
			auto result =  t1 - t2;
			// Overflow if signs of operands was different and result's
			// sign was opposite from the first argument's sign.
			// >> 63 gives the sign bit (either 64 1's or 64 0's).
			if ((t1 >> 63 != t2 >> 63) && (t1 >> 63 != result >> 63))
			{
				throw "Overflow TimeSpan too long";
			}
			return w_time_span(result);
		}

		inline w_time_span operator -= (w_time_span& pLeft, w_time_span& pRight)
		{
			pLeft = pLeft - pRight;
			return pLeft;
		}

		inline w_time_span operator + (w_time_span& pLeft, w_time_span& pRight)
		{
			return pLeft.add(pRight);
		}

		inline w_time_span operator += (w_time_span& pLeft, w_time_span& pRight)
		{
			pLeft = pLeft + pRight;
			return pLeft;
		}

		inline bool operator < (w_time_span& pLeft, w_time_span& pRight)
		{
			return pLeft.get_ticks() < pRight.get_ticks();
		}

		inline bool operator <= (w_time_span& pLeft, w_time_span& pRight)
		{
			return pLeft.get_ticks() <= pRight.get_ticks();
		}

		inline bool operator > (w_time_span& pLeft, w_time_span& pRight)
		{
			return pLeft.get_ticks() > pRight.get_ticks();
		}

		inline bool operator >= (w_time_span& pLeft, w_time_span& pRight)
		{
			return pLeft.get_ticks() >= pRight.get_ticks();
		}
	}
}

#endif //__W_TIME_SPAN_H__