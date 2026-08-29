#import <Metal/Metal.h>
#import <Foundation/Foundation.h>

@interface RSXMetalEngine : NSObject
@property (nonatomic, strong) id<MTLDevice> device;
@property (nonatomic, strong) id<MTLCommandQueue> commandQueue;
@end

@implementation RSXMetalEngine

- (instancetype)init {
    self = [super init];
    if (self) {
        // چالاککردنی ڕاستەوخۆی پرۆسێسەری گرافیکی A15 Bionic
        _device = MTLCreateSystemDefaultDevice();
        _commandQueue = [_device newCommandQueue];
    }
    return self;
}

@end
