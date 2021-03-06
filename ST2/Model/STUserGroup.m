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
//  STUserGroup.m
//  ST2
//
//  Created by Vinnie Moscaritolo on 3/3/14.
//

#import "STUserGroup.h"

@implementation STUserGroup

@synthesize uuid = uuid;
@synthesize groupName = groupName;
@synthesize userNames = userNames;

- (id)initWithUUID:(NSString *)inUUID
         groupName:(NSString *)inGroupName
{
    if ((self = [super init]))
	{
		uuid = [inUUID copy];
        groupName  = [inGroupName copy];
    }
	return self;
}


#pragma mark NSCoding

- (id)initWithCoder:(NSCoder *)decoder
{
	if ((self = [super init]))
	{
		int32_t version = [decoder decodeInt32ForKey:@"version"];
		
		if (version == 0) // OLD version
		{
        	uuid = [decoder decodeObjectForKey:@"uuid"];
			groupName = [decoder decodeObjectForKey:@"groupName"];
 			userNames = [decoder decodeObjectForKey:@"userNames"];
 			
	 			
		}
		else // NEW version(s)
		{
	      	uuid = [decoder decodeObjectForKey:@"uuid"];
			groupName = [decoder decodeObjectForKey:@"groupName"];
 			userNames = [decoder decodeObjectForKey:@"userNames"];
        }
	}
	return self;
}

- (void)encodeWithCoder:(NSCoder *)coder
{
	[coder encodeInt32:0 forKey:@"version"];
	
    [coder encodeObject:uuid forKey:@"uuid"];
    [coder encodeObject:groupName forKey:@"groupName"];
    [coder encodeObject:userNames forKey:@"userNames"];
    
}

#pragma mark NSCopying

- (id)copyWithZone:(NSZone *)zone
{
	STUserGroup *copy = [super copyWithZone:zone];
    
    copy->uuid = uuid;
    copy->groupName = groupName;
    copy->userNames = userNames;
   
	return copy;
}

@end
