#include "game_math.h"

#include <math.h>


V3 V3::operator/(f32 t)
{
    return {x / t, y / t, z / t};
}

V3 V3::operator-(V3 b)
{
    return {x - b.x, y - b.y, z - b.z};
}

inline V3 Norm(V3 a)
{
    f32 length = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
    return a / length;
}

Mat4 Ortho(f32 l, f32 r, f32 b, f32 t, f32 n, f32 f)
{
    return {
        2/(r-l), 0, 0, 0,
        0, 2/(t-b), 0, 0,
        0, 0, -2/(f-n), 0,
        -(r+l)/(r-l), -(t+b)/(t-b), -(f+n)/(f-n), 1,
    };
}

Mat4 LookAt(V3 eye, V3 target, V3 up)
{
    Mat4 res = {};

    V3 f = Norm(target - eye);
    V3 s = Norm(Cross(f, up));
    V3 u = Cross(s, f);

    res.v[0] = s.x;
    res.v[4] = s.y;
    res.v[8] = s.z;

    res.v[1] = u.x;
    res.v[5] = u.y;
    res.v[9] = u.z;

    res.v[2] = -f.x;
    res.v[6] = -f.y;
    res.v[10] = -f.z;

    res.v[12] = -Dot(s, eye);
    res.v[13] = -Dot(u, eye);
    res.v[14] = Dot(f, eye);

    res.v[15] = 1;

    return res;
}

Mat4 Mat4::operator*(Mat4 b)
{
    Mat4 res;

    for (u32 i = 0; i < 4; ++i) {
        for (u32 j = 0; j < 4; ++j) {
            float acc = 0;
            for (u32 k = 0; k < 4; ++k) {
                acc += v[i + 4 * k] * b.v[4 * j + k];
            }
            res.v[i + 4 * j] = acc;
        }
    }

    return res;
}