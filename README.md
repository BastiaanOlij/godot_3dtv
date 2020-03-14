# 3DTV Module

This GDNative module uses the AR/VR system to implement a stereo scopic camera setup that can be used for 3D TVs and 3D monitors. Currently it only supports side by side splitscreen.

Compiling this project 
----------------------
This module is dependent on godot-headers. 
Before compiling make sure it has been downloaded. If the godot_headers folder is empty the easiest way to do so is to run the following commands:
```
git submodule init
git submodule update --recursive
```

Now compile this module:
```
scons platform=windows target=release
```
(change platform to linux or osx if appropriate)

License
-------
Note that the source in this repository is licensed by the MIT license model. See LICENSE for details.

About this repository
---------------------
This repository was created by and is maintained by Bastiaan Olij a.k.a. Mux213

You can follow me on twitter for regular updates here:
https://twitter.com/mux213

Videos about my work with Godot including tutorials on working with VR in Godot can by found on my youtube page:
https://www.youtube.com/BastiaanOlij