Example of hiredis
====


Requirements
----
- [redis/hiredis](https://github.com/redis/hiredis)
- gcc

Build
----

```bash
gcc publish.c `pkg-config --cflags --libs hiredis`
```
