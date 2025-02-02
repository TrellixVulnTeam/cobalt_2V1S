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

#include "cobalt/media/base/format_support_query_metrics.h"

#include <algorithm>

#include "base/logging.h"
#include "base/strings/string_util.h"
#include "starboard/common/string.h"

namespace cobalt {
namespace media {

#if !defined(COBALT_BUILD_TYPE_GOLD)

// static
SbTimeMonotonic FormatSupportQueryMetrics::cached_query_durations_[] = {0};
char FormatSupportQueryMetrics::max_query_description_[] = {};
SbTimeMonotonic FormatSupportQueryMetrics::max_query_duration_ = 0;
SbTimeMonotonic FormatSupportQueryMetrics::total_query_duration_ = 0;
int FormatSupportQueryMetrics::total_num_queries_ = 0;

FormatSupportQueryMetrics::FormatSupportQueryMetrics() {
  query_start_time_ = SbTimeGetMonotonicNow();
}


void FormatSupportQueryMetrics::RecordQuery(const char* query_name,
                                            const std::string& mime_type,
                                            const std::string& key_system,
                                            SbMediaSupportType support_type) {
  auto get_support_type_str = [](SbMediaSupportType support_type) {
    switch (support_type) {
      case kSbMediaSupportTypeNotSupported:
        return " -> not supported/false";
      case kSbMediaSupportTypeMaybe:
        return " -> maybe/true";
      case kSbMediaSupportTypeProbably:
        return " -> probably/true";
      default:
        NOTREACHED();
        return "";
    }
  };

  SbTimeMonotonic duration = SbTimeGetMonotonicNow() - query_start_time_;
  total_query_duration_ += duration;

  std::string query_description = starboard::FormatString(
      "%s(%s%s%s, %" PRId64 " μs", query_name, mime_type.c_str(),
      (key_system.empty() ? ")" : ", " + key_system + ")").c_str(),
      get_support_type_str(support_type), duration);
  LOG(INFO) << query_description;

  if (total_num_queries_ < SB_ARRAY_SIZE_INT(cached_query_durations_)) {
    cached_query_durations_[total_num_queries_] = duration;
  }
  ++total_num_queries_;
  if (duration > max_query_duration_) {
    max_query_duration_ = duration;
    base::strlcpy(max_query_description_, query_description.c_str(),
                  SB_ARRAY_SIZE_INT(max_query_description_));
  }
}

// static
void FormatSupportQueryMetrics::PrintAndResetFormatSupportQueryMetrics() {
  if (total_num_queries_ == 0) {
    LOG(INFO) << "Format support query metrics:\n\tNumber of queries: 0";
    return;
  }

  auto get_median = []() {
    int num_elements = std::min(total_num_queries_,
                                SB_ARRAY_SIZE_INT(cached_query_durations_));
    int middle_index = num_elements / 2;
    std::nth_element(cached_query_durations_,
                     cached_query_durations_ + middle_index,
                     cached_query_durations_ + num_elements);
    auto middle_element = cached_query_durations_[middle_index];
    return middle_element;
  };

  LOG(INFO) << "Format support query metrics:\n\tNumber of queries: "
            << total_num_queries_
            << "\n\tTotal query time: " << total_query_duration_
            << " μs\n\tAverage query time: "
            << total_query_duration_ / total_num_queries_
            << " μs\n\tMedian query time: ~" << get_median()
            << " μs\n\tLongest query: " << max_query_description_;

  max_query_description_[0] = 0;
  max_query_duration_ = 0;
  total_query_duration_ = 0;
  total_num_queries_ = 0;
}

#endif  // !defined(COBALT_BUILD_TYPE_GOLD)

}  // namespace media
}  // namespace cobalt
