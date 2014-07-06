//
//  Created by matt on 27/05/14.
//

#import <CoreLocation/CoreLocation.h>

#define SGAPI_ENDPOINT @"http://api.seatgeek.com/2"

#ifdef DEBUG
#define SGPlatformLog(s, ...) \
    if (SGQuery.consoleLogging) { \
        NSLog(@"%@", [NSString stringWithFormat:(s), ##__VA_ARGS__]); \
    }
#else
#define SGPlatformLog(...)
#endif

#ifndef __weakSelf
#define __weakSelf __weak typeof(self)
#endif

/**
* `SGQuery` builds URLs for querying the SeatGeek Platform. See the
* [SeatGeek Platform docs](http://platform.seatgeek.com/) for available endpoints
* and parameters.
*/

@interface SGQuery : NSObject

/** @name Setup */

/**
Some SeatGeek Platform endpoints require an
[API key](https://seatgeek.com/account/develop). Set `clientId` to your API key
in your AppDelegate's `application:didFinishLaunchingWithOptions:`

    SGQuery.clientId = @"my_API_key";
*/
+ (void)setClientId:(NSString *)clientId;

/**
An optional `aid` value to append to all queries. Set this value in your
AppDelegate's `application:didFinishLaunchingWithOptions:`

    SGQuery.aid = @"my_aid";
*/
+ (void)setAid:(NSString *)aid;

/**
An optional `rid` value to append to all queries. Set this value in your
AppDelegate's `application:didFinishLaunchingWithOptions:`

     SGQuery.rid = @"my_rid";
*/
+ (void)setRid:(NSString *)rid;

/**
* Output debug information to console. Default is NO.
*/
+ (void)setConsoleLogging:(BOOL)logging;
+ (BOOL)consoleLogging;

#pragma mark - Events

/** @name Event queries */

/**
* Returns a new `SGQuery` instance for the
* [/events](http://platform.seatgeek.com/#events) endpoint.
*/
+ (SGQuery *)eventsQuery;

/**
* Returns a new `SGQuery` instance for the `/recommendations` endpoint.
* @warning The [/recommendations](http://platform.seatgeek.com/#recommendations)
* endpoint requires an API key. See <setClientId:> for details.
*/
+ (SGQuery *)recommendationsQuery;

/**
* Returns a new `SGQuery` instance for fetching a single event by id.
*/
+ (SGQuery *)eventQueryForId:(NSNumber *)eventId;

#pragma mark - Performers

/** @name Performer queries */

/**
* Returns a new `SGQuery` instance for the
* [/performers](http://platform.seatgeek.com/#performers) endpoint.
*/
+ (SGQuery *)performersQuery;

/**
* Returns a new `SGQuery` instance for fetching a single performer by id.
*/
+ (SGQuery *)performerQueryForId:(NSNumber *)performerId;

/**
* Returns a new `SGQuery` instance for fetching a single performer by slug.
*/
+ (SGQuery *)performerQueryForSlug:(NSString *)slug;

#pragma mark - Venues

/** @name Venue queries */

/**
* Returns a new `SGQuery` instance for the
* [/venues](http://platform.seatgeek.com/#venues) endpoint.
*/
+ (SGQuery *)venuesQuery;

/**
* Returns a new `SGQuery` instance for fetching a single venue by id.
*/
+ (SGQuery *)venueQueryForId:(NSNumber *)venueId;

#pragma mark - The Payoff

/** @name The payoff */

/**
Returns an `NSURL` for the constructed API query.

    SGQuery *query = SGQuery.eventsQuery;
    query.search = @"imagine dragons";

    NSLog(@"%@", query.URL);
    // http://api.seatgeek.com/2/events?q=imagine+dragons
*/
- (NSURL *)URL;

#pragma mark - Pagination

/** @name Pagination */

/**
* The results page to fetch. Page numbers start from 1.
*/
@property (nonatomic, assign) NSUInteger page;

/**
* The number of results to return per page. Default is 10.
*/
@property (nonatomic, assign) NSUInteger perPage;

#pragma mark - Keyword searches

/** @name Keyword searches */

/**
Apply a keyword search to the query.

    SGQuery *query = SGQuery.eventsQuery;
    query.search = @"imagine dragons";
*/
@property (nonatomic, copy) NSString *search;

#pragma mark - Location Parameters (for 'events' and 'venues')

/** @name Geolocation filters */

/**
* Filter results by a location coordinate.
*/
@property (nonatomic, assign) CLLocationCoordinate2D location;

/**
* Specify a range for location based filters. Accepts miles ("mi") and kilometres
* ("km"). Default is "30mi".
*/
@property (nonatomic, copy) NSString *range;

#pragma mark - Freeform Parameters and Filters

/** @name Other parameters and filters */

/**
Set a query parameter. Setting a parameter will override its previous value.
See the [API docs](http://platform.seatgeek.com/) for available parameters.

    [query setParameter:@"format" value:@"xml"];
    [query setParameter:@"sort" value:@"announce_date.desc"];
*/
- (void)setParameter:(NSString *)param value:(id)value;

/**
Add a results filter. Filters are stacked, and the same filters can be applied multiple times with different values. See the
[API docs](http://platform.seatgeek.com/) for available filters.

    [query addFilter:@"performers.slug" value:@"new-york-mets"];
    [query addFilter:@"performers.slug" value:@"new-york-yankees"];
*/
- (void)addFilter:(NSString *)filter value:(id)value;

// ignore plz
+ (SGQuery *)queryWithString:(NSString *)string;
+ (NSMutableDictionary *)globalParameters;

@end