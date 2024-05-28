#include "terminal.h"


iv iman_fn(char* arr,int start,iv vals)
{
    start+=5;
    int length = strlen(arr);
    char* page_name=malloc(MaxLimit);
    int c=0;
    for(int i=start;i<length;i++)
    {
        if(arr[i]=='\n'||arr[i]=='\t')
            break;
        page_name[c++]=arr[i];
    }
    page_name[c++]='\0';


    const char *hostname = "man.he.net";
    const char *service = "http"; 
    // char command[] = "sleep";     
    struct addrinfo add_rev;
    struct addrinfo *result, *xyz;
    int status, sockfd;

    memset(&add_rev, 0, sizeof(struct addrinfo));
    add_rev.ai_family = AF_UNSPEC;     
    add_rev.ai_socktype = SOCK_STREAM;
    status = getaddrinfo(hostname, service, &add_rev, &result);
    if (status != 0)
    {
        perror("");
        return vals;
    }

    for (xyz = result; xyz != NULL; xyz = xyz->ai_next)
    {
        sockfd = socket(xyz->ai_family, xyz->ai_socktype, xyz->ai_protocol);
        if (sockfd == -1)
        {
            perror("");
            continue;
        }

        if (connect(sockfd, xyz->ai_addr, xyz->ai_addrlen) != -1)
        {
            break;
        }

        close(sockfd); 
    }

    if (xyz == NULL)
    {
        perror("");
        freeaddrinfo(result);
        return vals;
    }

    freeaddrinfo(result);

    char url[MaxLimit];
    snprintf(url, sizeof(url), "/man1/%s.1", page_name);

    char http_request[MaxLimit];
    snprintf(http_request, sizeof(http_request), "GET /?topic=%s&section=all HTTP/1.1\r\nHost: man.he.net\r\n\r\n", page_name);
    if (write(sockfd, http_request, strlen(http_request)) == -1)
    {
        perror("");
        close(sockfd);
        return vals;
    }

    char buffer[MaxLimit];
    ssize_t n;
    int a = 0;
    while ((n = read(sockfd, buffer, sizeof(buffer))) > 0)
    {
        char *ans = malloc(MaxLimit);
        int c = 0, i = 0;
        while (i < n)
        {
            if (buffer[i] == '<')
            {
                while (buffer[i++] != '>')
                    ;
            }
            else if (a == 0)
            {
                while ((buffer[i] == 'N' && buffer[i + 1] == 'A' && buffer[i + 2] == 'M' && buffer[i + 3] == 'E'&& buffer[i + 4] == '\n')!=1)
                {
                    i++;
                }
                a++;
            }
            else
            {
                ans[c++] = buffer[i++];
                a++;
            }
        }
        ans[c++] = '\0';
        int a = strlen(ans);
        fwrite(ans, a, 1, stdout);
        a++;
    }

    if (n == -1)
    {
        perror("read");
    }


    close(sockfd);
    return vals;

}