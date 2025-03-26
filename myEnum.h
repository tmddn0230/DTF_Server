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
	Veemon,		    // ���̸�
	Hawkmon,	    // ȣũ��
	Armadilomon,    // �Ƹ�����
	Wormmon,	    // ���߸�
	FlameDramon,    // ȭ������
	LaiDramon,	    // ��������
	Guilmon,	    // ���
	Terriermon,     // �׸����
	Renamon,	    // ������
	Impmon,		    // ������
	Hagurumon,	    // ��ϸ�
	Guardromon,     // ����θ�
	Gottsumon,	    // ������
	Numemon,	    // ���Ÿ�
	//2 cost =============
	Greymon,	    // �׷��̸�
	Ikkakumon,	    // ���Ը�
	Megnamon,	    // �ű׳ʸ�
	Gargomon,	    // �������
	Kyubimon,	    // ����ȣ��
	Ogremon,	    // �찡��
	Wizardmon,	    // ���ڸ�
	Piximon,	    // ���ݸ�
	MetalSeadramon, // ��Ż�õ���
	Pinokimon,	    // �ǳ�Ű��
	Mamemon,	    // ��˸�
	LordKnightmon,  // �ε峪��Ʈ��
	Barbamon,	    // �߹ٸ�
	Luchemon,	    // ��ü��
	//3 cost =============
	Lilymon,	    // ������
	Angelmon,	    // ������
	PileDramon,	    // ���ϵ���
	Silphymon,	    // ���ǵ��
	Towmon,		    // ����
	Leomon,		    // ������
	Whamon,		    // ����
	Andromon,	    // �ȵ�θ�
	Pumpmon,	    // ������
	Etemon,		    // ���׸�
	Digitamon,	    // ����Ÿ��
	Livaimon,	    // �����̾��
	Belphemon,	    // �����
	//4 cost =============
	Angelwomon,	    // �������
	BanchoLilymon,  // ���ݸ�����
	Beelzemon,	    // ���������
	Skullgreymon,   // ���ñ׷��̸�
	Ladydevimon,    // ���̵𵥺��
	Machinedramon,  // �Ŀ�����
	Diablomon,	    // ��ƺ�θ�
	Dynasmon,	    // �೪����
	Cherubimon,	    // �ɷ���
	Deamon,	        // ���ո�
	Laylamon,	    // ��������
	MetalMamemon,   // ��Ż��˸�
	//5 cost =============
	Wargreymon,	    // ���׷��̸�
	MetalGarurumon, // ��Ż�����
	ImperialDramon,	// Ȳ������
	Omegamon,		// ���ް���
	BlackWargreymon,// �����׷��̸�
	Dukemon,	    // ��ũ��
	BanchoLeomon,   // ���ݷ�����
	Piedmon,		// �ǿ���
	Apocalymon,	    // ����ī����
	//6 cost =============
	Examon,		    // ���ڸ�
	UlforceVeedramon// ���������̵���
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
	BranchingOut,	       // ���� ����
	Titan,icTitan,         // �Ŵ��� ����
	CalledShot,		       // ��� ����
	OverEncumbered,	       // ����
	Firesale,	           // �޸�
	Kingslayer,	           // ���ս�����
	// Gold			       
	TradeSector,	       // ��ȯ����
	BRB,	               // �ݹ� �ð�
	PatientStudy,	       // ������ ����
	AllThatShimmers,       // ��¦�̴� �͵�
	StarryNight,	       // ���� ������ ��
	FavorOfCaretaker,      // ��ȣ���� ȣ��
	// Prismatic
	BirthdayPresent,	   // ���ϼ���
	CalculatedEnhancement, // ���� ��ȭ
	TiniestTitan,		   // ������ ����
	LevelUp				   // ������
};


// ���� ����
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