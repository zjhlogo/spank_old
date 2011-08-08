/*!
 * \file OpenGLAppDelegate.h
 * \date 7-20-2011 10:58:15
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#import <UIKit/UIKit.h>
#import "OpenGLView.h"

@interface OpenGLAppDelegate : NSObject <UIApplicationDelegate> {
	
}

@property (nonatomic, retain) IBOutlet OpenGLView* glView;
@property (nonatomic, retain) IBOutlet UIWindow* glWindow;

@end
