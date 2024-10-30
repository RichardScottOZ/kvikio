/*
 * Copyright (c) 2024, NVIDIA CORPORATION.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <fcntl.h>
#include <stdexcept>

#include <kvikio/file_handle.hpp>

namespace kvikio::detail {

int open_fd_parse_flags(const std::string& flags, bool o_direct)
{
  int file_flags = -1;
  if (flags.empty()) { throw std::invalid_argument("Unknown file open flag"); }
  switch (flags[0]) {
    case 'r':
      file_flags = O_RDONLY;
      if (flags[1] == '+') { file_flags = O_RDWR; }
      break;
    case 'w':
      file_flags = O_WRONLY;
      if (flags[1] == '+') { file_flags = O_RDWR; }
      file_flags |= O_CREAT | O_TRUNC;
      break;
    case 'a': throw std::invalid_argument("Open flag 'a' isn't supported");
    default: throw std::invalid_argument("Unknown file open flag");
  }
  file_flags |= O_CLOEXEC;
  if (o_direct) {
#if defined(O_DIRECT)
    file_flags |= O_DIRECT;
#else
    throw std::invalid_argument("'o_direct' flag unsupported on this platform");
#endif
  }
  return file_flags;
}
}  // namespace kvikio::detail
