/*
    Copyright (c) 2005-2023 Intel Corporation

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#ifndef __TBB_tbb_H
#define __TBB_tbb_H

/**
    This header bulk-includes declarations or definitions of all the functionality
    provided by TBB (save for tbbmalloc and 3rd party dependent headers).

    If you use only a few TBB constructs, consider including specific headers only.
    Any header listed below can be included independently of others.
**/

// Note: This is a minimal umbrella for Swift C++ interop compatibility.
// Excludes headers with X-macros and complex templates that don't compile
// in Swift module context (flow_graph.h, profiling.h, combinable.h, etc.)

#include "tbb/blocked_range.h"
#include "tbb/blocked_range2d.h"
#include "tbb/blocked_range3d.h"
#include "tbb/cache_aligned_allocator.h"
#include "tbb/concurrent_hash_map.h"
#include "tbb/concurrent_queue.h"
#include "tbb/concurrent_unordered_map.h"
#include "tbb/concurrent_unordered_set.h"
#include "tbb/concurrent_vector.h"
#include "tbb/enumerable_thread_specific.h"
#include "tbb/global_control.h"
#include "tbb/info.h"
#include "tbb/parallel_for.h"
#include "tbb/parallel_for_each.h"
#include "tbb/parallel_reduce.h"
#include "tbb/parallel_sort.h"
#include "tbb/queuing_rw_mutex.h"
#include "tbb/spin_mutex.h"
#include "tbb/spin_rw_mutex.h"
#include "tbb/task.h"
#include "tbb/task_arena.h"
#include "tbb/task_group.h"
#include "tbb/version.h"

#endif /* __TBB_tbb_H */
