#pragma once

enum enTamersDigimon
{
	T_None,
	T_Koromon,
	T_Tsunomon,
	T_Tokomon,
	T_Nyaromon,
	T_Yokomon,
	T_Tanemon,
	T_Motimon,
	T_Bukamon,
	T_END
};


enum enDigimon
{
	NoneDigimon,
	//1 cost =============
	Veemon,		    // 브이몬
	Hawkmon,	    // 호크몬
	Armadilomon,    // 아르마몬
	Wormmon,	    // 추추몬
	FlameDramon,    // 화염드라몬
	LaiDramon,	    // 번개드라몬
	Guilmon,	    // 길몬
	Terriermon,     // 테리어몬
	Renamon,	    // 레나몬
	Impmon,		    // 임프몬
	Hagurumon,	    // 톱니몬
	Guardromon,     // 가드로몬
	Gottsumon,	    // 울퉁몬
	Numemon,	    // 워매몬
	//2 cost =============
	Greymon,	    // 그레이몬
	Ikkakumon,	    // 원뿔몬
	Megnamon,	    // 매그너몬
	Gargomon,	    // 가르고몬
	Kyubimon,	    // 구미호몬
	Ogremon,	    // 우가몬
	Wizardmon,	    // 위자몬
	Piximon,	    // 피콜몬
	MetalSeadramon, // 메탈시드라몬
	Pinokimon,	    // 피노키몬
	Mamemon,	    // 콩알몬
	LordKnightmon,  // 로드나이트몬
	Barbamon,	    // 발바몬
	Luchemon,	    // 루체몬
	//3 cost =============
	Lilymon,	    // 릴리몬
	Angelmon,	    // 엔젤몬
	PileDramon,	    // 파일드라몬
	Silphymon,	    // 실피드몬
	Towmon,		    // 토우몬
	Leomon,		    // 레오몬
	Whamon,		    // 고래몬
	Andromon,	    // 안드로몬
	Pumpmon,	    // 펌프몬
	Etemon,		    // 에테몬
	Digitamon,	    // 디지타몬
	Livaimon,	    // 리바이어몬
	Belphemon,	    // 벨페몬
	//4 cost =============
	Angelwomon,	    // 엔젤우몬
	BanchoLilymon,  // 반쵸릴리몬
	Beelzemon,	    // 베르제브몬
	Skullgreymon,   // 스컬그레이몬
	Ladydevimon,    // 레이디데블몬
	Machinedramon,  // 파워드라몬
	Diablomon,	    // 디아블로몬
	Dynasmon,	    // 듀나스몬
	Cherubimon,	    // 케루비몬
	Deamon,	        // 마왕몬
	Laylamon,	    // 릴리스몬
	MetalMamemon,   // 메탈콩알몬
	//5 cost =============
	Wargreymon,	    // 워그레이몬
	MetalGarurumon, // 메탈가루몬
	ImperialDramon,	// 황제드라몬
	Omegamon,		// 오메가몬
	BlackWargreymon,// 블랙워그레이몬
	Dukemon,	    // 듀크몬
	BanchoLeomon,   // 반쵸레오몬
	Piedmon,		// 피에몬
	Apocalymon,	    // 아포카리몬
	//6 cost =============
	Examon,		    // 엑자몬
	UlforceVeedramon// 알포스브이드라몬
};


enum enItem
{
	NoneItem,
	FenrirSword,
	BerserkSword,
	Bushido,
	Excalibur,
	SpearofJudgement,
	BattleTomahawk,
	GigaStomp,
	DramonKiller,
	RudriTalpanner,
	Torento,
	BlutEvolution,
	Gram,
	SteelDrill,
	UlBullBooster,
	ShieldofIrony,
	MetalArmor,
	ThorHammer,
	BraveShield,
	FlameWings,
	Aegis,
	WhiteWing,
	StarEmblem,
	BlackHelmet,
	BolkeArmer,
	CureBox,
	RoyalMeister,
	AngelicStaff,
	LakeGuardianFlute,
	PositronLaser,
	HolyRing,
	HolyOrb,
	RapidFireGun,
	Romeo,
	SkinofDragon,
	Berenhena
};

enum enArgument
{
	None,           
	// Silver 
	BranchingOut,	       // 가지 뻗기
	Titan,icTitan,         // 거대한 거인
	CalledShot,		       // 결과 예측
	OverEncumbered,	       // 과적
	Firesale,	           // 급매
	Kingslayer,	           // 국왕시해자
	// Gold			       
	TradeSector,	       // 교환의장
	BRB,	               // 금방 올게
	PatientStudy,	       // 끈질긴 연구
	AllThatShimmers,       // 반짝이는 것들
	StarryNight,	       // 별이 빛나는 밤
	FavorOfCaretaker,      // 수호자의 호의
	// Prismatic
	BirthdayPresent,	   // 생일선물
	CalculatedEnhancement, // 계산된 강화
	TiniestTitan,		   // 꼬꼬마 거인
	LevelUp				   // 레벨업
};


// 라운드 종류
enum enRoundType
{
	Type_None,
	Type_Encounter,
	Type_Creep,
	Type_ArgSelect,
	Type_Combat,
	Type_Rolling,
	Type_Boss
};