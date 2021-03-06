/*
Copyright (C) 2014-2015, Silent Circle, LLC. All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Any redistribution, use, or modification is done solely for personal
      benefit and not for any commercial purpose or for monetary gain
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name Silent Circle nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL SILENT CIRCLE, LLC BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
//
//  CCMtest.c
//  sccrypto
//
//  Created by vinnie on 10/15/14.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SCcrypto.h"
#include "crypto_optest.h"


typedef  struct {
    Cipher_Algorithm algor;
    unsigned char key[64];
    int           keylen;
    
    uint8_t       seqNum[16];
    size_t        seqNumLen;

    unsigned char pt[64];
    size_t        ptLen;
    
    unsigned char ct[128];
    size_t         ctLen;
    
    unsigned char tag[16];
    int           tagLen;
} ccm_kat_vector;

static SCLError RunCCM_KAT( ccm_kat_vector *kat)
{
    SCLError err = kSCLError_NoErr;
    
    uint8_t* CT = NULL;
    size_t  CTLen = 0;
     unsigned char  T[16];
 
    uint8_t* PT = NULL;
    size_t  PTLen = 0;
  
    OPTESTLogInfo("%4zu", kat->ptLen);
 
    OPTESTLogDebug("\nKey: (%d)\n", (int)kat->keylen );
    dumpHex(IF_LOG_DEBUG, kat->key, (int)kat->keylen, 0);

    OPTESTLogDebug("\nPT: (%d)\n",(int) kat->ptLen  );
    dumpHex(IF_LOG_DEBUG,  kat->pt, (int)kat->ptLen, 0);
    
    err = CCM_Encrypt_Mem( kat->algor,
                           kat->key, kat->keylen,
                           kat->seqNum, kat->seqNumLen,
                           kat->pt, kat->ptLen,
                            &CT,    &CTLen,
                            T,      kat->tagLen); CKERR;
   
    err = compareResults( kat->tag, T, kat->tagLen , kResultFormat_Byte, "CCM Mac tag"); CKERR;
  
       OPTESTLogDebug("\nData: (%d)\n",(int) CTLen  );
      dumpHex(IF_LOG_DEBUG, CT, (int)CTLen, 0);
      OPTESTLogDebug("\nTag (%d): ", (int)sizeof(T));
        dumpHex8(IF_LOG_DEBUG,T);
        if(sizeof(T) > 8) dumpHex8(IF_LOG_DEBUG,T+8);
      OPTESTLogDebug("\n");
    
    
    /* check against know-answer */
     err = compareResults( kat->ct, CT, kat->ctLen , kResultFormat_Byte, "CCM Encrypt"); CKERR;
    
    err = CCM_Decrypt_Mem(kat->algor,
                          kat->key, kat->keylen,
                          kat->seqNum, kat->seqNumLen,
                          CT,     CTLen,
                          T,      kat->tagLen,
                          &PT,    &PTLen); CKERR;
    
    /* check against orginal plain-text  */
    err = compareResults( kat->pt, PT, kat->ptLen , kResultFormat_Byte, "CCM Decrypt"); CKERR;

    
done:
    
    if(CT)
    {
        memset(CT, CTLen, 0);
        XFREE(CT); CT = NULL;
    }

    return err;

}


SCLError TestCCM()
{
    SCLError err = kSCLError_NoErr;
    
    ccm_kat_vector ccm_kat_vector_array[] =
    {
    /*  16 + 16 byte key,  0 bytes */
        {   kCipher_Algorithm_AES128,
            
            /* key */
            { 	0x00, 0x01, 0x02, 0x03, 0x05, 0x06, 0x07, 0x08,
                0x0A, 0x0B, 0x0C, 0x0D, 0x0F, 0x10, 0x11, 0x12,
                0x14, 0x15, 0x16, 0x17, 0x19, 0x1A, 0x1B, 0x1C,
                0x1E, 0x1F, 0x20, 0x21, 0x23, 0x24, 0x25, 0x26 },
            32, /* key length */
            
            
            /* sequence num */
            { 0x00, 0x01, 0x02, 0x03, 0x05, 0x06, 0x07, 0x08 },
             8,
            
            /* paintext */
  
            {},
            0,
            
            /* Ciphertext KAT */
            
            {   0xDD, 0x41, 0x5B, 0xFD, 0xBE, 0x13, 0x0D, 0x0D, 0xC7, 0x3A, 0x27, 0xEF, 0x3D, 0x72, 0x52, 0x32,
                0x58, 0x82, 0x7C, 0x5A, 0x77, 0x7D, 0x37, 0x5D, 0x19, 0x9D, 0x63, 0xE4, 0x67, 0x08, 0x34, 0xC2
            },
            32,
            
            /* tag (MAC) */
             { 0xFF, 0x21, 0xE0, 0x0B, 0x56, 0x26, 0xEC, 0x5A, 0xD9, 0xA0, 0xCA, 0x34, 0xF7, 0x68, 0x8F, 0x93 },
             16,
        },

        /*  16 + 16 byte key, */
        {   kCipher_Algorithm_AES128,
            
            /* key */
            { 	0x00, 0x01, 0x02, 0x03, 0x05, 0x06, 0x07, 0x08,
                0x0A, 0x0B, 0x0C, 0x0D, 0x0F, 0x10, 0x11, 0x12,
                0x14, 0x15, 0x16, 0x17, 0x19, 0x1A, 0x1B, 0x1C,
                0x1E, 0x1F, 0x20, 0x21, 0x23, 0x24, 0x25, 0x26 },
            32, /* key length */
            
            
            /* sequence num */
            { 0x00, 0x01, 0x02, 0x03, 0x05, 0x06, 0x07, 0x08 },
            8,
            
            /* paintext */
            
            {  	0x00
            },
            1,
            
            /* Ciphertext KAT */
            
            {  0xFD, 0x7E, 0x64, 0xC2, 0x81, 0x2C, 0x32, 0x32, 0xF8, 0x05, 0x18, 0xD0, 0x02, 0x4D, 0x6D, 0x0D,
                0x67, 0xBD, 0x43, 0x65, 0x48, 0x42, 0x08, 0x62, 0x26, 0xA2, 0x5C, 0xDB, 0x58, 0x37, 0x0B, 0xFD,
            },
            32,
            
            /* tag (MAC) */
            { 0x6D, 0xF8, 0x57, 0x8C, 0x01, 0x86, 0xB3, 0x9C, 0x4D, 0x17, 0x30, 0x26, 0x03, 0xA2, 0x46, 0x2D  },
            16,
        },
        
        
        
        /*  16 + 16 byte key, */
        {   kCipher_Algorithm_AES128,
            
            /* key */
            { 	0x00, 0x01, 0x02, 0x03, 0x05, 0x06, 0x07, 0x08,
                0x0A, 0x0B, 0x0C, 0x0D, 0x0F, 0x10, 0x11, 0x12,
                0x14, 0x15, 0x16, 0x17, 0x19, 0x1A, 0x1B, 0x1C,
                0x1E, 0x1F, 0x20, 0x21, 0x23, 0x24, 0x25, 0x26 },
            32, /* key length */
            
            
            /* sequence num */
            { 0x00, 0x01, 0x02, 0x03, 0x05, 0x06, 0x07, 0x08 },
            8,
            
            /* paintext */
            
            {  	0x00, 0x01, 0x02, 0x03, 0x05, 0x06, 0x07, 0x08,
                0x0A, 0x0B, 0x0C, 0x0D, 0x0F, 0x10, 0x11, 0x12,
             },
            16
            ,
            
            /* Ciphertext KAT */
            
            {  0xFD, 0x60, 0x79, 0xDE, 0x9B, 0x35, 0x2A, 0x25, 0xED, 0x11, 0x0B, 0xC2, 0x12, 0x42, 0x63, 0x00,
                0x68, 0xB2, 0x4C, 0x6A, 0x47, 0x4D, 0x07, 0x6D, 0x29, 0xAD, 0x53, 0xD4, 0x57, 0x38, 0x04, 0xF2,
            },
            32,
            
            /* tag (MAC) */
            { 0xE2, 0xA0, 0xCD, 0xF2, 0x1C, 0x72, 0xE3, 0xED, 0x67, 0x86, 0xDE, 0xC5, 0x57, 0x3B, 0xB7, 0x70 },
            
            16,
        },
        
        
        
            /*  16 + 16 byte key, */
            {   kCipher_Algorithm_AES128,
                
                /* key */
                { 	0x00, 0x01, 0x02, 0x03, 0x05, 0x06, 0x07, 0x08,
                    0x0A, 0x0B, 0x0C, 0x0D, 0x0F, 0x10, 0x11, 0x12,
                    0x14, 0x15, 0x16, 0x17, 0x19, 0x1A, 0x1B, 0x1C,
                    0x1E, 0x1F, 0x20, 0x21, 0x23, 0x24, 0x25, 0x26 },
                32, /* key length */
                
                
                /* sequence num */
                { 0x00, 0x01, 0x02, 0x03, 0x05, 0x06, 0x07, 0x08 },
                8,
                
                /* paintext */
                
                {  	0x00, 0x01, 0x02, 0x03, 0x05, 0x06, 0x07, 0x08,
                    0x0A, 0x0B, 0x0C, 0x0D, 0x0F, 0x10, 0x11, 0x12,
                    0x14, 0x15, 0x16, 0x17, 0x19, 0x1A, 0x1B, 0x1C,
                    0x1E, 0x1F, 0x20, 0x21, 0x23, 0x24, 0x25, 0x26,
                    0x00, 0x01, 0x02, 0x03, 0x05, 0x06, 0x07, 0x08,
                    0x0A, 0x0B, 0x0C, 0x0D, 0x0F, 0x10, 0x11, 0x12,
                    0x14, 0x15, 0x16, 0x17, 0x19, 0x1A, 0x1B, 0x1C,
                    0x1E, 0x1F, 0x20, 0x21, 0x23, 0x24, 0x25, 0x26,
                },
                64,
                
                /* Ciphertext KAT */
                
                {  0xFD, 0x60, 0x79, 0xDE, 0x9B, 0x35, 0x2A, 0x25, 0xED, 0x11, 0x0B, 0xC2, 0x12, 0x42, 0x63, 0x00,
                    0x6C, 0xB7, 0x4A, 0x6D, 0x4E, 0x47, 0x0C, 0x61, 0x27, 0xA2, 0x63, 0xE5, 0x64, 0x0C, 0x31, 0xC4,
                    0x47, 0x00, 0x2E, 0x3E, 0x94, 0xC2, 0xA2, 0xE6, 0xDF, 0xF7, 0x72, 0x41, 0x3A, 0x6F, 0xD5, 0xDB,
                    0xCA, 0x4D, 0xA1, 0x57, 0x90, 0x82, 0x7B, 0xB0, 0x82, 0x3B, 0x24, 0xC8, 0x07, 0xC6, 0x42, 0xAF,
                    0x1F, 0x99, 0xAD, 0x67, 0x9C, 0x5C, 0xF9, 0xC2, 0x23, 0xC8, 0xAF, 0x27, 0x16, 0xF3, 0xAF, 0x8E,
                },
                80,
                
                /* tag (MAC) */
                { 0x60, 0xED, 0x9E, 0x7B, 0x28, 0xFA, 0x64, 0xA9,
                    0x7E, 0xA7, 0x2D, 0x2E, 0x73, 0x4D, 0x5E, 0x81
                },
                
                16,
            },
        
   //////// 2 FISH
        
        /*  16 + 16 byte key,  0 bytes */
        {   kCipher_Algorithm_2FISH256,
            
            /* key */
            { 	0x00, 0x01, 0x02, 0x03, 0x05, 0x06, 0x07, 0x08,
                0x0A, 0x0B, 0x0C, 0x0D, 0x0F, 0x10, 0x11, 0x12,
                0x14, 0x15, 0x16, 0x17, 0x19, 0x1A, 0x1B, 0x1C,
                0x1E, 0x1F, 0x20, 0x21, 0x23, 0x24, 0x25, 0x26,
                0x00, 0x01, 0x02, 0x03, 0x05, 0x06, 0x07, 0x08,
                0x0A, 0x0B, 0x0C, 0x0D, 0x0F, 0x10, 0x11, 0x12,
                0x14, 0x15, 0x16, 0x17, 0x19, 0x1A, 0x1B, 0x1C,
                0x1E, 0x1F, 0x20, 0x21, 0x23, 0x24, 0x25, 0x26 },
            32, /* key length */
        
        
            /* sequence num */
            { 0x00, 0x01, 0x02, 0x03, 0x05, 0x06, 0x07, 0x08 },
            8,
            
            /* paintext */
            
            {},
            0,
            
            /* Ciphertext KAT */
            
            {   0xDD, 0x3D, 0x95, 0xC7, 0x7C, 0xCD, 0xD1, 0xC6, 0xC0, 0x48, 0x17, 0xEF, 0x3E, 0xEF, 0xDB, 0x9C,
                0x6B, 0x4B, 0xED, 0xB1, 0x68, 0x79, 0x99, 0x10, 0x10, 0xA2, 0x3A, 0x0B, 0xAF, 0x16, 0xF4, 0xAC
            },
            32,
            
            /* tag (MAC) */
            { 0xE5, 0xA9, 0xDC, 0x32, 0x3E, 0xD2, 0x23, 0x6E, 0x5B, 0x41, 0xA6, 0xA2, 0xD9, 0xB8, 0xD7, 0xCF },
            16,
        },
        
#if 0
        /*  16 + 16 byte key, */
        {   kCipher_Algorithm_2FISH256,
            
            /* key */
            { 	0x00, 0x01, 0x02, 0x03, 0x05, 0x06, 0x07, 0x08,
                0x0A, 0x0B, 0x0C, 0x0D, 0x0F, 0x10, 0x11, 0x12,
                0x14, 0x15, 0x16, 0x17, 0x19, 0x1A, 0x1B, 0x1C,
                0x1E, 0x1F, 0x20, 0x21, 0x23, 0x24, 0x25, 0x26 },
            32, /* key length */
            
            
            /* sequence num */
            { 0x00, 0x01, 0x02, 0x03, 0x05, 0x06, 0x07, 0x08 },
            8,
            
            /* paintext */
            
            {  	0x00
            },
            1,
            
            /* Ciphertext KAT */
            
            {  0xFD, 0x7E, 0x64, 0xC2, 0x81, 0x2C, 0x32, 0x32, 0xF8, 0x05, 0x18, 0xD0, 0x02, 0x4D, 0x6D, 0x0D,
                0x67, 0xBD, 0x43, 0x65, 0x48, 0x42, 0x08, 0x62, 0x26, 0xA2, 0x5C, 0xDB, 0x58, 0x37, 0x0B, 0xFD,
            },
            32,
            
            /* tag (MAC) */
            { 0x6D, 0xF8, 0x57, 0x8C, 0x01, 0x86, 0xB3, 0x9C, 0x4D, 0x17, 0x30, 0x26, 0x03, 0xA2, 0x46, 0x2D  },
            16,
        },
        
        
        
        /*  16 + 16 byte key, */
        {   kCipher_Algorithm_2FISH256,
            
            /* key */
            { 	0x00, 0x01, 0x02, 0x03, 0x05, 0x06, 0x07, 0x08,
                0x0A, 0x0B, 0x0C, 0x0D, 0x0F, 0x10, 0x11, 0x12,
                0x14, 0x15, 0x16, 0x17, 0x19, 0x1A, 0x1B, 0x1C,
                0x1E, 0x1F, 0x20, 0x21, 0x23, 0x24, 0x25, 0x26 },
            32, /* key length */
            
            
            /* sequence num */
            { 0x00, 0x01, 0x02, 0x03, 0x05, 0x06, 0x07, 0x08 },
            8,
            
            /* paintext */
            
            {  	0x00, 0x01, 0x02, 0x03, 0x05, 0x06, 0x07, 0x08,
                0x0A, 0x0B, 0x0C, 0x0D, 0x0F, 0x10, 0x11, 0x12,
            },
            16
            ,
            
            /* Ciphertext KAT */
            
            {  0xFD, 0x60, 0x79, 0xDE, 0x9B, 0x35, 0x2A, 0x25, 0xED, 0x11, 0x0B, 0xC2, 0x12, 0x42, 0x63, 0x00,
                0x68, 0xB2, 0x4C, 0x6A, 0x47, 0x4D, 0x07, 0x6D, 0x29, 0xAD, 0x53, 0xD4, 0x57, 0x38, 0x04, 0xF2,
            },
            32,
            
            /* tag (MAC) */
            { 0xE2, 0xA0, 0xCD, 0xF2, 0x1C, 0x72, 0xE3, 0xED, 0x67, 0x86, 0xDE, 0xC5, 0x57, 0x3B, 0xB7, 0x70 },
            
            16,
        },
        
        
        
        /*  16 + 16 byte key, */
        {   kCipher_Algorithm_2FISH256,
            
            /* key */
            { 	0x00, 0x01, 0x02, 0x03, 0x05, 0x06, 0x07, 0x08,
                0x0A, 0x0B, 0x0C, 0x0D, 0x0F, 0x10, 0x11, 0x12,
                0x14, 0x15, 0x16, 0x17, 0x19, 0x1A, 0x1B, 0x1C,
                0x1E, 0x1F, 0x20, 0x21, 0x23, 0x24, 0x25, 0x26 },
            32, /* key length */
            
            
            /* sequence num */
            { 0x00, 0x01, 0x02, 0x03, 0x05, 0x06, 0x07, 0x08 },
            8,
            
            /* paintext */
            
            {  	0x00, 0x01, 0x02, 0x03, 0x05, 0x06, 0x07, 0x08,
                0x0A, 0x0B, 0x0C, 0x0D, 0x0F, 0x10, 0x11, 0x12,
                0x14, 0x15, 0x16, 0x17, 0x19, 0x1A, 0x1B, 0x1C,
                0x1E, 0x1F, 0x20, 0x21, 0x23, 0x24, 0x25, 0x26,
                0x00, 0x01, 0x02, 0x03, 0x05, 0x06, 0x07, 0x08,
                0x0A, 0x0B, 0x0C, 0x0D, 0x0F, 0x10, 0x11, 0x12,
                0x14, 0x15, 0x16, 0x17, 0x19, 0x1A, 0x1B, 0x1C,
                0x1E, 0x1F, 0x20, 0x21, 0x23, 0x24, 0x25, 0x26,
            },
            64,
            
            /* Ciphertext KAT */
            
            {  0xFD, 0x60, 0x79, 0xDE, 0x9B, 0x35, 0x2A, 0x25, 0xED, 0x11, 0x0B, 0xC2, 0x12, 0x42, 0x63, 0x00,
                0x6C, 0xB7, 0x4A, 0x6D, 0x4E, 0x47, 0x0C, 0x61, 0x27, 0xA2, 0x63, 0xE5, 0x64, 0x0C, 0x31, 0xC4,
                0x47, 0x00, 0x2E, 0x3E, 0x94, 0xC2, 0xA2, 0xE6, 0xDF, 0xF7, 0x72, 0x41, 0x3A, 0x6F, 0xD5, 0xDB,
                0xCA, 0x4D, 0xA1, 0x57, 0x90, 0x82, 0x7B, 0xB0, 0x82, 0x3B, 0x24, 0xC8, 0x07, 0xC6, 0x42, 0xAF,
                0x1F, 0x99, 0xAD, 0x67, 0x9C, 0x5C, 0xF9, 0xC2, 0x23, 0xC8, 0xAF, 0x27, 0x16, 0xF3, 0xAF, 0x8E,
            },
            80,
            
            /* tag (MAC) */
            { 0x60, 0xED, 0x9E, 0x7B, 0x28, 0xFA, 0x64, 0xA9,
                0x7E, 0xA7, 0x2D, 0x2E, 0x73, 0x4D, 0x5E, 0x81
            },
            
            16,
        },
        
#endif

    };
    
  
    OPTESTLogInfo("\nTesting CCM encoding");

    Cipher_Algorithm last_cipher = kCipher_Algorithm_Invalid;
    
    for (int i = 0; i < sizeof(ccm_kat_vector_array)/ sizeof(ccm_kat_vector) ; i++)
    {
        if(ccm_kat_vector_array[i].algor !=last_cipher)
        {
            OPTESTLogInfo("\n\t%-12s ", cipher_algor_table(ccm_kat_vector_array[i].algor) );
            last_cipher = ccm_kat_vector_array[i].algor;
         }
            
        
        
        err = RunCCM_KAT( &ccm_kat_vector_array[i]); CKERR;
        
    }

    OPTESTLogInfo("\n ******* FINISH THIS CODE FOR  Twofish-256 ******* \n");

    OPTESTLogInfo("\n");
    
done:
    return  err;
};
