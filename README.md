# protopia4c
this is library for linux network programming.
it include util function, define, etc..

## how to create library object
```
cd /path/to/protopia
make # then created shared library object at ./bin
sudo cp ./bin/libprotopia /usr/lib
```


## gcc sample
gcc -o object srcname.c -L/path/to/protopia/bin/protopia.so -lprotopia

