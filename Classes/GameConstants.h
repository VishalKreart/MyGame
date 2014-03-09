#define PTM_RATIO 32

const int kSensorBody = 10;
const int kInitCoin = 4;
const int kTagOfSaveMeLayer = 1;
const int kTagOfSaveMeBar = 2;

const cocos2d::CCString kKeyForBestScore = "bestscore";
const cocos2d::CCString kKeyForInitCoin = "initCoin";
static bool purchase = false;
enum 
{
    kGameReady,
    kGamePlay,
    kGameOver,
	kGameSaveMe
};