
#import "AppDelegate.h"
#import "ViewController.h"

@interface AppDelegate ()
@end

@implementation AppDelegate

- (BOOL) application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *) launchOptions {
	
	self.dribbbleAuth = [[Dribbble alloc] init];
	self.dribbbleAuth.clientId = @"2447cd8109407ee2e4f504f2ec303156611c212fb1d09067d5f56ef952dbb25e";
	self.dribbbleAuth.clientSecret = @"fcaeecb6ed606c797b3a6890653593eaf04bb42644360e376355d8e0056bcf83";
	
	self.window = [[UIWindow alloc] initWithFrame:[UIScreen mainScreen].bounds];
	self.window.rootViewController = [[ViewController alloc] init];
	[self.window makeKeyAndVisible];
	
	return YES;
}

- (BOOL) application:(UIApplication *)app openURL:(NSURL *)url options:(NSDictionary<NSString *,id> *)options {
	if([url.scheme isEqualToString:@"dribbbleauth"]) {
		[self.dribbbleAuth handleCustomSchemeCallback:url.absoluteString];
		return TRUE;
	}
	return FALSE;
}

@end
