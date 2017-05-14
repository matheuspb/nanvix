/*
 * Copyright(C) 2017 Matheus Bittencourt <bittencourt.matheus@gmail.com>
 *
 * This file is part of Nanvix.
 *
 * Nanvix is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Nanvix is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Nanvix. If not, see <http://www.gnu.org/licenses/>.
 */

#include <nanvix/klib.h>
#include <sys/types.h>

PRIVATE uint32_t _next = 0x2af65f78;

/**
 * @brief Seeds the PRNG function.
 */
EXTERN void ksrand(uint32_t seed)
{
	_next = seed;
}

/**
 * @brief PRNG function.
 *
 * @details Uses a linear congruential generator, with the parameters suggested
 *          by the ISO/IEC 9899, to generate pseudo-random numbers.
 *
 * @return A pseudo-randomly generated number.
 */
EXTERN uint32_t krand(void)
{
	/* x(n) = (a*x(n-1) + c) mod m */
	_next = (1103515245 * _next + 12345) & 0x7fffffff;
	return _next >> 16;
}
