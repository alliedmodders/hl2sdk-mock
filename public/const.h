// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

#include <stdint.h>

typedef unsigned long CRC32_t;

static constexpr int INVALID_EHANDLE_INDEX = -1;
static constexpr int MAX_LIGHTSTYLES = 64;
static constexpr int MAX_CUSTOM_FILES = 4;
static constexpr int MAX_EDICT_BITS = 11;
static constexpr int MAX_EDICTS = (1 << MAX_EDICT_BITS);
static constexpr int NUM_ENT_ENTRY_BITS = (MAX_EDICT_BITS + 2);
static constexpr int NUM_ENT_ENTRIES = (1 << NUM_ENT_ENTRY_BITS);
static constexpr int ABSOLUTE_PLAYER_LIMIT = 255;
static constexpr int MAX_PLAYER_NAME_LENGTH = 32;
static constexpr int LIFE_ALIVE = 0;

#define MASK_ALL (0xffffffff)
#define MAX_COORD_INTEGER (16384)
#define COORD_EXTENT (2*MAX_COORD_INTEGER)
#define MAX_TRACE_LENGTH (1.732050807569 * COORD_EXTENT)

enum USE_TYPE
{
    USE_OFF = 0, 
    USE_ON = 1, 
    USE_SET = 2, 
    USE_TOGGLE = 3
};

static constexpr int FL_ONGROUND = (1<<0); // At rest / on the ground
static constexpr int FL_DUCKING = (1<<1); // Player flag -- Player is fully crouched
static constexpr int FL_WATERJUMP = (1<<3); // player jumping out of water
static constexpr int FL_ONTRAIN = (1<<4); // Player is _controlling_ a train, so movement commands should be ignored on client during prediction.
static constexpr int FL_INRAIN = (1<<5); // Indicates the entity is standing in rain
static constexpr int FL_FROZEN = (1<<6); // Player is frozen for 3rd person camera
static constexpr int FL_ATCONTROLS = (1<<7); // Player can't move, but keeps key inputs for controlling another entity
static constexpr int FL_CLIENT = (1<<8); // Is a player
static constexpr int FL_FAKECLIENT = (1<<9); // Fake client, simulated server side; don't send network messages to them
static constexpr int FL_INWATER = (1<<10); // In water
static constexpr int PLAYER_FLAG_BITS = 11;
static constexpr int FL_FLY = (1<<11); // Changes the SV_Movestep(); behavior to not need to be on ground
static constexpr int FL_SWIM = (1<<12); // Changes the SV_Movestep(); behavior to not need to be on ground = (but stay in water);
static constexpr int FL_CONVEYOR = (1<<13);
static constexpr int FL_NPC = (1<<14);
static constexpr int FL_GODMODE = (1<<15);
static constexpr int FL_NOTARGET = (1<<16);
static constexpr int FL_AIMTARGET = (1<<17); // set if the crosshair needs to aim onto the entity
static constexpr int FL_PARTIALGROUND = (1<<18); // not all corners are valid
static constexpr int FL_STATICPROP = (1<<19); // Eetsa static prop!  
static constexpr int FL_GRAPHED = (1<<20); // worldgraph has this ent listed as something that blocks a connection
static constexpr int FL_GRENADE = (1<<21);
static constexpr int FL_STEPMOVEMENT = (1<<22); // Changes the SV_Movestep(); behavior to not do any processing
static constexpr int FL_DONTTOUCH = (1<<23); // Doesn't generate touch functions, generates Untouch(); for anything it was touching when this flag was set
static constexpr int FL_BASEVELOCITY = (1<<24); // Base velocity has been applied this frame = (used to convert base velocity into momentum);
static constexpr int FL_WORLDBRUSH = (1<<25); // Not moveable/removeable brush entity = (really part of the world, but represented as an entity for transparency or something);
static constexpr int FL_OBJECT = (1<<26); // Terrible name. This is an object that NPCs should see. Missiles, for example.
static constexpr int FL_KILLME = (1<<27); // This entity is marked for death -- will be freed by game DLL
static constexpr int FL_ONFIRE = (1<<28); // You know...
static constexpr int FL_DISSOLVING = (1<<29); // We're dissolving!
static constexpr int FL_TRANSRAGDOLL = (1<<30); // In the process of turning into a client side ragdoll.
static constexpr int FL_UNBLOCKABLE_BY_PLAYER = (1<<31); // pusher that can't be blocked by the player
