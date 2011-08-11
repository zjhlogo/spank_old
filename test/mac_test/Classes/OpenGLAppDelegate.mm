/*!
 * \file OpenGLAppDelegate.cpp
 * \date 7-20-2011 10:58:15
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#import "OpenGLAppDelegate.h"
#include <util/ConfigUtil.h>
#include <IRenderDevice.h>

@implementation OpenGLAppDelegate

@synthesize glView;
@synthesize glWindow;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
	[[UIApplication sharedApplication] setStatusBarOrientation:UIInterfaceOrientationLandscapeRight];
	ConfigUtil::GetInstance().AddInt("SCREEN_ORIENTATION", IRenderDevice::SR_N90);
	
	// spank initialize
	NSString* rootPath = [[NSBundle mainBundle] resourcePath];
	const char* pszRootPath = [rootPath cStringUsingEncoding: [NSString defaultCStringEncoding]];
	ConfigUtil::GetInstance().AddString("RESOURCE_DIR", pszRootPath);

    // Override point for customization after application launch.
    CGRect screenBounds = [[UIScreen mainScreen] bounds];
	ConfigUtil::GetInstance().AddInt("SURFACE_WIDTH", screenBounds.size.width);
	ConfigUtil::GetInstance().AddInt("SURFACE_HEIGHT", screenBounds.size.height);
	
    self.glView = [[[OpenGLView alloc] initWithFrame:screenBounds] autorelease];
	
    [self.glWindow addSubview: self.glView];
    [self.glWindow makeKeyAndVisible];
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application
{
    /*
     Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
     Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
     */
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    /*
     Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
     If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
     */
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    /*
     Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
     */
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    /*
     Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
     */
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    /*
     Called when the application is about to terminate.
     Save data if appropriate.
     See also applicationDidEnterBackground:.
     */
}

- (void)dealloc
{
    [glView release];
    [glWindow release];
    [super dealloc];
}

@end
