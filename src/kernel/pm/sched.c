/*
 * Copyright(C) 2011-2016 Pedro H. Penna      <pedrohenriquepenna@gmail.com>
 *              2015-2016 Davidson Francis    <davidsondfgl@hotmail.com>
 *              2017      Matheus Bittencourt <bittencourt.matheus@gmail.com>
 *              2017      Lucas P. Bordignon  <lucaspbordignon99@gmail.com>
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

#include <nanvix/clock.h>
#include <nanvix/const.h>
#include <nanvix/hal.h>
#include <nanvix/pm.h>
#include <nanvix/klib.h>
#include <signal.h>

/**
 * @brief Schedules a process to execution.
 * 
 * @param proc Process to be scheduled.
 */
PUBLIC void sched(struct process *proc)
{
	proc->state = PROC_READY;
	proc->tickets = PROC_TICKETS(proc);
}

/**
 * @brief Stops the current running process.
 */
PUBLIC void stop(void)
{
	curr_proc->state = PROC_STOPPED;
	sndsig(curr_proc->father, SIGCHLD);
	yield();
}

/**
 * @brief Resumes a process.
 * 
 * @param proc Process to be resumed.
 * 
 * @note The process must stopped to be resumed.
 */
PUBLIC void resume(struct process *proc)
{	
	/* Resume only if process has stopped. */
	if (proc->state == PROC_STOPPED)
		sched(proc);
}

/**
 * @brief Yields the processor.
 */
PUBLIC void yield(void)
{
	struct process *p;       /* Working process.               */
	struct process *next;    /* Next process to run.           */
	unsigned int totalt = 0; /* Total number of given tickets. */

	/* Re-schedule process for execution. */
	if (curr_proc->state == PROC_RUNNING)
		curr_proc->state = PROC_READY;

	/* Remember this process. */
	last_proc = curr_proc;

	/* Check alarm and count tickets. */
	for (p = FIRST_PROC; p <= LAST_PROC; p++)
	{
		/* Skip invalid processes. */
		if (!IS_VALID(p))
			continue;
		
		/* Alarm has expired. */
		if ((p->alarm) && (p->alarm < ticks))
			p->alarm = 0, sndsig(p, SIGALRM);

		/* Count the total number of tickets given to ready processes. */
		if (p->state == PROC_READY)
			totalt += p->tickets;
	}

	/* Choose a process to run next. */
	next = IDLE;

	if (totalt > 0)
	{
		/* Choose a ticket. */
		unsigned int ticket = (krand() % totalt) + 1;
		unsigned int losers = 0;

		/* Find the winning process. */
		for (p = FIRST_PROC; p <= LAST_PROC; p++)
		{
			/* Skip non-ready process. */
			if (p->state != PROC_READY)
				continue;
			
			/* Winning process found. */
			losers += p->tickets;
			if(losers >= ticket)
			{
				next = p;
				break;
			}
		}
	}

	/* Switch to next process. */
	if (next->priority != PRIO_USER)
	{
		next->priority = PRIO_USER;
		next->tickets = PROC_TICKETS(next);
	}
	next->state = PROC_RUNNING;
	next->counter = PROC_QUANTUM;
	switch_to(next);
}
