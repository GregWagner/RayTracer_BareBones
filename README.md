# RayTracer_BareBones
This project is an OpenFrameworks port of the code given in chapter 3 of Ray Tracing from the Ground Up by Kevin Suffern
(http://www.raytracegroundup.com/) <br><br>

NOTE: This project assumes OpenFrameworks (https://openframeworks.cc/) is installed and that the repository is cloned
within the correct place within the OpenFramworks directory structure. In particular, enter the command:<br>
<code>git clone https://github.com/castellanos70/RayTracer_BareBones.git/code><bt>
In the directory location:<br>
<code>OpenFrameworks_v0.10.1\apps\myApps\</code><br><br>

Changes include:<br>
<ol>
<li>Replaced wxwidets with OpenFrameworks.</li>
<li>Many rendering apps use floats over doubles because the difference
is too small to see and floats are faster. The textbook code mixes
floats and doubles. This is bad as you get the worst of both worlds 
(slow and inaccurate), confusing to the developer, and warnnings from
the compiler. Excepting the RGB values, Joel changed all floats to 
double. In the case of the RGB values, explicit casts or math functions
for floats (absf, not abs, powf, not pow) were used.</li>

<li>In this Bere Bones ray traser, I commented out all references to 
Material as it is not used.</li>

<li>changed some of the too short variable names: ie, 's' to 'pixelSize'.</li>

<li>Added constructors with arguments to set starting values.</li>

<li>Removed some of the levels of abstraction. For example, replaced the 
SingleSphere object (which just creates a single Sphear object) with 
simply making a single Sphere in ofApp.cpp.</li>
</ol>
