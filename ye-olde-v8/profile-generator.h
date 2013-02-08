// Copyright 2011 the V8 project authors. All rights reserved.
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

#ifndef V8_PROFILE_GENERATOR_H_EXN
#define V8_PROFILE_GENERATOR_H_EXN

#include "allocation.h"
#include "hashmap.h"
#include "../include/v8-profiler.h"

namespace v8 {
namespace internal {

// HeapEntry instances represent an entity from the heap (or a special
// virtual node, e.g. root).
class HeapEntry BASE_EMBEDDED {
 public:
  int retained_size() { return retained_size_; }
  void add_retained_size(int size) { retained_size_ += size; }
  void set_retained_size(int size) { retained_size_ = size; }
  int postorder_index() { return postorder_index_; }
  void set_postorder_index(int value) { postorder_index_ = value; }
  INLINE(int set_retainers_index(int index));
  void add_retainer(HeapGraphEdge* edge) {
    retainers_arr()[retainers_count_++] = edge;
  }
  Vector<HeapGraphEdge*> children() {
    return Vector<HeapGraphEdge*>(children_arr(), children_count_); }
  Vector<HeapGraphEdge*> retainers() {
    return Vector<HeapGraphEdge*>(retainers_arr(), retainers_count_); }
  INLINE(HeapEntry* dominator() const);
  void set_dominator(HeapEntry* entry) {
    ASSERT(entry != NULL);
    dominator_ = entry->index();
  }
  void clear_paint() { painted_ = false; }
  bool painted() { return painted_; }
  void paint() { painted_ = true; }
  bool user_reachable() { return user_reachable_; }
  void set_user_reachable() { user_reachable_ = true; }

 private:
  INLINE(HeapGraphEdge** retainers_arr());

  unsigned painted_: 1;
  unsigned user_reachable_: 1;
  int dominator_: 30;
  int retainers_count_: 28;
  int retainers_index_;
  int children_count_;
  union {
    int postorder_index_;  // Used during dominator tree building.
    int retained_size_;    // At that moment, there is no retained size yet.
  }

  List<HeapGraphEdge*>& retainers() { return retainers_; }
  void ClearPaint();
  void SetDominatorsToSelf();
  void FillChildrenAndRetainers();

  List<HeapGraphEdge*> retainers_;
};

class HeapSnapshotGenerator : public SnapshottingProgressReportingInterface {
 private:
  bool BuildDominatorTree(const Vector<HeapEntry*>& entries,
                          Vector<int>* dominators);
  bool CalculateRetainedSizes();
  void FillPostorderIndexes(Vector<HeapEntry*>* entries);
  bool IsUserGlobalReference(const HeapGraphEdge* edge);
  void MarkUserReachableObjects();
  bool SetEntriesDominators();
};

} }  // namespace v8::internal

#endif  // V8_PROFILE_GENERATOR_H_EXN
