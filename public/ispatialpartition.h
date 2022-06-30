// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

enum
{
    PARTITION_ENGINE_SOLID_EDICTS = (1 << 0),
    PARTITION_ENGINE_TRIGGER_EDICTS = (1 << 1),
    PARTITION_CLIENT_SOLID_EDICTS = (1 << 2),
    PARTITION_CLIENT_RESPONSIVE_EDICTS = (1 << 3),
    PARTITION_ENGINE_NON_STATIC_EDICTS = (1 << 4),
    PARTITION_CLIENT_STATIC_PROPS = (1 << 5),
    PARTITION_ENGINE_STATIC_PROPS = (1 << 6),
    PARTITION_CLIENT_NON_STATIC_EDICTS = (1 << 7),
    PARTITION_CLIENT_TRIGGER_ENTITIES = (1 << 8),
    PARTITION_CLIENT_IK_ATTACHMENT = (1 << 9),
};

typedef int SpatialPartitionListMask_t;

enum IterationRetval_t
{
    ITERATION_CONTINUE = 0,
    ITERATION_STOP,
};

class IHandleEntity;

class IPartitionEnumerator
{
  public:
    virtual IterationRetval_t EnumElement(IHandleEntity *pHandleEntity) = 0;
};

static constexpr char INTERFACEVERSION_SPATIALPARTITION[] = "SpatialPartition001";

class Vector;
struct Ray_t;

class ISpatialPartition
{
  public:
    virtual void EnumerateElementsInBox(
        SpatialPartitionListMask_t listMask,  
        const Vector& mins, 
        const Vector& maxs, 
        bool coarseTest, 
        IPartitionEnumerator* pIterator) = 0;
    virtual void EnumerateElementsInSphere(
        SpatialPartitionListMask_t listMask, 
        const Vector& origin, 
        float radius, 
        bool coarseTest, 
        IPartitionEnumerator* pIterator) = 0;
    virtual void EnumerateElementsAlongRay(
        SpatialPartitionListMask_t listMask, 
        const Ray_t& ray, 
        bool coarseTest, 
        IPartitionEnumerator* pIterator) = 0;

    virtual void EnumerateElementsAtPoint( 
        SpatialPartitionListMask_t listMask, 
        const Vector& pt, 
        bool coarseTest, 
        IPartitionEnumerator* pIterator) = 0;
};
