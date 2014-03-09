#ifndef __STORE_CONFIG_H__
#define __STORE_CONFIG_H__

using namespace std;

#define kTagGooglePlay 0
#define kTagIpayy 1
#define KTagAmazon 2
#define PAYMENT_GATEWAY kTagGooglePlay


namespace StoreConfig
{
	#define MAX_COIN_PACKS 4

  	enum CoinPackTags
	{
		kTagCoinPackBoost	= 0,
		kTagCoinPackMega	= 1,
		kTagCoinPackUltra	= 2,
		kTagAdfreeVersion	= 3,

	};

	// Default Currency For Coin Packs
	#define CURRENCY_COIN_PACK_BOOST 	"30 INR"
	#define CURRENCY_COIN_PACK_MEGA 	"60 INR"
	#define CURRENCY_COIN_PACK_ULTRA 	"90 INR"
    #define CURRENCY_COIN_PACK_ULTRA_ULTRA "150 INR"


	//TODO add / update secret key while publishing.
	#define STORE_SECRET_KEY	"TWIST_MOBILE"

	// Default Values For Coin Packs
	enum CoinPacks
	{
		COIN_PACK_BOOST	= 5000,
		COIN_PACK_MEGA	= 10000,
		COIN_PACK_ULTRA	= 15000,
		COIN_PACK_ULTRA_ULTRA= 30000,

	};

	// Default ITEM ID for coin packs
	static const string COIN_PACK_IDS[] = {
		"android.test.purchased",
		"20_coin",
		"50_coin",
		"ad_free",
	};

	// Default coin numbers for coin packs
	static const string COIN_PACK_COINS[] =
	{
		"5000",
		"12000",
		"30000",
		"100000",
	};

#if(PAYMENT_GATEWAY==kTagIpayy)
	// Default cost for coin packs
	static const string COIN_PACK_COSTS[] =
	{
		"Rs30-",    //"0.99$  ",
		"Rs60-",	//"1.99$  ",
		"Rs90-",	//"2.99$  ",
		"Rs150-",	//"4.99$  ",
	};

#else
	// Default cost for coin packs
		static const string COIN_PACK_COSTS[] =
		{
			"0.99$  ",
			"1.99$  ",
			"2.99$  ",
			"4.99$  ",
		};

#endif


	static const int AMOUNT[] =
			{
				30,
				60,
				90,
				150,
				30,
			};


	/*PowerUp Defaults*/

	static const int Initial_Currency=1000;

	static const int Reduceble_amount_For_Replay_Level=0;

	static const int Reduceble_amount_For_Skip_Level=3000;

	static const int Reduceble_amount_For_Extra_Slice=1000;

	static const int Numberof_Extra_Slice=1;

	static const int Reduceble_amount_For_PowerCut=2000;

	static const int Reduceble_amount_For_Hint=5000;


	static const int Entry_Level_For_Hint=3;

	static const int Entry_Level_For_ExtraCut=4;

	static const int Entry_Level_For_PowerCut=7;

	static const int Entry_Level_For_SkipLevel=10;

	/*PowerUp Defaults*/

	static const string Zone_Coins[] =
		{
			"0",
			"35000",
			"45000",
			"45000",
			"45000",
			"45000",
		};

	//TODO Change URL For Updated Store Configuration.
	//static const char* STORE_URL	= "http://180.179.207.245/Dragger-2/xmlgenerator.php";
	//static const char* STORE_URL	= "http://180.179.207.245/Dragger-2/xmls_file1.xml";
	static const char* STORE_XML_GEN = "http://180.179.207.245/cut_the_box1/xmls/file1373379239.xml";
	//static const char* STORE_URL	= "http://180.179.207.245/cut_the_box1/xmls/file1373379239.xml";
	// http://180.179.207.245/cut_the_box1/xmlgenerator.php
	//http://180.179.207.245/cut_the_box1/xmls/file1373379239.xml

    #if(PAYMENT_GATEWAY==kTagIpayy)
	const static char ADEFREE_POPUP_TEXT[50]="Remove ads for Rs30!";
    #else
	const static char ADEFREE_POPUP_TEXT[50]="Remove ads for 0.99$!";
    #endif

	static const char* m_sCoinKey	= "coin_pack_%d_price";
	static const char* m_sCostKey	= "coin_pack_%d_cost";

	static const char* m_sInitialCoins	= "InitialCoins";
	static const char* m_sCoinsToReduced	= "CoinsToReduce";

	static const char* m_sCoinsToReducedForSkipLevel	= "CoinsToReduceForSkipLevel";
	static const char* m_sCoinsToReducedForExtraSlice	= "CoinsToReduceForExtraSlice";
	static const char* m_NumberofExtraSlice				= "NumberofExtraSlice";
	static const char* m_sCoinsToReducedForPowerCut	    = "CoinsToReduceForPowerCut";
	static const char* m_sCoinsToReducedForHint	        = "CoinsToReduceForHint";

	static const char* m_sHintStartLevel				= "HintStartLevel";
	static const char* m_sExtraCutStartLevel	        = "ExtraCutStartLevel";
	static const char* m_sPOwerCutStartLevel	        = "POwerCutStartLevel";
	static const char* m_sSkipLevelStartLevel	        = "SkipLevelStartLevel";

	static const char* m_sZoneCoins	= "ZoneCoins%d";


	static const char* m_sStoreKey	= "coin_pack_exist";
};
#endif
