# RUN TEST
requirements:
-linux
-libgtest-dev
-bash execution access

Test only available in linux since google test does not support BSD. 
I don't wan't to include google test library to this repository,
so to run this test please install this libraries:

`sudo apt install libgtest-dev`

grant access needed to run test, to do that please run this command:

`chmod u+x test/exec`

then you can run the test by this command:

`test/exec`
