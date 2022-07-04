// vim: set sts=4 ts=8 sw=4 tw=99 et:
#include "spatialpartition.h"

#include "tier0/dbg.h"
#include "tier1/interface.h"

static SpatialPartition sSpatialPartition;

EXPOSE_SINGLE_INTERFACE_GLOBALVAR(SpatialPartition, ISpatialPartition, INTERFACEVERSION_SPATIALPARTITION,
		                  sSpatialPartition);

void SpatialPartition::EnumerateElementsInBox(
    SpatialPartitionListMask_t listMask,  
    const Vector& mins, 
    const Vector& maxs, 
    bool coarseTest, 
    IPartitionEnumerator* pIterator)
{
    Error("%s not implemented", __func__);
}

void SpatialPartition::EnumerateElementsInSphere(
    SpatialPartitionListMask_t listMask, 
    const Vector& origin, 
    float radius, 
    bool coarseTest, 
    IPartitionEnumerator* pIterator)
{
    Error("%s not implemented", __func__);
}

void SpatialPartition::EnumerateElementsAlongRay(
    SpatialPartitionListMask_t listMask, 
    const Ray_t& ray, 
    bool coarseTest, 
    IPartitionEnumerator* pIterator)
{
    Error("%s not implemented", __func__);
}

void SpatialPartition::EnumerateElementsAtPoint( 
    SpatialPartitionListMask_t listMask, 
    const Vector& pt, 
    bool coarseTest, 
    IPartitionEnumerator* pIterator)
{
    Error("%s not implemented", __func__);
}
