echo off
for %%x in (basic.vert basic.frag) do glslangValidator.exe -V shaders\%%x -o shaders\%%x.spv"
pause