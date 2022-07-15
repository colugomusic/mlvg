//------------------------------------------------------------------------
// Project     : VST SDK
//
// Category    : Helpers
// Filename    : public.sdk/source/vst/auwrapper/again/audiounitconfig.h
// Created by  : Steinberg, 12/2007
// Description : VST 3 -> AU Wrapper
//
//-----------------------------------------------------------------------------
// LICENSE
// (c) 2019, Steinberg Media Technologies GmbH, All Rights Reserved
//-----------------------------------------------------------------------------
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
// 
//   * Redistributions of source code must retain the above copyright notice, 
//     this list of conditions and the following disclaimer.
//   * Redistributions in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation 
//     and/or other materials provided with the distribution.
//   * Neither the name of the Steinberg Media Technologies nor the names of its
//     contributors may be used to endorse or promote products derived from this 
//     software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
// IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE 
// OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE  OF THIS SOFTWARE, EVEN IF ADVISED
// OF THE POSSIBILITY OF SUCH DAMAGE.
//-----------------------------------------------------------------------------

// AUWRAPPER_CHANGE

/* Bundle Identifier */
#define kAudioUnitBundleIdentifier	com.llllcompanyllll.vst3plugin.llllpluginnamellll.audiounit
/* Version Number (needs to be in hex)*/
#define kAudioUnitVersion			0x00010000
/* Company Name + Effect Name */
#define kAUPluginName 				llllCompanyllll: llllPluginNamellll
/* Effect Description */
#define kAUPluginDescription 		llllPluginNamellll
/* Audio Unit Type */
#define kAUPluginType 				aufx
/* Unique ID */
#define kAUPluginSubType 			lxxl
/* Registered Company ID */
#define kAUPluginManufacturer 		LXXL

// Definitions for the resource file
#define kAudioUnitName				"llllCompanyllll: llllPluginNamellll"	// same as kAUPluginName
#define kAudioUnitDescription		"llllPluginNamellll"	// same as kAUPluginDescription
#define kAudioUnitType				'aufx'	//kAudioUnitType_Effect // same as kAUPluginType
#define kAudioUnitComponentSubType	'lxxl'	// same as kAUPluginSubType
#define kAudioUnitComponentManuf	'LXXL'	// same as kAUPluginManufacturer

#define kAudioUnitCarbonView		1		// if 0 no Carbon view support will be added
