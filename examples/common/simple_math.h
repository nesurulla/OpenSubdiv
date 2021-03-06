//
//     Copyright (C) Pixar. All rights reserved.
//
//     This license governs use of the accompanying software. If you
//     use the software, you accept this license. If you do not accept
//     the license, do not use the software.
//
//     1. Definitions
//     The terms "reproduce," "reproduction," "derivative works," and
//     "distribution" have the same meaning here as under U.S.
//     copyright law.  A "contribution" is the original software, or
//     any additions or changes to the software.
//     A "contributor" is any person or entity that distributes its
//     contribution under this license.
//     "Licensed patents" are a contributor's patent claims that read
//     directly on its contribution.
//
//     2. Grant of Rights
//     (A) Copyright Grant- Subject to the terms of this license,
//     including the license conditions and limitations in section 3,
//     each contributor grants you a non-exclusive, worldwide,
//     royalty-free copyright license to reproduce its contribution,
//     prepare derivative works of its contribution, and distribute
//     its contribution or any derivative works that you create.
//     (B) Patent Grant- Subject to the terms of this license,
//     including the license conditions and limitations in section 3,
//     each contributor grants you a non-exclusive, worldwide,
//     royalty-free license under its licensed patents to make, have
//     made, use, sell, offer for sale, import, and/or otherwise
//     dispose of its contribution in the software or derivative works
//     of the contribution in the software.
//
//     3. Conditions and Limitations
//     (A) No Trademark License- This license does not grant you
//     rights to use any contributor's name, logo, or trademarks.
//     (B) If you bring a patent claim against any contributor over
//     patents that you claim are infringed by the software, your
//     patent license from such contributor to the software ends
//     automatically.
//     (C) If you distribute any portion of the software, you must
//     retain all copyright, patent, trademark, and attribution
//     notices that are present in the software.
//     (D) If you distribute any portion of the software in source
//     code form, you may do so only under this license by including a
//     complete copy of this license with your distribution. If you
//     distribute any portion of the software in compiled or object
//     code form, you may only do so under a license that complies
//     with this license.
//     (E) The software is licensed "as-is." You bear the risk of
//     using it. The contributors give no express warranties,
//     guarantees or conditions. You may have additional consumer
//     rights under your local laws which this license cannot change.
//     To the extent permitted under your local laws, the contributors
//     exclude the implied warranties of merchantability, fitness for
//     a particular purpose and non-infringement.
//
#ifndef SIMPLE_MATH_H
#define SIMPLE_MATH_H

#include <cmath>

inline void
cross(float *n, const float *p0, const float *p1, const float *p2) {

    float a[3] = { p1[0]-p0[0], p1[1]-p0[1], p1[2]-p0[2] };
    float b[3] = { p2[0]-p0[0], p2[1]-p0[1], p2[2]-p0[2] };
    n[0] = a[1]*b[2]-a[2]*b[1];
    n[1] = a[2]*b[0]-a[0]*b[2];
    n[2] = a[0]*b[1]-a[1]*b[0];

    float rn = 1.0f/sqrtf(n[0]*n[0] + n[1]*n[1] + n[2]*n[2]);
    n[0] *= rn;
    n[1] *= rn;
    n[2] *= rn;
}

inline void
normalize(float * p) {

    float dist = sqrtf( p[0]*p[0] + p[1]*p[1]  + p[2]*p[2] );
    p[0]/=dist;
    p[1]/=dist;
    p[2]/=dist;
}

inline void
multMatrix(float *d, const float *a, const float *b) {

    for (int i=0; i<4; ++i)
    {
        for (int j=0; j<4; ++j)
        {
            d[i*4 + j] =
                a[i*4 + 0] * b[0*4 + j] +
                a[i*4 + 1] * b[1*4 + j] +
                a[i*4 + 2] * b[2*4 + j] +
                a[i*4 + 3] * b[3*4 + j];
        }
    }
}

inline void
inverseMatrix(float *d, const float *m) {

    d[0] = m[ 5]*m[10]*m[15] - m[ 5]*m[11]*m[14] -
           m[ 9]*m[ 6]*m[15] + m[ 9]*m[ 7]*m[14] +
           m[13]*m[ 6]*m[11] - m[13]*m[ 7]*m[10];

    d[1] = -m[ 1]*m[10]*m[15] + m[ 1]*m[11]*m[14] +
            m[ 9]*m[ 2]*m[15] - m[ 9]*m[ 3]*m[14] -
            m[13]*m[ 2]*m[11] + m[13]*m[ 3]*m[10];

    d[2] = m[ 1]*m[ 6]*m[15] - m[ 1]*m[ 7]*m[14] -
           m[ 5]*m[ 2]*m[15] + m[ 5]*m[ 3]*m[14] +
           m[13]*m[ 2]*m[ 7] - m[13]*m[ 3]*m[ 6];

    d[3] = -m[ 1]*m[ 6]*m[11] + m[ 1]*m[ 7]*m[10] +
            m[ 5]*m[ 2]*m[11] - m[ 5]*m[ 3]*m[10] -
            m[ 9]*m[ 2]*m[ 7] + m[ 9]*m[ 3]*m[ 6];

    d[4] = -m[ 4]*m[10]*m[15] + m[ 4]*m[11]*m[14] +
            m[ 8]*m[ 6]*m[15] - m[ 8]*m[ 7]*m[14] -
            m[12]*m[ 6]*m[11] + m[12]*m[ 7]*m[10];

    d[5] = m[ 0]*m[10]*m[15] - m[ 0]*m[11]*m[14] -
           m[ 8]*m[ 2]*m[15] + m[ 8]*m[ 3]*m[14] +
           m[12]*m[ 2]*m[11] - m[12]*m[ 3]*m[10];

    d[6] = -m[ 0]*m[ 6]*m[15] + m[ 0]*m[ 7]*m[14] +
            m[ 4]*m[ 2]*m[15] - m[ 4]*m[ 3]*m[14] -
            m[12]*m[ 2]*m[ 7] + m[12]*m[ 3]*m[ 6];

    d[7] = m[ 0]*m[ 6]*m[11] - m[ 0]*m[ 7]*m[10] -
           m[ 4]*m[ 2]*m[11] + m[ 4]*m[ 3]*m[10] +
           m[ 8]*m[ 2]*m[ 7] - m[ 8]*m[ 3]*m[ 6];

    d[8] = m[ 4]*m[ 9]*m[15] - m[ 4]*m[11]*m[13] -
           m[ 8]*m[ 5]*m[15] + m[ 8]*m[ 7]*m[13] +
           m[12]*m[ 5]*m[11] - m[12]*m[ 7]*m[ 9];

    d[9] = -m[ 0]*m[ 9]*m[15] + m[ 0]*m[11]*m[13] +
            m[ 8]*m[ 1]*m[15] - m[ 8]*m[ 3]*m[13] -
            m[12]*m[ 1]*m[11] + m[12]*m[ 3]*m[ 9];

    d[10] = m[ 0]*m[ 5]*m[15] - m[ 0]*m[ 7]*m[13] -
            m[ 4]*m[ 1]*m[15] + m[ 4]*m[ 3]*m[13] +
            m[12]*m[ 1]*m[ 7] - m[12]*m[ 3]*m[ 5];

    d[11] = -m[ 0]*m[ 5]*m[11] + m[ 0]*m[ 7]*m[ 9] +
             m[ 4]*m[ 1]*m[11] - m[ 4]*m[ 3]*m[ 9] -
             m[ 8]*m[ 1]*m[ 7] + m[ 8]*m[ 3]*m[ 5];

    d[12] = -m[ 4]*m[ 9]*m[14] + m[ 4]*m[10]*m[13] +
             m[ 8]*m[ 5]*m[14] - m[ 8]*m[ 6]*m[13] -
             m[12]*m[ 5]*m[10] + m[12]*m[ 6]*m[ 9];

    d[13] = m[ 0]*m[ 9]*m[14] - m[ 0]*m[10]*m[13] -
            m[ 8]*m[ 1]*m[14] + m[ 8]*m[ 2]*m[13] +
            m[12]*m[ 1]*m[10] - m[12]*m[ 2]*m[ 9];

    d[14] = -m[ 0]*m[ 5]*m[14] + m[ 0]*m[ 6]*m[13] +
             m[ 4]*m[ 1]*m[14] - m[ 4]*m[ 2]*m[13] -
             m[12]*m[ 1]*m[ 6] + m[12]*m[ 2]*m[ 5];

    d[15] = m[ 0]*m[ 5]*m[10] - m[ 0]*m[ 6]*m[ 9] -
            m[ 4]*m[ 1]*m[10] + m[ 4]*m[ 2]*m[ 9] +
            m[ 8]*m[ 1]*m[ 6] - m[ 8]*m[ 2]*m[ 5];

    float det = m[0] * d[0] + m[1] * d[4] + m[2] * d[8] + m[3] * d[12];

    if (det == 0) return;
    det = 1.0f / det;

    for (int i = 0; i < 16; i++)
        d[i] = d[i] * det;
}

inline void
perspective(float *m, float fovy, float aspect, float znear, float zfar)
{
    float r = 2 * (float)M_PI * fovy / 360.0F;
    float t = 1.0f / tan(r*0.5f);
    m[0] = t/aspect;
    m[1] = m[2] = m[3] = 0.0;
    m[4] = 0.0;
    m[5] = t;
    m[6] = m[7] = 0.0;
    m[8] = m[9] = 0.0;
    m[10] = (zfar + znear) / (znear - zfar);
    m[11] = -1;
    m[12] = m[13] = 0.0;
    m[14] = (2*zfar*znear)/(znear - zfar);
    m[15] = 0.0;
}

inline void
identity(float *m)
{
    m[0] = 1; m[1] = 0; m[2] = 0; m[3] = 0;
    m[4] = 0; m[5] = 1; m[6] = 0; m[7] = 0;
    m[8] = 0; m[9] = 0; m[10] = 1; m[11] = 0;
    m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
}

inline void
translate(float *m, float x, float y, float z)
{
    float t[16];
    identity(t);
    t[12] = x;
    t[13] = y;
    t[14] = z;
    float o[16];
    for(int i = 0; i < 16; i++) o[i] = m[i];
    multMatrix(m, t, o);
}

inline void
ortho(float *m, float left, float top, float right, float bottom)
{
    identity(m);
    m[0] = 2.0f / (right - left);
    m[5] = 2.0f / (top - bottom);
    m[10] = -1;
    m[12] = -(right+left)/(right-left);
    m[13] = -(top+bottom)/(top-bottom);
}

inline void
rotate(float *m, float angle, float x, float y, float z)
{
    float r = 2 * (float) M_PI * angle/360.0f;
    float c = cos(r);
    float s = sin(r);
    float t[16];
    t[0] = x*x*(1-c)+c;
    t[1] = y*x*(1-c)+z*s;
    t[2] = x*z*(1-c)-y*s;
    t[3] = 0;
    t[4] = x*y*(1-c)-z*s;
    t[5] = y*y*(1-c)+c;
    t[6] = y*z*(1-c)+x*s;
    t[7] = 0;
    t[8] = x*z*(1-c)+y*s;
    t[9] = y*z*(1-c)-x*s;
    t[10] = z*z*(1-c)+c;
    t[11] = 0;
    t[12] = t[13] = t[14] = 0;
    t[15] = 1;
    float o[16];
    for(int i = 0; i < 16; i++) o[i] = m[i];
    multMatrix(m, t, o);
}

inline void
transpose(float *m)
{
    std::swap(m[1], m[4]);
    std::swap(m[2], m[8]);
    std::swap(m[3], m[12]);
    std::swap(m[6], m[9]);
    std::swap(m[7], m[13]);
    std::swap(m[11],m[14]);
}

#endif // SIMPLE_MATH_H
