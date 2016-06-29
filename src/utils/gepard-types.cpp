/* Copyright (C) 2015-2016, Gepard Graphics
 * Copyright (C) 2015, Szilard Ledan <szledan@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "gepard-types.h"

namespace gepard {

/* BoundingBox */

void BoundingBox::stretchX(const Float x)
{
    if (x < minX) {
        minX = x;
    }
    if (x > maxX) {
        maxX = x;
    }
}
void BoundingBox::stretchY(const Float y)
{
    if (y < minY) {
        minY = y;
    }
    if (y > maxY) {
        maxY = y;
    }
}
void BoundingBox::stretch(const FloatPoint& p)
{
    stretchX(p.x);
    stretchY(p.y);
}

/* Vec4 */

Float& Vec4::operator[](std::size_t idx)
{
    switch (idx) {
    case 0: return x;
    case 1: return y;
    case 2: return z;
    case 3: return w;
    default:
        GD_CRASH("Index out of bound!");
    }
}

/* Color */

const Color Color::WHITE(1.0f, 1.0f, 1.0f, 1.0f);

} // namespace gepard
