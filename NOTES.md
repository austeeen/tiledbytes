# Notes

Will be documenting some of my notes while developing this library here. My hope is to use the
scratch-work here as the seed for this library's future docs. In the meantime, perhaps this is
enough to get a few users started. Better than nothing right?...

## Wangsets

Tiled Map Editor supports edge, corner, and edge + corner wang sets and will encode all
possible orientations of every wang set into a comma separated char string
The 'wangid' entry this encoded char string.
Integer chars, at specific indexes, are used to denote the wang tile's identity.
         Edge Wang sets: "a,0,c,0,e,0,g,0"
       Corner Wang sets: "0,b,0,d,0,f,0,h"
Corner + Edge Wang sets: "a,b,c,d,e,f,g,h"
0 essentially means "ignored"
Entries take on an integer value: 0 < n <= (# wang colors)
