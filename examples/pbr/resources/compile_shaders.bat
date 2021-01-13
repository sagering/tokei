echo off
for %%x in (pbr.vert pbr.frag) do glslangValidator.exe -V shaders\%%x -o shaders\%%x.spv"
pause