// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

class Vector;

class ICollideable
{
  public:
    virtual const Vector& GetCollisionOrigin() const = 0;
};
