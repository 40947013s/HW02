#include "mysplit.h"
#include "mymatch.h"

int main()
{
	char *buf="appieke appieitiuke appieitiueke appeke";
	char **return_list; char *s = "app*??*eke";
    
    int n = mymatch(&return_list, s, buf);
    for(int i = 0; i < n; i++)
        printf("%s\n", return_list[i]);
    
    return 0;
}
