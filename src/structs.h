//////////////////////////
//    structs.h
//	Engine Structs
///////////////////////////
#pragma once
#include <cstdint>
#include <d3d11.h>
enum DvarFlags : std::uint32_t
{
    DVAR_FLAG_NONE = 0,
    DVAR_FLAG_SAVED = 0x1,
    DVAR_FLAG_LATCHED = 0x2,
    DVAR_FLAG_CHEAT = 0x4,
};

struct CmdText
{
    unsigned __int8* data;
    int maxsize;
    int cmdsize;
};

enum LocalClientNum_t : __int32
{
    LOCAL_CLIENT_INVALID = -1,
    LOCAL_CLIENT_0 = 0x0,
    LOCAL_CLIENT_LAST = 0x0,
    LOCAL_CLIENT_COUNT = 0x1,
};

enum errorParm_t
{
    ERR_FATAL = 0x0,
    ERR_DROP = 0x1,
    ERR_SERVERDISCONNECT = 0x2,
    ERR_DISCONNECT = 0x3,
    ERR_SCRIPT = 0x4,
    ERR_SCRIPT_DROP = 0x5,
    ERR_LOCALIZATION = 0x6,
    ERR_MAPLOADERRORSUMMARY = 0x7,
};

struct StringTableCell
{
	const char* string;
	int hash;
};

struct StringTable
{
	const char* name;
	int columnCount;
	int rowCount;
	StringTableCell* values;
};

struct XZoneInfo
{
    const char* name;
    int allocFlags;
    int freeFlags;
};
union DvarLimits
{
    struct
    {
        int stringCount;
        const char** strings;
    } enumeration;

    struct
    {
        int min;
        int max;
    } integer;

    struct
    {
        float min;
        float max;
    } value;

    struct
    {
        float min;
        float max;
    } vector;

    uint8_t bytes[16];
};

static_assert(sizeof(DvarLimits) == 0x10);


//temp
struct glyph_t {
    unsigned short letter;
    char x0;
    char y0;
    char dx;
    char pixelWidth;
    char pixelHeight;
    float s0;
    float t0;
    float s1;
    float t1;
};

//temp
struct font_t {
    const char* fontName;
    int pixelHeight;
    int glyphCount;
    void* material;
    void* glowMaterial;
    glyph_t* glyphs;
};

//temp
struct cmd_function_t {
    cmd_function_t* next;
    const char* name;
    void(__cdecl* func)(void);
};

struct LuaFile
{
    const char* name;
    int len;
    unsigned __int8 strippingType;
    const unsigned __int8* buffer;
};

//size 0x28
struct ScriptFile
{
    const char* name;
    int compressedLen;
    int len;
    int bytecodeLen;
    const char* buffer;
    char* bytecode;
};

static_assert(sizeof(ScriptFile) == 0x28);

struct RawFile
{
    const char* name;
    int compressedLen;
    int len;
    const char* buffer;
};

struct LocalizeEntry
{
    const char* value;
    const char* name;
};

struct scr_entref_t
{
    unsigned __int16 entnum;
    unsigned __int16 classnum;
};

enum XAssetType {
	ASSET_TYPE_PHYSPRESET = 0x0,
	ASSET_TYPE_SND_PHYSPRESET = 0x1,
	ASSET_TYPE_SND_MUSICSET = 0x2,
	ASSET_TYPE_PHYSCOLLMAP = 0x3,
	ASSET_TYPE_PHYSWATERPRESET = 0x4,
	ASSET_TYPE_PHYSWORLDMAP = 0x5,
	ASSET_TYPE_PHYSCONSTRAINT = 0x6,
	ASSET_TYPE_XANIMPARTS = 0x7,
	ASSET_TYPE_XSURFSHARED = 0x8,
	ASSET_TYPE_XMODEL_SURFS = 0x9,
    ASSET_TYPE_XMODEL = 0xA,
    ASSET_TYPE_XMODELBASE = 0xB,
    ASSET_TYPE_MAYHEM = 0xC,
    ASSET_TYPE_MATERIAL = 0xD,
    ASSET_TYPE_COMPUTESHADER = 0xE,
    ASSET_TYPE_VERTEXSHADER = 0xF,
    ASSET_TYPE_HULLSHADER = 0x10,
    ASSET_TYPE_DOMAINSHADER = 0x11,
    ASSET_TYPE_PIXELSHADER = 0x12,
    ASSET_TYPE_VERTEXDECL = 0x13,
	ASSET_TYPE_TECHNIQUE_SET = 0x14,
	ASSET_TYPE_IMAGE = 0x15,
	ASSET_TYPE_SOUND = 0x16,
	ASSET_TYPE_SOUND_SUBMIX = 0x17,
	ASSET_TYPE_SOUND_CURVE = 0x18,
	ASSET_TYPE_DIST_CURVE = 0x19,
	ASSET_TYPE_REVERB_CURVE = 0x1A,
	ASSET_TYPE_SOUND_CONTEXT = 0x1B,
	ASSET_TYPE_ALIAS_PARAMETER_MODIFIER = 0x1C,
	ASSET_TYPE_ALIAS_COMBAT_CONE = 0x1D,
	ASSET_TYPE_LOADED_SOUND = 0x1E,
	ASSET_TYPE_CLIPMAP = 0x1F,
	ASSET_TYPE_COMWORLD = 0x20,
	ASSET_TYPE_GLASSWORLD = 0x21,
	ASSET_TYPE_PATHDATA = 0x22,
	ASSET_TYPE_NAVMESH = 0x23,
	ASSET_TYPE_VEHICLE_TRACK = 0x24,
	ASSET_TYPE_MAP_ENTS = 0x25,
	ASSET_TYPE_FX_MAP = 0x26,
	ASSET_TYPE_GFXWORLD = 0x27,
	ASSET_TYPE_GFXWORLD_TRANS = 0x28,
	ASSET_TYPE_CLIPMAP_TRANS = 0x29,
	ASSET_TYPE_IESPROFILE = 0x2A,
    ASSET_TYPE_LIGHT_DEF = 0x2B,
	ASSET_TYPE_UI_MAP = 0x2C,
	ASSET_TYPE_ANIMCLASS = 0x2D,
	ASSET_TYPE_LOCALIZE_ENTRY = 0x2E,
	ASSET_TYPE_ATTACHMENT = 0x2F,
    ASSET_TYPE_WEAPON = 0x30,
	ASSET_TYPE_SNDDRIVER_GLOBALS = 0x31,
	ASSET_TYPE_FX = 0x32,
	ASSET_TYPE_IMPACT_FX = 0x33,
	ASSET_TYPE_SURFACE_FX = 0x34,
	ASSET_TYPE_AITYPE = 0x35,
	ASSET_TYPE_MPTYPE = 0x36,
	ASSET_TYPE_CHARACTER = 0x37,
	ASSET_TYPE_XMODELALIAS = 0x38,
    ASSET_TYPE_RAWFILE = 0x39,
    ASSET_TYPE_SCRIPTFILE = 0x3A,
    ASSET_TYPE_STRINGTABLE = 0x3B,
	ASSET_TYPE_LEADERBOARD = 0x3C,
	ASSET_TYPE_VIRTUAL_LEADERBOARD = 0x3D,
	ASSET_TYPE_STRUCTURED_DATA_DEF = 0x3E,
	ASSET_TYPE_DDL = 0x3F,
	ASSET_TYPE_TRACER = 0x40,
	ASSET_TYPE_VEHICLE = 0x41,
	ASSET_TYPE_ADDON_MAP_ENTS = 0x42,
	ASSET_TYPE_NET_CONST_STRINGS = 0x43,
	ASSET_TYPE_REVERB_PRESET = 0x44,
    ASSET_TYPE_LUA_FILE = 0x45,
	ASSET_TYPE_SCRIPTABLE = 0x46,
	ASSET_TYPE_EQUIPMENT_SND_TABLE = 0x47,
	ASSET_TYPE_VECTORFIELD = 0x48,
	ASSET_TYPE_PARTICLE_SIM_ANIMATION = 0x49,
	ASSET_TYPE_LASER = 0x4A,
	ASSET_TYPE_BEAM = 0x4B,
	ASSET_TYPE_SKELETON_SCRIPT = 0x4C,
	ASSET_TYPE_CLUT = 0x4D,
    ASSET_TYPE_FONT = 0x4E,
    ASSET_TYPE_SPLINE = 0x4F,
    ASSET_TYPE_PHYS_CLOTH_TUNING = 0x50,
	ASSET_TYPE_DLOGSCHEMA = 0x51,
	ASSET_TYPE_DLOGROUTES = 0x52,
};

struct GfxImageGpuHandles
{
    void* texture;
    void* shaderView;
    void* extraView;
};


//taken from s1
enum GfxWarningType
{
    R_WARN_FRONTEND_ENT_LIMIT = 0,
    R_WARN_KNOWN_MODELS = 1,
    R_WARN_KNOWN_DOBJ = 2,
    R_WARN_KNOWN_BRUSH = 3,
    R_WARN_KNOWN_PER_CLIENT_MODELS = 4,
    R_WARN_KNOWN_SPECIAL_MODELS = 5,
    R_WARN_MODEL_LIGHT_CACHE = 6,
    R_WARN_SCENE_ENTITIES = 7,
    R_WARN_MAX_SKINNED_CACHE_VERTICES = 8,
    R_WARN_MAX_SCENE_SURFS_SIZE = 9,
    R_WARN_MAX_SURF_BUF = 10,
    R_WARN_PORTAL_PLANES = 11,
    R_WARN_MAX_CLOUDS = 12,
    R_WARN_MAX_DLIGHTS = 13,
    R_WARN_MAX_SPOTLIGHTS = 14,
    R_WARN_DLIGHT_SMODEL_LIMIT = 15,
    R_WARN_SMODEL_LIGHTING = 16,
    R_WARN_SMODEL_VIS_DATA_LIMIT = 17,
    R_WARN_SMODEL_SURF_LIMIT = 18,
    R_WARN_SMODEL_SURF_DELAY_LIMIT = 19,
    R_WARN_MARK_SMODEL_COLLIDED_LIMIT = 20,
    R_WARN_MARK_WORLD_BRUSH_LIMIT = 21,
    R_WARN_BSPSURF_DATA_LIMIT = 22,
    R_WARN_BSPSURF_OMNI_LIGHT_LIMIT = 23,
    R_WARN_BSPSURF_SPOT_LIGHT_LIMIT = 24,
    R_WARN_MAX_DRAWSURFS = 25,
    R_WARN_GFX_CODE_EMISSIVE_SURF_LIMIT = 26,
    R_WARN_GFX_CODE_TRANS_SURF_LIMIT = 27,
    R_WARN_GFX_GLASS_SURF_LIMIT = 28,
    R_WARN_GFX_MARK_SURF_LIMIT = 29,
    R_WARN_GFX_SPARK_SURF_LIMIT = 30,
    R_WARN_MAX_SCENE_DRAWSURFS = 31,
    R_WARN_MAX_FX_DRAWSURFS = 32,
    R_WARN_NONEMISSIVE_FX_MATERIAL = 33,
    R_WARN_NONLIT_MARK_MATERIAL = 34,
    R_WARN_CMDBUF_OVERFLOW = 35,
    R_WARN_MISSING_DECL_NONDEBUG = 36,
    R_WARN_MAX_DYNENT_REFS = 37,
    R_WARN_MAX_SCENE_DOBJ_REFS = 38,
    R_WARN_MAX_SCENE_MODEL_REFS = 39,
    R_WARN_MAX_SCENE_BRUSH_REFS = 40,
    R_WARN_MAX_CODE_EMISSIVE_INDS = 41,
    R_WARN_MAX_CODE_EMISSIVE_VERTS = 42,
    R_WARN_MAX_CODE_EMISSIVE_ARGS = 43,
    R_WARN_MAX_CODE_TRANS_INDS = 44,
    R_WARN_MAX_CODE_TRANS_VERTS = 45,
    R_WARN_MAX_CODE_TRANS_ARGS = 46,
    R_WARN_MAX_GLASS_INDS = 47,
    R_WARN_MAX_GLASS_VERTS = 48,
    R_WARN_MAX_MARK_INDS = 49,
    R_WARN_MAX_MARK_VERTS = 50,
    R_WARN_MAX_SPARK_VERTS = 51,
    R_WARN_MAX_TRAIL_ELEMS_PER_TRAIL = 52,
    R_WARN_TRAIL_WITH_DELAY = 53,
    R_WARN_DEBUG_ALLOC = 54,
    R_WARN_SPOT_LIGHT_LIMIT = 55,
    R_WARN_FX_EFFECT_LIMIT = 56,
    R_WARN_FX_ELEM_LIMIT = 57,
    R_WARN_FX_BOLT_LIMIT = 58,
    R_WARN_WORKER_CMD_SIZE = 59,
    R_WARN_PHYSICS_BODY = 60,
    R_WARN_PHYSICS_JOINT = 61,
    R_WARN_UNKNOWN_STATICMODEL_SHADER = 62,
    R_WARN_UNKNOWN_XMODEL_SHADER = 63,
    R_WARN_DYNAMIC_INDEX_BUFFER_SIZE = 64,
    R_WARN_TOO_MANY_LIGHT_GRID_POINTS = 65,
    R_WARN_FOGABLE_2DTEXT = 66,
    R_WARN_FOGABLE_2DGLYPH = 67,
    R_WARN_OCCLUSION_QUERY = 68,
    R_WARN_MAX_OCCLUSION_QUERIES = 69,
    R_WARN_ESTIMATED_BOUNDS_TOO_SMALL_BEGIN = 70,
    R_WARN_ESTIMATED_BOUNDS_TOO_SMALL_BEGIN_STEPBACK = 69,
    R_WARN_ESTIMATED_BOUNDS_TOO_SMALL0 = 70,
    R_WARN_ESTIMATED_BOUNDS_TOO_SMALL1 = 71,
    R_WARN_ESTIMATED_BOUNDS_TOO_SMALL2 = 72,
    R_WARN_ESTIMATED_BOUNDS_TOO_SMALL_END = 73,
    R_WARN_ESTIMATED_BOUNDS_TOO_SMALL_END_STEPBACK = 72,
    R_WARN_GPU_TIMERS_INACCURATE = 73,
    R_WARN_MAX_JOINT_COUNT = 74,
    R_WARN_MAX_CONTACT_LIST = 75,
    R_WARN_MAX_FX_PER_FRAME = 76,
    R_WARN_ROTATED_CAPSULE_TRACE = 77,
    R_WARN_MINIMAP_ASSETS_NOT_PRECACHED = 78,
    R_WARN_DYNAMIC_INDEX_BUFFER_OVERFLOW = 79,
    R_WARN_PRETESS_INDEX_BUFFER_OVERFLOW = 80,
    R_WARN_RING_BUFFER = 81,
    R_WARN_FX_MAX_RETRIGGER = 82,
    R_WARN_FX_MAX_LIGHTGRID_SAMPLE_COUNT = 83,
    R_WARN_NO_SUN_OVERRIDE = 84,
    R_WARN_THERMAL_LIGHT_OVERFLOW = 85,
    R_WARN_FLARE_OVERFLOW = 86,
    R_WARN_MAX_FLARE_VERTS = 87,
    R_WARN_MAX_FLARE_INDICES = 88,
    R_WARN_SMALL_SCENE_SURFS_SIZE = 89,
    R_WARN_DRAWSURF_PREPASS_NOT_NONE = 90,
    R_WARN_DFOG_DISABLED_IN_FAST_FILE = 91,
    R_WARN_NORMAL_FOG_DISABLED_IN_FAST_FILE = 92,
    R_WARN_MATERIAL_OVERRIDE_LIMIT = 93,
    R_WARN_FX_TRACE_LIMIT_EXCEEDED = 94,
    R_WARN_TONEMAP_WORKER_NOT_FAST_ENOUGH = 95,
    R_WARN_COUNT = 96,
};

struct cmd_function_s
{
    cmd_function_s* next;
    const char* name;
    void(__fastcall* function)();
};

enum FF_DIR : __int32
{
    FFD_DEFAULT = 0x0,
    FFD_USER_MAP = 0x1,
};

enum dvarType_t : int8_t
{
    DVAR_TYPE_BOOL = 0x0,
    DVAR_TYPE_FLOAT = 0x1,
    DVAR_TYPE_FLOAT_2 = 0x2,
    DVAR_TYPE_FLOAT_3 = 0x3,
    DVAR_TYPE_FLOAT_4 = 0x4,
    DVAR_TYPE_INT = 0x5,
    DVAR_TYPE_ENUM = 0x6,
    DVAR_TYPE_STRING = 0x7,
    DVAR_TYPE_COLOR = 0x8,
    DVAR_TYPE_VEC3_ALT = 0x9,
    DVAR_TYPE_BOOL_SECURE = 0xA,
    DVAR_TYPE_FLOAT_SECURE = 0xB,
    DVAR_TYPE_INT_SECURE = 0xC,
    DVAR_TYPE_COUNT = 0xD,
};


union DvarValue
{
    bool enabled;
    int integer;
    unsigned int unsignedInt;
    float value;
    float vector[4];
    const char* string;
    unsigned char color[4];

    uint8_t bytes[16];
    uint32_t encoded[4];
};

struct dvar_t
{
    const char* name;       // 0x00
    int flags;             // 0x08
    dvarType_t type;        // 0x0C
    bool modified;          // 0x0D
    char pad_0E[2];         // 0x0E

    DvarValue current;      // 0x10
    DvarValue latched;      // 0x20
    DvarValue reset;        // 0x30

    DvarLimits domain;      // 0x40, should be 0x10 bytes

    void* unknown_50;       // 0x50, initialized to 0 in Dvar_RegisterNew
    dvar_t* hashNext;       // 0x58
};

static_assert(sizeof(DvarValue) == 0x10);
static_assert(offsetof(dvar_t, current) == 0x10);
static_assert(offsetof(dvar_t, latched) == 0x20);
static_assert(offsetof(dvar_t, reset) == 0x30);
static_assert(offsetof(dvar_t, domain) == 0x40);
static_assert(offsetof(dvar_t, hashNext) == 0x58);
static_assert(sizeof(dvar_t) == 0x60);

//making this from scratch
struct playerState_s
{
    int commandTime;
    int pm_type;
    int pm_time;
    int pm_flags;
    int otherFlags;
    int linkFlags;
    int bobCycle;
    float origin[3];
    float velocity[3];
    //more...
};

struct CmdArgs
{
    int nesting;
    LocalClientNum_t localClientNum[8];
    int controllerIndex[8];
    int argc[8];
    const char** argv[8];
};

enum ItemLockStatus
{
    ItemLockStatus_Unlocked = 0,
    ItemLockStatus_Lock_ChallengeNotCompleted = 1,
    ItemLockStatus_Lock_LevelNotReached = 2,
    ItemLockStatus_Lock_OnlineDataNotFetched = 3,
    ItemLockStatus_Lock_AllLocked = 4,
    ItemLockStatus_Lock_InvalidIntenvoryStatus = 5,
    ItemLockStatus_Lock_EntitlementNotUnlocked = 6,
    ItemLockStatus_Lock_ExtLevelNotReached = 7,
    ItemLockStatus_Lock_ExtPrestigeLevelNotReached = 8,
    ItemLockStatus_Lock_ExtinctionEscapesNotReached = 9,
    ItemLockStatus_Lock_ExtRelicEscapesNotReached = 10,
    ItemLockStatus_Lock_ExtKillsNotReached = 11,
    ItemLockStatus_Lock_ExtRevivesNotReached = 12,
    ItemLockStatus_Lock_PrestigeNotReached = 13,
    ItemLockStatus_Hidden_NotInInventory = 14,
    ItemLockStatus_Hidden_Unknown = 15,
};
struct GfxPlacement {
    float quat[4];
    float origin[3];
};

struct GfxScaledPlacement {
    GfxPlacement base;
    float scale;
};

struct cg_t
{
    char clientNum;                         // 0x000000

    char pad_0001[0x1E6C99 - 0x000001];     // 0x000001

    bool opaqueUnlit;                       // 0x1E6C99

    char pad_1E6C9A[0x1E6E80 - 0x1E6C9A];   // 0x1E6C9A

    float sunColor[3];                      // 0x1E6E80

    char pad_1E6E8C[0x2615C8 - 0x1E6E8C];   // 0x1E6E8C

    float viewModelAxis[4][3];              // 0x2615C8
    bool blockDrawViewmodel;                // 0x2615F8

    char pad_2615F9[0x43C600 - 0x2615F9];   // 0x2615F9
};

static_assert(offsetof(cg_t, clientNum) == 0x000000, "cg_t::clientNum offset mismatch");
static_assert(offsetof(cg_t, sunColor) == 0x1E6E80, "cg_t::sunColor offset mismatch");
static_assert(offsetof(cg_t, viewModelAxis) == 0x2615C8, "cg_t::viewModelAxis offset mismatch");
static_assert(offsetof(cg_t, blockDrawViewmodel) == 0x2615F8, "cg_t::blockDrawViewmodel offset mismatch");
static_assert(sizeof(cg_t) == 0x43C600, "cg_t size mismatch");

//WIP
// SIZE: 0x418
struct gentity_s {
    char pad0[0x144];
    int modelIndex;          // 0x144
    char pad1[0xEC];
    float origin[3];         // 0x234
    char pad2[0x4C];
    uint8_t autoPickupFlag;  // 0x28C
    char pad3[0x2B];         // 0x28D - 0x2B7
    int flags;               // 0x2B8
    char pad4[0x15C];        // 0x2BC - 0x417
};

static_assert(offsetof(gentity_s, modelIndex) == 0x144);
static_assert(offsetof(gentity_s, origin) == 0x234);
static_assert(offsetof(gentity_s, autoPickupFlag) == 0x28C);
static_assert(offsetof(gentity_s, flags) == 0x2B8);
static_assert(sizeof(gentity_s) == 0x418);

//SIZE: 0xA8
struct ComPrimaryLight {
    unsigned char type; //0x0
    unsigned char canUseShadowMap; //0x1
    unsigned char exponent; //0x2

    /*
        UNKNOWN
    */
    unsigned char pad03; //0x3
    unsigned char pad04[0x0C]; //0x04 --> 0x0F


    float color[3]; //0x10 --> 0x18
    float dir[3]; //0x1C --> 0x24
    float up[3]; //0x28 --> 0x30
    float origin[3]; //0x34 --> 0x3C
    float fadeOffset[2]; //0x40 --> 0x44
    float bulbRadius; //0x48
    float bulbLength[3]; //0x4C --> 0x54
    float radius; //0x58
    float cosHalfFovOuter; //0x5C
    float cosHalfFovInner; //0x60

    /*
        UNKNOWN
    */
    unsigned char pad64[0x3C]; //0x64 --> 0x9F

    const char* defName; //0xA0
};

//DOUBLE CHECK THIS
struct cplane_s {
    float normal[3];
    float dist;
    unsigned char type;
    unsigned char pad[3];
};

//DOUBLE CHECK THIS
struct GfxWorldDpvsPlanes {
    int cellCount;
    cplane_s* planes;
    unsigned __int16* nodes;
    unsigned int* sceneEntCellBits;
};

//WIP
//SIZE: 0x10C8
struct GfxWorld {
	const char* name;
	const char* baseName;

	//GfxSky* skies; //0x28

    GfxWorldDpvsPlanes dpvsPlanes; //0x58
    /*
    
    */
    unsigned int* cellCasterBits; //0xC50

	//GfxHeroOnlyLight* heroOnlyLights; //0x41F
};

enum HksBytecodeSharingMode
{
    HKS_BYTECODE_SHARING_OFF = 0x0,
    HKS_BYTECODE_SHARING_ON = 0x1,
    HKS_BYTECODE_SHARING_SECURE = 0x2,
};

enum HksCompilerSettings_IntLiteralOptions
{
    INT_LITERALS_NONE = 0x0,
    INT_LITERALS_LUD = 0x1,
    INT_LITERALS_32BIT = 0x1,
    INT_LITERALS_UI64 = 0x2,
    INT_LITERALS_64BIT = 0x2,
    INT_LITERALS_ALL = 0x3,
};

struct HksCompilerSettings
{
    int m_emitStructCode;                                   // 0x00
    int i1;                                                 // 0x04
    int i2;                                                 // 0x08
    int i3;                                                 // 0x0C
    int m_emitGlobalMemoization;                            // 0x10
    int _m_isHksGlobalMemoTestingMode;                      // 0x14
    HksBytecodeSharingMode m_bytecodeSharingMode;            // 0x18
    HksCompilerSettings_IntLiteralOptions m_enableIntLiterals; // 0x1C
    int(__fastcall* m_debugMap)(const char*, int);           // 0x20
};

static_assert(sizeof(HksCompilerSettings) == 0x28);

struct HksGlobal
{
    void* allocator;                  // 0x000
    void* allocatorUserData;           // 0x008

    std::uint64_t unk_010;             // 0x010
    std::uint64_t memUsed;             // 0x018
    std::uint64_t memHighWatermark;    // 0x020

    char pad_0028[0x158 - 0x028];

    void* compilerContext;             // 0x158, temporarily replaced in hks__CompilerFunc

    char pad_0160[0x1B8 - 0x160];

    void* currentLoadContext;          // 0x1B8

    HksBytecodeSharingMode m_bytecodeSharingMode; // 0x1C0

    char pad_01C4[0x558 - 0x1C4];

    HksCompilerSettings m_compilerSettings;       // 0x558
};

static_assert(offsetof(HksGlobal, compilerContext) == 0x158);
static_assert(offsetof(HksGlobal, currentLoadContext) == 0x1B8);
static_assert(offsetof(HksGlobal, m_bytecodeSharingMode) == 0x1C0);
static_assert(offsetof(HksGlobal, m_compilerSettings) == 0x558);
static_assert(offsetof(HksGlobal, m_compilerSettings.m_emitStructCode) == 0x558);
static_assert(offsetof(HksGlobal, m_compilerSettings.m_emitGlobalMemoization) == 0x568);
static_assert(offsetof(HksGlobal, m_compilerSettings.m_bytecodeSharingMode) == 0x570);

struct HksObject
{
    int type;        // 0x00
    int pad04;       // 0x04
    uint64_t value;  // 0x08
};


namespace hks
{
    struct ApiStack
    {
        HksObject* top;   // 0x00
        HksObject* base;  // 0x08
        HksObject* end;   // 0x10
    };

    static_assert(sizeof(ApiStack) == 0x18);
}

struct lua_State
{
    char pad_0000[0x10];

    HksGlobal* global;   // 0x10

    char pad_0018[0x30];        // 0x18

    hks::ApiStack m_apistack;   // 0x48

    char pad_0060[0x10];

    HksObject globals;          // 0x70
};

static_assert(offsetof(lua_State, global) == 0x10);
static_assert(offsetof(lua_State, m_apistack) == 0x48);
static_assert(offsetof(lua_State, globals) == 0x70);

struct GfxBuildInfo {
	const char* bspCommandline;
	const char* lightCommandline;
	const char* bspTimestamp;
	const char* lightTimestamp;
};
struct CardMemory {
	unsigned int platform[1];
};

struct GfxImage {
    const char* name;                    // 0x00
    ID3D11Texture2D* texture;             // 0x08
    ID3D11ShaderResourceView* shaderView; // 0x10

    char pad0[0x30];                     // 0x18 - 0x47

    int imageFormat;                     // 0x48
    uint16_t w;                          // 0x4C
    uint16_t h;                          // 0x4E
    uint16_t d;                          // 0x50
    uint16_t mipCount;                   // 0x52
    uint32_t cardMemory;                 // 0x54

    uint8_t type;                        // 0x58
    uint8_t semantic;                    // 0x59
    uint8_t category;                    // 0x5A
    uint8_t flags;                       // 0x5B
    uint8_t levelCount;                  // 0x5C

    char pad1[3];                        // 0x5D - 0x5F
};

union OmnvarValue
{
	bool enabled;
	int integer;
	unsigned int time;
	float value;
	unsigned int ncsString;
};

struct OmnvarData
{
	unsigned int timeModified;
	OmnvarValue current;
};

struct AttHybridSettings {
	float adsSpread;
	float adsAimPitch;
	float adsTransInTime;
	float adsTransInFromSprintTime;
	float adsTransOutTime;
	int adsReloadTransTime;
	float adsCrosshairInFrac;
	float adsCrosshairOutFrac;
	float adsZoomFov;
	float adsZoomInFrac;
	float adsZoomOutFrac;
	float adsFovLerpInTime;
	float adsFovLerpOutTime;
	float adsBobFactor;
	float adsViewBobMult;
	float adsViewErrorMin;
	float adsViewErrorMax;
	float adsFireAnimFrac;
};

union Weapon
{
    __int32 data;
};


//this is wrong lol; correct size tho
struct WeaponAttachment {
	const char* szInternalName;
	const char* szDisplayName;
	int type;
	int weaponType;
	int weapClass;
	int greebleType;
	void** worldModels;
	void** viewModels;
	void** reticleViewModels;
	void* chargeInfo;
	AttHybridSettings* hybridSettings;
	unsigned short* fieldOffsets;
	void* fields;
	int numFields;
	int loadIndex;
	int adsSettingsMode;
	float adsSceneBlurStrength;
	int knifeAttachTagOverride;
	BOOL hideIronSightsWithThisAttachment;
	BOOL showMasterRail;
	BOOL showSideRail;
	BOOL shareAmmoWithAlt;
	BOOL knifeAlwaysAttached;
	BOOL useDualFOV;
	BOOL riotShield;
	BOOL adsSceneBlur;
	BOOL automaticAttachment;
};
struct MapEnts;

union XAssetHeader {
    ScriptFile* script;
    RawFile* rawfile;
    StringTable* table;
    LocalizeEntry* localize;
    GfxImage* image;
    LuaFile* luafile;
    MapEnts* mapents;
    void* data;
};

struct XAsset
{
    XAssetType type;
    XAssetHeader header;
};

struct TriggerHull
{
    char data[0x10];
};

struct TriggerSlab
{
    char data[0x28];
};

struct TriggerWinding
{
    char data[0x14];
};

struct MapTriggers
{
    int count;                  // 0x00
    int pad04;                 // 0x04
    TriggerHull* hulls;         // 0x08, count * 0x10
    int slabCount;              // 0x10
    int pad14;                 // 0x14
    TriggerSlab* slabs;         // 0x18, slabCount * 0x28
    int windingCount;           // 0x20
    int pad24;                 // 0x24
    TriggerWinding* windings;   // 0x28, windingCount * 0x14
};

struct ClientTriggerUnknown1C
{
    char data[0x1C];
};

struct ClientTriggerUnknown0C
{
    char data[0x0C];
};

struct ClientTriggerNested
{
    uint32_t* values;           // 0x00, count * 4
    int count;                  // 0x08
    int pad0C;                 // 0x0C
};

struct ClientTriggers
{
    MapTriggers triggers;                 // 0x00
    uint16_t unknown1CCount;              // 0x30
    char pad32[0x06];                    // 0x32
    ClientTriggerUnknown1C* unknown1C;    // 0x38, unknown1CCount * 0x1C
    int unknownCharCount;                 // 0x40
    int pad44;                           // 0x44
    char* unknownChars;                   // 0x48, unknownCharCount bytes
    int* triggerType;                     // 0x50, triggers.count * 4
    int* unknown58;                       // 0x58, triggers.count * 4
    int* unknown60;                       // 0x60, triggers.count * 4
    uint16_t* unknown68;                  // 0x68, triggers.count * 2
    ClientTriggerUnknown0C* unknown70;    // 0x70, triggers.count * 0x0C
    int* unknown78;                       // 0x78, triggers.count * 4
    uint16_t* unknown80;                  // 0x80, triggers.count * 2
    uint16_t* unknown88;                  // 0x88, triggers.count * 2
    uint16_t* unknown90;                  // 0x90, triggers.count * 2
    uint16_t* unknown98;                  // 0x98, triggers.count * 2
    uint16_t* unknownA0;                  // 0xA0, triggers.count * 2
    ClientTriggerNested* unknownA8;       // 0xA8, triggers.count * 0x10
};

struct MapEntsUnknown1C
{
    char data[0x1C];
};

struct MapEntsUnknown1CArray
{
    uint16_t count;               // 0x00
    char pad02[0x06];            // 0x02
    MapEntsUnknown1C* entries;    // 0x08, count * 0x1C
};

struct MapEntsUnknown2C
{
    uint32_t unknown00;           // 0x00
    uint32_t remap04;             // 0x04, remapped during load
    uint32_t remap08;             // 0x08, remapped during load
    uint32_t remap0C;             // 0x0C, remapped during load
    uint32_t remap10;             // 0x10, remapped during load
    char pad14[0x18];            // 0x14
};

struct MapEntsUnknown2CArray
{
    uint16_t count;               // 0x00
    char pad02[0x06];            // 0x02
    MapEntsUnknown2C* entries;    // 0x08, count * 0x2C
};

struct MapEntsUnknown48
{
    char pad00[0x08];             // 0x00
    char* fixedString40;          // 0x08, fixed 0x40-byte buffer
    char pad10[0x28];             // 0x10
    void* unknown30;              // 0x38, fixed 0x30-byte buffer
    void* unknown24;              // 0x40, fixed 0x24-byte buffer
};

struct MapEntsUnknown48List
{
    uint16_t count;               // 0x00
    char pad02[0x06];            // 0x02
    MapEntsUnknown48* entries;    // 0x08, count * 0x48
};

struct MapEntsUnknown48Root
{
    uint16_t count;                   // 0x00
    char pad02[0x06];                // 0x02
    MapEntsUnknown48List* entries;    // 0x08, count * 0x10
};

struct MapEntsComplexRecord4C
{
    char pad00[0x48];             // 0x00
    uint32_t remap48;             // 0x48, remapped during load
};

struct MapEntsComplexC8
{
    void* asset;                              // 0x00
    char* data08;                            // 0x08, sized from asset byte 0x36
    MapEntsComplexRecord4C* records4C;        // 0x10, byte 0x52 * 0x4C
    char pad18[0x30];                        // 0x18
    uint32_t remap48;                         // 0x48, remapped during load
    char pad4C[0x0C];                        // 0x4C
    uint32_t* table58;                        // 0x58, asset word 0x2E * 4
    char* data60;                            // 0x60, sized from asset byte 0x35
    char pad68[0x48];                        // 0x68
    char* dataB0;                            // 0xB0, sized from asset byte 0x39
    uint16_t* valuesB8;                       // 0xB8, asset byte 0x38 * 2
    uint16_t* valuesC0;                       // 0xC0, byte 0xAB * 2
};

struct MapEntsComplexString
{
    const char* name;             // 0x00, XString
    char pad08[0x08];            // 0x08
};

struct MapEntsComplex30
{
    char pad00[0x04];                 // 0x00
    int recordCount;                  // 0x04
    char pad08[0x08];                // 0x08
    MapEntsComplexC8* records;        // 0x10, recordCount * 0xC8
    int stringCount;                  // 0x18
    int pad1C;                       // 0x1C
    MapEntsComplexString* strings;    // 0x20, stringCount * 0x10
    char pad28[0x08];                // 0x28
};

struct MapEntsUnknown50
{
    uint32_t remap00;             // 0x00, remapped during load
    uint32_t remap04;             // 0x04, remapped during load
    uint32_t remap08;             // 0x08, remapped during load
    uint32_t remap0C;             // 0x0C, remapped during load
    char pad10[0x40];            // 0x10
};

struct MapEntsUnknown50Array
{
    uint16_t count;               // 0x00
    char pad02[0x06];            // 0x02
    MapEntsUnknown50* entries;    // 0x08, count * 0x50
};

struct MapEntsUnknown10
{
    char data[0x10];
};

struct MapEntsUnknown10Array
{
    uint32_t count;               // 0x00
    uint32_t pad04;               // 0x04
    MapEntsUnknown10* entries;    // 0x08, count * 0x10
};

struct MapEnts
{
    const char* name;                         // 0x000, XString
    char* entityString;                       // 0x008
    int numEntityChars;                       // 0x010
    int pad014;                              // 0x014
    MapTriggers triggers;                     // 0x018
    ClientTriggers clientTriggers;            // 0x048
    MapEntsUnknown1CArray unknown0F8;         // 0x0F8
    MapEntsUnknown2CArray unknown108;         // 0x108
    MapEntsUnknown48Root unknown118;          // 0x118
    MapEntsComplex30 unknown128;              // 0x128
    MapEntsUnknown50Array unknown158;         // 0x158
    MapEntsUnknown10Array unknown168;         // 0x168
};

static_assert(sizeof(TriggerHull) == 0x10);
static_assert(sizeof(TriggerSlab) == 0x28);
static_assert(sizeof(TriggerWinding) == 0x14);
static_assert(sizeof(MapTriggers) == 0x30);
static_assert(sizeof(ClientTriggers) == 0xB0);
static_assert(sizeof(MapEntsUnknown1CArray) == 0x10);
static_assert(sizeof(MapEntsUnknown2CArray) == 0x10);
static_assert(sizeof(MapEntsUnknown48) == 0x48);
static_assert(sizeof(MapEntsUnknown48List) == 0x10);
static_assert(sizeof(MapEntsUnknown48Root) == 0x10);
static_assert(sizeof(MapEntsComplexRecord4C) == 0x4C);
static_assert(sizeof(MapEntsComplexC8) == 0xC8);
static_assert(sizeof(MapEntsComplexString) == 0x10);
static_assert(sizeof(MapEntsComplex30) == 0x30);
static_assert(sizeof(MapEntsUnknown50) == 0x50);
static_assert(sizeof(MapEntsUnknown50Array) == 0x10);
static_assert(sizeof(MapEntsUnknown10Array) == 0x10);
static_assert(offsetof(MapEnts, triggers) == 0x18);
static_assert(offsetof(MapEnts, clientTriggers) == 0x48);
static_assert(offsetof(MapEnts, unknown0F8) == 0xF8);
static_assert(offsetof(MapEnts, unknown108) == 0x108);
static_assert(offsetof(MapEnts, unknown118) == 0x118);
static_assert(offsetof(MapEnts, unknown128) == 0x128);
static_assert(offsetof(MapEnts, unknown158) == 0x158);
static_assert(offsetof(MapEnts, unknown168) == 0x168);
static_assert(sizeof(MapEnts) == 0x178);

struct MaterialPassArgDef
{
    char data[0x10];
}; // size 0x10

struct MaterialPass
{
    void* vertexDecl;                         // 0x00, loaded via sub_7FF6CCA48D00
    void* vertexShader;                       // 0x08, loaded via sub_7FF6CCA48B40
    void* hullShader;                         // 0x10, unknown exact type
    void* domainShader;                       // 0x18, unknown exact type
    void* pixelShader;                        // 0x20, unknown exact type

    uint8_t pad_028;                          // 0x28

    uint8_t perPrimArgCount;                  // 0x29
    uint8_t perObjArgCount;                   // 0x2A
    uint8_t stableArgCount;                   // 0x2B
    uint8_t customSamplerFlags;               // 0x2C, names not proven

    uint8_t pad_02D[0x36 - 0x2D];             // 0x2D

    uint16_t zoneIndexOrRuntimeIndex;         // 0x36, patched by sub_7FF6CC668A70

    uint8_t pad_038[0x50 - 0x38];             // 0x38

    void* args;                               // 0x50, count = bytes[0x29..0x2C] sum, elem size 0x10
};

static_assert(sizeof(MaterialPass) == 0x58);
static_assert(offsetof(MaterialPass, args) == 0x50);

struct MaterialTechnique
{
    const char* name;                         // 0x000 XString

    uint8_t flags;                            // 0x008 likely
    uint8_t unk09;                            // 0x009

    uint16_t passCount;                       // 0x00A

    uint16_t unk0C;                           // 0x00C
    uint16_t unk0E;                           // 0x00E

    MaterialPass passes[1];                   // 0x010 variable length, count = passCount
};

static_assert(offsetof(MaterialTechnique, name) == 0x000);
static_assert(offsetof(MaterialTechnique, flags) == 0x008);
static_assert(offsetof(MaterialTechnique, passCount) == 0x00A);
static_assert(offsetof(MaterialTechnique, passes) == 0x010);

struct MaterialTechniqueSet
{
    const char* name;                         // 0x000 XString
    uint8_t pad_008[0x08];                    // 0x008 unknown
    MaterialTechnique* techniques[0x72];      // 0x010
};

struct MaterialInfo
{
    const char* name;        // +0x00 XString
    char        pad08[0x28]; // +0x08
}; // size 0x30


struct MaterialConstantDef
{
    char data[0x20];         // i only see 0x20 size
}; // size 0x20

struct MaterialStateBitsOrArgDef
{
    char     pad00[0x18];    // +0x00
    uint16_t unk18;          // +0x18 loaded/processed separately
    char     pad1A[0x0E];    // +0x1A
}; // size 0x28

struct MaterialConstantBufferDef
{
    uint32_t vsDataSize;     // +0x00
    uint32_t hsDataSize;     // +0x04
    uint32_t dsDataSize;     // +0x08
    uint32_t psDataSize;     // +0x0C

    uint32_t vsUshortCount;  // +0x10
    uint32_t hsUshortCount;  // +0x14
    uint32_t dsUshortCount;  // +0x18
    uint32_t psUshortCount;  // +0x1C

    void* vsData;         // +0x20
    void* hsData;         // +0x28
    void* dsData;         // +0x30
    void* psData;         // +0x38

    uint16_t* vsUshorts;     // +0x40
    uint16_t* hsUshorts;     // +0x48
    uint16_t* dsUshorts;     // +0x50
    uint16_t* psUshorts;     // +0x58

    ID3D11Buffer* vsBuffer;  // +0x60
    ID3D11Buffer* hsBuffer;  // +0x68
    ID3D11Buffer* dsBuffer;  // +0x70
    ID3D11Buffer* psBuffer;  // +0x78
}; // size 0x80

union MaterialTextureDefInfo
{
    GfxImage* image;
    void* water;
};

struct MaterialTextureDef
{
    unsigned int nameHash;
    char nameStart;
    char nameEnd;
    unsigned char samplerState;
    unsigned char semantic;
    MaterialTextureDefInfo u;
};

struct GfxStateBits
{
    char data[0x20];
};

struct Material
{
    MaterialInfo info;                         // 0x000, size 0x30

    char pad_0030[0xA2 - 0x30];        // 0x030

    char textureCount;                 // 0x0A2
    char stateBitsCount;               // 0x0A3
    char constantCount;                // 0x0A4

    char pad_00A5[0xAD - 0xA5];        // 0x0A5

    char constantBufferCount;          // 0x0AD
    char layerCount;                   // 0x0AE

    char pad_00AF[0xB8 - 0xAF];        // 0x0AF

    MaterialTechniqueSet* techniqueSet;        // 0x0B8
    MaterialTextureDef* textureTable;          // 0x0C0
    GfxStateBits* stateBitsTable;              // 0x0C8
    MaterialConstantDef* constantTable;         // 0x0D0
    Material* materialHandle;                  // 0x0D8, name uncertain

    char pad_00E0[0x158 - 0xE0];       // 0x0E0

    MaterialConstantBufferDef* constantBufferTable; // 0x158
    const char** subMaterials;                      // 0x160
};



static_assert(offsetof(Material, textureCount) == 0xA2);
static_assert(offsetof(Material, stateBitsCount) == 0xA3);
static_assert(offsetof(Material, constantCount) == 0xA4);
static_assert(offsetof(Material, constantBufferCount) == 0xAD);
static_assert(offsetof(Material, layerCount) == 0xAE);
static_assert(offsetof(Material, techniqueSet) == 0xB8);
static_assert(offsetof(Material, textureTable) == 0xC0);
static_assert(offsetof(Material, stateBitsTable) == 0xC8);
static_assert(offsetof(Material, constantTable) == 0xD0);
static_assert(offsetof(Material, constantBufferTable) == 0x158);
static_assert(offsetof(Material, subMaterials) == 0x160);
static_assert(sizeof(Material) == 0x168);
