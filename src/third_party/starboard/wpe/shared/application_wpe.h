// Copyright 2016 The Cobalt Authors. All Rights Reserved.
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

#ifndef THIRD_PARTY_STARBOARD_WPE_SHARED_APPLICATION_WPE_H_
#define THIRD_PARTY_STARBOARD_WPE_SHARED_APPLICATION_WPE_H_

#include "starboard/configuration.h"
#include "starboard/input.h"
#include "starboard/shared/internal_only.h"
#include "starboard/shared/starboard/application.h"
#include "starboard/shared/starboard/queue_application.h"
#include "starboard/types.h"
#include <mutex>              
#include <condition_variable>

namespace third_party {
namespace starboard {
namespace wpe {
namespace shared {

class Application : public ::starboard::shared::starboard::QueueApplication {
 public:
  Application();
  ~Application() override;

  static third_party::starboard::wpe::shared::Application* Get() {
    return static_cast<third_party::starboard::wpe::shared::Application*>(
        ::starboard::shared::starboard::Application::Get());
  }

  static void WaitForInit();

  SbWindow CreateWindow(const SbWindowOptions* options);
  bool DestroyWindow(SbWindow window);
  void InjectInputEvent(SbInputData* data);

  void NavigateTo(const char* url);
  void DeepLink(const char* link_data);
  void Suspend();
  void Resume();
  void Stop();

 protected:
  // --- Application overrides ---
  void Initialize() override;
  void Teardown() override;
  void OnSuspend() override;
  void OnResume() override;
  void Inject(Event* e) override;

  // --- QueueApplication overrides ---
  bool MayHaveSystemEvents() override;
  Event* PollNextSystemEvent() override;
  Event* WaitForSystemEventWithTimeout(SbTime time) override;
  void WakeSystemEventWait() override;

protected:
  // guarantees suspend & resume events order
  std::mutex suspend_lock_;

  static std::mutex g_lock_;
  static std::condition_variable g_finished_init_;

 private:
  SbWindow window_{nullptr};
  ::starboard::Mutex window_lock_;
  bool display_released_{false};
  std::string deep_link_{};
};

}  // namespace shared
}  // namespace wpe
}  // namespace starboard
}  // namespace third_party

#endif  // THIRD_PARTY_STARBOARD_WPE_SHARED_APPLICATION_WPE_H_
