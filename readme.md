# Dribbble API Objective-C

A simple API class for Dribbble API.

You should probably be somewhat familiar with the [dribbble api here](http://developer.dribbble.com/v1/).

It supports only a subset of the dribble API, but it'd be very straight-forward to exend and add other API endpoints.

Some features:

* Authentication with OAuth
* Listing Shots with API Parameters
* Like Shot / Unlike Shot
* Follow User / Unfollow User

See Dribbble.h for other methods available.

## Dribbble Object

You need to setup a dribbble object to make requests.

You'll need these from Dribbble:

* Dribbble Application [register here](http://developer.dribbble.com/)
* Client Secret and Client ID from your Dribbble Application

Once you have those you can create a dribbble object:

````
Dribbble * d = [[Dribbble alloc] init];
d.clientSecret = @"";
d.clientId = @"";
````

### Authenticating

Authentication with OAuth is easy with a dribbble object.

First you need to register your iOS or Mac app to handle custom URL callbacks. You receive these callbacks from Dribbble when authenticating to complete the OAuth process.

Replace _myscheme_ below with the callback scheme you used when registering a Dribbble Application.

And replace _com.myapp_ with an ID of your choice, usually reverse URL format.

iOS:

````
<key>CFBundleURLTypes</key>
<array>
	<dict>
		<key>CFBundleURLName</key>
		<string>com.myapp</string>
		<key>CFBundleURLSchemes</key>
		<array>
			<string>myscheme</string>
		</array>
	</dict>
</array>
````

Mac:

````
<key>CFBundleURLTypes</key>
<array>
	<dict>
		<key>CFBundleTypeRole</key>
		<string>Editor</string>
		<key>CFBundleURLName</key>
		<string>com.my.app</string>
		<key>CFBundleURLSchemes</key>
		<array>
			<string>myscheme</string>
		</array>
	</dict>
</array>
````

### Authorization Steps

Authorization happens in four steps:

1. You start the authorization process
2. Dribbble performs a callback to your application
3. You handle the callback
4. Your completion is called, save _**accessToken**_ somewhere.

### Starting authorization:

Make sure to save the _**accessToken**_ somewhere after authorization is complete.

````
Dribbble * d = [[Dribbble alloc] init];
d.clientSecret = @"";
d.clientId = @"";
[d authorizeWithScopes:@[DribbbleScopePublic] completion:^(DribbbleResponse * response){
    if(!response.error) {
        //authorization is complete,
        //save d.accessToken
    }
}];
````

### Handling callbacks from Dribbble:

**iOS**

````
//AppDelegate.m

- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation {
    if([url.scheme containsString:@"myscheme"]) {
        [dribbbleInstance handleCustomSchemeCallback:url];
        return TRUE;
    }
    return FALSE;
}
````

**Mac**

````
//AppDelegate.m

- (void) applicationDidFinishLaunching:(NSNotification *) aNotification {
    [[NSAppleEventManager sharedAppleEventManager] setEventHandler:self andSelector:@selector(handleURLEvent:withReplyEvent:) forEventClass:kInternetEventClass andEventID:kAEGetURL];
}

- (void) handleURLEvent:(NSAppleEventDescriptor*) event withReplyEvent:(NSAppleEventDescriptor*) replyEvent {
	NSString * url = [[event paramDescriptorForKeyword:keyDirectObject] stringValue];
	[dribbbleInstance handleCustomSchemeCallback:url];
}

````

### Authorization Sample Code iOS

````
//AppDelegate.m

#import "Dribbble.h"

@interface AppDelegate ()
@property Dribbble * dribbbleAuth;
@end

@implementation AppDelegate

- (BOOL) application:(UIApplication *) application didFinishLaunchingWithOptions:(NSDictionary *) launchOptions {
	self.dribbbleAuth = [[Dribbble alloc] init];
	self.dribbbleAuth.clientId = @"";
	self.dribbbleAuth.clientSecret = @"";
}

- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation {
    if([url.scheme containsString:@"myscheme"]) {
        [self.dribbbleAuth handleCustomSchemeCallback:url];
        return TRUE;
    }
    return FALSE;
}

- (void) authorizeDribbble {
    [self.dribbbleAuth authorizeWithScopes:@[DribbbleScopePublic] completion:^(DribbbleResponse * response){
        [[NSuserDefaults standardUserDefaults] setObject:self.dribbbleAuth.accessToken forKey:@"DribbbleAccessKey"];
    }];
}

@end
````

### Auth Scopes

The _authorizeWithScopes:completion:_ method accepts an array of any of these scopes:

````
//scopes
extern NSString * const DribbbleScopePublic;
extern NSString * const DribbbleScopeWrite;
extern NSString * const DribbbleScopeComment;
extern NSString * const DribbbleScopeUpload;
````

## Using a test accessToken

When you register your dribbble application, you'll get an access token you can use to test without having to authenticate:

````
Dribbble * d = [[Dribbble alloc] init];
d.clientId = @"";
d.clientSecret = @"";
d.accessToken = @"MY_TEST_ACCESS_TOKEN"; //from your dribbble application.
````

_**Do not ship your app with this access token in it.**_ This is for testing purposes only.

## DribbbleResponse Object

The DribbbleResponse object is passed to all of your callbacks. It's a very simple object:

````
//response object for all asynchronous dribbble methods.
@interface DribbbleResponse : NSObject
@property id data;
@property NSError * error;
@end
````

## Listing Shots Example

````
Dribbble * d = [[Dribbble alloc] init];
d.clientId = @"";
d.clientSecret = @"";
d.accessToken = @"";
[d listShotsWithParameters:@{} completion:^(DribbbleResponse * response){
    if(response.error) {
        NSLog(@"ERROR: %@",response.error);
        return;
    }
    NSLog(@"%@",response.data);
}];
````

## API Call Parameters

Dribbble accepts parameters to API calls. Check the [Dribbble API](http://developer.dribbble.com/v1/) for more info.

For example, **list shots** [api](http://developer.dribbble.com/v1/shots/#list-shots). You can pass parameters easily like this:

````
Dribbble * d = [[Dribbble alloc] init];
d.clientId = @"";
d.clientSecret = @"";
d.accessToken = @"";
[d listShotsWithParameters:@{@"list":@"debuts",@"sort":@"recent"} completion:^(DribbbleResponse * response){
    if(response.error) {
        NSLog(@"ERROR: %@",response.error);
        return;
    }
    NSLog(@"%@",response.data);
}];
````

# License

The MIT License (MIT)
Copyright (c) 2016 Aaron Smith

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.