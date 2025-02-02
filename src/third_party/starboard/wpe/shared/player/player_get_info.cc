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

#include "base/logging.h"
#include "starboard/player.h"
#include "third_party/starboard/wpe/shared/player/player_internal.h"

#if SB_API_VERSION >= 10
void SbPlayerGetInfo2(SbPlayer player, SbPlayerInfo2* out_player_info) {
  player->player_->GetInfo(out_player_info);
}
#else
void SbPlayerGetInfo(SbPlayer /*player*/, SbPlayerInfo* /*out_player_info*/) {
  NOTIMPLEMENTED();
}
#endif  // SB_API_VERSION >= 10
