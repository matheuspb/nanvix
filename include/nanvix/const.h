/*
 * Copyright(C) 2011-2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Nanvix. If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file
 * 
 * @brief Kernel Constants
 */

#ifndef CONST_H_
#define CONST_H_

	/**
	 * @name System Information
	 */
	/**@{*/
	#define SYSNAME "Nanvix"      /**< Operating system name. */
	#define NODENAME ""           /**< Network node name.     */
	#define RELEASE "1.0"         /**< Kernel release.        */
	#define VERSION "beta"        /**< Kernel version.        */
	#define MACHINE "Intel 80386" /**< Hardware name.         */
	/**@}*/

	/**
	 * @name Scope Constants
	 */
	/**@{*/
	#define PUBLIC         /**< Global scope       */
	#define PRIVATE static /**< File scope.        */
	#define EXTERN extern  /**< Defined elsewhere. */
	/**@}*/

	/**
	 * @name Logical Constants
	 */
	#define FALSE 0 /**< False. */
	#define TRUE  1 /**< True.  */
	
	/**
	 * @name Other Constants
	 */
	/**@{*/

	/**
	 * @brief Null pointer.
	 */
	#ifndef _NULL
	#define _NULL
		#define NULL ((void *) 0)
	#endif
	/**@}*/

#endif /* CONST_H_ */
