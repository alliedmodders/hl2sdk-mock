// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

#include "ehandle.h"
#include "datamap.h"
#include "string_t.h"
#include "Color.h"
#include "vector.h"

class CBaseEntity;

class variant_t
{
  CHandle<CBaseEntity> eVal;
  fieldtype_t fieldType;

  public:
    void SetBool( bool b ) { fieldType = FIELD_BOOLEAN; }
    void SetString( string_t str ) {fieldType = FIELD_STRING; }
    void SetInt( int val ) { fieldType = FIELD_INTEGER; }
    void SetFloat( float val ) { fieldType = FIELD_FLOAT; }
    void SetEntity( CBaseEntity *val );
    void SetVector3D( const Vector &val ) { fieldType = FIELD_VECTOR; }
    void SetPositionVector3D( const Vector &val ) { fieldType = FIELD_POSITION_VECTOR; }
    void SetColor32( color32 val ) { fieldType = FIELD_COLOR32; }
    void SetColor32( int r, int g, int b, int a ) { fieldType = FIELD_COLOR32; }
};
