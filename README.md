# OnlineJudges
My solutions to challenges from various online judges, mainly HackerRank.
## Sample
**HackerRank: Super Reduced String**  
Given a string, repeatedly remove pairs of adjacent matching elements and print the reduced result.   
Examples:  
`abc` :arrow_right: `abc`  
`abbc` :arrow_right: `ac`  
`abba` :arrow_right: `[empty string]`  
<details>
  <summary>click for part of my solution</summary>
  
```C++

int super_reduce(char *a, int n)
{
    int cnt=0;

    for (int i=0; i!=n; ++i)
    {
        char ch=a[i];

        if (cnt==0 || a[cnt-1]!=ch)//stack empty or top != incoming
            a[cnt++] = ch;//push
        else
            --cnt;//pop
    }

    return cnt;//length of reduced string
}

```
 
</details>

## Highlights
### [Washing Plates](./HackerRank/washingPlates.cpp)
Text.
### [Candies](./HackerRank/candies.cpp)
Text.
### [Lisa's WorkBook](./HackerRank/lisasWorkbook.cpp)
Text.
### [2's Complement](./HackerRank/2sComplement.c)
Text.
