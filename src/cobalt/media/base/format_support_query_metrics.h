// Copyright 2022 The Cobalt Authors. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef COBALT_MEDIA_BASE_FORMAT_SUPPORT_QUERY_METRICS_H_
#define COBALT_MEDIA_BASE_FORMAT_SUPPORT_QUERY_METRICS_H_

#include <string>

#include "starboard/media.h"
#include "starboard/time.h"

namespace cobalt {
namespace media {

#if defined(COBALT_BUILD_TYPE_GOLD)

class FormatSupportQueryMetrics {
 public:
  FormatSupportQueryMetrics() = default;
  ~FormatSupportQueryMetrics() = default;
  void RecordQuery(const char* query_name, const std::string& mime_type,
                   const std::string& key_system,
                   SbMediaSupportType support_type) {}
  static void PrintAndResetFormatSupportQueryMetrics() {}
};

#else  // defined(COBALT_BUILD_TYPE_GOLD)

class FormatSupportQueryMetrics {
 public:
  FormatSupportQueryMetrics();
  ~FormatSupportQueryMetrics() {}

  void RecordQuery(const char* query_name, const std::string& mime_type,
                   const std::string& key_system,
                   SbMediaSupportType support_type);

  static void PrintAndResetFormatSupportQueryMetrics();

 private:
  static constexpr int kMaxCachedQueryDurations = 150;
  static constexpr int kMaxQueryDescriptionLength = 350;

  static SbTimeMonotonic cached_query_durations_[kMaxCachedQueryDurations];
  static char max_query_description_[kMaxQueryDescriptionLength];
  static SbTimeMonotonic max_query_duration_;
  static SbTimeMonotonic total_query_duration_;
  static int total_num_queries_;

  SbTimeMonotonic query_start_time_ = 0;
};

#endif  // defined(COBALT_BUILD_TYPE_GOLD)

}  // namespace media
}  // namespace cobalt

#endif  // COBALT_MEDIA_BASE_FORMAT_SUPPORT_QUERY_METRICS_H_
