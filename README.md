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
Pretty neato and uses `nth_element`.
### [Candies](./HackerRank/candies.cpp)
Made an online algorithm that doesn't use extra space, unlike top solutions in search results.
### [Lisa's WorkBook](./HackerRank/lisasWorkbook.cpp)
Figured out a pattern to create a linear time solution I haven't seen elsewhere.
### [2's Complement](./HackerRank/2sComplement.c)
Was really satisfying to solve and I think I implemented it well.
