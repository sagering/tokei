echo off
for %%x in (default.vert default.frag suzanne.vert suzanne.frag) do glslangValidator.exe -V shaders\%%x -o shaders\%%x.spv"
pause