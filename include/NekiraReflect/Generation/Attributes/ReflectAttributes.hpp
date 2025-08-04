/**
 * MIT License
 *
 * Copyright (c) 2025 TokiraNeo (https://github.com/TokiraNeo)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */


#pragma once



#ifdef __REFLECT_GEN_ENABLE__

#define NCLASS(...) __attribute__((annotate("NClass", #__VA_ARGS__)))

#define NSTRUCT(...) __attribute__((annotate("NStruct", #__VA_ARGS__)))

#define NENUM(...) __attribute__((annotate("NEnum", #__VA_ARGS__)))

#define NPROPERTY(...) __attribute__((annotate("NProperty", #__VA_ARGS__)))

#define NFUNCTION(...) __attribute__((annotate("NFunction", #__VA_ARGS__)))

#else // __REFLECT_GEN_ENABLE__

#define NCLASS(...)

#define NSTRUCT(...)

#define NENUM(...)

#define NPROPERTY(...)

#define NFUNCTION(...)

#endif // __REFLECT_GEN_ENABLE__