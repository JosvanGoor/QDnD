# QDnd

# todo list:
* Disconnecting

* Grid objects + saving / loading
* Colouring grid blocks
* Setting grid default color
* Coloured lines
* Ping tool (also for display)

* Status Icons (concentration etc..)
* AOE / Cone markers


# On the subject of rendering lines
Lets assume there are 1000 active lines consisting of 1001 points each.

Possible storage methods:
* Line Strip w uniform color:
  * 1 Line per buffer (means lots of buffers = slow)
  * 1001 * 4 * 2 bytes memory per line = 8008,
  * ~8MB vram usage for 1000 lines

* Line Strip w interleaved color:
  * 1 Line per buffer (means lots of buffers = slow)
  * 1001 * 4 * 5 bytes memory per line = 20 020,
  * ~20MB vram usage lines

* Line segments w uniform color:
    * 1 Line per buffer
    * 1001 * 4 * 4 bytes memory per line = 16016
    * ~16MB vram usage

* Line segments w interleaved color:
    * 1 buffer per user's lines
    * 1001 * 4 * 10 bytes memory per line = 32032
    * ~32MB vram usage