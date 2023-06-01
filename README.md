# Witch
Halloween '22 Game for DIY 8-bit microcomputer Durango-X (www.durangoretro.com).

![imagen](https://github.com/durangoretro/witch/assets/6067824/89ec5cbe-e98b-43bd-a9ff-eea9a23f3d1b)


Press Start button to start a new game. Press left or right to move and press A to fire.

If you are using Perdita start with ```-g``` to emulate gamepads.

## Compile

To compile this game you will need:

* [DurangoLib](https://github.com/durangoretro/durangolib)
* [Rescomp](https://github.com/durangoretro/rescomp)

and follow the instructions on MakeFile.

Also, you can use the [Durango Dev Kit Docker Image](https://hub.docker.com/r/zerasul/durangodevkit); using next instructions:

```bash
docker run --rm -v $PWD:/src/durango zerasul/durangodevkit:latest
``` 
