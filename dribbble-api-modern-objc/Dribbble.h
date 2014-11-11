
#import <Cocoa/Cocoa.h>

//forwards
@class Dribbble;
@class DribbbleResponse;
@class DribbbleShotsCollection;

//error domain
NSString * const DribbbleErrorDomain;

//scopes
NSString * const DribbbleScopePublic;
NSString * const DribbbleScopeWrite;
NSString * const DribbbleScopeComment;
NSString * const DribbbleScopeUpload;

//completions
typedef void (^DribbbleCompletionBlock)(DribbbleResponse * response);
typedef void (^DribbbleCollectionCompletionBlock)(Dribbble * dribbble, DribbbleResponse * response);

//main Dribbble class
@interface Dribbble : NSObject <NSURLSessionDelegate>

//default configured session.
@property NSURLSession * defaultSession;

//auth properties
@property NSString * clientId;
@property NSString * clientSecret;
@property NSString * accessToken;

//authorize
- (void) authorizeWithScopes:(NSArray *) scopes completion:(DribbbleCompletionBlock) completion;
- (void) handleCustomSchemeCallback:(NSString *) url;

//shots
- (void) listShotsWithParameters:(NSDictionary *) params completion:(DribbbleCompletionBlock) completion;
- (void) likeShot:(NSString *) shotId withCompletion:(DribbbleCompletionBlock) completion;
- (void) unlikeShot:(NSString *) shotId withCompletion:(DribbbleCompletionBlock) completion;

//user
- (void) getAuthedUser:(DribbbleCompletionBlock) completion;
- (void) listShotsLikedParameters:(NSDictionary *) params withCompletion:(DribbbleCompletionBlock) completion;
- (void) listShotsOfPlayersFollowedParameters:(NSDictionary *) params withCompletion:(DribbbleCompletionBlock) completion;
- (void) listShotsOfUser:(NSString *) user parameters:(NSDictionary *) params withCompletion:(DribbbleCompletionBlock) completion;
- (void) followUser:(NSString *) user withCompletion:(DribbbleCompletionBlock) completion;
- (void) unfollowUser:(NSString *) user withCompletion:(DribbbleCompletionBlock) completion;

@end

//response object for all asynchronous dribbble methods.
@interface DribbbleResponse : NSObject
@property id data;
@property NSError * error;
@end

//custom collection object to gather shots however needed.
//subclass this and use a Dribbble instance to do whatever is needed
//for the overall collection of shots.
@interface DribbbleShotsCollection : NSObject
@property Dribbble * dribbble;
@property NSMutableArray * shots;
@property NSDictionary * parameters;
@property NSUInteger page;
- (id) initWithDribbble:(Dribbble *) dribbble parameters:(NSDictionary *) parameters;
- (void) loadShotsWithCompletion:(DribbbleCollectionCompletionBlock) completion;
- (void) addShots:(NSArray *) shots;
- (void) incrementPage;
- (void) reset;
- (NSDictionary *) APICallParameters;
@end
