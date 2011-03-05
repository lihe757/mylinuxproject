#import <Foundation/Foundation.h>

#import "Car.h"
#import "Slant6.h"
#import "AllWeatherRadial.h"

int main (int argc,const char* argv[])
{
	NSAutoreleasePool *pool=[[NSAutoreleasePool alloc] init];

	Car  *car;
	Engine *engine;
	
	engine = [Slant6 new];
	car = [Car new];
	[car setEngine:engine];
	int i=0;
	for(i=0;i<4;i++){
		Tire *tire=[AllWeatherRadial new];
		[car setTire:tire
		     atIndex:i];
	}

	[car print];

	NSLog (@"hello world");
	[pool drain];
	return 0;
}
