
#import "ViewController.h"
#import "Dribbble.h"
#import "AppDelegate.h"

@interface ViewController ()
@property Dribbble * dribbble;
@end

@implementation ViewController

- (void) viewDidLoad {
	[super viewDidLoad];
}

- (IBAction) onAuth:(id) sender {
	AppDelegate * apd = (AppDelegate *)[UIApplication sharedApplication].delegate;
	[apd.dribbbleAuth authorizeWithScopes:@[DribbbleScopePublic] completion:^(DribbbleResponse *response) {
		if(response.error) {
			NSLog(@"%@",response.error);
			return;
		}
		NSLog(@"token: %@",apd.dribbbleAuth.accessToken);
		NSLog(@"Success!");
	}];
}

- (IBAction) listLoggedInUser:(id) sender {
	AppDelegate * apd = (AppDelegate *)[UIApplication sharedApplication].delegate;
	[apd.dribbbleAuth getAuthedUser:^(DribbbleResponse *response) {
		NSLog(@"%@",response.data);
	}];
}

@end
