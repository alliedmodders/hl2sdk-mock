// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

class CSendProxyRecipients;
class SendProp;

class DVariant;

typedef int (*ArrayLengthSendProxyFn)(const void *, int);
typedef void* (*SendTableProxyFn)(const SendProp*, const void*, const void*, CSendProxyRecipients*,
                                  int);
typedef void(*SendVarProxyFn)(const SendProp*, const void*, const void*, DVariant*, int, int);

static constexpr int DT_MAX_STRING_BITS = 9;
static constexpr int DT_MAX_STRING_BUFFERSIZE = (1 << DT_MAX_STRING_BITS);

static constexpr int SPROP_UNSIGNED = (1<<0);
static constexpr int SPROP_COORD = (1<<1);
static constexpr int SPROP_NOSCALE = (1<<2);
static constexpr int SPROP_ROUNDDOWN = (1<<3);
static constexpr int SPROP_ROUNDUP = (1<<4);
static constexpr int SPROP_NORMAL = (1<<5);
static constexpr int SPROP_EXCLUDE = (1<<6);
static constexpr int SPROP_XYZE = (1<<7);
static constexpr int SPROP_INSIDEARRAY = (1<<8);
static constexpr int SPROP_PROXY_ALWAYS_YES = (1<<9);
static constexpr int SPROP_IS_A_VECTOR_ELEM = (1<<10);
static constexpr int SPROP_COLLAPSIBLE = (1<<11);
static constexpr int SPROP_COORD_MP = (1<<12);
static constexpr int SPROP_COORD_MP_LOWPRECISION = (1<<13);
static constexpr int SPROP_COORD_MP_INTEGRAL = (1<<14);
static constexpr int SPROP_CELL_COORD = (1<<15);
static constexpr int SPROP_CELL_COORD_LOWPRECISION = (1<<16);
static constexpr int SPROP_CELL_COORD_INTEGRAL = (1<<17);
static constexpr int SPROP_CHANGES_OFTEN = (1<<18);
static constexpr int SPROP_VARINT = (1<<19);
static constexpr int SPROP_NUMFLAGBITS_NETWORKED = 19;

enum SendPropType
{
    DPT_Int=0,
    DPT_Float,
    DPT_Vector,
    DPT_VectorXY,
    DPT_String,
    DPT_Array,
    DPT_DataTable,
    DPT_Int64,
    DPT_NUMSendPropTypes
};

class SendProp
{
  public:
    const char* GetName() const { return m_Name; }
    int GetOffset() const { return m_Offset; }
    SendPropType GetType() const { return m_Type; }
    ArrayLengthSendProxyFn GetArrayLengthProxy() const { return nullptr; }
    SendTableProxyFn GetDataTableProxyFn() const { return nullptr; }
    SendVarProxyFn GetProxyFn() const { return nullptr; }
    int GetNumElements() const { return m_nElements; }
    int GetElementStride() const { return m_ElementStride; }
    SendProp* GetArrayProp() const { return nullptr; }
    SendTable* GetDataTable() const { return nullptr; }
    int GetFlags() const { return 0; }
    bool IsInsideArray() const { return false; }
    const void* GetExtraData() const { return nullptr; }

    const char* m_Name;
    int m_nBits;
    SendPropType m_Type;
    int m_Offset;
    int m_nElements;
    int m_ElementStride;
};

class SendTable
{
  public:
    int GetNumProps() const { return 0; }
    SendProp* GetProp(int i) const { return nullptr; }
    const char* GetName() { return nullptr; }
};

class CSendProxyRecipients
{
  public:
};

class DVariant
{
  public:
    DVariant() {}
    explicit DVariant(const char* str)
     : m_pString(str)
    {}

    const char* m_pString;
};
