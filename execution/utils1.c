#include "execution.h"

char *get_path()
{
    char *path = getenv("PATH");
    if (path != NULL) 
        return path;
    else
        return NULL;
}
         
char *ft_strjoin3(char *s1, char *s2, char *s3)
{
    char *temp = ft_strjoin(s1, s2);
    if (!temp)
        return NULL;
    
    char *result = ft_strjoin(temp, s3);
    free(temp);
    return result;
}

void clean_string_array(char **arr)
{
    int i = 0; 
    while (arr[i])
        free(arr[i++]);
    free(arr);
}
