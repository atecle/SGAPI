//
//  Created by matt on 18/01/14.
//

#import <Foundation/Foundation.h>

@class SGQuery;

/**
* `SGItemSet` is the abstract base class for item sets, providing the core
* request handling and pagination. Create instances of `SGEventSet`,
* `SGPerformerSet`, and `SGVenueSet` to fetch paginated results.
*/

@interface SGItemSet : NSObject

/** @name Modifying the API query */

/**
An <SGQuery> instance for defining the parameters and filters of the API query.

    SGEventSet *events = SGEventSet.eventsQuery;
    events.query.search = @"new york mets";
    events.query.perPage = 30;
*/
@property (nonatomic, strong) SGQuery *query;

/** @name State change callbacks */

/**
A block assigned to `onPageLoaded` will be called after each result page
request has completed.

    events.onPageLoaded = ^(NSOrderedSet *results) {
        for (SGEvent *event in results) {
            NSLog(@"event: %@", event.title);
        }
    };
*/
@property (nonatomic, copy) void (^onPageLoaded)(NSOrderedSet* newItems);

/**
 A block assigned to `onPageLoadFailed` will be called after a page request
 failed to load.

 events.onPageLoadFailed = ^(NSError *error) {
 NSLog(@"error: %@", error);
 };
 */
@property (nonatomic, copy) void (^onPageLoadFailed)(NSError* error);

/** @name Fetching results */

/**
* Fetch the next page of results. If the set is already <fetching>
* `fetchNextPage` will do nothing. If all results have already been fetched
* (<lastPageAlreadyFetched>) `fetchNextPage` will do nothing.
*/
- (void)fetchNextPage;

/**
* Fetch a specific page of results. Usually you will want to call
* `fetchNextPage` instead, but in some cases you may want to refetch a specific
* page.
*
* Note that item sets contain only unique items, so a page refetch will only
* add any new results to the set, without duplicates. If the <query> hasn't
* been modified then most likely no new items will be added.
*/
- (void)fetchPage:(int)page;

/**
* Cancel an in progress results fetch.
*/
- (void)cancelFetch;

/**
* Returns YES if the last page of results has already been fetched.
*/
- (BOOL)lastPageAlreadyFetched;

/**
* Returns YES if a results fetch is in progress.
*/
- (BOOL)fetching;

/** @name Content inspection */

/**
* Returns the page number of the last fetched page.
*/
- (int)lastFetchedPage;

/**
* Returns the total number of pages available for the <query>. Note that if
* no pages have been fetched yet, `totalPages` will return 0.
*/
- (int)totalPages;

/**
* Returns an `NSArray` of the items in the set.
*/
- (NSArray *)array;

/**
* Returns an `NSOrderedSet` of the items in the set.
*/
- (NSOrderedSet *)orderedSet;
- (NSOrderedSet *)orderdSet __deprecated;

/**
* Returns the first item in the set.
*/
- (id)firstObject;

/**
* Returns the last item in the set.
*/
- (id)lastObject;

/**
* Returns a count of the items in the set so far. Note that this is not the
* total available for the query, but instead the number of items fetched so far.
*/
- (NSUInteger)count;

/** @name Caching results */

/**
* Caches the current results set to disk.
*/
- (void)cacheItemsWithCacheKey:(NSString *)cacheKey;

/**
* Returns YES if cached results are available for the given cache key.
*/
- (BOOL)hasCachedItemsForCacheKey:(NSString *)cacheKey;

/**
* Restores the results set to a previously cached state.
*/
- (void)loadCachedItemsForCacheKey:(NSString *)cacheKey;

/**
* Returns YES if the current items were loaded from cache.
*/
- (BOOL)itemsAreFromCache;

/** @name Resetting internal state */

/**
* Reset the internal state of the set. Note that this doesn't reset the <query>
* parameters. After being reset, a subsequent <fetchNextPage> will fetch the
* first page of results.
*/
- (void)reset;

/** @name Status bar indicator */

/**
* Whether to show a status bar activity indicator while fetching results.
* Default is YES.
*/
@property (nonatomic, assign) BOOL allowStatusBarSpinner;

// ignore plz
@property (nonatomic, copy) NSString *resultArrayKey;

- (id)objectAtIndexedSubscript:(NSUInteger)index;

- (NSDictionary *)lastResponseDict;

@end
