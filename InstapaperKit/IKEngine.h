//
//  IKEngine.h
//  Instapaper
//
//  Created by Matthias Plappert on 3/12/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CommonCrypto/CommonHMAC.h>


@class IKEngine, IKURLConnection, IKUser, IKFolder, IKBookmark;


@protocol IKEngineDelegate <NSObject>

@optional
- (void)engine:(IKEngine *)engine willStartConnection:(IKURLConnection *)connection;
- (void)engine:(IKEngine *)engine didFinishConnection:(IKURLConnection *)connection;
- (void)engine:(IKEngine *)engine didFailConnection:(IKURLConnection *)connection error:(NSError *)error;
- (void)engine:(IKEngine *)engine didCancelConnection:(IKURLConnection *)connection;

- (void)engine:(IKEngine *)engine connection:(IKURLConnection *)connection didReceiveAuthToken:(NSString *)token andTokenSecret:(NSString *)secret;
- (void)engine:(IKEngine *)engine connection:(IKURLConnection *)connection didVerifyCredentialsForUser:(IKUser *)user;

- (void)engine:(IKEngine *)engine connection:(IKURLConnection *)connection didReceiveBookmarks:(NSArray *)bookmarks ofUser:(IKUser *)user;
- (void)engine:(IKEngine *)engine connection:(IKURLConnection *)connection didUpdateReadProgressOfBookmark:(IKBookmark *)bookmark;
- (void)engine:(IKEngine *)engine connection:(IKURLConnection *)connection didAddBookmark:(IKBookmark *)bookmark;
- (void)engine:(IKEngine *)engine connection:(IKURLConnection *)connection didDeleteBookmarkWithBookmarkID:(NSInteger)bookmarkID;
- (void)engine:(IKEngine *)engine connection:(IKURLConnection *)connection didStarBookmark:(IKBookmark *)bookmark;
- (void)engine:(IKEngine *)engine connection:(IKURLConnection *)connection didUnstarBookmark:(IKBookmark *)bookmark;
- (void)engine:(IKEngine *)engine connection:(IKURLConnection *)connection didArchiveBookmark:(IKBookmark *)bookmark;
- (void)engine:(IKEngine *)engine connection:(IKURLConnection *)connection didUnarchiveBookmark:(IKBookmark *)bookmark;
- (void)engine:(IKEngine *)engine connection:(IKURLConnection *)connection didMoveBookmark:(IKBookmark *)bookmark toFolderWithFolderID:(NSInteger)folderID;
- (void)engine:(IKEngine *)engine connection:(IKURLConnection *)connection didReceiveText:(NSString *)text ofBookmarkWithBookmarkID:(NSInteger)bookmarkID;

- (void)engine:(IKEngine *)engine connection:(IKURLConnection *)connection didReceiveFolders:(NSArray *)folders;
- (void)engine:(IKEngine *)engine connection:(IKURLConnection *)connection didAddFolder:(IKFolder *)folder;
- (void)engine:(IKEngine *)engine connection:(IKURLConnection *)connection didDeleteFolderWithFolderID:(NSInteger)folderID;
- (void)engine:(IKEngine *)engine connection:(IKURLConnection *)connection didOrderFolders:(NSArray *)folders;

@end


@interface IKEngine : NSObject {
    id <IKEngineDelegate> _delegate;
    NSString *_OAuthToken;
    NSString *_OAuthTokenSecret;
    
    NSMutableDictionary *_connections;
}

@property (nonatomic, assign) id <IKEngineDelegate> delegate;
@property (nonatomic, copy) NSString *OAuthToken;
@property (nonatomic, copy) NSString *OAuthTokenSecret;

+ (void)setOAuthConsumerKey:(NSString *)key andConsumerSecret:(NSString *)secret;

- (id)initWithDelegate:(id <IKEngineDelegate>)delegate;

- (NSString *)authTokenForUsername:(NSString *)username password:(NSString *)password userInfo:(id)userInfo;
- (NSString *)verifyCredentialsWithUserInfo:(id)userInfo;

- (NSString *)bookmarksWithUserInfo:(id)userInfo;
- (NSString *)bookmarksInFolder:(IKFolder *)folder limit:(NSUInteger)limit existingBookmarks:(NSArray *)bookmarks userInfo:(id)userInfo;
- (NSString *)updateReadProgressOfBookmark:(IKBookmark *)bookmark toProgress:(CGFloat)progress userInfo:(id)userInfo;
- (NSString *)addBookmarkWithURL:(NSURL *)URL userInfo:(id)userInfo;
- (NSString *)addBookmarkWithURL:(NSURL *)URL title:(NSString *)title description:(NSString *)description folder:(IKFolder *)folder resolveFinalURL:(BOOL)resolveFinalURL userInfo:(id)userInfo;
- (NSString *)deleteBookmark:(IKBookmark *)bookmark userInfo:(id)userInfo;
- (NSString *)starBookmark:(IKBookmark *)bookmark userInfo:(id)userInfo;
- (NSString *)unstarBookmark:(IKBookmark *)bookmark userInfo:(id)userInfo;
- (NSString *)archiveBookmark:(IKBookmark *)bookmark userInfo:(id)userInfo;
- (NSString *)unarchiveBookmark:(IKBookmark *)bookmark userInfo:(id)userInfo;
- (NSString *)moveBookmark:(IKBookmark *)bookmark toFolder:(IKFolder *)folder userInfo:(id)userInfo;
- (NSString *)textOfBookmark:(IKBookmark *)bookmark userInfo:(id)userInfo;

- (NSString *)foldersWithUserInfo:(id)userInfo;
- (NSString *)addFolderWithTitle:(NSString *)title userInfo:(id)userInfo;
- (NSString *)deleteFolder:(IKFolder *)folder userInfo:(id)userInfo;
- (NSString *)orderFolders:(NSArray *)folders userInfo:(id)userInfo;

- (IKURLConnection *)connectionForIdentifier:(NSString *)identifier;
- (NSString *)identifierForConnection:(IKURLConnection *)connection;
- (NSUInteger)numberOfConnections;

- (void)cancelConnection:(IKURLConnection *)connection;
- (void)cancelAllConnections;

@end