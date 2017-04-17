#ifndef CLASSES_H
#define CLASSES_H

#include <windows.h>
#include <math.h>

#include "Offsets.h"
#include "Enums.h"
#include "Utils.h"

class Vec3
{
public:

	Vec3( )
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
	};

	Vec3( float px, float py, float pz )
	{
		this->x = px;
		this->y = py;
		this->z = pz;
	};

	Vec3 sub( Vec3 v )
	{
		Vec3 p = Vec3( this->x, this->y, this->z );
		p.x -= v.x;
		p.y -= v.y;
		p.z -= v.z;
		return p;
	};

	float dot( Vec3 vec )
	{
		float temp = 0;
		temp = this->x*vec.x + this->y*vec.y + this->z*vec.z;
		return temp;
	};

	float dist( Vec3 vec )
	{
		return sqrt( ( this->x - vec.x ) * ( this->x - vec.x ) + ( this->y - vec.y ) * ( this->y - vec.y ) + ( this->z - vec.z ) * ( this->z - vec.z ) );
	}

	Vec3 mul( Vec3 v )
	{
		return Vec3( x * v.x, y * v.y, z * v.z );
	};

	Vec3 mul( float f )
	{
		return Vec3( x * f, y * f, z * f );
	};

	Vec3 div( Vec3 v )
	{
		return Vec3( x / v.x, y / v.y, z / v.z );
	};

	Vec3& operator + ( const Vec3& v ) const
	{
		return Vec3( x + v.x, y + v.y, z + v.z );
	}

	Vec3& operator / ( const float& div ) const
	{
		return Vec3( x / div, y / div, z / div );
	}

	Vec3& operator - ( const Vec3& v ) const
	{
		return Vec3( x - v.x, y - v.y, z - v.z );
	}

	float Length( )
	{
		float flLengthX, flLengthY, flLengthZ, flLength;

		flLengthX = x * x;
		flLengthY = y * y;
		flLengthZ = z * z;

		flLength = sqrt( flLengthX + flLengthY + flLengthZ );

		return fabs( flLength );
	}

	void Normalize( )
	{
		float length, ilength;

		length = this->Length( );

		if( length )
		{
			ilength = 1 / length;

			this->x *= ilength;
			this->y *= ilength;
			this->z *= ilength;
		}
	}

	Vec3 &div( float f )
	{
		x /= f;
		y /= f;
		z /= f;
		return *this;
	}

	float x;
	float y;
	float z;
};

class Vec4
{
public:

	Vec4( )
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
		this->w = 0;
	};

	Vec4( float px, float py, float pz, float pw )
	{
		this->x = px;
		this->y = py;
		this->z = pz;
		this->w = pw;
	};

	float Length( )
	{
		float flLengthX, flLengthY, flLengthZ, flLengthW, flLength;

		flLengthX = x * x;
		flLengthY = y * y;
		flLengthZ = z * z;
		flLengthW = w * w;

		flLength = sqrt( flLengthX + flLengthY + flLengthZ + flLengthW );

		return fabs( flLength );
	}

	void Normalize( )
	{
		float length, ilength;

		length = this->Length( );

		if( length )
		{
			ilength = 1 / length;

			this->x *= ilength;
			this->y *= ilength;
			this->z *= ilength;
			this->w *= ilength;
		}
	}

	Vec4 &div( float f )
	{
		x /= f;
		y /= f;
		z /= f;
		w /= f;
		return *this;
	}

	float x;
	float y;
	float z;
	float w;
};

//Source
struct glmatrixf
{
	float v[16];

	glmatrixf( )
	{
	}

	glmatrixf( float vals[16] )
	{
		for( int i = 0; i < 16; i++ )
			v[i] = vals[i];
	}

#define MULMAT( row, col ) \
	v[col + row] = x[row] * y[col] + x[row + 4] * y[col + 1] + x[row + 8] * y[col + 2] + x[row + 12] * y[col + 3];

	template<class XT, class YT>
	void mul( const XT x[16], const YT y[16] )
	{
		MULMAT( 0, 0 ); MULMAT( 1, 0 ); MULMAT( 2, 0 ); MULMAT( 3, 0 );
		MULMAT( 0, 4 ); MULMAT( 1, 4 ); MULMAT( 2, 4 ); MULMAT( 3, 4 );
		MULMAT( 0, 8 ); MULMAT( 1, 8 ); MULMAT( 2, 8 ); MULMAT( 3, 8 );
		MULMAT( 0, 12 ); MULMAT( 1, 12 ); MULMAT( 2, 12 ); MULMAT( 3, 12 );
	}
	/*
	glmatrixf multiply( glmatrixf pMatrix )
	{
		float vals[16];

		vals[0] = v[0] * pMatrix.v[0] + v[1] * pMatrix.v[4] + v


		return *this;
	}
	*/

	Vec4 multiplyVec4( Vec4 pVector )
	{
		return Vec4
		(
			pVector.x*v[0] + pVector.y*v[4] + pVector.z*v[8] + pVector.w*v[12],
			pVector.x*v[1] + pVector.y*v[5] + pVector.z*v[9] + pVector.w*v[13],
			pVector.x*v[2] + pVector.y*v[6] + pVector.z*v[10] + pVector.w*v[14],
			pVector.x*v[3] + pVector.y*v[7] + pVector.z*v[11] + pVector.w*v[15]
		);
	}

	float transformx( const Vec3 &p ) const
	{
		return p.x*v[0] + p.y*v[4] + p.z*v[8] + v[12];
	}

	float transformy( const Vec3 &p ) const
	{
		return p.x*v[1] + p.y*v[5] + p.z*v[9] + v[13];
	}

	float transformz( const Vec3 &p ) const
	{
		return p.x*v[2] + p.y*v[6] + p.z*v[10] + v[14];
	}

	float transformw( const Vec3 &p ) const
	{
		return p.x*v[3] + p.y*v[7] + p.z*v[11] + v[15];
	}
};

struct sqr
{
	unsigned char type;
	char floor, ceil;
	unsigned char wtex, ftex, ctex;
	unsigned char r, g, b;
	unsigned char vdelta;
	char defer;
	char occluded;
	unsigned char utex;
	unsigned char tag;
	unsigned char reserved[2];
};

namespace AssaultCube
{
	class Player;
	class Weapon;

	class ScreenSettings
	{
	public:
		__int32 m_Width; //0x0000 
		__int32 m_Height; //0x0004 
		char _0x0008[8];
		__int32 m_GraphicDetail; //0x0010 VIDEO: INSANE - MEDIUM = 8, LOWER = 0 
		__int32 m_AntiAlias; //0x0014  VIDEO: INSANE = 8, HIGH = 4, LOWER = 0
		__int32 m_VSync; //0x0018 
		BYTE m_Fullscreen; //0x001C 
		char _0x001D[23];
		__int32 m_Gamma; //0x0034 
		__int32 m_MaxFPS; //0x0038 
		char _0x003C[12];
		__int32 m_GameSpeed; //0x0048   100 is normal
		bool m_Paused; //0x004C
		char _0x004C[8];
		__int32 m_GameStarts;

		static ScreenSettings* GetInstance( )
		{
			return reinterpret_cast< ScreenSettings* >( OFFSET_SCREENSETTINGS );
		}

	};//Size=0x0080

	class Player
	{
	public:
		virtual void Function0( ); //
		virtual ~Player( ); //
		virtual void Function2( ); //
		virtual void Function3( ); //
		virtual void OnCollision( ); //
		virtual void OnMoved( const Vec3 &dist ); //
		virtual void Function6( ); //
		virtual void Function7( ); //
		virtual void Function8( ); //
		virtual void Function9( ); //

		Vec3 m_HeadPos; //0x0004 
		Vec3 m_Velocity; //0x0010 
		char _0x001C[24];
		Vec3 m_FootPos; //0x0034 
		float m_Yaw; //0x0040 
		float m_Pitch; //0x0044 
		float m_Roll; //0x0048 
		float m_PitchVel; //0x004C
		float m_MaxSpeed; //0x0050
		__int32 m_AirTime; //0x0054 
		float m_Radius; //0x0058 
		float m_Height; //0x005C 
		float m_NormalHeight; //0x0060 
		float m_HeightAboveHead; //0x0064 
		BYTE m_IsInWater; //0x0068 
		BYTE m_IsOnFloor; //0x0069 
		BYTE m_IsOnLadder; //0x006A 
		BYTE m_JumpNext; //0x006B 
		BYTE m_Crouching; //0x006C 
		BYTE m_AirCrouch; //0x006D 
		char _0x006E[1];
		BYTE m_CanCollide; //0x006F 
		BYTE m_IsNotInGame; //0x0070 
		BYTE m_Scoping; //0x0071 
		BYTE m_Shooting; //0x0072 
		char _0x0073[5];
		float m_LastJumpYPos; //0x0078 
		__int32 m_LastSplash; //0x007C 
		BYTE m_Move; //0x0080 
		BYTE m_Strafe; //0x0081 
		BYTE m_State; //0x0082 
		BYTE m_Type; //0x0083 
		char _0x0084[116];
		__int32 m_Health; //0x00F8 
		__int32 m_Armor; //0x00FC 
		__int32 m_Primary; //0x0100 
		char _0x0104[4];
		__int32 m_GunSelect; //0x0108 
		BYTE m_AkimboEquipped; //0x010C 
		char _0x010D[7];
		__int32 m_SecondaryAmmoInReserve; //0x0114 
		char _0x0118[16];
		__int32 m_PrimaryAmmoInReserve; //0x0128 
		char _0x012C[8];
		__int32 m_AkimboAmmoInReserve; //0x0134 
		char _0x0138[4];
		__int32 m_SecondaryAmmo; //0x013C 
		char _0x0140[16];
		__int32 m_PrimaryAmmo; //0x0150 
		char _0x0154[4];
		__int32 m_GrenadeAmmo; //0x0158 
		__int32 m_AkimboAmmo; //0x015C 
		__int32 m_MeleeDelayTime; //0x0160 
		__int32 m_SecondaryDelayTime; //0x0164 
		char _0x0168[16];
		__int32 m_PrimaryDelayTime; //0x0178 
		char _0x017C[4];
		__int32 m_GrenadeWaitingTime; //0x0180 
		__int32 m_AkimboWaitingTime; //0x0184 
		__int32 m_MeleeShotsFired; //0x0188 
		__int32 m_SecondaryShotsFired; //0x018C 
		char _0x0190[16];
		__int32 m_PrimaryShotsFired; //0x01A0 
		char _0x01A4[4];
		__int32 m_GrenadeShotsFired; //0x01A8 
		__int32 m_AkimboShotsFired; //0x01AC 
		char _0x01B0[44];
		__int32 m_Skin; //0x01DC 
		__int32 m_NextSkin; //0x01E0 
		__int32 m_ClientID; //0x01E4 
		__int32 m_LastUpdate; //0x01E8 
		__int32 m_Lag; //0x01EC 
		__int32 m_Ping; //0x01F0 
		DWORD m_Address; //0x01F4 
		__int32 m_TimesRespawned; //0x01F8 
		__int32 m_Kills; //0x01FC 
		__int32 m_FlagScore; //0x0200 
		__int32 m_Deaths; //0x0204 
		__int32 m_Score; //0x0208 
		__int32 m_TeamKills; //0x020C 
		__int32 m_LastAction; //0x0210 
		__int32 m_LastMove; //0x0214 
		__int32 m_LastHurt; //0x0218 
		__int32 m_LastVoiceCom; //0x021C 
		__int32 m_ClientRole; //0x0220 
		BYTE m_IsShooting; //0x0224 
		char m_Name[260]; //0x0225 
		char pad_0x0329[0x3]; //0x0329
		__int32 m_Team; //0x032C 
		__int32 m_WeaponChanging; //0x0330 
		__int32 m_NextWeapon; //0x0334 
		unsigned char m_SpectateMode; //0x0338 
		unsigned char m_SpectateCN; //0x0339 
		char pad_0x033A[0xE]; //0x033A
		/*
		__int32 m_Team; //0x0329 / C
		__int32 m_Weaponchanging; //0x032D
		__int32 m_NextWeapon; //0x0331
		//char _0x0335[3];
		BYTE m_SpectateMode; //0x0338
		__int32 m_SpectateCN; //0x0339
		__int32 m_EarDamageMillis; //0x033D
		//__int32 m_RespawnOffset; //0x0341
		char __0xbuf[3];
		*/
		Weapon* m_Weapons[NUMGUNS]; //0x348
		char __0xbuf2[22];
		DWORD m_LastMillis; //0x0388 

		Weapon *GetCurrentWeapon( )
		{
			return this->m_Weapons[this->m_GunSelect];
		}

	};//Size=0x0349

	class Weapon
	{
	public:

		class Info
		{
		public:
			char m_Name[260]; //0x0000 
			__int16 m_Sound; //0x0104 
			__int16 m_Reload; //0x0106 
			__int16 m_ReloadTime; //0x0108 
			__int16 m_AttackDelay; //0x010A 
			__int16 m_Damage; //0x010C 
			__int16 m_Piercing; //0x010E 
			__int16 m_ProjSpeed; //0x0110 
			__int16 m_Part; //0x0112 
			__int16 m_Spread; //0x0114 
			__int16 m_Recoil; //0x0116 
			__int16 m_MagSize; //0x0118 
			__int16 m_MdlKickRot; //0x011A 
			__int16 m_MdlKickBack; //0x011C 
			__int16 m_RecoilIncrease; //0x011E 
			__int16 m_RecoilBase; //0x0120 
			__int16 m_MaxRecoil; //0x0122 
			__int16 m_RecoilBackFade; //0x0124 
			__int16 m_PushFactor; //0x0126 
			BYTE m_IsAuto; //0x0128 

		};//Size=0x0129

		virtual ~Weapon( );
		virtual int dynspread( );
		virtual float dynrecoil( );

		virtual void attacksound( );
		virtual bool reload( bool autoreloaded );
		virtual void reset( );
		virtual bool busy( );

		__int32 m_Type; //0x0004 
		Player* m_Owner; //0x0008 
		Info* m_Info; //0x000C 
		__int32* m_AmmoInReserve; //0x0010 
		__int32* m_Ammo; //0x0014 
		__int32* m_Gunwait; //0x0018 
		__int32 m_Shots; //0x001C 
		__int32 m_Reloading; //0x0020 
		__int32 m_LastAction; //0x0024 

	};//Size=0x0028

	class Game
	{
	public:

		class GameMode
		{
		public:
			__int32 m_ID; //0x0000 
			char* m_Name; //0x0004 
		};//Size=0x0008

		char** m_MapNames; //0x0000 
		char _0x0004[8];
		BYTE m_SendMap; //0x000C 
		BYTE m_GetMap; //0x000D 
		char _0x000E[50];
		__int32 m_GameMode; //0x0040 
		char _0x0044[84];
		Player* m_LocalPlayer; //0x0098 
		Player** m_OtherPlayers; //0x009C 
		__int32 m_MaxPlayerCount; //0x00A0 
		__int32 m_PlayerCount; //0x00A4 
		char _0x00A8[80];
		DWORD* m_GameModes; //0x00F8 
		char _0x00FC[68];

		Player* GetPlayer( int index )
		{
			if( index < 0 )
				return NULL;

			if( index > 32 )
				return NULL;

			if( Utils::IsValidPtr( this->m_OtherPlayers ) )
			{
				if( Utils::IsValidPtr( this->m_OtherPlayers[index] ) )
				{
					return this->m_OtherPlayers[index];
				}
			}

			return NULL;
		}

		static Game* GetInstance( )
		{
			return reinterpret_cast< Game* >( OFFSET_GAME );
		}

	};//Size=0x0140

	class hitmsg
	{
	public:
		__int32 target; //0x0000 
		__int32 lifesequence; //0x0004 
		__int32 info; //0x0008 
		__int32 x; //0x000C 
		__int32 y; //0x0010 
		__int32 z; //0x0014 

	};//Size=0x0018

	class Entity
	{
	public:
		__int16 x; //0x0000 
		__int16 y; //0x0002 
		__int16 z; //0x0004 
		__int16 attr1; //0x0006 
		BYTE type; //0x0008 
		BYTE attr2; //0x0009 
		BYTE attr3; //0x000A 
		BYTE attr4; //0x000B 
		BYTE spawned; //0x000C 
		char pad_0x000D[0x3]; //0x000D
		__int32 lastmillis; //0x0010 

	};//Size=0x0014


	class EntityList
	{
	public:
		class CEntityList
		{
		public:
			Entity m_Entities[1024];
		};


		CEntityList* m_Entities; //0x0000 
		__int32 m_MaxEntityCount; //0x0004 
		__int32 m_EntityCount; //0x0008 

		Entity* GetEntity( int index )
		{
			if( index <0 || index> this->m_EntityCount )
				return NULL;

			if( Utils::IsValidPtr( this->m_Entities ) )
			{
				return &m_Entities->m_Entities[index];
			}
			return NULL;
		}

		static EntityList *GetInstance( )
		{
			return reinterpret_cast< EntityList* >( OFFSET_ENTITYLIST );
		}
	};//Size=0x000C

	class BounceEntity
	{
	public:
		virtual void Function0( ); //

		Vec3 m_HeadPos; //0x0004 
		Vec3 m_Velocity; //0x0010 
		char _0x001C[24];
		Vec3 m_FootPos; //0x0034 
		float m_Yaw; //0x0040 
		float m_Pitch; //0x0044 
		float m_Roll; //0x0048 
		float m_PitchVel; //0x004C
		float m_MaxSpeed; //0x0050
		__int32 m_AirTime; //0x0054 
		float m_Radius; //0x0058 
		float m_Height; //0x005C 
		float m_NormalHeight; //0x0060 
		float m_HeightAboveHead; //0x0064 
		BYTE m_IsInWater; //0x0068 
		BYTE m_IsOnFloor; //0x0069 
		BYTE m_IsOnLadder; //0x006A 
		BYTE m_JumpNext; //0x006B 
		BYTE m_Crouching; //0x006C 
		BYTE m_AirCrouch; //0x006D 
		char _0x006E[1];
		BYTE m_CanCollide; //0x006F 
		BYTE m_IsNotInGame; //0x0070 
		BYTE m_Scoping; //0x0071 
		BYTE m_Shooting; //0x0072 
		char _0x0073[5];
		float m_LastJumpYPos; //0x0078 
		__int32 m_LastSplash; //0x007C 
		BYTE m_Move; //0x0080 
		BYTE m_Strafe; //0x0081 
		BYTE m_State; //0x0082 
		BYTE m_Type; //0x0083 
		float m_EyeHeightLevel;
		int m_LastPos;

		int m_Millis;
		int m_TimeToLive;
		int m_Bouncetype;
		float m_RotationSpeed;
		bool m_PlClipped;
		Player *m_Owner;

	};//Size=0x0014

	class BounceEntityList
	{
	public:

		BounceEntity **m_Entities; //0x0000 
		__int32 m_MaxEntityCount; //0x0004 
		__int32 m_EntityCount; //0x0008 

		BounceEntity* GetEntity( int index )
		{
			if( index < 0 || index> this->m_EntityCount )
				return NULL;

			if( Utils::IsValidPtr( this->m_Entities ) )
			{
				return m_Entities[index];
			}
			return NULL;
		}

		static BounceEntityList *GetInstance( )
		{
			return reinterpret_cast< BounceEntityList* >( OFFSET_BOUNCEENTS );
		}
	};//Size=0x000C


}


#endif