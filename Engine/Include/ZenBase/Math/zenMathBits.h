#pragma once
#ifndef __LibZenBase_Api_Math_Bits_h__
#define __LibZenBase_Api_Math_Bits_h__

namespace zen { namespace zenMath 
{
	zUInt	BitsCount( zU16 _uValue );			// Number of bits set to 1 in value
	zUInt	BitsCount( zU32 _uValue );
	zUInt	BitsCount( zU64 _uValue );
	zU8	BitsReverse( zU8 _uValue );			// Reverser bits order (0x0100 -> 0x0010)
	zU16	BitsReverse( zU16 _uValue );
	zU32	BitsReverse( zU32 _uValue );
	zU64	BitsReverse( zU64 _uValue );
	int		BitsScan( zU8 _uValue );				// Index of 1st bit set to 1 (starting from 0, <0 if none)
	int		BitsScan( zU16 _uValue );			
	int		BitsScan( zU32 _uValue );			
	int		BitsScan( zU64 _uValue );
	int		BitsScanReverse( zU8 _uValue );		// Index of 1st bit set to 1 (starting from last bits, <0 if none)
	int		BitsScanReverse( zU16 _uValue );		
	int		BitsScanReverse( zU32 _uValue );	
	int		BitsScanReverse( zU64 _uValue );

}  } // namespace zen, zenMath

//#include ZENInlinePlatform( CMathBits )

#endif
