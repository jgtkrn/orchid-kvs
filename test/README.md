# RUN TEST
requirements:
-linux
-libgtest-dev
-bash execution access

test only available in linux since google test does not support BSD, and this program only support Linux and BSD. 
to run this test, some libraries needed, because i don't wan't to include google test library to this repository.
please install this library:

`sudo apt install libgtest-dev`

grant access needed to run test, to do that please run this command:

`chmod u+x test/exec`

then you can run the test by this command:

`test/exec`
