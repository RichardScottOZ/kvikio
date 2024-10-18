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

package ai.rapids.kvikio.cufile;

abstract class CuFileHandle implements AutoCloseable {
    private final long pointer;

    static {
        CuFile.initialize();
    }

    protected CuFileHandle(long pointer) {
        this.pointer = pointer;
    }

    public void close() {
        destroy(pointer);
    }

    protected long getPointer() {
        return this.pointer;
    }

    private static native void destroy(long pointer);
}