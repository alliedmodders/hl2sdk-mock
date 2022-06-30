// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

#include "ispatialpartition.h"

class SpatialPartition : public ISpatialPartition
{
  public:
    void EnumerateElementsInBox(
        SpatialPartitionListMask_t listMask,  
        const Vector& mins, 
        const Vector& maxs, 
        bool coarseTest, 
        IPartitionEnumerator* pIterator) override;
    void EnumerateElementsInSphere(
        SpatialPartitionListMask_t listMask, 
        const Vector& origin, 
        float radius, 
        bool coarseTest, 
        IPartitionEnumerator* pIterator) override;
    void EnumerateElementsAlongRay(
        SpatialPartitionListMask_t listMask, 
        const Ray_t& ray, 
        bool coarseTest, 
        IPartitionEnumerator* pIterator) override;

    void EnumerateElementsAtPoint( 
        SpatialPartitionListMask_t listMask, 
        const Vector& pt, 
        bool coarseTest, 
        IPartitionEnumerator* pIterator) override;
};
