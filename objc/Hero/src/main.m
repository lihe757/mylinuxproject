#import <Foundation/Foundation.h>
#import "Hero.h"
int main (int argc,const char* argv[])
{
	NSAutoreleasePool *pool=[[NSAutoreleasePool alloc] init];

	Hero *hero;
	hero = [Hero new];
	NSLog (@"%@",hero);


	NSLog (@"hello world");
	[pool release];
	return 0;
}
