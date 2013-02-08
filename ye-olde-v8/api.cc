// Copyright 2012 the V8 project authors. All rights reserved.
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
//       copyright notice, this list of conditions and the following
//       disclaimer in the documentation and/or other materials provided
//       with the distribution.
//     * Neither the name of Google Inc. nor the names of its
//       contributors may be used to endorse or promote products derived
//       from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "api.h"

//#include <math.h>  // For isnan.
//#include <string.h>  // For memcpy, strlen.
//#include "../include/v8-debug.h"
//#include "../include/v8-profiler.h"
//#include "../include/v8-testing.h"
//#include "bootstrapper.h"
//#include "compiler.h"
//#include "conversions-inl.h"
//#include "counters.h"
//#include "debug.h"
//#include "deoptimizer.h"
//#include "execution.h"
//#include "global-handles.h"
//#include "heap-profiler.h"
//#include "messages.h"
//#ifdef COMPRESS_STARTUP_DATA_BZ2
//#include "natives.h"
//#endif
//#include "parser.h"
//#include "platform.h"
//#include "profile-generator-inl.h"
//#include "property-details.h"
//#include "property.h"
//#include "runtime-profiler.h"
//#include "scanner-character-streams.h"
//#include "snapshot.h"
//#include "unicode-inl.h"
//#include "v8threads.h"
//#include "version.h"
//#include "vm-state-inl.h"

namespace v8 {

static i::HeapEntry* ToInternal(const HeapGraphNode* entry) {
  return const_cast<i::HeapEntry*>(
      reinterpret_cast<const i::HeapEntry*>(entry));
}

int HeapGraphNode::GetRetainedSize() const {
  i::Isolate* isolate = i::Isolate::Current();
  IsDeadCheck(isolate, "v8::HeapSnapshot::GetRetainedSize");
  return ToInternal(this)->retained_size();
}

int HeapGraphNode::GetRetainersCount() const {
  i::Isolate* isolate = i::Isolate::Current();
  IsDeadCheck(isolate, "v8::HeapSnapshot::GetRetainersCount");
  return ToInternal(this)->retainers().length();
}

const HeapGraphEdge* HeapGraphNode::GetRetainer(int index) const {
  i::Isolate* isolate = i::Isolate::Current();
  IsDeadCheck(isolate, "v8::HeapSnapshot::GetRetainer");
  return reinterpret_cast<const HeapGraphEdge*>(
      ToInternal(this)->retainers()[index]);
}


const HeapGraphNode* HeapGraphNode::GetDominatorNode() const {
  i::Isolate* isolate = i::Isolate::Current();
  IsDeadCheck(isolate, "v8::HeapSnapshot::GetDominatorNode");
  return reinterpret_cast<const HeapGraphNode*>(ToInternal(this)->dominator());
}

}  // namespace v8
