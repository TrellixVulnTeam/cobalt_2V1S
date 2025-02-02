// Copyright 2018 The Cobalt Authors. All Rights Reserved.
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

#include "starboard/player.h"

#include "third_party/starboard/wpe/shared/player/player_internal.h"

#if SB_API_VERSION >= 10
void SbPlayerWriteSample2(SbPlayer player,
                          SbMediaType sample_type,
                          const SbPlayerSampleInfo* sample_infos,
                          int number_of_sample_infos) {
  player->player_->WriteSample(sample_type, sample_infos,
                               number_of_sample_infos);
}
#else
void SbPlayerWriteSample(SbPlayer /*player*/,
                         SbMediaType /*sample_type*/,
                         const void* const* /*sample_buffers*/,
                         const int* /*sample_buffer_sizes*/,
                         int /*number_of_sample_buffers*/,
                         SbMediaTime /*sample_pts*/,
                         const SbMediaVideoSampleInfo* /*video_sample_info*/,
                         const SbDrmSampleInfo* /*sample_drm_info*/) {
  NOTIMPLEMENTED();
}

#endif  // SB_API_VERSION >= 10
