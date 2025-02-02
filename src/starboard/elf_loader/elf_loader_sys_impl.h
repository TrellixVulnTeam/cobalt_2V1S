// Copyright 2019 The Cobalt Authors. All Rights Reserved.
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

#ifndef STARBOARD_ELF_LOADER_ELF_LOADER_SYS_IMPL_H_
#define STARBOARD_ELF_LOADER_ELF_LOADER_SYS_IMPL_H_

#include "starboard/common/scoped_ptr.h"

namespace starboard {
namespace elf_loader {

// Implementation of the elf loader.
class ElfLoaderImpl {
 public:
  ElfLoaderImpl();
  bool Load(const char* file_name,
            const void* (*custom_get_extension)(const char* name) = NULL,
            bool use_compression = false,
            bool use_memory_mapped_file = false);
  void* LookupSymbol(const char* symbol);
  ~ElfLoaderImpl();

 private:
  void* handle_;

  ElfLoaderImpl(const ElfLoaderImpl&) = delete;
  void operator=(const ElfLoaderImpl&) = delete;
};

}  // namespace elf_loader
}  // namespace starboard
#endif  // STARBOARD_ELF_LOADER_ELF_LOADER_SYS_IMPL_H_
