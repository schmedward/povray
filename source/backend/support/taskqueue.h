/*******************************************************************************
 * taskqueue.h
 *
 * ---------------------------------------------------------------------------
 * Persistence of Vision Ray Tracer ('POV-Ray') version 3.7.
 * Copyright 1991-2013 Persistence of Vision Raytracer Pty. Ltd.
 *
 * POV-Ray is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * POV-Ray is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * ---------------------------------------------------------------------------
 * POV-Ray is based on the popular DKB raytracer version 2.12.
 * DKBTrace was originally written by David K. Buck.
 * DKBTrace Ver 2.0-2.12 were written by David K. Buck & Aaron A. Collins.
 * ---------------------------------------------------------------------------
 * $File: //depot/public/povray/3.x/source/backend/support/taskqueue.h $
 * $Revision: #1 $
 * $Change: 6069 $
 * $DateTime: 2013/11/06 11:59:40 $
 * $Author: chrisc $
 *******************************************************************************/

#ifndef POVRAY_BACKEND_TASKQUEUE_H
#define POVRAY_BACKEND_TASKQUEUE_H

#include <boost/thread.hpp>
#include <boost/thread/condition.hpp>

#include "base/povmscpp.h"
#include "backend/support/task.h"

namespace pov
{

using boost::recursive_mutex;

class TaskQueue
{
		class TaskEntry
		{
			public:
				enum EntryType
				{
					kTask,
					kSync,
					kMessage,
					kFunction,
				};

				TaskEntry(EntryType et) : entryType(et) { }
				TaskEntry(shared_ptr<Task> rt) : entryType(kTask), task(rt) { }
				TaskEntry(POVMS_Message& m) : entryType(kMessage), msg(m) { }
				TaskEntry(const boost::function1<void, TaskQueue&>& f) : entryType(kFunction), fn(f) { }
				~TaskEntry() { }

				shared_ptr<Task> GetTask() { return task; }
				POVMS_Message& GetMessage() { return msg; }
				boost::function1<void, TaskQueue&>& GetFunction() { return fn; }

				EntryType GetEntryType() { return entryType; }
			private:
				EntryType entryType;
				shared_ptr<Task> task;
				POVMS_Message msg;
				boost::function1<void, TaskQueue&> fn;
		};
	public:
		TaskQueue();
		~TaskQueue();

		void Stop();
		void Pause();
		void Resume();

		bool IsPaused();
		bool IsRunning();
		bool IsDone();
		bool Failed();

		int FailureCode(int defval = kNoError);

		Task::TaskData *AppendTask(Task *task);
		void AppendSync();
		void AppendMessage(POVMS_Message& msg);
		void AppendFunction(const boost::function1<void, TaskQueue&>& fn);

		bool Process();

		void Notify();
	private:
		/// queued task list
		std::queue<TaskEntry> queuedTasks;
		/// active task list
		list<TaskEntry> activeTasks;
		/// queue mutex
		boost::recursive_mutex queueMutex;
		/// failed code
		int failed;
		/// wait for data in queue or related operation to be processed
		boost::condition processCondition;
		/// not available
		TaskQueue(const TaskQueue&);

		/// not available
		TaskQueue& operator=(const TaskQueue&);
};

}

#endif // POVRAY_BACKEND_TASKQUEUE_H
