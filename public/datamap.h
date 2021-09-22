// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

#include "dt_send.h"
#include "basehandle.h"

class CBaseEntity;

struct inputdata_t;
typedef void (CBaseEntity::*inputfunc_t)(inputdata_t& data);

static constexpr int FTYPEDESC_GLOBAL = 0x0001;
static constexpr int FTYPEDESC_SAVE = 0x0002;
static constexpr int FTYPEDESC_KEY = 0x0004;
static constexpr int FTYPEDESC_INPUT = 0x0008;
static constexpr int FTYPEDESC_OUTPUT = 0x0010;
static constexpr int FTYPEDESC_FUNCTIONTABLE = 0x0020;
static constexpr int FTYPEDESC_PTR = 0x0040;
static constexpr int FTYPEDESC_OVERRIDE = 0x0080;
static constexpr int FTYPEDESC_INSENDTABLE = 0x0100;
static constexpr int FTYPEDESC_PRIVATE = 0x0200;
static constexpr int FTYPEDESC_NOERRORCHECK = 0x0400;
static constexpr int FTYPEDESC_MODELINDEX = 0x0800;
static constexpr int FTYPEDESC_INDEX = 0x1000;
static constexpr int FTYPEDESC_VIEW_OTHER_PLAYER = 0x2000;
static constexpr int FTYPEDESC_VIEW_OWN_TEAM = 0x4000;
static constexpr int FTYPEDESC_VIEW_NEVER = 0x8000;

enum fieldtype_t
{
    FIELD_VOID = 0,
    FIELD_FLOAT,
    FIELD_STRING,
    FIELD_VECTOR,
    FIELD_QUATERNION,
    FIELD_INTEGER,
    FIELD_BOOLEAN,
    FIELD_SHORT,
    FIELD_CHARACTER,
    FIELD_COLOR32,
    FIELD_EMBEDDED,
    FIELD_CUSTOM,
    FIELD_CLASSPTR,
    FIELD_EHANDLE,
    FIELD_EDICT,
    FIELD_POSITION_VECTOR,
    FIELD_TIME,
    FIELD_TICK,
    FIELD_MODELNAME,
    FIELD_SOUNDNAME,
    FIELD_INPUT,
    FIELD_FUNCTION,
    FIELD_VMATRIX,
    FIELD_VMATRIX_WORLDSPACE,
    FIELD_MATRIX3X4_WORLDSPACE,
    FIELD_INTERVAL,
    FIELD_MODELINDEX,
    FIELD_MATERIALINDEX,
    FIELD_VECTOR2D,
    FIELD_INTEGER64,
    FIELD_VECTOR4D,
    FIELD_TYPECOUNT,
};
typedef fieldtype_t _fieldtypes;

struct datamap_t;

struct typedescription_t {
    const char* fieldName;
    const char* externalName;
    int fieldOffset;
    int flags;
    datamap_t* td;
    int fieldSizeInBytes;
    inputfunc_t inputFunc;
    fieldtype_t fieldType;
    unsigned short fieldSize;
};

struct datamap_t {
    int dataNumFields;
    typedescription_t* dataDesc;
    datamap_t* baseMap;
    char const* dataClassName;
};
