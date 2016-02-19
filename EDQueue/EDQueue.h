//
//  EDQueue.h
//  queue
//
//  Created by Andrew Sliwinski on 6/29/12.
//  Copyright (c) 2012 Andrew Sliwinski. All rights reserved.
//

@import Foundation;

#import "EDQueueJob.h"
#import "EDQueuePersistentStorageProtocol.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, EDQueueResult) {
    EDQueueResultSuccess = 0,
    EDQueueResultFail,
    EDQueueResultCritical
};

typedef void (^EDQueueCompletionBlock)(EDQueueResult result);

extern NSString *const EDQueueDidStart;
extern NSString *const EDQueueDidStop;
extern NSString *const EDQueueJobDidSucceed;
extern NSString *const EDQueueJobDidFail;
extern NSString *const EDQueueDidDrain;

extern NSString *const EDQueueNameKey;
extern NSString *const EDQueueDataKey;

@class EDQueue;

@protocol EDQueueDelegate <NSObject>
- (void)queue:(EDQueue *)queue processJob:(EDQueueJob *)job completion:(EDQueueCompletionBlock)block;
@end

@interface EDQueue : NSObject

@property (nonatomic, weak) id<EDQueueDelegate> delegate;
@property (nonatomic, strong, readonly) id<EDQueuePersistentStorage> storage;

/**
 * Returns true if Queue is running (e.g. not stopped).
 */
@property (nonatomic, readonly) BOOL isRunning;
/**
 * Returns true if Queue is performing Job right now
 */
@property (nonatomic, readonly) BOOL isActive;
/**
 * Retry limit for failing tasks (will be elimitated and moved to Job later)
 */
@property (nonatomic) NSUInteger retryLimit;

- (instancetype)initWithPersistentStore:(id<EDQueuePersistentStorage>)persistentStore;

- (void)enqueueJob:(EDQueueJob *)job;
- (void)start;
- (void)stop;
- (void)empty;

- (BOOL)jobExistsForTask:(NSString *)task;
- (BOOL)jobIsActiveForTask:(NSString *)task;
- (nullable EDQueueJob *)nextJobForTask:(NSString *)task;

@end


NS_ASSUME_NONNULL_END