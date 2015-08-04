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
//  MoreMenuView.h
//  ST2
//
//  Created by Vinnie Moscaritolo on 2/3/14.
//

#import <UIKit/UIKit.h>

@protocol MoreMenuViewControllerDelegate;

@class STMessage;
@class STDynamicHeightView;

@interface MoreMenuViewController : UIViewController

- (id)initWithDelegate:(id)inDelagate message:(STMessage *)inMessage;

@property (nonatomic, weak, readonly) id <MoreMenuViewControllerDelegate> delegate;

@property (nonatomic, assign) BOOL isInPopover;

@property (nonatomic, strong) IBOutlet UIView *containerView; // strong to support moving around

@property (nonatomic, weak) IBOutlet STDynamicHeightView *infoContainerView;
@property (nonatomic, weak) IBOutlet STDynamicHeightView *buttonContainerView;

@property (nonatomic, weak) IBOutlet UILabel *label0;
@property (nonatomic, weak) IBOutlet UILabel *label1;
@property (nonatomic, weak) IBOutlet UILabel *label2;
@property (nonatomic, weak) IBOutlet UILabel *label3;
@property (nonatomic, weak) IBOutlet UILabel *label4;

@property (nonatomic, weak) IBOutlet UILabel *value0;
@property (nonatomic, weak) IBOutlet UILabel *value1;
@property (nonatomic, weak) IBOutlet UILabel *value2;
@property (nonatomic, weak) IBOutlet UILabel *value3;
@property (nonatomic, weak) IBOutlet UILabel *value4;

@property (nonatomic, weak) IBOutlet UIButton *button0;
@property (nonatomic, weak) IBOutlet UIButton *button1;
@property (nonatomic, weak) IBOutlet UIButton *button2;
@property (nonatomic, weak) IBOutlet UIButton *button3;

- (CGSize)preferredPopoverContentSize;

@end


@protocol MoreMenuViewControllerDelegate <NSObject>
@required

- (void)moreMenuView:(MoreMenuViewController *)sender setPopoverContentSize:(CGSize)size;

- (void)moreMenuView:(MoreMenuViewController *)sender clearButton:(STMessage*)message;

- (void)moreMenuView:(MoreMenuViewController *)sender forwardButton:(STMessage*)message;

- (void)moreMenuView:(MoreMenuViewController *)sender sendAgainButton:(STMessage*)message;

- (void)moreMenuView:(MoreMenuViewController *)sender uploadAgainButton:(STMessage*)message;

- (void)moreMenuView:(MoreMenuViewController *)sender needsHidePopoverAnimated:(BOOL)animated;

@end