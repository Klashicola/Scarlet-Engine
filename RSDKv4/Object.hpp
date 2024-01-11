#ifndef OBJECT_H
#define OBJECT_H

#define NATIVEENTITY_COUNT (0x100)

#define ENTITY_COUNT     (0x4A0)
#define TEMPENTITY_START (ENTITY_COUNT - 0x80)
#define OBJECT_COUNT     (0x100)
#define TYPEGROUP_COUNT  (0x103)

enum ObjectControlModes {
    CONTROLMODE_NONE   = -1,
    CONTROLMODE_NORMAL = 0,
};

struct TypeGroupList {
    int entityRefs[ENTITY_COUNT];
    int listSize;
};

struct Entity {
    int xpos;
    int ypos;
    int xvel;
    int yvel;
    int speed;
    int values[48];
    int state;
    int angle;
    int scale;
    int rotation;
    int alpha;
    int animationTimer;
    int animationSpeed;
    int lookPosX;
    int lookPosY;
    ushort groupID;
    byte type;
    byte propertyValue;
    byte priority;
    byte drawOrder;
    byte direction;
    byte inkEffect;
    byte animation;
    byte prevAnimation;
    byte frame;
    byte collisionMode;
    byte collisionPlane;
    sbyte controlMode;
    byte controlLock;
    byte pushing;
    byte visible;
    byte tileCollisions;
    byte objectInteractions;
    byte gravity;
    byte left;
    byte right;
    byte up;
    byte down;
    byte jumpPress;
    byte jumpHold;
    byte scrollTracking;
    // was 3 on S1 release, but bumped up to 5 for S2
    byte floorSensors[5];
};

struct NativeEntityBase {
    void (*eventCreate)(void *objPtr);
    void (*eventMain)(void *objPtr);
    int slotID;
    int objectID;
};

struct NativeEntity {
    void (*eventCreate)(void *objPtr);
    void (*eventMain)(void *objPtr);
    int slotID;
    int objectID;
    void *extra[0x100];
};

enum ObjectTypes {
    OBJ_TYPE_BLANKOBJECT = 0 // 0 is always blank obj
};

enum ObjectGroups {
    GROUP_ALL = 0 // 0 is always "all"
};

enum ObjectPriority {
    // The entity is active if the entity is on screen or within 128 pixels of the screen borders on any axis
    PRIORITY_BOUNDS,
    // The entity is always active, unless the stage state is PAUSED/FROZEN
    PRIORITY_ACTIVE,
    // Same as PRIORITY_ACTIVE, the entity even runs when the stage state is PAUSED/FROZEN
    PRIORITY_ALWAYS,
    // Same as PRIORITY_BOUNDS, however it only does checks on the x-axis, so when in bounds on the x-axis, the y position doesn't matter
    PRIORITY_XBOUNDS,
    // Same as PRIORITY_XBOUNDS, however the entity's type will be set to BLANK OBJECT when it becomes inactive
    PRIORITY_XBOUNDS_DESTROY,
    // Never Active.
    PRIORITY_INACTIVE,
    // Same as PRIORITY_BOUNDS, but uses the smaller bounds (32px off screen rather than the normal 128)
    PRIORITY_BOUNDS_SMALL,
    // Same as PRIORITY_ACTIVE, but uses the smaller bounds in object.outOfBounds
    PRIORITY_ACTIVE_SMALL
};

extern int objectEntityPos;
extern int curObjectType;
extern Entity objectEntityList[ENTITY_COUNT * 2];
extern int processObjectFlag[ENTITY_COUNT];
extern TypeGroupList objectTypeGroupList[TYPEGROUP_COUNT];

extern char typeNames[OBJECT_COUNT][0x40];

extern int OBJECT_BORDER_X1;
extern int OBJECT_BORDER_X2;
extern int OBJECT_BORDER_X3;
extern int OBJECT_BORDER_X4;
extern const int OBJECT_BORDER_Y1;
extern const int OBJECT_BORDER_Y2;
extern const int OBJECT_BORDER_Y3;
extern const int OBJECT_BORDER_Y4;

void ProcessStartupObjects();
void ProcessObjects();
void ProcessPausedObjects();
void ProcessFrozenObjects();
void Process2PObjects();

void SetObjectTypeName(const char *objectName, int objectID);

extern int playerListPos;

void ProcessObjectControl(Entity *entity);

#endif // !OBJECT_H
