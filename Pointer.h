// TwMs v169.2 pointer Data
// UPDate:zeach01
// 角色資料
#define CharBase           0x01543DE8
#define CharHPOffset       0x27DC
#define CharMPOffset       0x27E0

// 警告資料
#define WarnBase           0x01548484
#define WarnHPOffset       0x50
#define WarnMPOffset       0x54

// 人物資料
#define PeopleBase         0x01543DF4
#define PeopleTeleSW       0x9E00 // 瞬移
#define PeopleTeleX        0x9E08 // 瞬移
#define PeopleTeleY        0x9E0C // 瞬移
#define PeopleSkillCount   0xA0A4 // 主動技能次數
#define PeopleUberX        0xB2DC // 吸怪 撿物
#define PeopleUberY        0xB2E0 // 吸怪 撿物
#define PeopleFullOffset   0xB2E4 // 集氣瞬滿
#define PeopleJumpOffset   0xB8C4 // 連續跳躍
#define PeopleSkillAct	   0x0528 //技能動作

//#define PeopleDelayOffset  0x // 冰風暴加速
//#define PeopleActionOffset 0x

// 紅點資料
#define RedPointBase       0x01548388
#define RedPointOffset     0x2c // 紅點數量

// 怪物資料
#define MonsterBase        0x0154838C
#define MonsterCountOffset 0x24 // 怪物數量

// 物品資料
#define DropBase           0x01548CB8
#define DropCount          0x40

// 地圖資料
#define MapBase            0x0154FF4C
#define MapIDOffset        0x13E4 // 地圖ID
#define MapCharXOffset     0x12A4 // 地圖X
#define MapCharYOffset     0x12A8 // 地圖Y

// 牆值資料
#define WallBase           0x01548384
#define WallLeftOffset     0x1C
#define WallRightOffset    0x24
#define WallUpOffset	   0x20
#define WallDownOffset     0x28

// 滑鼠資料
#define MouseBase          0x01543DF0
#define MouseAction        0xA28 // 滑鼠動作
#define MouseXY            0x978 // 滑鼠座標
#define MouseXOffset       0x88 // 滑鼠X
#define MouseYOffset       0x8C // 滑鼠Y

// 系統時間
#define SystemTimeBase     0x015487D0
#define SystemTimeOffset   0x20

// 其他
#define SystemBase         0x01543A98
#define SuperPickOffset    0x21B4 // 超級撿物
#define SuperPickOffset2   0x21B8
#define JailBreakOffset    0x6FCC // 逃離監獄
#define SpawnSwitchOffset  0x6FE8
#define SpawnXOffset       0x6FE0
#define SpawnYOffset       0x6FE4

//神域護佑
#define GodBlessAddress  0x01565F10
#define GodBlessAddress2 0x01566F64

//視窗黑屏
#define BlackScreenAddress 0x52206C5A


#define pLogin   			0x015515A4
#define oLoginPage       	0x2C8
#define oLoginChar    		0x30C

#define plServer  			0x01550DCC
#define olServer     		0xC0

#define plChannel  			0x01550dd0
#define olChannel  			0x11C
