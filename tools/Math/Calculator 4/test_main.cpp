#include "public.h"

void main()
{	
	logo();
	double ans;
	while (true)
	{
		ans=.0;
		printf("Calculate> ");
		ans=calculate();
		if(!event_box.incident)
			printf("Answer> %.8lf\n\n",ans);
		else
			massage(event_box.incident);
	}
}