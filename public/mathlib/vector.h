// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

#include <math.h>

typedef float vec_t;

class Vector
{
  public:
    float x, y, z;

    Vector() : x(0), y(0), z(0) {}
    Vector(float x, float y, float z) : x(x), y(y), z(z) {}

    void Init(float x = 0.0f, float y = 0.0f, float z = 0.0f) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    float Length() const {
        return sqrt(x * x + y * y + z * z);
    }
    float LengthSqr() const {
        return x * x + y * y + z * z;
    }
    float DistTo(const Vector& other) const {
        Vector v(x - other.x, y - other.y, z - other.z);
        return v.Length();
    }
    float DistToSqr(const Vector& other) const {
        Vector v(x - other.x, y - other.y, z - other.z);
        return v.LengthSqr();
    }
    float Dot(const Vector& b) const {
        return x * b.x + y * b.y + z * b.z;
    }
    float NormalizeInPlace() {
        float r = Length();
        if (!r)
            return 0.0f;
        x *= r;
        y *= r;
        z *= r;
        return r;
    }
    Vector Cross(const Vector& b) const {
        return Vector(y * b.z - z * b.y,
                      z * b.x - x * b.z,
                      x * b.y - y * b.x);
    }

    Vector operator +(const Vector& v) const {
        return Vector(x + v.x, y + v.y, z + v.z);
    }
    Vector operator *(int v) const {
        return Vector(x * v, y * v, z * v);
    }
};

class QAngle
{
  public:
    float x, y, z;

    QAngle() : x(0), y(0), z(0) {}
    QAngle(float x, float y, float z) : x(x), y(y), z(z) {}

    void Init(float x = 0.0f, float y = 0.0f, float z = 0.0f) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
};

static inline void AngleVectors(const QAngle& angles, Vector* fwd) {
    // Not implemented.
    (void)angles;
    (void)fwd;
}

static inline void AngleVectors(const QAngle& angles, Vector* fwd, Vector* right, Vector* up) {
    // Not implemented.
    (void)angles;
    (void)fwd;
    (void)right;
    (void)up;
}

static inline void VectorAngles(const Vector& forward, QAngle& angles) {
    // Not implemented.
    (void)forward;
    (void)angles;
}

static inline void VectorVectors(const Vector& forward, Vector& right, Vector& up) {
    // Not implemented.
    (void)forward;
    (void)right;
    (void)up;
}

static inline float VectorNormalize(Vector& vec) {
    float r = vec.Length();
    if (!r)
        return 0.0f;
    vec.x *= r;
    vec.y *= r;
    vec.z *= r;
    return r;
}
