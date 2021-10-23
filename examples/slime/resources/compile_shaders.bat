echo off
for %%x in (particles.comp post.comp fullscreen.frag fullscreen.vert) do glslangValidator.exe -V shaders\%%x -o shaders\%%x.spv"
pause