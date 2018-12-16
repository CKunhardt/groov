# Groov
Clinton Kunhardt & Ansel Colby  
A final project for COMP 465 - Interactive Computer Graphics

## What is Groov?
Groov is a toolkit for a graphical DJ.  
Events that have a DJ will often times accompany the music with a graphical representation of the music, 
but usually this is just a predetermined set of visuals that does not have the capability of responding 
fluidly to the music. Our goal for this project was to create a set of visuals that are almost completely
tweakable during the performance, allowing for a greater level of control and the ability to have a 
graphical representation of music that is responsive and feels alive.  
To accomplish this task we implemented JUCE.  
Our project as it is now is more of an MVP - a taste at what we had envisioned. Ideally there would be 
multiple scenes with different moods that the Graphics DJ could select from, as realistically there is
only so much that one person can change and modify during a live performance. Currently there is only one
demo scene of two orbitals of cubes surrounding one central cube.

## Overall Architecture
**GroovPlayer.cpp** contains the user interface aspects of the application. In it are all the buttons,
    sliders, and other parameterized controls that allow the Graphical DJ to interact with the scene.
    GroovPlayer also contains our reference to the GroovRenderer.  
**GroovRenderer.cpp** is an OpenGLRenderer and handles all of the graphical elements. All of the OpenGL 
    work is accomplished here, from setting up shaders to doing all the matrix math, to loading our meshes
    and actually rendering the scene. There's also several samplers that are set up to be used to generate a 
    simplex noise texture for our background cube.  
**GroovAudioProcessor.cpp** is an AudioProcessor that has access to all the audio information in the program.
    Being an audio plugin, it is the root of the plugin, and contains pointers to all other components.
    It's what directly interfaces with the plugin host.  
**GroovRenderWindow.cpp** is a class that allows the graphics window to pop up on a full-screen window,
    either on one screen for testing or a second monitor/projector for performance.  
**Mesh.h** was mostly repurposed from JUCE's OpenGLDemo.h, though we added more uniforms to pass through
    to the shader. It allows for the loading of .obj files into binary data.  
**Shaders.h** contains the shaders we implemented, one Blinn-Phong based vert/frag pair, and a shader for the
    environment cube that uses a simplex noise algorithm.  
**GLMHelpers.h** provides some helper functions for conversions between JUCE and GLM data types.  
**Utilities.h** contains several miscellaneous utility functions that are used by the various JUCE demos that we
    needed to port some functionality over from JUCE's OpenGLDemo.h.  
**WavefrontObjParser.h** is a parser provided by JUCE for the wavefront 3D OBJ file format.  

## How to build and run

The Assets.zip folder needs to be extracted and placed in a folder called Groov in your application data directory.
This is either %APPDATA% on Windows (usually C:\Users\you\AppData\Roaming) or ~/Library on OS X.

Once that is done, there are three external dependencies needed to build this program: JUCE, GLM, and the VST3 SDK.
Once JUCE is installed (or rather extracted), ideally into your root directory (C:\ or /), run the Projucer application,
and open Groov.jucer.

Download the latest source for GLM -- it is a header-only library, so just put it somewhere convenient. Do the same with
the VST3 SDK -- it can be obtained from Steinberg's website. In order to include these in the project, in Projucer,
click on the settings gear, and add the path to GLM and the VST3_SDK folders to the Header Search Paths field. Export to
your preferred IDE, and build as normal.

The end result is three files -- a VST, an AU, and an OS-specific executable file. Ideally, you would have a DAW such as
Ableton or, in our case, REAPER, to add the .vst3 file into your pre-existing VST folder, and then add the VST plugin to a
new project in your DAW. Once you route audio via sends into the plugin channel, you should be good to go.

There's another option if you don't have a DAW available -- that's the OS-specific executable, which is compiled under
the "Standalone Plugin" folder. Run the executable, and you can route audio in from an device input, but won't have access
to MIDI controls or BPM information from something like a DAW. Regardless, it's a good way to visualize the project without
needing extra software.

Should you want to visualize this with music playing and control BPM, our previous standalone application is located in [this repo](https://github.com/CKunhardt/music-materialized). Most of the commit history is in this repository, in case you're wondering.

## Credits

-   Much of the code was adapted from JUCE example code, Copyright (c) 2017 - ROLI Ltd, which requires the following notice:
 
 ```
    The code included in this file is provided under the terms of the ISC license
    http://www.isc.org/downloads/software-support-policy/isc-license. Permission
    To use, copy, modify, and/or distribute this software for any purpose with or
    without fee is hereby granted provided that the above copyright notice and
    this permission notice appear in all copies.

    THE SOFTWARE IS PROVIDED "AS IS" WITHOUT ANY WARRANTY, AND ALL WARRANTIES,
    WHETHER EXPRESSED OR IMPLIED, INCLUDING MERCHANTABILITY AND FITNESS FOR
    PURPOSE, ARE DISCLAIMED.
```

-   We were kickstarted on our project by [this tutorial](http://redwoodaudio.net/Tutorials/juce_for_vst_development__intro.html).

-   Simplex noise algorithm copyright Stefan Gustavson (stegu@itn.liu.se) 2004. Example file located [here](http://www.davidcornette.com/glsl/GLSL-noise.zip).

-   HSV conversion adapted from [this Stack Overflow answer](https://stackoverflow.com/questions/3018313/algorithm-to-convert-rgb-to-hsv-and-hsv-to-rgb-in-range-0-255-for-both).