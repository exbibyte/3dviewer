3dviewer
========
Project for the 3D computer graphics course, implemented with OpenGL glut library. Expected product is creation of a building model from Vancouver region and creative rendering of building, environment with camera movement.


Completed:

part 1: Model entity class for storing model data and transformation hierarchy

part 2: converter utility from .obj file from modelling software to custom format for the course

part 3: Implemented lighting, parametric curve, animation manager, clock, model pool, xml parser, scene graph rendering

Extra: 
Will implement extra rendering effects (shadow, animation) in near future

Progress screenshots link: https://www.behance.net/gallery/20140226-Sea-Island-Station/14890125

A sample video of animation scene created with this engine: http://youtu.be/KPcf5DIqKU0

Documentation #####################################################################################################
run doxygen doxyconfig

Running ###########################################################################################################
Required files: city file, animation file, motionpath file, lighting file, model files

1. extract model files from testcase/models/ to testcase/city1/ folder
2. create an outputimage/ folder to store captured images
3. run using: build/RecorderTest testcase/motionpaths/curvetest1.xml testcase/animation/animationparse.xml testcase/city1/funland.city testcase/lighting/lighting.xml norecord outputimage/



